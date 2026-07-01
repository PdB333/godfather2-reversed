// FUNC_NAME: InputManager::getPressedButtonAction
enum EInputAction : int {
    INPUT_ACTION_NONE   = 0,
    INPUT_ACTION_PRESS  = 1,
    INPUT_ACTION_HOLD   = 2,
    INPUT_ACTION_RELEASE = 3,
    INPUT_ACTION_DOUBLE = 4
};

EInputAction InputManager::getPressedButtonAction() {
    // this +0x50: pointer to some input device/manager
    // *(int*)(*(int*)(this+0x50) + 0x1f30) is a vtable pointer
    // +8 (slot 2) -> virtual method returning an object (likely a key code or state)
    int currentKey = (**(code**)(*(int*)(*(int*)(this + 0x50) + 0x1f30) + 8))(0);
    
    // 0x00464b40 likely returns the current button code (0-16 mapping)
    char keyState = getCurrentInputKey(currentKey, 0);
    
    // Mapping from key code to game action (0-4)
    if (keyState == 0x0f || keyState == 0x07) {
        return INPUT_ACTION_DOUBLE;
    }
    if (keyState != 0x0b && keyState != 0x03) {
        if (keyState != 0x09 && keyState != 0x01 && keyState != 0x0a && 
            keyState != 0x02 && keyState != 0x10 && keyState != 0x08) {
            if (keyState != 0x0d && keyState != 0x05 && 
                keyState != 0x0c && keyState != 0x04 && keyState != 0x0e && keyState != 0x06) {
                return INPUT_ACTION_NONE;
            }
            return INPUT_ACTION_HOLD;
        }
        return INPUT_ACTION_PRESS;
    }
    return INPUT_ACTION_RELEASE;
}