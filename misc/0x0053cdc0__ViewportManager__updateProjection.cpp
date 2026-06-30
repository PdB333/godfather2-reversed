// FUNC_NAME: ViewportManager::updateProjection
void ViewportManager::updateProjection()
{
    // Global array of per-player viewport data (size 0x2c per entry)
    // DAT_01125c58 is base, DAT_01125d78 is current player index
    int* playerDataBase = (int*)0x01125c58;
    int playerIndex = *(int*)0x01125d78; // current player index
    int* playerData = &playerDataBase[playerIndex * 0x2c / 4]; // offset by 0x2c per entry

    // Check first field (offset +0x00)
    if (playerData[0] != 0) {
        FUN_006063b0(); // likely a render setup function
    }

    // Check second field (offset +0x04)
    if (playerData[1] != 0) {
        // unaff_ESI is a register parameter (likely a handle or ID)
        // It is not declared in the decompiled signature; assume it's passed in ESI
        uint handle = unaff_ESI; // from register ESI

        // Array of handle data structures (size 0x38 per entry)
        // DAT_011a0f28 is base
        byte* handleDataBase = (byte*)0x011a0f28;
        byte* handleData = nullptr;
        if (handle < 0x1000) {
            handleData = handleDataBase + handle * 0x38;
        }

        // Global scaling factors
        float screenWidth = *(float*)0x00e2b1a4; // e.g., 1280.0f
        float screenHeight = *(float*)0x00e2b1a4; // same? Actually DAT_00e2b1a4 used twice
        float scaleFactor = *(float*)0x00e2cd54; // some global scale

        // Read ushort values from handle data at offsets +0x02 and +0x04
        ushort widthDivisor = *(ushort*)(handleData + 2);
        ushort heightDivisor = *(ushort*)(handleData + 4);

        float local_20 = screenWidth / (float)widthDivisor;
        float local_1c = screenHeight / (float)heightDivisor;
        float local_18 = local_20 * scaleFactor;
        float local_14 = local_1c * scaleFactor;

        // Call projection setup with a pointer to the four floats
        // DAT_01125ba4 is likely a render context pointer
        FUN_0060add0(*(int*)0x01125ba4, playerData[1], &local_20);
    }
}