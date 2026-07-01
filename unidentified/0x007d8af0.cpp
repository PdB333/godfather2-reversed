// FUN_007d8af0: PlayerController::isInputAllowed
bool __fastcall PlayerController::isInputAllowed(int this) {
    // +0x74: pointer to a state structure (e.g., PlayerStateFlags)
    int* stateStructPtr = *(int**)(this + 0x74);
    // Check if bit 1 (0x02) of that structure's byte at +4 is set
    if ((*(byte*)(stateStructPtr + 1) & 2) != 0) { // stateStructPtr+4 as byte, bit 1
        int* globalState = (int*)FUN_007ab160(); // e.g., GameManager::getInstance() or similar singleton
        // Check if global state has bit 2 (0x04) at its +4 offset set
        if ((*(byte*)((int)globalState + 4) & 4) != 0) {
            // DAT_0112a838: pointer to an object (e.g., DialogManager, CutsceneManager)
            // Its +0x5C field being zero means no active blocking action
            if (DAT_0112a838 == 0 || *(int*)(DAT_0112a838 + 0x5C) == 0) {
                return true;
            }
        }
    }
    return false;
}