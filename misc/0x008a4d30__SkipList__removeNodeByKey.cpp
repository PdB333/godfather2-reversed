// FUNC_NAME: SkipList::removeNodeByKey
// Function at 0x008a4d30: Removes a node with the given key from a skip list structure.
// This is a standard skip list deletion: search for the node, update forward pointers
// of predecessors at each level, then free the node and its forward pointer array.
// Structure fields:
//   SkipList +0x00: root node pointer (Node*)
//   SkipList +0x04: maximum level (int)
//   SkipList +0x10: node count (int)
//   SkipList +0x14: path buffer (int*), an array of predecessor node pointers (offset by 4? actually +4+level*4)
// Node fields:
//   Node +0x00: key (int)
//   Node +0x04: ? (unused, possibly value)
//   Node +0x08: forward array pointer (Node**)

class SkipList {
public:
    struct Node {
        int key;
        int /* likely unused */;
        Node** forward;   // array of forward pointers, one per level
    };

private:
    Node* root;          // +0x00
    int maxLevel;        // +0x04
    int count;           // +0x10
    Node** pathBuffer;   // +0x14 (array of Node* for predecessors)

    // Forward declarations for memory deallocation (assumed from callees)
    void deallocateForwardArray(Node** forward);
    void deallocateNode(Node* node);

public:
    // Removes a node with the exact key (if it exists). Key is passed as pointer.
    void __thiscall removeNodeByKey(int* keyPtr) {
        int key = *keyPtr;
        Node* current = root;               // piVar5
        int level = maxLevel;               // iVar3

        // Search: start from top level, move forward while key > current->key, then descend
        if (level >= 0) {
            do {
                Node* next = current->forward[level];   // piVar7 = piVar5->forward[level]
                if (next != nullptr) {
                    Node* node = next;                   // piVar6
                    // Follow forward pointers at this level while key > node->key
                    while (node != nullptr && key > node->key) {
                        current = node;                  // piVar5 = piVar6
                        node = node->forward[level];     // piVar7 = piVar6->forward[level]
                    }
                }
                // Record predecessor at this level (stored in pathBuffer starting at index 1? offset +4)
                // Actually pathBuffer[level+1] = current? The original code: *(int **)(param_1[5] + 4 + iVar3 * 4) = piVar5;
                // That suggests pathBuffer is an int* where the first int is maybe something else.
                // We'll assume pathBuffer[level+1] = current (since +4 accounts for first element)
                pathBuffer[level + 1] = current;
                level--;
            } while (level >= 0);
        }

        // Check if the node to delete actually exists: next node (from level 0 predecessor) matches the key
        Node* target = current->forward[0];   // this is piVar7 after loop? Actually after loop, piVar7 is the last "node" or next?
        if (target != nullptr && target->key == key) {
            // Update forward pointers for all levels where target is referenced
            unsigned int updateLevel = 0;
            do {
                Node* predecessor = pathBuffer[updateLevel + 1];   // +1 due to offset
                Node** predForward = predecessor->forward;
                // Update predecessor's forward pointer to target's forward at same level
                predForward[updateLevel] = target->forward[updateLevel];
                updateLevel++;
            } while (updateLevel <= (unsigned int)maxLevel);

            // Free the target's forward array and then the target itself
            deallocateForwardArray(target->forward);
            deallocateNode(target);
            count--;
        }
    }

private:
    // Stubs for memory deallocation (actual implementations at 0x009c8f10 and 0x009c8eb0)
    void deallocateForwardArray(Node** forward) {
        // Assuming this frees the array of forward pointers
    }
    void deallocateNode(Node* node) {
        // Frees the node structure
    }
};