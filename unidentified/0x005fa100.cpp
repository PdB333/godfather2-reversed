/*
 * Function address: 0x005fa100
 * Identified role: Smart pointer initialization for EARS reference-counted objects.
 * Likely belongs to a class like "SmartPtr" or "RefPtr" inside EA's EARS engine.
 * The function takes an object (pObject) and a reference counting info ID (refCountInfo).
 * It sets up a smart pointer structure (this) with a pointer to the managed object (+0x8)
 * and a reference count entry offset (+0xC).
 * Virtual function calls at vtable offsets 0x0, 0x4, 0x8, 0xC are used for ref counting
 * (likely AddRef, Release, etc.) but exact order is unclear.
 */

// The object being managed must have a vtable with at least 4 entries.
class ManagedObject {
public:
    // vtable offsets:
    // 0x00: virtual void vfunc0();       // unknown
    // 0x04: virtual void vfunc1(int, int); // used with refCountInfo and 0
    // 0x08: virtual void vfunc2();       // called with and without arguments
    // 0x0C: virtual void vfunc3();       // called at end
};

// Smart pointer class layout:
// +0x0: vtable pointer (of RefCountedPtr itself)
// +0x4: (unknown)
// +0x8: ManagedObject* m_pObject;
// +0xC: int m_refCountEntry;  // handle/index into reference count table

class RefCountedPtr {
public:
    // Externally linked helper functions (reconstructed)
    static int getRefCountEntry(int refCountInfo, ManagedObject* obj);   // FUN_004265d0
    static void storeRefCountEntry(ManagedObject* obj, int entry);      // FUN_005fa360

    // This function (0x5fa100) – __thiscall
    void initialize(ManagedObject* pObject, int refCountInfo) {
        ManagedObject* piVar2 = pObject;

        // Call vtable+0x8 on pObject (likely AddRef or similar)
        piVar2->vfunc2();

        int uVar1;
        if (refCountInfo == 0) {
            uVar1 = 0;
        } else {
            uVar1 = RefCountedPtr::getRefCountEntry(refCountInfo, piVar2);
        }
        RefCountedPtr::storeRefCountEntry(piVar2, uVar1);

        // Assign the object pointer to this smart pointer's storage (offset +0x8)
        this->m_pObject = piVar2;

        // Second call to vfunc2 on the same object (argument missing in decompiler, likely same)
        piVar2->vfunc2();

        if (refCountInfo != 0) {
            uVar1 = RefCountedPtr::getRefCountEntry(refCountInfo, this->m_pObject);
            this->m_refCountEntry = uVar1; // offset +0xC
            // Call vtable+0x04 with (refCountInfo, 0)
            piVar2->vfunc1(refCountInfo, 0);
            // Call vtable+0x0C
            piVar2->vfunc3();
            return;
        }
        this->m_refCountEntry = 0;
        piVar2->vfunc3();
    }
};