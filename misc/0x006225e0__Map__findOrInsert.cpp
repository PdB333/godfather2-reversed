// FUNC_NAME: Map::findOrInsert
// Address: 0x006225e0
// Role: Find or insert a node in a red-black tree map. Returns pointer to node via outNode.

#include <cstdint>

// Forward declarations of helper functions
void Map_insert(Map* map, void* outNode, int flag, uint32_t* key); // FUN_00623310
void Map_assertValid(Map* map, int validationThis); // FUN_00b97aea
void Map_rebalanceLeft(Map* map); // FUN_00624370
void Map_rebalanceRight(Map* map); // FUN_006243f0
bool Map_isRed(RBNode* node); // FUN_00622a60
void* Map_lookup(Map* map, int* local_c, uint32_t* key); // FUN_00623130

// Node structure offsets (in bytes)
// +0x00: left child (RBNode*)
// +0x04: right child (RBNode*)
// +0x08: value pointer (void*) - points to a structure with a color flag at +0x15
// +0x0C: key (uint32_t)
// +0x10: parent (RBNode*)
// +0x14: color (char) - 0 = red, 1 = black (if stored directly, but here color is in value)
struct RBNode {
    RBNode* left;      // +0x00
    RBNode* right;     // +0x04
    void* value;       // +0x08
    uint32_t key;      // +0x0C
    RBNode* parent;    // +0x10
    char color;        // +0x14 (if stored here, but code uses value+0x15)
};

// Map class layout
// +0x1C: pointer to root node pointer (RBNode**)
// +0x20: initialized flag (int)
class Map {
public:
    RBNode** m_ppRoot; // +0x1C
    int m_bInitialized; // +0x20

    // Main function
    void* findOrInsert(void* outNode, uint32_t* key, int validationThis, RBNode* node) {
        RBNode* root;
        int local_c;
        bool bVar3;

        if (m_bInitialized == 0) {
            Map_insert(this, outNode, 1, key);
            return outNode;
        }

        root = *m_ppRoot; // dereference pointer to root

        if (validationThis == 0 || validationThis != (int)this) {
            Map_assertValid(this, validationThis);
        }

        if (node == root) {
            if (*key < node->key) {
                Map_insert(this, outNode, 1, key);
                return outNode;
            }
        } else {
            root = *m_ppRoot; // re-read root? Possibly a bug or intentional
            if (validationThis == 0 || validationThis != (int)this) {
                Map_assertValid(this, validationThis);
            }
            if (node == root) {
                // Compare key with root's left child's key? Actually: *(uint*)(*(int*)(*(int*)(param_1+0x1c)+8)+0xc)
                // That is: root->left->key
                if (root->left->key < *key) {
                    Map_insert(this, outNode, 0, key);
                    return outNode;
                }
            } else {
                bVar3 = node->key < *key;
                if (*key < node->key) {
                    Map_rebalanceLeft(this);
                    if (node->key < *key) {
                        // Check color flag in value structure at offset +0x15
                        char* valuePtr = (char*)node->value;
                        if (valuePtr[0x15] == '\0') {
                            Map_insert(this, outNode, 1, key);
                            return outNode;
                        }
                        Map_insert(this, outNode, 0, key);
                        return outNode;
                    }
                    bVar3 = node->key < *key;
                }
                if (bVar3) {
                    root = *m_ppRoot;
                    local_c = (int)this;
                    Map_rebalanceRight(this);
                    bool isRed = Map_isRed(node);
                    if (isRed || *key < node->key) {
                        char* valuePtr = (char*)node->value;
                        if (valuePtr[0x15] == '\0') {
                            Map_insert(this, outNode, 1, key);
                            return outNode;
                        }
                        Map_insert(this, outNode, 0, key);
                        return outNode;
                    }
                }
            }
        }

        // Perform lookup and copy result
        void* result = Map_lookup(this, &local_c, key);
        uint32_t* out = (uint32_t*)outNode;
        uint32_t* res = (uint32_t*)result;
        out[0] = res[0];
        out[1] = res[1];
        return outNode;
    }
};