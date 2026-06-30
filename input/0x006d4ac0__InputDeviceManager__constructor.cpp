// FUNC_NAME: InputDeviceManager::constructor
undefined4 * __fastcall InputDeviceManager::constructor(InputDeviceManager *this)
{
    // Call base constructors
    baseConstructor1();
    // Set vtable pointers (multiple inheritance)
    this->vtableBase1 = &PTR_LAB_00d5f3d0;   // +0x58 (index 0x16)
    this->vtablePrimary = &PTR_FUN_00d5f3f0;  // +0x00 (primary vtable)
    this->vtableBase2 = &PTR_LAB_00d5f3e0;    // +0x3C (index 0xf)
    this->vtableBase3 = &PTR_LAB_00d5f3dc;    // +0x48 (index 0x12)
    this->vtableBase4 = &PTR_LAB_00d5f3d8;    // +0x50 (index 0x14)
    this->vtableBase1 = &PTR_LAB_00d5f3d4;    // +0x58 (index 0x16) overwritten?
    baseConstructor2();
    // Initialize controller slot debug values (16 slots, each 4 DWORDs = 16 bytes)
    // Indices 0x2d..0x88 cover an array of 16 structs with sentinel values
    this->controllerState[0].marker1 = 0xBADBADBA;
    this->controllerState[0].marker2 = 0xBEEFBEEF;
    this->controllerState[0].marker3 = 0xEAC15A55;
    this->controllerState[0].marker4 = 0x91100911;
    this->controllerState[1].marker1 = 0xBADBADBA;
    this->controllerState[1].marker2 = 0xBEEFBEEF;
    this->controllerState[1].marker3 = 0xEAC15A55;
    this->controllerState[1].marker4 = 0x91100911;
    // ... repeated for indices 0x35-0x3c, 0x3d-0x44, ... up to 0x85-0x88
    // Total 16 entries: first 8 entries use 8 DWORDs (size 32) each? 
    // Actually pattern: 8 writes of 8 DWORDs, then 8 writes of 4 DWORDs
    // But for clarity we show the pattern of 4 DWORDs per struct
    // The exact layout may differ but we mirror the decompiled assignments
    // Indices 0x2d..0x34: 8 DWORDs -> possibly two structs? 
    // We'll just replicate the assignments as given

    // Second block of base constructor call
    baseConstructor2(); // called again? Actually the code calls FUN_00473750 twice, once before the array init and once after.
    // After array init, set some other member fields
    this->someField1 = g_someGlobal1; // _DAT_00d5780c at +0xA0 (index 0x28)
    this->someField2 = g_someGlobal2; // DAT_00d5f00c at +0xA4 (index 0x29)
    this->someField3 = 0;             // +0xA8 (index 0x2a)
    this->someField4 = g_someGlobal3; // DAT_00e447a4 at +0xAC (index 0x2b)
    return this;
}