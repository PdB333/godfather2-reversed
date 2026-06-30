// FUNC_NAME: UnknownClass::releaseSubObject
// Address: 0x004de3a0
// Sets vtable to base, releases a sub-object (if exists) via virtual function at vtable+0xc,
// then restores vtable. Likely a destructor/cleanup step for a composite object.

class UnknownClass {
public:
    void* vtable;         // +0x00 vtable pointer
    UnknownClass* child;  // +0x04 sub-object pointer (can be null)

    void __thiscall releaseSubObject();
};

// External vtable globals (from data references)
extern void* base_vtable;    // PTR_FUN_00e36f1c
extern void* derived_vtable; // PTR_LAB_00e362b8

void __thiscall UnknownClass::releaseSubObject() {
    // Switch to base vtable (safe cleanup of base sub-object)
    this->vtable = &base_vtable;

    // If child exists, call its virtual function at offset 0xc (likely a destructor/release)
    if (this->child != nullptr) {
        void** childVtable = *(void***)(this->child);
        // vtable entry at offset 0xc = index 3
        void (__thiscall *childFunc)(void*) = (void (__thiscall *)(void*))childVtable[3];
        childFunc(this->child);
    }

    // Restore derived vtable
    this->vtable = &derived_vtable;
}