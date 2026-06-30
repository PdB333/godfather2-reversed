// FUNC_NAME: NodeManager::replaceNode
// Address: 0x0056f620
// This function replaces the current node pointer stored at this+0x34 with a new node,
// updating reference counts and removing the old node from a global linked list if its
// reference count drops to zero and its flag byte is clear.

struct ListNode {
    ListNode* prev;   // +0x00
    ListNode* next;   // +0x04
    char flag;        // +0x08  (boolean, maybe marks node as non-removable)
    char refCount;    // +0x09
};

struct ListHead {
    // +0x00: unused here? Possibly head pointer
    ListNode* tail;   // +0x04
    ListNode* unknown1; // +0x08 (used as both pointer and value copy)
    ListNode* unknown2; // +0x0c (used only when tail becomes null)
};

// Global list head structure (address 0x01205564)
static ListHead* gListHead = reinterpret_cast<ListHead*>(0x01205564);

// __fastcall: ECX = this, EDX = newNode (pointer to a ListNode)
void __fastcall NodeManager::replaceNode(void* thisPtr, ListNode* newNode)
{
    if (newNode != nullptr) {
        newNode->refCount += 1;  // increment ref count of new node
    }

    ListNode* oldNode = *reinterpret_cast<ListNode**>(static_cast<char*>(thisPtr) + 0x34);

    if (oldNode != nullptr) {
        oldNode->refCount -= 1;  // decrement ref count of old node

        // Remove old node if its flag is zero and ref count becomes zero
        if (oldNode->flag == 0 && oldNode->refCount == 0) {
            ListNode* prevNode = oldNode->prev;   // previous node (or nullptr)
            ListNode* nextNode = oldNode->next;   // next node (or nullptr)

            if (prevNode != nullptr) {
                prevNode->next = nextNode;        // unlink from left
            }

            if (nextNode != nullptr) {
                nextNode->prev = prevNode;        // unlink from right
                // Early return after unlinking (and after updating this->currentNode below)
                // Actually the decompiler returns here after updating this->currentNode.
                // We'll fall through to the final assignment.
            }
            else {
                // oldNode was the tail of the list; update global list head
                gListHead->unknown1 = reinterpret_cast<ListNode*>(gListHead->tail);
                gListHead->tail = prevNode;
                if (prevNode == nullptr) {
                    gListHead->unknown1 = gListHead->unknown2;
                }
            }
        }
    }

    // Always update this->currentNode to the new node
    *reinterpret_cast<ListNode**>(static_cast<char*>(thisPtr) + 0x34) = newNode;
}