// FUNC_NAME: MultiplayerMenuManager::onItemRollOver
// 0x00918cb0 - Handles mouse hover/rollover on menu items in the multiplayer menu (comm screen).
// It checks if the hovered path matches button paths (0-2) or various content item sub-paths.
// Depending on the current state (offset 0xb8), it either checks predefined specialty paths or generic item paths.
// When a match is found, it sends UI events like "RollOverButton" or "RollOverSelection" and updates ranking text.

#include <cstring>

// Forward declarations of helper functions (not provided, but named based on usage)
void formatString(char* dest, const char* format, ...); // FUN_00910160
void sendUIEvent(const char* eventName, int unk1, const char* category, int unk2, void* data); // FUN_005a04a0
void playSound(int soundId, int unk); // FUN_00402050
int getNumItems(); // FUN_009185a0 (returns number of items in the current submenu)
void formatItemPath(void* data, const char* format, int index); // FUN_00910180
void updateRankingComponent(int basePtr, int param2, int param3); // FUN_00918940
void playGenericSound(int handle, int mode); // FUN_00408a00

bool MultiplayerMenuManager::onItemRollOver(const char* path) {
    char formattedPath[64];
    bool found = false;
    int itemIndex = 0;

    // First, check if the hovered path matches one of the 3 button paths (0,1,2)
    for (int btn = 0; btn <= 2; btn++) {
        formatString(formattedPath, "/comm/buttons/button_%d/button", btn);
        if (strcmp(formattedPath, path) == 0) {
            formatString(formattedPath, "item%d", btn); // Format something like "item0" (DAT_00e3266c is "item%d")
            sendUIEvent("RollOverButton", 0, "mcMain", 1, formattedPath);
            playSound(0x011301c0, 0);
            found = true;
            break;
        }
    }

    // If not found and the state is in a certain range (offset 0xb8 - 10 < 0x10, i.e., 10 to 25)
    // This branch handles the lobby or matchmaking submenu with specialty rows.
    int state = *(int*)((uint8_t*)this + 0xb8); // +0xB8: current menu state enum
    if (state >= 10 && state <= 25) {
        int numSpecialtyItems = reinterpret_cast<int>(getNumItems()); // Actually returns a count
        int unk = *reinterpret_cast<int*>((uint8_t*)this + 0xec); // +0xEC: number of specialty items? unused here
        // Note: param_2 is reused as local loop limit; original code reused the input pointer variable.
        // We'll use a local variable.
        unsigned int specialtyCount = (unsigned int)numSpecialtyItems; // Number of specialty slots (from getNumItems)
        if (!found) {
            for (unsigned int i = 0; i < specialtyCount; i++) {
                if (found) return true; // Early exit if found in a previous iteration? Actually the loop condition checks found.
                // Check each possible specialty path for this item index
                const char* pathsToCheck[] = {
                    "/comm/mcMain/content_mc/item%d/overallRow_hspt",
                    "/comm/mcMain/content_mc/item%d/gameModesRow_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_17_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_18_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_19_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_20_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_21_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_22_hspt",
                    "/comm/mcMain/content_mc/item%d/speciality_23_hspt",
                    "/comm/mcMain/content_mc/item%d/combatRow_hspt"
                };
                for (int p = 0; p < 10; p++) {
                    formatString(formattedPath, pathsToCheck[p], i);
                    if (strcmp(formattedPath, path) == 0) {
                        // Found a match – send "RollOverSelection" event with the item index
                        formatItemPath(&path, "item%d", i); // Reuse path variable? Actually the decompiler used &param_2
                        // In original, param_2 is overwritten. We'll use a temporary.
                        char temp[64];
                        formatString(temp, "item%d", i);
                        sendUIEvent("RollOverSelection", 0, "mcMain", 1, temp);
                        // Then update ranking component and text
                        int* basePtr = (int*)((uint8_t*)this + 0xb4); // +0xB4: base of some component
                        int* ptr0xf0 = (int*)((uint8_t*)this + 0xf0); // +0xF0: pointer to ranking text?
                        updateRankingComponent(*basePtr + *(int*)((uint8_t*)this + 0xc0), *ptr0xf0, 0x80);
                        sendUIEvent("UpdateRankingText", 0, "mcMain", 1, *ptr0xf0);
                        playSound(0x011301c0, 0);
                        found = true;
                        break;
                    }
                }
            }
        }
    } else {
        // For other states (like main menu or submenu selection)
        int numItems = *(int*)((uint8_t*)this + 0xec); // +0xEC: number of items in current list
        for (unsigned int i = 0; i < (unsigned int)numItems && !found; i++) {
            formatString(formattedPath, "/comm/mcMain/content_mc/item%d/item_hspt", i);
            if (strcmp(formattedPath, path) == 0) {
                // Build the item identifier and send rollover event
                char itemId[64];
                formatString(itemId, "item%d", i);
                sendUIEvent("RollOverSelection", 0, "mcMain", 1, itemId);
                // Play a sound with different parameters?
                int soundData[3] = { 0x011301c0, 0, 0 }; // local_4c, local_48, local_44
                playGenericSound(soundData, 0);
                found = true;
            }
        }
    }
    return found;
}