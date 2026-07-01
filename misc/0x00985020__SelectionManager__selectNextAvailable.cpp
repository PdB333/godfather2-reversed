// FUNC_NAME: SelectionManager::selectNextAvailable
// Address: 0x00985020
// Role: Selects the next available item in a list, moving in a given direction (positive = forward, negative = backward).
//       Updates the current selection index and triggers selection events.

#include <cstdint>

// Global array of selection flags (3 ints per entry, first int is availability flag)
extern int32_t g_selectionList[]; // DAT_00e57608

// Global IDs for selection results
extern int32_t g_validSelectionId;   // DAT_011302b0
extern int32_t g_invalidSelectionId; // DAT_011301f8

// Forward declarations of called functions
void debugLog(const char* message, int32_t arg1, void* arg2, int32_t arg3); // FUN_005a04a0
void applySelection(void* selectionData, int32_t arg); // FUN_00408a00

class SelectionManager {
public:
    // Offset 0x50: number of items in the list
    int32_t m_itemCount;
    // Offset 0x64: currently selected index (0-based)
    int32_t m_currentSelection;

    void selectNextAvailable(int32_t direction) {
        int32_t count = *(int32_t*)((uint8_t*)this + 0x50);
        int32_t current = *(int32_t*)((uint8_t*)this + 0x64);
        int32_t loopCount = 0;

        if (count != 0) {
            // Calculate starting index based on current selection and direction
            int32_t mask = (current < 1) ? 0 : -1;
            int32_t start = count + ((current & mask) + count + direction) % count;

            do {
                int32_t idx = start % count;
                // Check if the item at idx is available (first int of the 3-int entry is 0)
                if (g_selectionList[idx * 3] == 0) {
                    if (idx != -1) {
                        // Update current selection
                        *(int32_t*)((uint8_t*)this + 0x64) = idx;
                        debugLog("UpdateSelection", 0, nullptr, 0); // FUN_005a04a0

                        // Set selection data to valid ID
                        struct SelectionData {
                            int32_t id;
                            int32_t padding[2];
                        } data;
                        data.id = g_validSelectionId;
                        data.padding[0] = 0;
                        data.padding[1] = 0;
                        applySelection(&data, 0); // FUN_00408a00
                        return;
                    }
                    break;
                }
                loopCount++;
                // Move in direction: +1 if direction >= 0, -1 if direction < 0
                start += (direction >= 0) ? 1 : -1;
            } while (loopCount < count);
        }

        // No available item found; use invalid selection ID
        struct SelectionData {
            int32_t id;
            int32_t padding[2];
        } data;
        data.id = g_invalidSelectionId;
        data.padding[0] = 0;
        data.padding[1] = 0;
        applySelection(&data, 0); // FUN_00408a00
    }
};