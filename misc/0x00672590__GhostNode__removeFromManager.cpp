// FUNC_NAME: GhostNode::removeFromManager
// Ghidra address: 0x00672590
// Role: Removes this ghost node from the ghost manager, freeing both the node pointed to by `prev` (or next) and itself.
// Uses a memory allocation header at (user pointer - 16 bytes) containing an index into a slot array.

#include <cstdint>

// Global memory deallocator (assumed from DAT_01206694)
extern void gMemoryFree(void* ptr);  // deallocate a memory block

// Forward declarations
struct GhostManager;

// +0x00: pointer to previous node (or next, used as raw int* in arithmetic)
// +0x04: unused in this function
// +0x08: unused
// +0x0C: unused
// +0x10: byte flag – 1 = active node, 0 = inactive/special handling
// +0x14: pointer to the owning GhostManager
struct GhostNode {
    GhostNode* prev;          // offset 0x00
    int field_0x04;           // offset 0x04
    int field_0x08;           // offset 0x08
    int field_0x0C;           // offset 0x0C
    uint8_t flag;             // offset 0x10 (byte)
    GhostManager* manager;    // offset 0x14
};

// +0x00: unknown
// +0x04: count of active nodes
// +0x0C: pointer to an array of ints (slots) indexed by node header index
// +0x10: unknown
// ...
// +0x3C: head node pointer
// +0x74: flag (set to 1 when removing head)
struct GhostManager {
    int field_0x00;            // offset 0x00
    int count;                 // offset 0x04
    int* slotArray;            // offset 0x0C – array of ints (slots)
    int field_0x10;            // offset 0x10
    // ... gaps ...
    GhostNode* head;           // offset 0x3C
    // ... gaps ...
    int headRemovedFlag;       // offset 0x74
};

// Memory header layout (16 bytes before user data):
// [-16]: magic or previous free pointer
// [-12]: unknown
// [ -8]: index into slotArray
// [ -4]: unknown
// [  0]: start of GhostNode data

// __thiscall: this in ECX, potential output pointer in EAX
void __thiscall GhostNode::removeFromManager(void* outputInEAX)
{
    if (this == nullptr)
        return;

    // If output pointer was provided, zero it (common pattern for error indicators)
    if (outputInEAX != nullptr)
        *static_cast<int*>(outputInEAX) = 0;

    GhostManager* mgr = this->manager;

    // If flag is not 1 (inactive node), handle special case
    if (this->flag != 1)
    {
        // If this node is not the head of the manager's list, call another function
        if (this != mgr->head)
        {
            // FUN_00673160 – likely a different removal path (e.g. for non-activated nodes)
            // We'll call it as a stub; actual implementation unknown.
            // helperFunctionForInactiveNode(this);
            return;
        }
        // This node is the head – just set a flag in the manager
        mgr->headRemovedFlag = 1;
        return;
    }

    // Active node: flag == 1
    // Remove the node pointed to by `prev` (deferenced as a raw int* for header access)
    GhostNode* otherNode = this->prev;  // this->prev is a node pointer
    int* otherData = reinterpret_cast<int*>(otherNode);

    if (otherData != nullptr)
    {
        // Read the index from the other node's memory header (at offset -8)
        int otherIndex = otherData[-2];

        // Clear the corresponding slot in the manager's slot array
        mgr->slotArray[otherIndex] = 0;

        // Decrement the count in the manager
        mgr->count--;

        // Free the other node's memory block (header starts 16 bytes before data)
        gMemoryFree(otherData - 4);  // otherData - 4 ints = -16 bytes
    }

    // Now remove the current node itself
    // The current node's index is stored at offset -8 from its data pointer
    int* thisData = reinterpret_cast<int*>(this);
    int thisIndex = thisData[-2];

    // Clear slot
    mgr->slotArray[thisIndex] = 0;

    // Decrement count again (since both nodes were removed)
    mgr->count--;

    // Free current node's memory block
    gMemoryFree(thisData - 4);  // thisData - 4 ints = -16 bytes
}