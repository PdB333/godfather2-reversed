// Xbox PDB: EARS_Apt_CustomSetUpScreen_ShowListing
// FUNC_NAME: FamilyManager::populateRankStore
// Address: 0x0096d420
// This function populates a rank store (list of items for each rank) for a player.
// It copies player's world position data and then iterates over available ranks
// to add selection items. It uses a global game manager singleton.

// External global: g_pGameManager (0x01129930)
extern int* g_pGameManager;

// External global: g_bInitialized (0x01223484)
extern bool g_bInitialized;

// External globals for dynamic array of rank entries
extern int g_rankArrayCount;      // DAT_01130808
extern int g_rankArrayCapacity;   // DAT_0113080c
extern int* g_rankArrayBuffer;    // DAT_01130804
extern int g_rankStoreCount;      // DAT_0113082c

// Forward declarations of called functions (not all known)
void __fastcall GameManager_InitStore(int* gameMgrPlus0xE0);  // Method at vtable+0x84
void FUN_009386b0(); // unknown
void FUN_004d3bc0(const char* string); // likely localization/log
void FUN_00407880(int size); // likely allocate memory
void FUN_004d3b50(int* data); // add entry to list
int FUN_00962e40(); // get number of ranks
void FUN_0095f870(int rank, int param); 
void FUN_0095c2d0(int rank, int* address);
void FUN_0095fbc0(int rank, int a, int b);
void FUN_005a04a0(const char* action, int a, const char* string, int b);
void FUN_0096c920(); // unknown
void FUN_0095e7d0(int val);

