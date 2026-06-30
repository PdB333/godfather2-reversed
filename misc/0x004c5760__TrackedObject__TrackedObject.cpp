// FUNC_NAME: TrackedObject::TrackedObject
class TrackedObject {
public:
    void* vtable;              // offset +0x00
    TrackedObject* listNext;   // offset +0x04 (used in tracking list)
};

// Global memory manager pointer (DAT_01206880)
extern void* gMemoryManager;

// Vtable for TrackedObject (PTR_FUN_00e362f4)
extern void* gTrackedObjectVTable;

// Constant used for list manipulation (PTR_LAB_01124770)
extern int* gListMarker;

// External function for cleanup/destruction (FUN_009c8eb0)
extern void destroyTrackedObject(TrackedObject* obj);

// Returns this pointer (standard for constructor)
TrackedObject* __thiscall TrackedObject::TrackedObject(TrackedObject* this, byte param2) {
    // Set vtable pointer
    this->vtable = &gTrackedObjectVTable;

    // Access global memory manager offset 0x14 (presumably a pointer to list head)
    int** listHeadPtr = (int**)((char*)gMemoryManager + 0x14);

    // Overwrite the head pointer with a fixed marker (PTR_LAB_01124770)
    **listHeadPtr = (int)gListMarker;

    // Advance pointer (like incrementing through a linked list)
    int* listIter = *listHeadPtr;
    *listHeadPtr = (int*)(listIter + 1);  // move to next slot

    // Align the pointer to 4-byte boundary
    int* alignedNode = (int*)((uintptr_t)(*listHeadPtr) + 3U & ~3U);
    *listHeadPtr = alignedNode;

    // Store address of this->listNext into the list node
    *alignedNode = (int)(&(this->listNext));

    // Advance list pointer again
    *listHeadPtr = alignedNode + 1;

    // If param2 has low bit set, perform cleanup (destructor or deallocation)
    if ((param2 & 1) != 0) {
        destroyTrackedObject(this);
    }

    return this;
}