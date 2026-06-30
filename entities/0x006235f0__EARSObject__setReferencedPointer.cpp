// FUNC_NAME: EARSObject::setReferencedPointer
// Function address: 0x006235f0
// Role: Sets a referenced pointer member (at +0x14) with ref counting and owner management

class EARSObject {
public:
    // Field offsets: +0x14 = pointer to attached object, +0x18 = reference handle/count
    void* m_pObjectAt14;   // +0x14
    int   m_refHandleAt18; // +0x18
};

// External helper functions (assumed from EA EARS engine)
extern int __cdecl addRef(void* obj, void* existingPtr);          // FUN_004265d0
extern void __cdecl releaseAndSet(void* ptr, int refVal);        // FUN_00623ea0

// Virtual function indices for the object pointed to by param_2
// Vtable offsets: +0 = unknown, +4 = ownerSetFunction(void* owner, int flag), +8 = release(), +12 = finalize()
typedef void (__thiscall* ReleaseFunc)(void* self);
typedef void (__thiscall* OwnerSetFunc)(void* self, void* owner, int flag);
typedef void (__thiscall* FinalizeFunc)(void* self);

__thiscall int setReferencedPointer(EARSObject* this, void* pObj, void* pOwner) {
    void* pPtr = pObj;  // The object whose pointer will be managed

    // Step 1: Release the incoming object's previous reference (if any)
    ((ReleaseFunc)(*(void***)pPtr)[2])(pPtr);  // vtable+8

    int refHandle;
    if (pOwner != nullptr) {
        refHandle = addRef(pOwner, pPtr);
    } else {
        refHandle = 0;
    }

    // Step 2: Update internal reference trackers
    releaseAndSet(pPtr, refHandle);

    // Step 3: Store the pointer in this object
    this->m_pObjectAt14 = pPtr;

    // Step 4: Release again (possibly transferring ownership or double-check)
    ((ReleaseFunc)(*(void***)pPtr)[2])(pPtr);  // vtable+8 again

    if (pOwner != nullptr) {
        // Re-acquire reference from the owner through the stored pointer
        refHandle = addRef(pOwner, this->m_pObjectAt14);
        this->m_refHandleAt18 = refHandle;

        // Notify the attached object of its new owner
        ((OwnerSetFunc)(*(void***)pPtr)[1])(pPtr, pOwner, 0);  // vtable+4

        // Finalize the attachment
        ((FinalizeFunc)(*(void***)pPtr)[3])(pPtr);  // vtable+12
        return reinterpret_cast<int>(this);
    }

    // No owner: clear reference handle and finalize
    this->m_refHandleAt18 = 0;
    ((FinalizeFunc)(*(void***)pPtr)[3])(pPtr);  // vtable+12
    return reinterpret_cast<int>(this);
}