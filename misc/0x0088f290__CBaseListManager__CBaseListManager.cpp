// FUNC_NAME: CBaseListManager::CBaseListManager
// Constructor for a base list manager. Initializes a doubly linked list (circular) and sets allocation parameters.
// Address: 0x0088f290

#include <cstdint>

class CBaseListManager : public CBasePool { // CBasePool is the base constructor called at 0x46c590
public:
    CBaseListManager(uint poolId);
    // ... other members

private:
    // Embedded list node structure (offsets from this)  
    struct ListNode {
        ListNode* next;      // +0x64 (4 bytes)
        ListNode* prev;      // +0x68 (4 bytes)
        void* data;          // +0x6C (4 bytes)
        uint8_t flags;       // +0x70 (1 byte)
        int someInt;         // +0x74 (4 bytes)
    } listNode;

    // Configuration fields set by constructor
    int maxItems;            // +0x50 (0x32 = 50)
    int itemSize;            // +0x54 (2)
    int allocationSize;      // +0x58 (0x40 = 64)
    int nullSentinel;        // +0x5C (0xFFFFFFFF = -1)
};

CBaseListManager::CBaseListManager(uint poolId)
    : CBasePool(poolId) // parent constructor call at 0x46c590
{
    // Set vtable pointers (multiple inheritance: 3 vtables)
    this->vtable = &CBaseListManager_vtable;               // +0x00
    *(void**)((uint8*)this + 0x3C) = &CBaseListManager_vtable2; // +0x3C
    *(void**)((uint8*)this + 0x48) = &CBaseListManager_vtable3; // +0x48

    // Initialize configuration
    this->maxItems = 50;        // +0x50
    this->itemSize = 2;         // +0x54
    this->allocationSize = 64;  // +0x58
    this->nullSentinel = -1;    // +0x5C

    // Clear the embedded list node (starting at +0x64)
    // First clear the next/prev pointers (8 bytes)
    *reinterpret_cast<uint64*>(&this->listNode.next) = 0;
    // Then clear the data and the following 8 bytes (covers data and possibly padding)
    *reinterpret_cast<uint64*>(&this->listNode.data) = 0;

    // Make the list circular (next and prev point to itself)
    this->listNode.next = &this->listNode;  // +0x64 = this
    this->listNode.prev = &this->listNode;  // +0x68 = this

    // Set remaining fields to zero (already zero after clear, but explicit)
    this->listNode.data = nullptr;   // +0x6C
    this->listNode.flags = 0;        // +0x70
    this->listNode.someInt = 0;      // +0x74

    // Final initialization call
    this->initList(); // FUN_0088dd00
}