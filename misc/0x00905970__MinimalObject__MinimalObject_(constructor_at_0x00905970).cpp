// FUNC_NAME: MinimalObject::MinimalObject (constructor at 0x00905970)
// Minimal class with only vtable pointer (4 bytes)
// Allocates memory via custom allocator (FUN_009c8e50) and sets vtable

extern void* __cdecl operator_new(size_t size); // likely FUN_009c8e50
extern void* PTR_LAB_00d82678; // vtable for MinimalObject

class MinimalObject {
public:
    void* vfptr; // +0x00

    // __thiscall constructor
    MinimalObject() {
        // Attempt to allocate 4 bytes (size of vtable pointer)
        void* rawMem = operator_new(4);
        if (rawMem != nullptr) {
            this->vfptr = &PTR_LAB_00d82678; // set vtable
        } else {
            // Allocation failed - returned nullptr
        }
    }
};