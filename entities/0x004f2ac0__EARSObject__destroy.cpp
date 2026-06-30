// FUNC_NAME: EARSObject::destroy
// 0x004f2ac0: Destructor/cleanup for EARSObject-derived classes, returns memory to a fixed-size block pool
// Uses a custom allocator stack at g_allocator (+0x14) for returning freed blocks

extern uint8_t g_allocator;            // 0x01206880: Root of allocator structure
extern void* g_vtableEARSObjectBase;   // 0x00e37110: Base class vtable
extern void* g_vtableFreeBlock;        // 0x01123be8: Vtable for freed memory blocks (sentinel)

void __fastcall FUN_009c8eb0(EARSObject* obj);  // operator delete or free helper

class EARSObject {
public:
    void* vtable;      // +0x00
    int field_0x04;    // +0x04
    int field_0x08;    // +0x08
    int field_0x0C;    // +0x0C
    void* freeNode;    // +0x10: Pointer to a memory block (internal node) that can be returned to pool
    int field_0x14;    // +0x14

    // flag: 0 = just release internal node, 1 = release node and delete this object
    EARSObject* destroy(byte flag);
};

EARSObject* EARSObject::destroy(byte flag) {
    // Set vtable to base class to prevent virtual calls during destruction
    this->vtable = &g_vtableEARSObjectBase;

    void* node = this->freeNode;          // +0x10
    if (node != nullptr) {
        // Get pointer to the free block stack top from the global allocator
        int** stackTopPtr = (int**)((uint8_t*)&g_allocator + 0x14);
        int* stackTop = *stackTopPtr;

        // Push two values onto the stack (8-byte record):
        // first: pointer to the free block vtable (sentinel), second: the node address
        *stackTop = (int)&g_vtableFreeBlock;
        stackTop++;
        *stackTop = (int)node;
        stackTop++;

        // Update stack top
        *stackTopPtr = stackTop;

        // Clear the freed node reference
        this->freeNode = nullptr;
        this->field_0x14 = 0;
    }

    // If the low bit of flag is set, deallocate the object memory itself
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}