// FUNC_NAME: InputDeviceManager::InputDeviceManager
// Constructor at 0x0068cad0 - Initializes the singleton controller manager
// Registers messages for "WaitForControllerAttach" and registers event callbacks

InputDeviceManager* __thiscall InputDeviceManager::ctor(InputDeviceManager* this) {
    // Vtable setup (+0x00)
    this->vtable = (void**)&PTR_FUN_00d5c4d8;
    this->field_04 = 1;                // +0x04
    this->field_08 = 0;                // +0x08
    this->field_0C = (void*)&PTR_LAB_00d5c4d0; // +0x0C (temporary base pointer)

    // Store singleton global
    DAT_01129814 = this;

    // Call base class init or internal setup (0x0040fc70)
    FUN_0040fc70(&LAB_0068c920);

    // Override pointer with derived vtable/pointer
    this->field_0C = (void*)&PTR_LAB_00d5c4d4; // +0x0C final

    this->field_10 = 0;                // +0x10
    *(uint8*)(&this->field_10 + 4) = 0x12; // +0x14 (flags)
    *(uint8*)((uint32)this + 0x15) = 1;    // +0x15

    // Clear remaining fields
    this->field_18 = 0;                // +0x18
    this->field_1C = 0;                // +0x1C
    this->field_20 = 0;                // +0x20
    this->field_24 = 0;                // +0x24
    this->field_28 = 0;                // +0x28
    this->bitmask_2C = 0;              // +0x2C

    // Set bit from global configuration (+0x53d of DAT_012233b4)
    uint8 configByte = *(uint8*)((uint32)DAT_012233b4 + 0x53d);
    this->bitmask_2C |= (1 << (configByte & 0x1f));

    this->field_30 = DAT_01205210;     // +0x30

    // Register message names for controller attach/detach events
    FUN_00408240(&DAT_01129aa0, "iMsgStartWaitingForControllerAttach");
    FUN_00408240(&DAT_01129a98, "iMsgStopWaitingForControllerAttach");

    // Register callbacks for specific events if pointers are non-null
    if (DAT_012069c4 != 0) {
        FUN_00408900(this, &DAT_012069c4, 0x8000);
    }
    if (DAT_012069b4 != 0) {
        FUN_00408900(this, &DAT_012069b4, 0x8000);
    }

    return this;
}