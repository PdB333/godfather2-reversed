// FUNC_NAME: EARSObject::constructor
// Reconstructed C++ for EARSObject constructor at 0x006d2050
// Calls base initializer (FUN_006d1bc0) then optionally allocates memory
// and invokes a VTable entry to complete construction.

typedef unsigned int uint32;
typedef unsigned char byte;

// Forward declaration of base class (likely EARSBaseObject or similar)
class EARSObject;

// Base class initializer (calls at 0x006d1bc0)
extern void BaseEARSObject_init(EARSObject* thisPtr);

// Memory allocation function (at 0x009c8f80) – returns pointer to allocated block
extern void* EARSAllocator_get(void);

// VTable layout for this class (assumed offset 0 = destructor, offset 4 = constructor helper)
typedef void (__thiscall *VTConstructFunc)(EARSObject* obj, uint32 size);

// Class definition (partial)
class EARSObject {
public:
    // VTable pointer at offset 0
    void** vtable;  // +0x00

    // Constructor (thiscall, takes a bool allocFlag)
    __thiscall EARSObject(uint32 allocFlag) {
        // Step 1: call base initialization
        BaseEARSObject_init(this);

        // Step 2: if bit0 of allocFlag is set, allocate memory and invoke second vtable entry
        if ((allocFlag & 1) != 0) {
            void* allocBlock = EARSAllocator_get();   // returns pointer to some allocator state
            int* vtablePtr = (int*)allocBlock;        // treat as vtable pointer
            VTConstructFunc construct = (VTConstructFunc)(*vtablePtr + 4); // offset 4 = constructor helper
            construct(this, 0xF0);                    // size 0xF0 (240 bytes)
        }
    }
};

// Concrete reconstruction (without the actual class name we approximate)
EARSObject* __thiscall EARSObject_constructor(uint32 this, byte allocFlag) {
    FUN_006d1bc0();                                              // base init
    if ((allocFlag & 1) != 0) {
        int* ptr = (int*)FUN_009c8f80();                         // get allocator
        (**(code**)(*ptr + 4))(this, 0xF0);                    // call second vtable entry with size
    }
    return this;
}