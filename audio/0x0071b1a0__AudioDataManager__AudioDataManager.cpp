// FUNC_NAME: AudioDataManager::AudioDataManager
// Constructor for AudioDataManager (CrewComponent?) at 0x0071b1a0
// Initializes vtable, resource handle, and several fields from global DAT_00d5ccf8

void __thiscall AudioDataManager::AudioDataManager(AudioDataManager* this)
{
    // Vtable pointer at +0x00
    this->vtable = &PTR_FUN_00d61b38; // set vtable
    // +0x04: some identifier (0)
    this->field_0x04 = 0;
    // +0x08: index or state (-1 = invalid)
    this->field_0x08 = 0xFFFFFFFF;
    // +0x0C to +0x24: zero-initialized (fields 3-9)
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    this->field_0x20 = 0;
    this->field_0x24 = 0;

    // Local struct (probably GUID or resource ID)
    int initStruct[3] = {0, 0, 0}; // local_c, local_8, local_4

    // Create resource and register with type 3
    int resourceHandle = FUN_004dddd0(initStruct); // returns a handle
    FUN_0071a810(3, resourceHandle, initStruct);   // register resource

    // Fields at +0x3C to +0x50 (indices 0xf-0x14)
    this->field_0x3C = 0;               // +0x3C: zero
    this->field_0x40 = DAT_00d5ccf8;    // +0x40: global audio system pointer
    this->field_0x44 = DAT_00d5ccf8;    // +0x44: same pointer
    this->field_0x48 = 0;               // +0x48: zero
    this->field_0x4C = DAT_00d5ccf8;    // +0x4C: same pointer
    this->field_0x50 = DAT_00d5ccf8;    // +0x50: same pointer
}