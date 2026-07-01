// FUNC_NAME: DonControlGadget::enterDonSitdown
void __thiscall DonControlGadget::enterDonSitdown(int* thisPtr, Player* player)
{
    // Global singleton (probably DonControlManager or NetSession)
    int* globalManager = DAT_01223484;

    // Validate inputs
    if (player != nullptr && globalManager != nullptr)
    {
        // Player position from offsets 0xF0 and 0xF4 (likely Vec2 or Vec3 x/y)
        float playerPosX = *(float*)(player + 0xF0);  // +0xF0: player position X
        float playerPosY = *(float*)(player + 0xF4);  // +0xF4: player position Y

        // Call to start the sitdown animation/state
        // FUN_008b60e0 signature: void __cdecl someFunction(const char* name, const Vec2* pos, int playerId, int timeoutMs, int extra)
        // DAT_00962f40 likely a string name (e.g., "don_sitdown")
        FUN_008b60e0(
            &DAT_00962f40,        // Animation name or state key
            &playerPosX,          // Position pointer
            *(int*)(player + 0x100), // Player ID or some index (+0x100)
            thisPtr[0x17],       // this->timeoutDuration (+0x5C = 0x17 * 4)
            10000                // Default timeout 10 seconds
        );

        // Call virtual method at vtable offset 0x0C (e.g., onStartSitdown)
        (*(void (**)(DonControlGadget*))(*(int*)thisPtr + 0x0C))(thisPtr);

        // Notify multiplayer system about the sitdown
        FUN_00983120("$mp_online_enter_don_sitdown", 0, 0); // Probably a UI event or network message

        // Set state to 2 (e.g., SITDOWN_ACTIVE)
        thisPtr[0x79] = 2;            // +0x1E4 = state field

        // Store player data
        thisPtr[0x67] = *(int*)(player + 0x100); // +0x19C = playerId/slot
        thisPtr[0x68] = *(int*)(player + 0xFC);  // +0x1A0 = some other player attribute (team/crew?)

        // Call virtual method on the global manager (vtable offset 0x80)
        (*(void (**)(int*))(*(int*)globalManager + 0x80))(globalManager);
    }
}