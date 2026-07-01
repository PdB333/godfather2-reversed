// FUNC_NAME: setupStateCallbacks
void __fastcall setupStateCallbacks(void* object)
{
    // If object is non-null, use the address of its field at offset 0x14 as the registration base;
    // otherwise use nullptr.
    void* callbackRegBase;
    if (object == nullptr) {
        callbackRegBase = nullptr;
    } else {
        // The field at +0x14 is likely a callback registrar structure.
        callbackRegBase = reinterpret_cast<unsigned char*>(object) + 0x14;
    }

    // Register the "begin" callback (LAB_009767b0)
    FUN_005c0c50(callbackRegBase, &LAB_009767b0);

    // Register the "end" callback (LAB_00976800)
    // Note: the original code uses the same base for both calls; if object is null, the second call also uses null.
    if (object != nullptr) {
        FUN_005c0c50(callbackRegBase, &LAB_00976800);
    } else {
        FUN_005c0c50(nullptr, &LAB_00976800);
    }
}