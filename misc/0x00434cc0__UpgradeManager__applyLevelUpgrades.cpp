// FUNC_NAME: UpgradeManager::applyLevelUpgrades
uint* UpgradeManager::applyLevelUpgrades() {
    // Get pointer to upgrade state structure (global or per-player)
    uint* upgradeState = getUpgradeState();  // FUN_004345d0
    if (upgradeState == nullptr) {
        return nullptr;
    }

    uint currentLevel = upgradeState[0];               // +0x00: current player level
    uint* upgradeSlots = (uint*)upgradeState[1];       // +0x04: base pointer to upgrade slot array

    // Apply upgrades based on level thresholds (values 1 = unlock, 2 = upgrade to rank 2)
    if (currentLevel > 26) {
        *(int*)((uint8*)upgradeSlots + 0x4e0) = 1;   // unlock slot at offset 0x4e0
    }
    if (currentLevel > 8) {
        *(int*)((uint8*)upgradeSlots + 0x180) = 1;    // unlock slot at offset 0x180
    }
    if (currentLevel > 9) {
        *(int*)((uint8*)upgradeSlots + 0x1b0) = 1;    // unlock slot at offset 0x1b0
    }
    if (currentLevel > 12) {
        *(int*)((uint8*)upgradeSlots + 0x240) = 1;    // unlock slot at offset 0x240
    }
    if (currentLevel > 17) {
        *(int*)((uint8*)upgradeSlots + 0x330) = 2;    // upgrade slot at offset 0x330 to rank 2
    }
    if (currentLevel > 10) {
        *(int*)((uint8*)upgradeSlots + 0x1e0) = 2;    // upgrade slot at offset 0x1e0 to rank 2
    }
    if (currentLevel > 13) {
        *(int*)((uint8*)upgradeSlots + 0x270) = 2;    // upgrade slot at offset 0x270 to rank 2
    }
    if (currentLevel > 16) {
        *(int*)((uint8*)upgradeSlots + 0x300) = 2;    // upgrade slot at offset 0x300 to rank 2
    }
    if (currentLevel > 18) {
        *(int*)((uint8*)upgradeSlots + 0x360) = 2;    // upgrade slot at offset 0x360 to rank 2
    }
    if (currentLevel > 19) {
        *(int*)((uint8*)upgradeSlots + 0x390) = 2;    // upgrade slot at offset 0x390 to rank 2
    }
    if (currentLevel > 20) {
        *(int*)((uint8*)upgradeSlots + 0x3c0) = 2;    // upgrade slot at offset 0x3c0 to rank 2
    }
    if (currentLevel > 21) {
        *(int*)((uint8*)upgradeSlots + 0x3f0) = 2;    // upgrade slot at offset 0x3f0 to rank 2
    }
    if (currentLevel > 22) {
        *(int*)((uint8*)upgradeSlots + 0x420) = 2;    // upgrade slot at offset 0x420 to rank 2
    }
    if (currentLevel > 15) {
        *(int*)((uint8*)upgradeSlots + 0x2d0) = 1;    // unlock slot at offset 0x2d0
    }
    if (currentLevel > 12) {
        // Set function pointer at offset 0x248 to callback (0x00434c90)
        *(int (**)())((uint8*)upgradeSlots + 0x248) = (int (*)())0x00434c90;
        *(int*)((uint8*)upgradeSlots + 0x250) = 0;    // argument for callback
    }
    if (currentLevel > 12) {
        // Set function pointer at offset 0x264 to callback (0x00434c90)
        *(int (**)())((uint8*)upgradeSlots + 0x264) = (int (*)())0x00434c90;
        *(int*)((uint8*)upgradeSlots + 0x26c) = -1;   // argument for callback
    }

    // Return upgrade state only if all thresholds are met (level > 26)
    if (currentLevel > 26) {
        return upgradeState;
    }
    return nullptr;
}