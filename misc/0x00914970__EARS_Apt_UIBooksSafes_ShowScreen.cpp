// Xbox PDB: EARS_Apt_UIBooksSafes_ShowScreen
// FUNC_NAME: BuildingManager::populateSafesDebugScreen
// Address: 0x00914970
// Purpose: Populates a debug screen listing building safe groups and their safe states.

#include <cstdint>

// Forward declarations of engine functions
void DebugPrint(const char* format, int arg1, int* context, int arg3, ...);
const char* GetLocalizedString(int unknown); // FUN_00849530
const char* GetSafeLocalizedName();          // FUN_006b2160
bool IsSafeClosed();                         // FUN_006b4440

// Global building manager pointer (DAT_0112a66c)
extern BuildingManager* g_pBuildingManager;

// Building structure offsets (likely)
// +0x10: array of Building pointers? Actually piVar9 = (int*)(g_pBuildingManager+0x10)
// +0x14: count of buildings? Actually *(int*)(g_pBuildingManager+0x14)
// Building object offsets (based on usage):
// +0x58: flags byte (bit0? used with complement)
// +0x94: pointer to array of safe entries
// +0x98: count of safe entries
// Safe entry offsets:
// +0x34: uint flags (bit9 = isSafe? bit26 = isOpen?)

void __fastcall populateSafesDebugScreen(int* pOutCounts)
{
    int buildingIndex = 0;
    int safeGroupCount = 0;

    // Start the debug screen
    DebugPrint("ShowScreen", 0, &DAT_00d84448, 1, "Safes");

    *pOutCounts = 0;
    pOutCounts[1] = 0;

    // g_pBuildingManager is at DAT_0112a66c
    BuildingManager* manager = reinterpret_cast<BuildingManager*>(DAT_0112a66c);
    if (manager == nullptr)
        return;

    // Get pointer to building array: manager + 0x10
    int** buildingArray = reinterpret_cast<int**>(reinterpret_cast<uint8_t*>(manager) + 0x10);
    int buildingCount = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(manager) + 0x14);

    if (buildingCount <= 0)
        goto show;

    do
    {
        int* building = *reinterpret_cast<int**>(&buildingArray[buildingIndex]);
        if (building != nullptr)
        {
            // Check flag: complement of bit0 at +0x58
            uint8_t flags = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(building) + 0x58);
            bool hasKnownLocation = (~flags & 1) == 0; // bVar5
            const char* groupName;

            if (!hasKnownLocation)
            {
                groupName = "$dv_mono_unknown_loc";
            }
            else
            {
                // Get localized building name
                int* localizedPtr = reinterpret_cast<int*>(GetLocalizedString()); // FUN_00849530
                groupName = reinterpret_cast<const char*>(*localizedPtr);
                if (groupName == nullptr)
                    groupName = &DAT_0120546e; // fallback empty string?
            }

            // Add group header
            DebugPrint("SafesSetGroup", 0, &DAT_00d84448, 2, groupName, &DAT_00e2f044);

            // Iterate over safe entries
            int safeCount = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(building) + 0x98);
            int* safeArray = *reinterpret_cast<int**>(reinterpret_cast<uint8_t*>(building) + 0x94);
            int safeIndex = 0;
            int safeAdded = 0;

            if (safeCount > 0 && safeArray != nullptr)
            {
                do
                {
                    int* safeEntry = reinterpret_cast<int*>(safeArray[safeIndex]);
                    if (safeEntry != nullptr)
                    {
                        uint32_t safeFlags = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(safeEntry) + 0x34);

                        // Check if this entry is a safe (bit9)
                        if ((safeFlags >> 9) & 1)
                        {
                            const char* safeName;
                            const char* statusText;

                            // Check if safe is open (bit26)
                            if (!((safeFlags >> 0x1a) & 1))
                            {
                                // Closed or unknown
                                if (hasKnownLocation && !IsSafeClosed()) // FUN_006b4440 returns true if closed
                                {
                                    safeName = "Unknown";
                                    statusText = "$dv_mono_unknown_loc";
                                }
                                else
                                {
                                    int* localizedPtr2 = reinterpret_cast<int*>(GetSafeLocalizedName()); // FUN_006b2160
                                    safeName = reinterpret_cast<const char*>(*localizedPtr2);
                                    if (safeName == nullptr)
                                        safeName = &DAT_0120546e;
                                    statusText = "Closed";
                                }
                            }
                            else
                            {
                                // Open
                                int* localizedPtr2 = reinterpret_cast<int*>(GetSafeLocalizedName()); // FUN_006b2160
                                safeName = reinterpret_cast<const char*>(*localizedPtr2);
                                if (safeName == nullptr)
                                    safeName = &DAT_0120546e;
                                statusText = "Open";
                            }

                            // Add item to list
                            DebugPrint("SafesAddItem", 0, &DAT_00d84448, 2, statusText, safeName);
                            safeAdded++;
                        }
                    }
                    safeIndex++;
                } while (safeIndex < safeCount);
            }

            *pOutCounts += 1;                  // Increment group count
            pOutCounts[1] += safeAdded;        // Increment total safe count
        }
        buildingIndex++;
    } while (buildingIndex < buildingCount);

show:
    DebugPrint("SafesShowScreen", 0, &DAT_00d84448, 0);
}