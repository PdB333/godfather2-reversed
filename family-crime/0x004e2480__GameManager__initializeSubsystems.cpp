// FUNC_NAME: GameManager::initializeSubsystems
void GameManager::initializeSubsystems(void)
{
    int iVar1;
    byte *pbVar3;
    uint uVar4;
    undefined4 uStack_4;

    // Reset global flag
    g_SomeFlag = 0;

    // Determine index into configuration table
    uVar4 = g_ConfigIndex;
    if (g_ConfigPtr != 0) {
        uVar4 = *(uint *)(g_ConfigPtr + 0x16c); // +0x16c: some config field
    }

    // Get pointer to configuration entry (stride 0x38)
    undefined1 *puVar2;
    if (uVar4 < 0x1000) {
        puVar2 = &g_ConfigTable + uVar4 * 0x38;
    } else {
        puVar2 = (undefined1 *)0x0;
    }

    // Initialize subsystems
    FUN_004e1dd0(*(undefined2 *)(puVar2 + 2), *(undefined2 *)(puVar2 + 4)); // e.g., screen resolution
    FUN_004e2250(); // e.g., renderer setup
    FUN_005332e0(); // e.g., audio
    FUN_004eebd0(); // e.g., input

    // Set global pointers to static data
    g_SomePtr1 = DAT_00e446c0;
    g_SomePtr2 = DAT_00e2b050;
    g_SomeCounter = 0;
    g_SomePtr3 = 0;
    g_SomePtr4 = DAT_00e2b1a4;
    g_SomeVec1.x = 0;
    g_SomeVec1.y = 0;
    g_SomeVec1.z = DAT_00e2b1a4;
    g_SomeVec1.w = DAT_00e2b1a4;
    g_SomeFlag2 = 1;

    // More subsystem initializations
    FUN_00517870(); // e.g., physics
    FUN_00514af0(); // e.g., AI
    FUN_00531cc0(); // e.g., streaming
    g_SomeFlag3 = 1;
    FUN_0052e4b0(); // e.g., UI
    FUN_00527fa0(); // e.g., missions
    FUN_0052b900(); // e.g., vehicles
    FUN_005261d0(); // e.g., weapons
    FUN_00527890(); // e.g., characters
    FUN_00511fa0(); // e.g., networking
    FUN_00505b30(); // e.g., audio
    FUN_0051e8e0(); // e.g., effects

    // Initialize controller/device list
    uVar4 = 0;
    uStack_4 = CONCAT31(uStack_4._1_3_, 0x80); // Build a value with low byte 0x80

    if (g_DeviceCount != 0) {
        pbVar3 = &g_DeviceList; // Array of 0xC-byte entries
        do {
            if (0x80 < *pbVar3) { // Check first byte (device type?)
                FUN_00609bf0(); // Error handler
                return;
            }
            uVar4 = uVar4 + 1;
            pbVar3 = pbVar3 + 0xc;
        } while (uVar4 < g_DeviceCount);
    }

    // Add a new device entry if space remains (max 0x20)
    if (g_DeviceCount < 0x20) {
        iVar1 = g_DeviceCount * 0xc;
        *(undefined8 *)(&g_DeviceList + g_DeviceCount * 3) = 0x4e3bc0004e3ba0; // Two 4-byte values packed
        *(undefined4 *)(&g_DeviceList + iVar1) = uStack_4; // Low byte 0x80
        g_DeviceCount = g_DeviceCount + 1;
    }

    return;
}