// FUNC_NAME: Map::insert
// Address: 0x0088f510
// Role: Binary search tree insert with duplicate detection and iterator output.
// This function combines lower_bound search and conditional insertion.
// It is used by the EA EARS engine's custom map/set implementation (likely a red-black tree).
// The tree nodes are structured as:
//   Node* right;   // +0
//   Node* left;    // +4
//   Node* parent;  // +8
//   bool isRed;    // +12
//   uint32_t key;  // +16
// The map object (this) embeds a sentinel header node at offset 0x4, with:
//   header.right  -> largest element (offset +0x4)
//   header.left   -> smallest element (offset +0x8)
//   header.parent -> root node (offset +0xC)
//   header.key    -> unused (offset +0x14)

typedef unsigned int uint32_t;

class Map {
public:
    // Embedded sentinel node (size 20 bytes)
    struct Node {
        Node* right;   // +0
        Node* left;    // +4
        Node* parent;  // +8
        bool isRed;    // +12
        uint32_t key;  // +16
    };

    // This class is just a structural wrapper for the decompilation.
    // Actual fields are accessed via offsets.
    char data[0x18]; // placeholder; real size unknown
};

// External functions (not provided in decompilation)
extern Node* nodePredecessor(Node* node);   // FUN_00ab3c90 - returns predecessor of given node
extern Node* insertNode( Node** parent, Node* position, Node* newKey, int unknown ); // FUN_0088f3a0

// __thiscall
void* Map::insert( Pair<Iterator, bool>* result, const uint32_t* key ) {
    Node* head = reinterpret_cast<Node*>(this + 0x4);
    Node* root = reinterpret_cast<Node*>(this->data[0xC]); // actually *(Node**)(this + 0xC)
    Node* current = head;   // start at sentinel

    bool wentLeft = true;
    if (root != nullptr) {
        Node* child = root;
        do {
            current = child;
            wentLeft = (*key < current->key);       // compare key with node's key
            if (wentLeft) {
                child = current->left;              // +4
            } else {
                child = current->right;             // +0
            }
        } while (child != nullptr);
    }

    Node* target = current;
    if (wentLeft) {
        // We went left from `current`. If we are at the smallest node (header.left),
        // then there is no predecessor; skip.
        if (current == head->left) { // head->left is at this + 0x8
            goto LAB_0088f565;
        }
        target = nodePredecessor(current);
    }

    // Check if key already exists: if key <= target->key, it's already present
    if (*key <= target->key) {
        result->first = target;
        result->second = false; // insertion not performed
        return result;
    }

LAB_0088f565:
    // Insert new node
    Node* newNode = insertNode( &key, current, const_cast<uint32_t*>(key), 0 );
    result->first = newNode;
    result->second = true; // insertion performed
    return result;
}