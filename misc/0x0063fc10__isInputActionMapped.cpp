// FUNC_NAME: isInputActionMapped
bool isInputActionMapped(unsigned int actionId)
{
    // Check if the given action ID corresponds to a mapped input action.
    // These constants are likely custom action IDs defined by the game's input system.
    switch (actionId) {
    case 0x104:
    case 0x105:
    case 0x106:
    case 0x114:
    case 0x11f:
        return true;
    default:
        return false;
    }
}