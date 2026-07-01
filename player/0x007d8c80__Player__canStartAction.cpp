// FUNC_NAME: Player::canStartAction
__thiscall int Player::canStartAction(void)
{
    char isGameActive;
    void* actionOptions;
    int playerState;
    int actionType;
    int result;

    isGameActive = isGameInProgress();
    if (isGameActive != '\0') {
        actionOptions = allocateMemory(0x38); // sizeof(ActionOptions)
        isGameActive = initializeActionOptions(actionOptions);
        if ((((isGameActive != '\0') &&
              (playerState = *(int *)(*(int *)(this + 0x58) + 0x74c), playerState != 0)) &&
             (playerState != 0x48)) && // Not ACTION_NONE = 0x48
            (result = getPlayerComponent(), result != 0)) {
            setInputBlocked(1);
            if (*(int *)(result + 0x328) != 0) { // m_pCurrentAction or m_bActionActive
                return 1;
            }
        }
    }
    return 0;
}