// FUNC_NAME: EARSListNode::~EARSListNode
// EARSListNode is a base linked list node (prev/next pointers at +0x2c/+0x30)
// This destructor unlinks the node from any list, then frees the memory
// by returning it to a global freelist (identified by DAT_01206880+0x14)
// The global freelist uses a simple bump allocator pattern.

class EARSListNode {
public:
    // Vtable pointer at +0x00
    // Offset +0x04: unknown
    // Offset +0x10: pointer to previous list head or next free block? (param_1[4])
    // Offset +0x14: unknown (param_1[5])
    // Offset +0x2c: pointer to previous node in list (param_1[0xb])
    // Offset +0x30: pointer to next node in list (param_1[0xc])
    // ... other fields likely present.

    // This is the destructor (__thiscall)
    void __thiscall ~EARSListNode() {
        // First, set vtable to a "destroyed" stub (probably a debug sentinel)
        this->vtable = &PTR_FUN_00e37670;

        // Unlink this node from any doubly linked list it might be in.
        // The list is stored in global memory at DAT_012234c8 (likely a sentinel node or head pointer).
        if (this->next == nullptr) {
            // If this node is the tail, update the global tail pointer (+4)
            *(int*)(DAT_012234c8 + 4) = (int)this->prev;
        } else {
            // Else, update the next node's prev pointer
            this->next->prev = this->prev;
        }
        if (this->prev != nullptr) {
            // Update the previous node's next pointer
            this->prev->next = this->next;
        }
        this->prev = nullptr;
        this->next = nullptr;

        // Change vtable again (possibly to a different destructor phase)
        this->vtable = &PTR_FUN_00e37110;

        // If there is a block of memory assigned to this node (likely from a pool),
        // return it to the global freelist.
        int* block = this->block; // offset +0x10
        if (block != nullptr) {
            // Global freelist pointer at DAT_01206880+0x14
            // It is used as a simple bump pointer: the list head points to a sentinel,
            // then the next 4 bytes are used to store the freed block.
            int** freelist = (int**)(DAT_01206880 + 0x14);
            // Insert this block into the freelist (common EA pattern)
            *freelist = (int*)&PTR_LAB_01123be8; // sentinel vtable for free block?
            *freelist = *freelist + 4; // advance past sentinel
            *freelist = block; // store block pointer
            *freelist = *freelist + 4; // advance for next allocation
            this->block = nullptr;
            this->blockSize = 0;
        }
    }

private:
    void* vtable; // +0x00
    // unknown fields
    int* block;   // +0x10 (pointer to allocated memory block)
    int blockSize;// +0x14
    EARSListNode* prev; // +0x2c
    EARSListNode* next; // +0x30
    // ... other fields
};

// Global variables used
extern int DAT_012234c8; // base of a list head/tail structure (offset +0? +4 used)
extern int DAT_01206880; // pointer to some global memory manager state
extern void* PTR_FUN_00e37670; // vtable stub for destruction in progress
extern void* PTR_FUN_00e37110; // vtable stub for final destruction
extern void* PTR_LAB_01123be8; // sentinel for free list blocks

// Function at address 0x004f3850 is the destructor above.
// Called from 0x004f3390 (likely a derived class destructor).