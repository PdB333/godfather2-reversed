// FUNC_NAME: EA::EARS::Modules::StreamManager::shutdown
void __thiscall EA::EARS::Modules::StreamManager::shutdown(int* this) {
    // Offset +0x48 (byte) – initialized flag
    if (*(char*)(this + 0x12) != '\0') {
        // Virtual function at vtable+0xC (pre‑shutdown hook)
        (*(void (__thiscall**)(int*))(*this + 0xC))(this);
        *(char*)(this + 0x12) = 0;

        // Check if additional cleanup is needed
        char extraCleanup = FUN_005c1ba0();
        if (extraCleanup != '\0') {
            FUN_005c1b40();
            FUN_005c1c20();
        }

        int* streamList = this + 5; // Offset +0x14 – list of streams
        // Remove all registered stream callbacks
        FUN_005c0d50(streamList, &LAB_005bfd50, 0);
        (*(void (__thiscall**)(int*))(*this + 0x30))(this); // vtable+0x30 – post‑cleanup
        FUN_005c0d50(streamList, &LAB_005bfb30, 0);
        FUN_005c0d50(this + 10, &LAB_005bf690, 0); // +0x28 – another list
        FUN_005c0d50(streamList, &LAB_005bfb50, 0);
        FUN_005c0d50(streamList, &LAB_005bfcd0, 0);
        FUN_005c0d50(streamList, &LAB_005bfbb0, 0);
        FUN_005c0d50(streamList, &LAB_005bfca0, 0);
        FUN_005c0d50(streamList, &LAB_005bfc70, 0);

        // Retrieve some object at +0x10 (this+4) and call its vtable+4
        int* object = *(int**)(this + 4); // Offset +0x10
        int result = (*(int (__thiscall**)(int*))(*(int*)object + 4))(object);

        // Construct a temporary pair and pass to resource manager
        struct {
            int field0; // result from above
            int field4; // DAT_01222060 (global resource handle)
            char field8_pad; // zero
        } temp;
        temp.field0 = result;
        temp.field4 = DAT_01222060;
        temp.field8_pad = 0;
        FUN_00408a00(&temp, 0);

        // Decrement global reference counter
        DAT_01205658--;
        if (DAT_01205658 == 0) {
            // Free global resource objects when no users remain
            FUN_00408310(&DAT_01222058);
            FUN_00408310(&DAT_01222060);
        }
    }
}