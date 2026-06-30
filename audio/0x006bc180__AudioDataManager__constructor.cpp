// FUNC_NAME: AudioDataManager::constructor

void __fastcall AudioDataManager::constructor(undefined4 *this)
{
    // Set primary vtable pointer at +0x00
    *this = &PTR_FUN_00d5e880;
    // Set additional vtable pointers for multiple inheritance
    this[0xf] = &PTR_LAB_00d5e870;   // +0x3C
    this[0x12] = &PTR_LAB_00d5e86c;  // +0x48
    this[0x14] = &PTR_LAB_00d5e868;  // +0x50
    this[0x15] = &PTR_LAB_00d5e808;  // +0x54
    this[0x16] = &PTR_LAB_00d5e7a0;  // +0x58
    // Initialize sub-object at offset +0x188 (this + 0x62 elements)
    subObjectInit(this + 0x62);
    subObjectSetup(this + 0x62);
    // Initialize global static objects
    subObjectInit(&DAT_0120e93c);
    subObjectInit(&DAT_0112a628);
    subObjectInit(&DAT_0112a600);
    // Final global initialization call
    initializeGlobalResources();
}