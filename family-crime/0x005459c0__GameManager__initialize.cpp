// FUNC_NAME: GameManager::initialize
void __thiscall GameManager::initialize(int *this, undefined4 param_2)
{
    char isInitialized;
    int subObject;

    // Check if already initialized via virtual function at vtable+0x198
    isInitialized = (**(code (__thiscall **)(int *))(*this + 0x198))();
    if (isInitialized == '\0') {
        // First-time initialization: allocate and initialize sub-objects
        TlsGetValue(DAT_01139810); // Thread-local storage access
        subObject = FUN_00aa2680(0x30, 0xb); // Allocate 0x30 bytes, pool 0xb
        *(undefined2 *)(subObject + 4) = 0x30; // Mark allocated size at +4
        subObject = FUN_00bee410(); // Factory creation
        FUN_00548d80(); // Post-constructor for this sub-object
        this[0xdd] = subObject; // Store at this+0x374

        TlsGetValue(DAT_01139810);
        subObject = FUN_00aa2680(0x30, 0xb);
        *(undefined2 *)(subObject + 4) = 0x30;
        subObject = FUN_00beda70();
        FUN_00548b50();
        this[0xe2] = subObject; // Store at this+0x388

        FUN_005489d0(this);

        subObject = FUN_00548310(param_2, this);
        this[0xe1] = subObject; // Store at this+0x384

        subObject = FUN_00547530(param_2, this);
        this[0xda] = subObject; // Store at this+0x368

        subObject = FUN_005470a0(param_2, this);
        this[0xdf] = subObject; // Store at this+0x37C

        subObject = FUN_00546e10(param_2, this);
        this[0xe0] = subObject; // Store at this+0x380

        subObject = FUN_00546da0();
        this[0xde] = subObject; // Store at this+0x378

        TlsGetValue(DAT_01139810);
        subObject = FUN_00aa2680(0x14, 0xb); // Allocate 0x14 bytes
        *(undefined2 *)(subObject + 4) = 0x14;
        subObject = FUN_00bee050();
        FUN_00548fd0(subObject); // Post-constructor for temporary object
        this[0xe3] = subObject; // Store at this+0x38C

        return;
    }
    // Re-initialization path: update existing sub-objects
    FUN_00548d80();
    FUN_00548b50();
    FUN_005489d0(this);
    FUN_00548440(param_2, this);
    FUN_005477e0(param_2, this);
    FUN_00547220(param_2, this[0xdf], this);
    FUN_00546ec0(this[0xe0], this);
    FUN_00548fd0(this[0xe3]); // Destroy/release the object at offset 0x38C
    return;
}