void __thiscall FamilyManager::populateRankStore(int* player, uint startIndex)
{
    int gameMgr = g_pGameManager;
    int* playerPtr = player; // copy of this pointer

    // Call method on player vtable at offset 0x84 (likely initialize store)
    (*(void (__thiscall**)(int*))(*(int*)player + 0x84))(g_pGameManager + 0xE0);

    // Copy position/some data from game manager to player fields
    player[0x14] = *(int*)(g_pGameManager + 0x1B8);  // +0x50: maybe worldX
    player[0x15] = *(int*)(g_pGameManager + 0x1B0);  // +0x54: worldY
    player[0x16] = *(int*)(g_pGameManager + 0x1DC);  // +0x58: worldZ
    player[0x17] = *(int*)(g_pGameManager + 0x1CC);  // +0x5C: something
    player[0x18] = *(int*)(g_pGameManager + 0x1C8);  // +0x60: something
    *(char*)(player + 0x19) = *(char*)(g_pGameManager + 0x222); // +0x64: byte

    if (g_bInitialized)
    {
        *(int*)(g_pGameManager + 0x134) = 0; // reset rank item count

        FUN_009386b0();
        FUN_004d3bc0("$rank_soldier");
        // Ensure capacity in rank array
        if (g_rankArrayCount == g_rankArrayCapacity)
        {
            int newCapacity = (g_rankArrayCapacity == 0) ? 1 : (g_rankArrayCapacity * 2);
            FUN_00407880(newCapacity * 0x10); // Reallocate with larger size (0x10 per entry?)
        }
        int currentIndex = g_rankArrayCount++;
        if (currentIndex * 0x10 + g_rankArrayBuffer != 0)
        {
            FUN_004d3b50(playerPtr); // Add player entry to array
        }

        FUN_004d3bc0("$rank_capo");
        if (g_rankArrayCount == g_rankArrayCapacity)
        {
            int newCapacity = (g_rankArrayCapacity == 0) ? 1 : (g_rankArrayCapacity * 2);
            FUN_00407880(newCapacity * 0x10);
        }
        currentIndex = g_rankArrayCount++;
        if (currentIndex * 0x10 + g_rankArrayBuffer != 0)
        {
            FUN_004d3b50(playerPtr);
        }

        FUN_004d3bc0("$rank_underboss");
        if (g_rankArrayCount == g_rankArrayCapacity)
        {
            int newCapacity = (g_rankArrayCapacity == 0) ? 1 : (g_rankArrayCapacity * 2);
            FUN_00407880(newCapacity * 0x10);
        }
        currentIndex = g_rankArrayCount++;
        if (currentIndex * 0x10 + g_rankArrayBuffer != 0)
        {
            FUN_004d3b50(playerPtr);
        }

        // Conditionally add consigliere and don ranks
        if (*(char*)(g_pGameManager + 500) != '\0') // +0x1F4: some flag (e.g., hasConsigliere?)
        {
            FUN_004d3bc0("$rank_consigliere");
            if (g_rankArrayCount == g_rankArrayCapacity)
            {
                int newCapacity = (g_rankArrayCapacity == 0) ? 1 : (g_rankArrayCapacity * 2);
                FUN_00407880(newCapacity * 0x10);
            }
            currentIndex = g_rankArrayCount++;
            if (currentIndex * 0x10 + g_rankArrayBuffer != 0)
            {
                FUN_004d3b50(playerPtr);
            }

            FUN_004d3bc0("$rank_don");
            if (g_rankArrayCount == g_rankArrayCapacity)
            {
                int newCapacity = (g_rankArrayCapacity == 0) ? 1 : (g_rankArrayCapacity * 2);
                FUN_00407880(newCapacity * 0x10);
            }
            currentIndex = g_rankArrayCount++;
            if (currentIndex * 0x10 + g_rankArrayBuffer != 0)
            {
                FUN_004d3b50(playerPtr);
            }
            *(int*)(g_pGameManager + 0x1BC) = g_rankArrayCount - 1; // store last index
        }

        // If player flag (byte at player[0x13] low byte) is set, update global indices
        if (*(char*)(player + 0x13) != '\0') // +0x4C: byte flag
        {
            *(int*)(g_pGameManager + 0x1D0) = g_rankStoreCount - 1;
            *(int*)(g_pGameManager + 0x1BC) = g_rankArrayCount - 1;
        }

        // Now iterate over all ranks and add selection items
        int totalRanks = FUN_00962e40();
        for (uint rankIdx = startIndex; rankIdx < totalRanks + startIndex; rankIdx++)
        {
            // Set a flag based on rank index and some condition
            if (((rankIdx == 0) || (rankIdx == 5) || (rankIdx == 6) || (rankIdx == 9)) &&
                (*(int*)(g_pGameManager + 0xDC) == 3))
            {
                *(char*)(g_pGameManager + 0xD0) = 0;  // disable something
            }
            else
            {
                *(char*)(g_pGameManager + 0xD0) = 1;  // enable something
            }

            if (rankIdx == 6)
            {
                if (*(char*)(g_pGameManager + 500) != '\0')
                {
                    goto LAB_disableFlag;
                }
            }
            else if ((rankIdx == 9) && (*(char*)(g_pGameManager + 500) == '\0'))
            {
                goto LAB_disableFlag;
            }

            // Call functions to add selectable items for this rank
            FUN_0095f870(rankIdx, *(int*)(g_pGameManager + 0xEC));
            FUN_0095c2d0(rankIdx, g_pGameManager + 0x140);
            FUN_0095fbc0(rankIdx, *(int*)(g_pGameManager + 200), *(int*)(g_pGameManager + 0xCC));

            FUN_005a04a0("AddSelectItem", 0, &DAT_00d8cdec, 0);
            (*(int*)(g_pGameManager + 0x134))++; // increment item count

            LAB_0096d74c:
            ; // fallthrough from goto

        } // end for

        *(char*)(g_pGameManager + 0xD0) = 1; // reset flag after loop
    } // end if g_bInitialized

    FUN_0096c920();
    FUN_005a04a0("ItemsAdded", 0, &DAT_00d8cdec, 0);
    FUN_0095e7d0(*(int*)(g_pGameManager + 0xD4) + *(int*)(g_pGameManager + 0xC4));
}