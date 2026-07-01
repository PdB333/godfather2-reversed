// FUNC_NAME: TutorialManager::handleTutorialKeyInput
bool __thiscall TutorialManager::handleTutorialKeyInput(TutorialManager* this, int param2, int param3, int param4, int keyCode, int param6)
{
    bool result;
    int* piVar1;
    char cVar2;
    bool bVar3;
    int iVar5;
    void* soundId;
    int gameManager;

    result = true;
    switch (keyCode) {
    case 0x31: // '1' key
        soundId = getAudioManager();               // FUN_007ab360
        playSound(soundId);                        // FUN_00728250
        return true;
    case 0x32: // '2'
    case 0x33: // '3'
    case 0x34: // '4'
    case 0x35: // '5'
    case 0x36: // '6'
    case 0x37: // '7'
    case 0x38: // '8'
    case 0x3a: // ':'
        break;
    case 0x39: // '9'
        // Check a state flag at offset +0x88
        if ((this->field_0x88 != 0) && (this->field_0x88 != 0x48)) {
            // Send a command with hash 0xe45b1c56
            (this->vtable[0x0B])(0xe45b1c56, 1, 1, 0, 1.0f, 1.0f);
            piVar1 = &this->field_0x90;            // +0x90
            if (this->field_0x90 != 0) {
                deletePointer(piVar1);             // FUN_004daf90
                *piVar1 = 0;
            }
            gameManager = getGameManager();        // FUN_006abcf0
            showNotification(gameManager);         // FUN_006f62b0
            if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
                if (*piVar1 == 0) {
                    iVar5 = 0;
                } else {
                    iVar5 = *piVar1 - 0x48;
                }
                cVar2 = checkSomeCondition(iVar5); // FUN_006aba10
                *(bool*)((int)this + 0x7e) = (cVar2 == '\0');
                return true;
            }
            showTutorial();                        // FUN_008d8e40
            *(bool*)((int)this + 0x7e) = true;
            hideTutorial();                        // FUN_008de0e0
            return true;
        }
        break;
    case 0x3b: // ';'
        (this->vtable[0x0B])(0x4c0e259d, 1, 1, 0, 1.0f, 1.0f);
    case 0x3c: // '<'
        dismissTutorial();                         // FUN_006f6ea0
        return true;
    default:
        result = defaultKeyHandler(param2, param3, param4, keyCode, param6); // FUN_007abec0
    }
    return result;
}