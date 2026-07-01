// FUNC_NAME: NetConnection::processPendingQueue
// Address: 0x007e3560
// Role: Processes pending entries in a linked list stored at this+0xC0.
// Each node has: +0 pointer to an object with vtable at (object-0x48), +8 byte flag (0=unprocessed), +12 next pointer.
// Calls a virtual method at vtable+0x15c on the object if flag is 0 and object exists.
// Sets this+0x80 to 1 when any entry is processed.
// Removes the node from the list via removeNodeFromPendingList.
// Finally resets all node flags to 0.

#include <cstdint>

// Forward declarations
class NetObject;
struct PendingNode;

// Function to remove node from pending list – likely defined elsewhere
static void removeNodeFromPendingList(PendingNode* node, PendingNode** listHead);

// Node structure for pending list
struct PendingNode {
    NetObject* object;      // +0x00
    int32_t unknown;        // +0x04 (maybe timestamp or ID)
    uint8_t flag;           // +0x08
    uint8_t padding[3];     // +0x09
    PendingNode* next;      // +0x0C
};

// Class containing the pending list (likely a network connection)
class NetConnection {
    // ... other members ...
    PendingNode* pendingListHead;  // +0xC0
    uint8_t pendingProcessed;      // +0x80 (set when an entry is processed)

    void processPendingQueue(); // 0x007e3560
};

// Virtual function table offset constants
constexpr uint32_t kObjectVtableOffset = 0x48; // offset from object pointer to vtable
constexpr uint32_t kProcessVirtualCallOffset = 0x15c; // function at vtable+0x15c

void __fastcall NetConnection::processPendingQueue()
{
    PendingNode* currentNode;
    PendingNode* nextNode;

    // First pass: process all unprocessed entries
    currentNode = this->pendingListHead;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        if (currentNode->flag == 0) {
            if (currentNode->object != nullptr) {
                // Calculate vtable pointer: object - 0x48
                void** vtable = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(currentNode->object) - kObjectVtableOffset);
                // Call virtual function at offset 0x15c (likely send/process)
                // The vtable entry is a function pointer that takes NetObject* (this for the object)
                void (*processFunc)(NetObject* obj) = reinterpret_cast<void (*)(NetObject*)>(vtable[0x15c / 4]);
                processFunc(currentNode->object);
            }
            this->pendingProcessed = 1;
            removeNodeFromPendingList(currentNode, &this->pendingListHead);
        }
        currentNode = nextNode;
    }

    // Second pass: reset all flags in the (now possibly modified) list
    for (PendingNode* node = this->pendingListHead; node != nullptr; node = node->next) {
        node->flag = 0;
    }
}