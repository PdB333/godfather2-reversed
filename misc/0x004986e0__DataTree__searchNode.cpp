// FUNC_NAME: DataTree::searchNode
// Address: 0x004986e0
// Searches for a node with a given key in a multi-level ordered tree structure.
// The tree uses per-level linked lists indexed by a digit/level (0..maxLevel-1).
// Node layout:
//   +0x00: key (uint)
//   +0x0c: childTable (uint**), an array of pointers to child nodes (one per level); each level is a sorted linked list.
// Root structure layout:
//   +0x00: rootNode (DataTree::Node*)
//   +0x04: maxLevel (int) - number of levels/digits in the tree

#include <cstdint>

class DataTree {
public:
    struct Node {
        uint32_t key;                   // +0x00
        uint32_t* childTable;           // +0x0c: pointer to array of child node pointers
    };

    // __thiscall: this points to the tree root structure
    Node* __thiscall searchNode(uint32_t* keyPtr) {
        uint32_t searchKey = *keyPtr;
        Node* current = reinterpret_cast<Node*>(this->rootNode);   // *param_1
        int level = this->maxLevel - 1;                             // param_1[1], loop counts down from maxLevel-1

        for (; level >= 0; level--) {
            // Traverse the linked list at childTable[level] of current node
            Node* scan = (current->childTable) ? reinterpret_cast<Node**>(current->childTable)[level] : nullptr;
            if (scan != nullptr) {
                do {
                    Node* prev = scan;
                    if (searchKey <= scan->key) {
                        break; // stop when key <= current node's key
                    }
                    scan = (scan->childTable) ? reinterpret_cast<Node**>(scan->childTable)[level] : nullptr;
                    current = prev; // update current to the node we just inspected
                } while (scan != nullptr);
            }

            // After traversing, check the first child (childTable[0]) of the current node
            Node* firstChild = (current->childTable) ? reinterpret_cast<Node**>(current->childTable)[0] : nullptr;
            if (firstChild == nullptr) {
                break; // no further nodes
            }
            if (firstChild->key == searchKey) {
                return firstChild;
            }
        }

        return nullptr; // not found
    }

    // Root structure fields (offsets relative to this):
    Node* rootNode;      // +0x00
    int maxLevel;        // +0x04
};