// FUNC_NAME: Player::canAcceptInput
bool __thiscall Player::canAcceptInput(void)
{
    char bGlobalState;
    
    bGlobalState = IsControllerConnected();  // FUN_00481730 - possibly checks if game window has focus or controller is active
    if (((bGlobalState != '\0') && (*(int *)(this + 0x138) == 0)) && (*(char *)(this + 0x128) != '\0')) {
        return true;
    }
    return false;
}