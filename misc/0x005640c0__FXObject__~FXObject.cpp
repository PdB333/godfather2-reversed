// FUNC_NAME: FXObject::~FXObject
// Function at 0x005640c0 - Destructor for FXObject (visual effects object)
// Releases three resource handles (type 0x17, likely particle or sound effects)
// Then sets vtable pointers to base classes for proper destruction chain.

// Assumed member offsets (each offset in bytes from 'this'):
// +0x00: vtable pointer (BaseClass1)
// +0x10: vtable pointer (BaseClass2)
// +0x18: m_pResourceA   (pointer to first resource manager context)
// +0x20: m_nResourceA   (first resource handle, int)
// +0x24: m_pResourceB   (pointer to second resource manager context)
// +0x2c: m_nResourceB   (second resource handle, int)
// +0x30: m_pResourceC   (pointer to third resource manager context)
// +0x38: m_nResourceC   (third resource handle, uint with flags in high bits)

// External functions used:
//   TlsGetValue(DAT_01139810) - retrieves thread-local storage pointer (resource manager)
//   FUN_00aa26e0(pContext, index, type) - releases a resource of given type (type=0x17)

void __thiscall FXObject::~FXObject(void* this) // ECX = this
{
    uint uHandleC = *(uint*)((char*)this + 0x38); // m_nResourceC
    if ((int)uHandleC >= 0) {
        void* tls = TlsGetValue(DAT_01139810);
        // Mask off flags (upper bits) to get the actual resource index
        FUN_00aa26e0(*(void**)((char*)this + 0x30), uHandleC & 0x3fffffff, 0x17);
    }

    int iHandleB = *(int*)((char*)this + 0x2c); // m_nResourceB
    if (iHandleB >= 0) {
        void* tls = TlsGetValue(DAT_01139810);
        // Shift left by 4 bits – index is stored multiplied by 16
        FUN_00aa26e0(*(void**)((char*)this + 0x24), iHandleB << 4, 0x17);
    }

    int iHandleA = *(int*)((char*)this + 0x20); // m_nResourceA
    if (iHandleA >= 0) {
        void* tls = TlsGetValue(DAT_01139810);
        // Shift left by 4 bits
        FUN_00aa26e0(*(void**)((char*)this + 0x18), iHandleA << 4, 0x17);
    }

    if (this != nullptr) {
        // Set vtable pointers to base classes (in case of virtual inheritance or derived destructor chain)
        *(void**)((char*)this + 0x10) = &PTR_LAB_00d987cc;  // BaseClass2 vtable
        *(void**)this = &PTR_LAB_00d96914;                   // BaseClass1 vtable
        return;
    }
    // Handle null this (special case? Unusual – might be a static object destructor)
    ppuRam00000000 = &PTR_LAB_00d96914;
}