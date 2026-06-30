// FUNC_NAME: Manager::removeByIndex (or ObjectManager::removeEntry)

struct Node {
    int* prev;   // +0x00? Not used directly here
    Node* next;  // +0x04
};

struct Slot {
    Node* node;  // +0x00 pointer to node
    Node** link; // +0x04 used as tail/next? Actually used as slot->link = node->next
};

class Manager {
    Slot* slots;   // [this+0x00]
    int   count;   // [this+0x04] current number of active slots
public:
    // Removes the node at index `idx` from the container.
    // Uses swap-with-last technique to keep the array contiguous.
    void removeByIndex(int idx) {
        if (idx != count - 1) {
            Slot* pLast = &slots[count - 1];
            Slot* pIdx  = &slots[idx];

            if (pIdx->node != pLast->node) {
                // Detach the node currently at idx (if any) from its list
                if (pIdx->node != nullptr) {
                    detachNode(pIdx);
                }
                // Move the last slot's node into idx slot
                pIdx->node = pLast->node;
                if (pIdx->node != nullptr) {
                    // Update the linked list to point back to the slot
                    pIdx->link = pLast->node->next;
                    pLast->node->next = pIdx;
                }
            }
        }
        count--;
        // After decrement, the slot at the old last position is now "outside"
        // the active range. If it still holds a node, detach it.
        if (slots[count].node != nullptr) {
            detachNode(&slots[count]);   // likely missing argument in Ghidra
        }
    }
};

// Standalone function to detach a node from the list it belongs to.
// Takes a pointer to the Slot that holds the node.
void detachNode(Slot* slot); // defined elsewhere