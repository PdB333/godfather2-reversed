// FUNC_NAME: EntityDataLoader::loadTransformFromDataTable
// Function address: 0x00917d80
// Reads position/rotation data from a data table and stores into entity fields.
// Also retrieves an additional value from a game manager singleton.

void __thiscall EntityDataLoader::loadTransformFromDataTable(
    int* thisPtr,                    // +0x00 this
    int unused,                      // param_2 not used
    DataTable* pDataTable,           // param_3 data source
    uint32_t keyX,                   // param_4 key for X component
    uint32_t keyY,                   // param_5 key for Y component
    uint32_t keyZ)                   // param_6 key for Z component
{
    char buffer[64];                 // local_284
    char floatBuffer[64];            // local_144
    int intValue;                    // local_294
    int someInt;                     // local_290
    float floatValue;                // local_104
    int tempInt;                     // local_29c
    int arg1, arg2;                  // local_28c, local_288

    intValue = 0;
    buffer[0] = 0;
    floatBuffer[0] = 0;
    floatValue = 0.0f;
    someInt = 0;
    arg1 = 0;
    arg2 = 0;

    // Read an integer property from the data table
    if (dataTableGetInt(pDataTable, &intValue)) {
        stringClear(buffer);         // clear buffer (unused)
        if (someInt > 0) {
            thisPtr[0x2c / 4] = someInt;   // +0x2c: some integer field
        }
    }

    // Read X component as float
    uint32_t hashX = stringHash(keyX);
    if (dataTableGetFloat(pDataTable, hashX, floatBuffer)) {
        tempInt = (int)(floatValue + 0.5f); // rounding
        thisPtr[0x14 / 4] = tempInt;        // +0x14: X position/rotation
    }

    // Read Y component as float
    uint32_t hashY = stringHash(keyY);
    if (dataTableGetFloat(pDataTable, hashY, floatBuffer)) {
        tempInt = (int)(floatValue + 0.5f);
        thisPtr[0x18 / 4] = tempInt;        // +0x18: Y
    }

    // Read Z component as float
    uint32_t hashZ = stringHash(keyZ);
    if (dataTableGetFloat(pDataTable, hashZ, floatBuffer)) {
        tempInt = (int)(floatValue + 0.5f);
        thisPtr[0x1c / 4] = tempInt;        // +0x1c: Z
    }

    // Get a value from a game manager singleton
    GameManager* pManager = getGameManager();
    if (pManager != nullptr) {
        SomeSubsystem* pSub = pManager->getSubsystem(); // vtable+0x48
        if (pSub != nullptr) {
            uint32_t result = pSub->getValue(arg1, arg2); // vtable+0x18
            thisPtr[0x10 / 4] = result;                   // +0x10: some ID or handle
        }
    }
}