// FUN_NAME: EARSObject::EARSObject

class EARSObject {
public:
    // vtable pointer at +0x00 (set to PTR_FUN_00e32f30)
    // Additional vtable pointers at +0x3C (index 0xF), +0x48 (index 0x12), +0x50 (index 0x14)
    // Members:
    // +0x54 (index 0x15): undefined4
    // +0x58 (index 0x16): unsigned short
    // +0x5A: unsigned short
    // +0x5C (index 0x17): undefined4
    // +0x60 (index 0x18): unsigned short
    // +0x62: unsigned short
    // +0x64 (index 0x19): undefined4
    // +0x68 (index 0x1A): unsigned short
    // +0x6A: unsigned short
    // +0x6C (index 0x1B): undefined4
    // +0x70 (index 0x1C): undefined4
    // +0x74 (index 0x1D): int (initialized to -1)
    // +0x78 (index 0x1E): int (initialized to 4)
    // +0x7C (index 0x1F): undefined4
    // +0x80 (index 0x20): undefined4
    // +0x84 (index 0x21): undefined4
    // +0x88 (index 0x22): undefined4

    void *__cdecl operator new(size_t size); // not relevant

    EARSObject(int initData);
};

// external functions
extern void __thiscall BaseConstructor(int initData); // FUN_0046c590
extern void __thiscall RegisterWithGlobal(void *ptr, void *global); // FUN_00407e60
extern void *DAT_0120e924; // some global pointer

EARSObject::EARSObject(int initData) {
    BaseConstructor(initData);

    // Set up multiple vtable pointers (multiple inheritance or interface tables)
    *(void**)((char*)this + 0x50) = &PTR_LAB_00e32e7c;   // First vtable for base at +0x50
    *(void**)this = &PTR_FUN_00e32f30;                    // Primary vtable at +0x00
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00e32f4c;   // Interface vtable at +0x3C
    *(void**)((char*)this + 0x48) = &PTR_LAB_00e32f5c;   // Interface vtable at +0x48
    *(void**)((char*)this + 0x50) = &PTR_LAB_00e32f60;   // Overwrite previous vtable at +0x50 (likely derived class override)

    // Clear a block of members from +0x54 to +0x70
    *(int*)((char*)this + 0x54) = 0;         // +0x54
    *(unsigned short*)((char*)this + 0x58) = 0;  // +0x58
    *(unsigned short*)((char*)this + 0x5A) = 0;  // +0x5A
    *(int*)((char*)this + 0x5C) = 0;         // +0x5C
    *(unsigned short*)((char*)this + 0x60) = 0;  // +0x60
    *(unsigned short*)((char*)this + 0x62) = 0;  // +0x62
    *(int*)((char*)this + 0x64) = 0;         // +0x64
    *(unsigned short*)((char*)this + 0x68) = 0;  // +0x68
    *(unsigned short*)((char*)this + 0x6A) = 0;  // +0x6A
    *(int*)((char*)this + 0x6C) = 0;         // +0x6C
    *(int*)((char*)this + 0x70) = 0;         // +0x70

    // Set default values for some fields
    *(int*)((char*)this + 0x74) = -1;        // +0x74 (e.g., handle or ID)
    *(int*)((char*)this + 0x78) = 4;         // +0x78 (e.g., type or count)

    // Zero remaining fields
    *(int*)((char*)this + 0x7C) = 0;
    *(int*)((char*)this + 0x80) = 0;
    *(int*)((char*)this + 0x84) = 0;
    *(int*)((char*)this + 0x88) = 0;

    // If a global pointer exists, register this object's interface (at +0x3C) with it
    if (DAT_0120e924 != 0) {
        RegisterWithGlobal((char*)this + 0x3C, &DAT_0120e924);
    }
}