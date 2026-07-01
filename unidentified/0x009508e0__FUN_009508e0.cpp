// FUNC_NAME: SomeManager::~SomeManager (destructor at 0x009508e0)

void __fastcall SomeManager::~SomeManager(void* this) {
    int* piVar1 = reinterpret_cast<int*>(this) + 0x5a; // +0x168

    // Set vtable pointers for base classes / subobjects
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d8bbf8;  // main vtable at offset 0
    reinterpret_cast<void**>(this)[0xf] = &PTR_LAB_00d8bbe8; // offset 0x3C
    reinterpret_cast<void**>(this)[0x12] = &PTR_LAB_00d8bbe4; // offset 0x48
    reinterpret_cast<void**>(this)[0x14] = &PTR_LAB_00d8bbcc; // offset 0x50

    // Cleanup pointer at +0x168 if not null and not 0x48 (maybe a sentinel)
    if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
        FUN_00791350(reinterpret_cast<int*>(this) + 0x14);  // +0x50 subobject destructor
    }

    // Zero out two memory regions (initializers or resets)
    FUN_004089b0(reinterpret_cast<int*>(this) + 0x17, 0); // +0x5C
    FUN_004089b0(reinterpret_cast<int*>(this) + 0x19, 0); // +0x64

    // Global debug flag affects extra cleanup
    if (DAT_01130030 != 0) {
        FUN_0097e040(this);
    }

    // Free external pointer at +0x17C (if allocated)
    if (reinterpret_cast<void**>(this)[0x5f] != 0) {
        *reinterpret_cast<int*>(reinterpret_cast<void**>(this)[0x5f] + 8) = 0;
        reinterpret_cast<void**>(this)[0x5f] = 0;
    }

    // Free external pointer at +0x170
    if (reinterpret_cast<void**>(this)[0x5c] != 0) {
        FUN_004daf90(reinterpret_cast<int*>(this) + 0x5c); // +0x170
    }

    // Free pointer at +0x168 (same as piVar1)
    if (*piVar1 != 0) {
        FUN_004daf90(piVar1);
    }

    // Global cleanup call
    FUN_0046c640();
}