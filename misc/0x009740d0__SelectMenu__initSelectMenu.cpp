// FUNC_NAME: SelectMenu::initSelectMenu

#include <cstdint>

// Reconstructed structure for the 9-byte resource initialization block?
struct ResourceInitBlock {
    int32_t field_0;      // +0x00
    int32_t field_4;      // +0x04
    uint8_t field_8;      // +0x08
};

// Global data references
extern int32_t DAT_01130378;   // resource ID or filename
extern int32_t DAT_0112b56c;   // another resource ID
extern int32_t DAT_00e574c8[]; // array of structures: each entry is 12 bytes? (3 int32s)

// External functions (reconstructed names)
void loadResource(void* block, int32_t mode);     // FUN_00408a00
void clearState();                                 // FUN_0093c210
void setDisplayMode(int32_t mode);                // FUN_0081dd40
void registerInitFunction(const char* name, int32_t param1, const char* param2, int32_t param3); // FUN_005a04a0

void __fastcall SelectMenu::initSelectMenu(SelectMenu* thisPtr)
{
    // Offsets relative to thisPtr
    // +0x64 (100): initialized flag (bool)
    // +0x50: number of menu entries
    // +0x60: currently selected index (-1 means none)
    uint8_t& initFlag = *(uint8_t*)((uint8_t*)thisPtr + 100);  // +0x64
    int32_t& entryCount = *(int32_t*)((uint8_t*)thisPtr + 0x50);
    int32_t& selectedIndex = *(int32_t*)((uint8_t*)thisPtr + 0x60);

    initFlag = 1;  // Mark initialization as started

    // Load first resource (likely background sound/music)
    ResourceInitBlock block1;
    block1.field_0 = DAT_01130378;
    block1.field_4 = 0;
    block1.field_8 = 0;
    loadResource(&block1, 0);

    // Reset some state
    clearState();

    // Set display mode to something (2 = menu?)
    setDisplayMode(2);

    // Load second resource (perhaps highlight sound)
    ResourceInitBlock block2;
    block2.field_0 = DAT_0112b56c;
    block2.field_4 = 0;
    block2.field_8 = 0;
    loadResource(&block2, 0);

    // Process menu entries array (starts at DAT_00e574c8)
    uint32_t firstAvailableIndex = 0xFFFFFFFF;  // will store index of first disabled (available) entry
    uint32_t entryIndex = 0;

    if (entryCount != 0) {
        int32_t* entryArray = &DAT_00e574c8;  // each entry is 3 int32s (12 bytes)
        do {
            int32_t newState;
            switch (entryArray[0]) {  // entry type field?
                case 0:
                case 1:
                case 2:
                case 3:
                    newState = 0;  // Available/Enabled
                    break;
                default:
                    newState = 2;  // Locked/Disabled
                    break;
            }
            entryArray[2] = newState;  // Set state field

            // Remember first entry with state 0
            if ((firstAvailableIndex == 0xFFFFFFFF) && (newState == 0)) {
                firstAvailableIndex = entryIndex;
            }

            entryIndex++;
            entryArray += 3;  // Move to next entry
        } while (entryIndex < (uint32_t)entryCount);
    }

    // If no selection is set yet and we found an available entry, select it
    if ((selectedIndex == -1) && (firstAvailableIndex != 0xFFFFFFFF)) {
        selectedIndex = firstAvailableIndex;
    }

    // Register the "InitSelectMenu" callback with the engine
    registerInitFunction("InitSelectMenu", 0, &DAT_00d8f604, 0);

    return;
}