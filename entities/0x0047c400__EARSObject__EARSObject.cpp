// FUNC_NAME: EARSObject::EARSObject

class EARSObject {
public:
    // vtable pointer at +0x00
    void* vtable;
    // unknown members...
    // sub-object at +0x14
    // pointer at +0x3C (offset 0x0F * 4)
    // pointer at +0x48 (offset 0x12 * 4)

    EARSObject(byte constructorFlags);
};

EARSObject::EARSObject(byte constructorFlags) {
    // Set vtable for this class
    vtable = reinterpret_cast<void**>(0x00e3317c);

    // Set two function pointers at offsets 0x3C and 0x48
    *(void**)(reinterpret_cast<char*>(this) + 0x3C) = &PTR_LAB_00e33198; // unknown override
    *(void**)(reinterpret_cast<char*>(this) + 0x48) = &PTR_LAB_00e331a8; // unknown override

    // Initialize sub‑object at offset 0x14
    FUN_004086d0(reinterpret_cast<char*>(this) + 0x14);
    FUN_00408310(reinterpret_cast<char*>(this) + 0x14);

    // Global engine factory registration
    FUN_0046c640();

    // Optional registration with a manager object
    if (constructorFlags & 1) {
        // Dereference global manager table (DAT_01223410 + 0x2D4),
        // fetch vtable entry at index 1, and call it with this and 0.
        typedef void (__thiscall *ManagerFunc)(void* obj, int arg);
        ManagerFunc func = reinterpret_cast<ManagerFunc>(
            (*reinterpret_cast<int**>(DAT_01223410 + 0x2D4))[1]
        );
        func(this, 0);
    }
}