// FUNC_NAME: SimManager::staticInitialize
void SimManager::staticInitialize()
{
    // +4: Initialize function from vtable at gSimManagerVTable (DAT_0121b740)
    uint32_t initResult = (*(code **)(gSimManagerVTable + 4))();

    // Store result of FUN_0060d740 (likely a handle/ID) into global
    gSimManagerHandle = FUN_0060d740(initResult); // _DAT_0121b748

    // +0x10: Finalize function from vtable
    (*(code **)(gSimManagerVTable + 0x10))();

    // Preserve previous singleton pointer (DAT_012058ec)
    gPreviousSimManagerPtr = gSimManagerSingletonPtr;

    // Increment reference count
    gSimManagerRefCount++; // DAT_012058f8

    // Initialize three fields with constant (DAT_00e2b1a4, likely -1 or 0)
    gSimManagerValue1 = DAT_00e2b1a4; // DAT_01219200
    gSimManagerValue2 = DAT_00e2b1a4; // DAT_01219204
    gSimManagerValue3 = DAT_00e2b1a4; // DAT_01219208

    // Set singleton pointer to address of vtable base
    gSimManagerSingletonPtr = &gSimManagerVTable; // DAT_012058ec

    // Store reference count as timestamp
    gSimManagerTimestamp = gSimManagerRefCount; // _DAT_0121b74c

    // Zero out 8 flag bytes (0x012191ec..0x0121920c)
    gSimManagerFlags[0] = 0; // _DAT_012191ec
    gSimManagerFlags[1] = 0; // _DAT_012191e8
    gSimManagerFlags[2] = 0; // _DAT_012191e4
    gSimManagerFlags[3] = 0; // _DAT_012191e0
    gSimManagerFlags[4] = 0; // _DAT_012191fc
    gSimManagerFlags[5] = 0; // _DAT_012191f8
    gSimManagerFlags[6] = 0; // _DAT_012191f4
    gSimManagerFlags[7] = 0; // _DAT_012191f0

    // Zero out next group (0x0121920c, 0x0121921c, 0x01219218, 0x01219214, 0x01219210, 0x01219220, 0x0121922c)
    gSimManagerFlag9   = 0; // _DAT_0121920c
    gSimManagerFlag10  = 0; // _DAT_0121921c
    gSimManagerInt1    = 0; // DAT_01219218
    gSimManagerInt2    = 0; // DAT_01219214
    gSimManagerInt3    = 0; // DAT_01219210
    gSimManagerInt4    = 0; // DAT_01219220
    gSimManagerInt5    = 0; // DAT_0121922c

    // Initialize with DAT_00e2eb58 (another constant)
    gSimManagerInt6    = DAT_00e2eb58; // DAT_01219224
    gSimManagerInt7    = DAT_00e2eb58; // DAT_01219228

    // Zero out remaining
    gSimManagerInt8    = 0; // DAT_01219230
    gSimManagerInt9    = 0; // DAT_01219240
}