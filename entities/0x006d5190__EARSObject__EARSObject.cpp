// FUNC_NAME: EARSObject::EARSObject
// Address: 0x006d5190
// Role: Constructor for EARS base object, sets two vtable pointers and optionally performs custom allocation.
// Note: The two vtable pointers (at +0x00 and +0x08) are typical for EARS engine objects with multiple inheritance.
// Allocator vtable call at offset 4 is used to allocate or recycle memory of size 0xD0 (208 bytes).

extern void* PTR_FUN_00d5f3bc;   // Vtable for this class
extern void* PTR_LAB_00d5f3b4;   // Second vtable (interface or derived)
extern void  FUN_00473a60(void); // Base class constructor or initialization
extern void* FUN_009c8f80(void); // Returns pointer to allocator interface (e.g. memory manager)

class EARSObject {
public:
    // +0x00: primary vtable pointer
    void* __vtable;
    // +0x04: unknown field (size 4 bytes)
    // +0x08: secondary vtable pointer (often for interface or RTTI)
    void* __vtable2;

    // Constructor with allocation flag
    // param_2: if bit 0 is set, object memory is allocated/recycled via allocator
    __thiscall EARSObject(byte allocationFlags) {
        __vtable = &PTR_FUN_00d5f3bc;   // Set primary vtable
        __vtable2 = &PTR_LAB_00d5f3b4;  // Set secondary vtable

        // Call base class initialization
        FUN_00473a60();

        // If allocation flag indicates custom memory handling
        if ((allocationFlags & 1) != 0) {
            // Retrieve allocator interface
            struct AllocatorVTable {
                // offset +0: destructor or release
                // offset +4: allocate/recycle with (this, size)
                void* funcs;
            };
            AllocatorVTable* allocator = (AllocatorVTable*)FUN_009c8f80();

            // Call the function at vtable offset 4 to allocate or prepare memory
            auto allocateFunc = (void (__thiscall*)(void*, uint))allocator->funcs[1];
            allocateFunc(this, 0xD0); // 0xD0 = 208 bytes, likely the size of this object
        }
    }
};