// FUNC_NAME: Player::isActionAllowed
bool __thiscall Player::isActionAllowed() {
    bool result = false;
    int stateId = this->stateId; // +0x330

    if (stateId != 0) {
        int adjustedIndex = stateId - 0x48;
        if (adjustedIndex != 0) {
            char checkResult = checkStateCondition(adjustedIndex, 0); // FUN_00714f30
            result = (checkResult == 0);
            if (result) {
                result = false;
                // re-check stateId again (maybe ensures it's not 0x48, though already excluded)
                if (this->stateId != 0 && this->stateId != 0x48) {
                    char globalCheck = checkGlobalCondition(); // FUN_007178e0
                    if (globalCheck != 0) {
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}