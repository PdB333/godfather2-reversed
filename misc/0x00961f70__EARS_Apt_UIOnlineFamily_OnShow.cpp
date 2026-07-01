// Xbox PDB: EARS_Apt_UIOnlineFamily_OnShow
// FUNC_NAME: NetSession::populatePlayerList
void __thiscall NetSession::populatePlayerList(void* thisPtr) {
    uint playerIndex = 0;
    *(int*)((char*)thisPtr + 0x58) = 0; // clear player count

    // Log: clear players
    FUN_005a04a0("ClearPlayers", 0, &DAT_00d8d914, 0);

    // Get total number of players from the session interface
    uint totalPlayers = (**(code (__thiscall**)(void*))(**(int**)((char*)thisPtr + 0x50) + 0x40))(
        *(void**)((char*)thisPtr + 0x50));

    // Get the current player pointer from the session interface
    int* currentPlayer = (int*)(**(code (__thiscall**)(void*))(**(int**)((char*)thisPtr + 0x50) + 0x28))(
        *(void**)((char*)thisPtr + 0x50));

    if (totalPlayers != 0) {
        do {
            // Get the player at index playerIndex
            int* playerAtIdx = (int*)(**(code (__thiscall**)(void*))(**(int**)((char*)thisPtr + 0x50) + 0x44))(
                *(void**)((char*)thisPtr + 0x50));

            // Get the player's name buffer (size 0x80)
            char* nameBuffer = (char*)(**(code (__thiscall**)(void*))(**(int**)(*playerAtIdx) + 8))(
                *playerAtIdx);
            // Allocate a temporary buffer for the name
            void* tempName = (**(code (__thiscall**)(int, int))(**(int**)(*playerAtIdx) + 4))(0x80, 0);

            // Add the player to the local list (param_1+0x54 is the list)
            FUN_005c4660(*(void**)((char*)thisPtr + 0x54), tempName);

            // Get the player's actual name string
            char* playerName = (char*)(**(code (__thiscall**)(void*))(**(int**)(*playerAtIdx) + 8))(
                *playerAtIdx);
            char* nameStr = (char*)(**(code (__thiscall**)(void*))(**(int**)(*playerAtIdx) + 4))(
                FUN_00564830()); // FUN_00564830 likely returns a string ID or pointer

            // Compare the name with a constant string (likely "0x80" or a marker)
            int cmpResult = _strncmp(nameStr, (char*)0x80, playerIndex);
            char* addType = "AddUser";
            if (cmpResult != 0) {
                addType = "AddPlayer";
            }

            // If the current player pointer matches the one at this index, record it
            if (currentPlayer == playerAtIdx) {
                *(uint*)((char*)thisPtr + 0x5c) = playerIndex; // store local player index
            }

            // Log the addition
            FUN_005a04a0(addType, 0, &DAT_00d8d914, 0);

            playerIndex++;
        } while (playerIndex < totalPlayers);
    }

    // Log: show players
    FUN_005a04a0("ShowPlayers", 0, &DAT_00d8d914, 0);
}