// FUNC_NAME: ObjectFactory::allocateSomeObject
// Address: 0x005e0b10
// Role: Allocates and initializes a small object (0x18 bytes) from a custom allocator.

class ObjectFactory {
public:
    // +0x04: Pointer to allocator vtable (first function is allocate)
    void** allocatorVtable;
    // +0x08: Allocator context (may be null, uses stack buffer as placeholder)
    void* allocatorContext;

    __thiscall void allocateSomeObject() {
        void* allocContext;
        uint localStack[3] = {0, 0, 0}; // stack buffer when allocatorContext is null

        // Determine allocator context
        if (this->allocatorContext != nullptr) {
            allocContext = this->allocatorContext;
        } else {
            allocContext = localStack; // fallback stack buffer
        }

        // Call allocator's allocate function (first vtable entry, size 0x18)
        int (*allocate)(int size, void* context) = (int (*)(int, void*))this->allocatorVtable[0];
        int* newObj = (int*)allocate(0x18, allocContext); // 0x18 = 24 bytes

        // Initialize the allocated object
        if (newObj != nullptr) {
            newObj[0] = 0;   // offset 0x00
            newObj[1] = 0;   // offset 0x04
            newObj[2] = 0;   // offset 0x08
            *(char*)(newObj + 5) = 1;  // offset 0x14 (byte)
            *(char*)((int)newObj + 0x15) = 0; // offset 0x15 (byte)
        }
    }
};