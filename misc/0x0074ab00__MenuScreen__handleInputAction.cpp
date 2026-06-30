// FUNC_NAME: MenuScreen::handleInputAction
bool __thiscall MenuScreen::handleInputAction(void* this, uint32_t param_2, uint32_t param_3, int32_t actionType, uint32_t param_5)
{
    // +0x5c: pointer to a structure (e.g., menu state or UI context)
    void* uiContext = *(void**)((char*)this + 0x5c);

    // 0x12 = 18, likely "confirm" or "select"
    if (actionType == 0x12) {
        // +0x70: flag byte, bit0 = some toggle state
        return *(uint8_t*)((char*)this + 0x70) & 1;
    }
    // 0x13 = 19, likely "cancel" or "back"
    if (actionType == 0x13) {
        return (~*(uint8_t*)((char*)this + 0x70)) & 1;
    }
    // 0x14 = 20, likely a special action (e.g., "confirm with check")
    if (actionType != 0x14) {
        // Delegate to default handler
        return FUN_0073e300(param_2, param_3, actionType, param_5);
    }

    // Handle action 0x14
    FUN_00716430(); // Possibly returns current menu/internal state manager
    int32_t menuState = FUN_00713960(); // e.g., 0 = inactive, 1 = active, etc.
    if (menuState == 1) {
        // +0x24c4: offset into uiContext; valid range check
        int32_t selectedIndex = *(int32_t*)((char*)uiContext + 0x24c4);
        if (selectedIndex != 0 && selectedIndex != 0x48) {
            // +0x30 and +0x38: likely data from a structure (e.g., option string or ID)
            void* someObject = (void*)FUN_00471610();
            bool isOptionValid = FUN_0074a400(
                *(uint8_t*)((char*)someObject + 0x30),
                *(uint32_t*)((char*)someObject + 0x38)
            );
            // Return true if the option is invalid (invert result)
            return !isOptionValid;
        }
        // No specific selection, still allow the action
        return true;
    }
    // Menu not in active state, block action
    return false;
}