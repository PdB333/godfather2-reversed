// FUNC_NAME: RefCountedArray::~RefCountedArray

// Destructor for a collection that owns ref-counted objects.
// Frees each object (decrements ref count, calls destructor if needed),
// then deallocates the internal pointer array.
// Address: 0x004c2ef0

class RefCountedArray {
public:
    // VTable pointer at +0x000
    // +0x208: pointer to array of object pointers (void**)
    // +0x20C: count of elements in array
    // +0x210: capacity (unused in this destructor? set to 0)

    void __thiscall destructor() {
        // Set vtable to base class vtable (or sentinel)
        *(void***)this = &PTR_FUN_00e36260;

        // Get pointer to array of object pointers
        void** objArray = *(void***)((int)this + 0x208);  // offset 0x82 * 4
        int count = *(int*)((int)this + 0x20C);            // offset 0x83 * 4

        if (objArray != objArray + count) {
            do {
                void* objPtr = *objArray;  // pointer to the actual object (or control block?)
                if (objPtr != nullptr) {
                    // The object has a ref count structure at offset 20
                    int* refBlock = *(int**)((int)objPtr + 20);  // piVar2 at piVar1[5]
                    // Decrement reference count
                    (*refBlock)--;

                    // If ref count reached zero, call the destructor via vtable
                    if (*refBlock == 0) {
                        // refBlock[0x43] points to a vtable; at +0x18 is the destructor
                        void** vtable = *(void***)(refBlock + 0x43);
                        typedef void (__thiscall *DestructorFn)(void*);
                        DestructorFn dtor = (DestructorFn)(vtable[0x18 / 4]);
                        dtor(refBlock);
                    }

                    // If the object's own reference count is nonzero, call a cleanup function
                    if (*(int*)objPtr != 0) {
                        // objPtr[3] is a function pointer (likely vtable entry)
                        void (*cleanupFn)(int) = (void (*)(int))(*(int*)((int)objPtr + 12));
                        cleanupFn(*(int*)objPtr);
                    }

                    // Free the object memory (operator delete)
                    FUN_009c8eb0(objPtr);
                }
                objArray++;
            } while (objArray != (void**)((int)this + 0x208 + count * 4));
        }

        // Reset count to 0
        *(int*)((int)this + 0x20C) = 0;

        // Free the array itself
        FUN_009c8f10(*(void**)((int)this + 0x208));
        *(void***)((int)this + 0x208) = nullptr;
        *(int*)((int)this + 0x210) = 0;  // capacity

        // Redundant check (likely compiler artifact)
        if (*(void**)((int)this + 0x208) != nullptr) {
            FUN_009c8f10(*(void**)((int)this + 0x208));
        }

        // Additional cleanup
        FUN_004c27f0();
    }

private:
    // External helper functions (likely from memory manager)
    void FUN_009c8eb0(void* ptr);   // operator delete or similar
    void FUN_009c8f10(void* ptr);   // deallocation for array
    void FUN_004c27f0(void);        // additional cleanup
};