// FUNC_NAME: ManagedObject::ManagedObject (0x00684070)
// Constructor for a small object (0x50 bytes) with multiple virtual tables.
// The flag parameter indicates if memory was dynamically allocated; if bit 0 is set,
// the object frees itself on failure (or here, after base init) – common EA pattern.

class ManagedObject : public BaseClass {
public:
    // Offsets:
    // +0x00: vtable pointer (PTR_FUN_00d5888c)
    // +0x3C: pointer to secondary vtbl or interface table (PTR_LAB_00d5887c)
    // +0x48: pointer to tertiary vtbl (PTR_LAB_00d58878)
    // Total size = 0x50

    __thiscall ManagedObject(byte allocated) {
        this->vtable = &_vtbl_ManagedObject;      // PTR_FUN_00d5888c
        this->field_0x3C = &_secVtbl_ManagedObject; // PTR_LAB_00d5887c
        this->field_0x48 = &_terVtbl_ManagedObject; // PTR_LAB_00d58878

        // Call base class initializer (e.g., component or core functionality)
        BaseClass::BaseClass(); // FUN_0046c640

        // If memory was allocated (bit 0 set), free it after construction.
        // This handles the case where the constructor might need to undo allocation.
        if (allocated & 1) {
            operator delete(this, 0x50); // FUN_0043b960
        }

        return this;
    }
};