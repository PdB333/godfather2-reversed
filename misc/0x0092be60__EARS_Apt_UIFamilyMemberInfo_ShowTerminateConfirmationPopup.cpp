// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_ShowTerminateConfirmationPopup
// FUNC_NAME: PauseMenu::setupMarkForDeathConfirmButton

// Structure for a pause menu action/button (size 0xF0)
struct PauseMenuAction {
    int32_t actionType;          // +0x0C
    int32_t unk_0x10;            // +0x10 (gap?)
    int32_t unk_0x14;            // +0x14 - function pointer (callback)
    int32_t unk_0x18;            // +0x18 (gap?)
    int32_t unk_0x1C;            // +0x1C - some constant flag
    int32_t unk_0x20;            // +0x20 - another constant flag
    // ... more fields up to 0xF0
};

// Helper function to allocate memory for action data
// This is likely a global memory allocator (e.g. NEW or pool allocator)
PauseMenuAction* AllocateActionData(uint32_t size);

// Initialize the action data structure (returns pointer to initialised data)
PauseMenuAction* InitActionData(PauseMenuAction* action, int32_t initParam);

// Set the localized text string for this action
void SetActionText(PauseMenuAction* action, const char* textKey);

// Register/finalize the action (adds to menu system)
void RegisterAction(PauseMenuAction* action);

void PauseMenu::setupMarkForDeathConfirmButton(void)
{
    // Allocate and initialise the action data block (size = 0xF0)
    PauseMenuAction* action = AllocateActionData(0xF0);
    if (action != (PauseMenuAction*)0x0) {
        action = InitActionData(action, 0);
    }

    // Set the button text from the localization key
    SetActionText(action, "$pause_button_mark_for_death_confirm");

    // Configure the action parameters
    action->actionType = 2;                         // +0x0C: Confirm action type
    action->unk_0x20 = 0xB9754031;                  // +0x20: Unknown constant (event ID?)
    action->unk_0x1C = 0x997DEE17;                  // +0x1C: Another constant (maybe flag)
    action->unk_0x14 = (int32_t)&PauseMenu::markForDeathConfirmCallback; // +0x14: callback function

    // Add the action to the pause menu system
    RegisterAction(action);
    return;
}