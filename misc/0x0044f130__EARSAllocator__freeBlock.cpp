// FUNC_NAME: EARSAllocator::freeBlock
// Address: 0x0044f130
// Deallocates a memory block. If destroyFlag is non-zero, only calls the virtual destructor.
// The block header contains magic numbers and a pointer to the owning allocator context.

#define MAGIC1 0xBBADBEBA
#define MAGIC2 0xBEEFBEEF
#define MAGIC3 0xEAC15A55
#define MAGIC4 0x91100911

// External functions used for error reporting and debugging
extern void reportCorruptionCallback(int param1); // FUN_0044fd00
extern void reportBlockCorruption(uint magic1, uint magic2, uint magic3, uint magic4); // FUN_00450840

// Global memory manager structure (allocator context)
extern AllocatorGlobals* gAllocatorGlobals; // DAT_01206880
extern void* gAllocatorLogCallback; // DAT_012233a4

// Thread-local storage pointer for the per-thread allocation list
// FS:[0x2c] is used to get a pointer to a linked list header (e.g., AllocLinkedList)
#define THREAD_ALLOC_LIST (*((AllocLinkedList**)(__readfsdword(0x2c))))

// Constants for vtable/class descriptors used in debug tracking
extern const void* CLASS_DESC1; // PTR_LAB_0110b878
extern const void* CLASS_DESC2; // PTR_LAB_0110b8a0
extern const void* CLASS_DESC3; // PTR_LAB_0110b8b4

// Allocation stack: a simple linked list recorded for debugging
struct AllocStackEntry {
    AllocStackEntry* prev;
    const void* classDesc;
    void* pointer;
};

int __fastcall EARSAllocator::freeBlock(void* ptr, char destroyFlag)
{
    // When destroyFlag == 0, full deallocation including header validation and memory tracking.
    if (destroyFlag == 0) {
        // Null pointer returns 0 (failure)
        if (ptr == 0) {
            return 0;
        }

        // Check if a special field at offset 0x20 (ptr + 0x20) is non-zero.
        // Possibly a reference to a destructor or a cleanup function that must be called.
        if (*(int*)((char*)ptr + 0x20) != 0) {
            reportCorruptionCallback(gAllocatorLogCallback);
        }

        // Thread-local allocation list pointer
        AllocLinkedList* threadList = THREAD_ALLOC_LIST;
        
        // Global allocator's stack pointer (debug stack)
        int* stackPtr = gAllocatorGlobals->debugStackPtr; // gAllocatorGlobals + 0x14
        // Push a debug entry: set the current stack entry's class descriptor
        *(const void**)stackPtr = CLASS_DESC1;
        stackPtr = (int*)(((int)stackPtr + 4) & ~3); // align to 4 bytes
        *stackPtr = (int)ptr;
        stackPtr++;
        gAllocatorGlobals->debugStackPtr = (int)stackPtr; // update stack pointer

        // Retrieve something from the thread_local list (likely a base address)
        int baseAddr = *(int*)(*(int*)threadList + 8); // (threadList->firstNode + 8)
        
        // Access a flag at: baseAddr + 0x7c + ptr[6] (offset 0x18 from ptr)
        uint* flagPtr = (uint*)(baseAddr + 0x7c + *((int*)ptr + 6));
        if ((*(byte*)flagPtr & 0x20) != 0) {
            *flagPtr &= ~0x20; // Clear the flag

            // Push another debug entry for the cleared flag
            stackPtr = gAllocatorGlobals->debugStackPtr;
            *(const void**)stackPtr = CLASS_DESC2;
            stackPtr = (int*)(((int)stackPtr + 4) & ~3);
            *stackPtr = (int)ptr;
            stackPtr++;
            gAllocatorGlobals->debugStackPtr = stackPtr;
        }

        // Validate magic numbers at offsets 0x24, 0x28, 0x2c, 0x30 (ptr[9], ptr[10], ptr[11], ptr[12])
        if (ptr[9] != MAGIC1 || ptr[10] != MAGIC2 || ptr[11] != MAGIC3 || ptr[12] != MAGIC4) {
            reportBlockCorruption(ptr[9], ptr[10], ptr[11], ptr[12]);
        }

        // Push final debug entry
        stackPtr = gAllocatorGlobals->debugStackPtr;
        *(const void**)stackPtr = CLASS_DESC3;
        stackPtr = (int*)(((int)stackPtr + 4) & ~3);
        *stackPtr = (int)ptr;
        stackPtr++;
        gAllocatorGlobals->debugStackPtr = stackPtr;

        return 1;
    }
    else {
        // destroyFlag != 0: only call the virtual destructor (first entry in vtable) with argument 1
        if (ptr != 0) {
            (*(void(__thiscall*)(void*, int))(*((void***)ptr)[0]))(ptr, 1);
        }
        return 1;
    }
}