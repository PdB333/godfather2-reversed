// FUNC_NAME: MenuManager::processAction
// Function at 0x00957b70: Handles input actions for menu navigation. Dispatches to submenu handlers or processes global actions (confirm, cancel, navigation).
#include <cstdint>

// Forward declarations for called functions (guessed names based on EA EARS patterns)
void startFadeIn(int value);               // FUN_00957780
void closeMenu();                          // FUN_00956e50
void moveSelection(int direction);         // FUN_009577d0, direction = -1 (up) or 1 (down)
void movePage(int direction);              // FUN_009569d0, direction = 1 (next) or -1 (previous)
void executeSelection();                   // FUN_00957880
bool isItemSelectable();                   // FUN_00976440
void triggerItem(int param);               // FUN_00402050
void debugLogConsole(const char* buffer, int mode); // FUN_00408a00
int getConfirmAction();                    // FUN_00466840
int getCancelAction();                     // FUN_00466860

extern uint DAT_01130448;                  // Global data reference (likely a string constant)

int __thiscall MenuManager::processAction(int actionId) {
    uint result = 0;
    // Flag at +0x50 indicates whether we are in a submenu (1) or main menu (0)
    if (*(char*)(this + 0x50) == 0) {
        // Main menu level
        // +0x6c holds the index of the current submenu handler (0 when no submenu active)
        if (actionId == 10 && *(int*)(this + 0x6c) == 0) {
            // Action 10 (typically "back") when no submenu active -> exit menu
            startFadeIn(1);
            closeMenu();
            return 0;
        }
        // Skip actions 2 and 4 (possibly reserved for movement/input types)
        if (actionId != 2 && actionId != 4) {
            // Delegate to the current submenu's virtual handler
            // +0x54 holds pointer to an array of submenu handler objects
            int* handlerArray = *(int**)(this + 0x54);
            int submenuIndex = *(int*)(this + 0x6c);
            int* handlerObject = (int*)handlerArray[submenuIndex];
            int vtable = *handlerObject;
            // Offset 0x68 in the vtable is the handler function for action input
            int handlerFunc = *(int*)(vtable + 0x68);
            result = ((int(__thiscall*)(int, int))handlerFunc)((int)handlerObject, actionId);
        }
    } else {
        // Submenu active
        int confirmAction = getConfirmAction();
        if (actionId == confirmAction) {
            // Confirm action triggered
            struct {
                uint data1; // initialised from DAT_01130448
                uint data2; // zero
                char data3; // zero
            } debugBuffer;
            debugBuffer.data1 = DAT_01130448;
            debugBuffer.data2 = 0;
            debugBuffer.data3 = 0;
            debugLogConsole((const char*)&debugBuffer, 0);
            closeMenu();
            return 0;
        }
        int cancelAction = getCancelAction();
        if (actionId == cancelAction) {
            bool canSelect = isItemSelectable();
            if (!canSelect) {
                closeMenu();
                executeSelection();
                return 0;
            }
            triggerItem(0);
            return 0;
        }
        switch (actionId) {
        case 0:
            return 1; // Consumed but no operation
        case 2:
        case 6:
            moveSelection(0xffffffff); // Up/previous
            return 0;
        case 4:
        case 7:
            moveSelection(1); // Down/next
            return 0;
        case 8:
            movePage(1); // Next page
            return 0;
        case 9:
            movePage(0xffffffff); // Previous page
            return 0;
        }
    }
    return result;
}