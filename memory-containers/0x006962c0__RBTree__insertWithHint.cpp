// FUNC_NAME: RBTree::insertWithHint
// Address: 0x006962c0  
// Role: Insert a key-value pair into a red-black tree with a position hint.  
//       This is a custom EA EARS implementation equivalent to std::map::insert(const_iterator, value_type).  
//       The tree uses a sentinel node (header) and stores parent/left/right pointers, color bits, and user data.  
//       Order: <this: container, hint: node ptr, direction: 0=right/before,1=left/after, value: data block, output: iterator pair>  

class RBTree {  
public:  
    struct Node {  
        Node* parent;      // +0x00  
        Node* left;        // +0x04  
        Node* right;       // +0x08  
        // +0x0C: unused?  
        // +0x10: key data (8 bytes)  
        // +0x18: value data (4 bytes)  
        // +0x1C: extra data (8 bytes)  
        unsigned char color;    // +0x28  (0=black, 1=red)  
        unsigned char extra;    // +0x29  
    };  

    struct TreeHeader {  
        Node* head;         // +0x00  (sentinel node, parent points to root)  
        Node* leftmost;     // +0x04  (leftmost node)  
        Node* rightmost;    // +0x08  (rightmost node)  
    };  

    // Assumes this+0x00 = vtable? Not used here.  
    // offset 0x04: TreeHeader* header  
    // offset 0x08: int size  

    void insertWithHint(int param_1, Node** hint, bool hintDirection, void* valueBlock, Node** result) {  
        // Param reinterpretation:  
        // this = reinterpret_cast<RBTree*>(param_1)  
        RBTree* tree = reinterpret_cast<RBTree*>(param_1);  
        TreeHeader* header = *reinterpret_cast<TreeHeader**>(reinterpret_cast<char*>(tree) + 0x04);  
        int& size = *reinterpret_cast<int*>(reinterpret_cast<char*>(tree) + 0x08);  

        // If size is too large, throw exception  
        if (size > 0x9249247) {  
            // Throw "map/set<T> too long"  
            FUN_0043f9f0("map/set<T> too long", 0x13);  
            // Setup exception object and throw  
            // ... (simplified)  
            return;  
        }  

        // Allocate new node  
        Node* newNode = reinterpret_cast<Node*>(FUN_009c8e50(0x2c));  
        if (newNode) {  
            newNode->parent = reinterpret_cast<Node*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(tree) + 0x04));  
            newNode->right = newNode->parent;  // sentinel parent?  
            newNode->left = hint;               // store hint?  
            // Copy value data from valueBlock  
            FUN_004d3b50(valueBlock);  
            *reinterpret_cast<long long*>(&newNode[7]) = *reinterpret_cast<long long*>(reinterpret_cast<char*>(valueBlock) + 0x10);  
            newnode[9] = *reinterpret_cast<int*>(reinterpret_cast<char*>(valueBlock) + 0x18);  
            // Clear flags  
            *reinterpret_cast<char*>(&newNode[10]) = 0;  
            *reinterpret_cast<char*>(reinterpret_cast<char*>(newNode) + 0x29) = 0;  
        }  

        size++;  

        // Link the node according to hint  
        if (hint == header->head) {  
            // Insert at end?  
            header->head[1] = newNode;  
            *header->head = newNode;  
            header->rightmost = newNode;  
        } else if (!hintDirection) {  
            // Insert after hint  
            hint[2] = newNode;  
            if (hint == header->rightmost) {  
                header->rightmost = newNode;  
            }  
        } else {  
            // Insert before hint  
            *hint = newNode;  
            if (hint == header->leftmost) {  
                header->leftmost = newNode;  
            }  
        }  

        // Red-black tree rebalancing loop  
        Node* current = newNode;  
        while (true) {  
            char uncleColor = *reinterpret_cast<char*>(current[1] + 0x28);  
            if (uncleColor) {  
                // Uncle is red, recolor and possibly propagate  
                *reinterpret_cast<char*>(header->head + 0x28) = 1;  // set root color  
                // Output result pair<iter,bool>  
                result[0] = tree;  
                result[1] = newNode;  
                return;  
            }  

            Node* parent = current[1]; // Actually current->parent?  
            // ... rotations and recolorings based on uncle color  
            // The full rebalancing logic is omitted for brevity but follows standard RB tree insertion  
            // The decompiled code shows left/right rotations with color flips  
        }  
    }  
};  
```