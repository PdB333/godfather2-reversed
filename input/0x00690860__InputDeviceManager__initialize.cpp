// FUNC_NAME: InputDeviceManager::initialize
InputDeviceManager* __fastcall InputDeviceManager::initialize(InputDeviceManager* this)
{
    int iVar1;
    int iVar2;
    uint slotIdx;

    slotIdx = 0;
    this->field_0x4 = 1;                  // +0x04: likely reference count or init flag
    this->field_0x8 = 0;                  // +0x08: unknown
    this->vtable = &PTR_FUN_00d5c958;     // +0x00: vtable pointer

    // Register with various global modules (0x8000 is likely an event flag)
    if (g_module1 != 0) {
        registerWithModule(this, &g_module1, 0x8000); // FUN_00408900
    }
    if (g_module2 != 0) {
        registerWithModule(this, &g_module2, 0x8000);
    }
    if (g_module3 != 0) {
        registerWithModule(this, &g_module3, 0x8000);
    }
    if (g_module4 != 0) {
        registerWithModule(this, &g_module4, 0x8000);
    }
    if (g_module5 != 0) {
        registerWithModule(this, &g_module5, 0x8000);
    }
    if (g_module6 != 0) {
        registerWithModule(this, &g_module6, 0x8000);
    }
    if (g_module7 != 0) {
        registerWithModule(this, &g_module7, 0x8000);
    }
    if (g_module8 != 0) {
        registerWithModule(this, &g_module8, 0x8000);
    }
    if (g_module9 != 0) {
        registerWithModule(this, &g_module9, 0x8000);
    }
    if (g_module10 != 0) {
        registerWithModule(this, &g_module10, 0x8000);
    }
    if (g_module11 != 0) {
        registerWithModule(this, &g_module11, 0x8000);
    }
    if (g_module12 != 0) {
        registerWithModule(this, &g_module12, 0x8000);
    }

    iVar1 = g_inputDeviceManagerSingleton; // DAT_012233b4: pointer to the primary InputDeviceManager instance
    *(byte*)(iVar1 + 0x52c) = 1;           // +0x52C: flag for "need update" or "scanning active"

    do {
        iVar2 = getControllerSlotInfo(slotIdx); // FUN_00410540: returns slot info pointer
        if ( (*(byte*)(iVar2 + 0x3e) != '\0') &&   // +0x3E: controller connected flag
             ((byte)slotIdx < 0x10) &&
             ((byte)slotIdx != *(byte*)(iVar1 + 0x53d)) ) // +0x53D: active controller slot index
        {
            *(byte*)(iVar1 + 0x52d + (slotIdx & 0xff)) = 1; // +0x52D+: bitmask per slot
        }
        slotIdx = slotIdx + 1;
    } while (slotIdx != 0x10);

    return this;
}