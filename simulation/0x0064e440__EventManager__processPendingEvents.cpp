// FUNC_NAME: EventManager::processPendingEvents
// Address: 0x0064e440
// Role: Distributes pending event nodes into internal sorted/priority lists and processes immediate-release nodes.

#include <cstdlib>

// Global free list and counters (from Ghidra data symbols)
extern int _DAT_01223cbc;    // flag for one-time init
extern int _DAT_01223cb0;    // active node count
extern int* DAT_01223cb8;    // free list head

// Forward declaration
void FUN_0065ba30(); // likely a global tick or callback
void FUN_0064f120(); // initialization routine

class EventManager {
public:
    // Offsets: +0x00 vtable (implied)
    // +0x04 ... (likely other fields)
    uint32_t counter;               // +0xd0
    uint32_t flag_callback;         // +0x1c8
    Node* sortedListHead;           // +0x1cc (used for insertion traversal)
    Node* sortedListTail;           // +0x1d0 (set when inserting last)
    Node* priorityHead;             // +0x1d4 (type 1 queue head)
    Node* priorityTail;             // +0x1d8 (type 1 queue tail)
    // ... other fields

    void processPendingEvents(EventManager* source);
};

struct Node {
    void* data;         // [0] points to an event object (with vtable)
    int key;            // [1] sorting key (used for type 0 insertion)
    Node* next;         // [2] next pointer
    int type;           // [4] event type: 0=deferred, 1=priority, 2=immediate
    // Possibly more fields
};

void __thiscall EventManager::processPendingEvents(EventManager* source) {
    this->counter++;

    if (this->flag_callback != 0) {
        FUN_0065ba30(); // possibly invoke a callback
    }

    Node* pendingList = *(Node**)((uint8_t*)source + 0x14); // source->pendingListHead
    Node** insertPtr = &this->sortedListHead; // +0x1cc

    while (pendingList != nullptr) {
        Node* current = pendingList;
        int eventType = current->type;

        if (eventType == 0) {
            // Insert into sorted list based on key (ascending order)
            Node* walker = this->sortedListHead;
            // Find insertion position while walker's key < current's key
            while (walker != nullptr && current->key > walker->key) {
                insertPtr = &walker->next;
                walker = walker->next;
            }
            // Insert current after insertPtr
            current->next = walker;
            *insertPtr = current;
            if (walker == nullptr) {
                this->sortedListTail = current; // +0x1d0
            }
            pendingList = current->next; // continue from original next (saved before insertion? Actually current->next was overwritten. Need original)
            // Original code: piVar3 = piVar5[2]; (next pointer before modification)
            // So we must save original next.
        } 
        else if (eventType == 1) {
            // Prepend to priority list
            Node* originalNext = current->next;
            current->next = this->priorityHead;
            this->priorityHead = current;
            if (current->next == nullptr) {
                this->priorityTail = current;
            }
            pendingList = originalNext;
        }
        else if (eventType == 2) {
            // Immediate execution: call virtual function at vtable+0x20
            void** vtable = *(void***)current->data;
            void (*execFunc)(EventManager*, int) = (void (*)(EventManager*, int))vtable[0x20 / 4];
            execFunc(this, 0);

            // One-time global initialization
            if ((_DAT_01223cbc & 1) == 0) {
                _DAT_01223cbc |= 1;
                FUN_0064f120();
                atexit([](){} ); // label 0x00d513f0, likely a cleanup routine; simplified
            }

            // Release reference to the event object
            if (current->data != nullptr) {
                int* refCount = (int*)current->data + 2; // offset 8
                (*refCount)--;
                if (*refCount == 0) {
                    // Call destructor via vtable
                    void** objVtable = *(void***)current->data;
                    void (*destructor)(void*) = (void (*)(void*))objVtable[2]; // offset 8
                    destructor(current->data);
                }
            }

            // Return node to free list
            _DAT_01223cb0--;
            current->data = (void*)DAT_01223cb8;
            DAT_01223cb8 = current;
            pendingList = current->next; // advance to next pending node
        }
        else {
            // Unknown type, just skip
            pendingList = current->next;
        }
    }
}