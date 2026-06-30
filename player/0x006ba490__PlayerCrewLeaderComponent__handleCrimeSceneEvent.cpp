// FUNC_NAME: PlayerCrewLeaderComponent::handleCrimeSceneEvent
void __thiscall PlayerCrewLeaderComponent::handleCrimeSceneEvent(int this, int pTarget) {
    char canProceed;
    int gameSettings;
    undefined4 profileToken;
    undefined4 unused;

    validateCrimeScene(pTarget);
    if ((pTarget != 0) && (*(int*)(pTarget + 0x1ed4) == 0x637b907)) {
        gameSettings = getGameSettings();
        if (((*(uint*)(gameSettings + 0x5c) >> 0x1b & 1) == 0) &&
           ((*(int*)(this + 0x9c) != 0 && (*(int*)(*(int*)(this + 0x9c) + 0x40) == 0x637b907)))
           ) {
            canProceed = isActionAllowed();
            if (canProceed != '\0') {
                unused = 0;
                profileToken = enterProfileScope(0, 0);
                logGameplayEvent(0x431128ef, 0x10, profileToken, unused);
                leaveProfileScope();
            }
        }
    }
    return;
}