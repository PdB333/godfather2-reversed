// FUNC_NAME: Player::processActiveState
void __thiscall Player::processActiveState(Player* this) {
    int* globalManager = (int*)GameManager::getInstance(); // FUN_00ad8d40
    if (globalManager != nullptr) {
        int* activeController = (int*)(*(code**)(*globalManager + 0x34))(); // vtable call: getActiveController()
        if (activeController != nullptr) {
            int* playerObj = (int*)(*(code**)(*activeController + 0x3c))(); // vtable call: getPlayer()
            if (playerObj != nullptr) {
                someInitFunction(); // FUN_00b1a890
                processTransform(this + 0x38); // FUN_00b22400: update world transform at offset +0x38
                int manager = getSomeManager(); // FUN_00ad9f90
                registerToManager(manager); // FUN_008a33c0
                finalize(); // FUN_00ad9db0
            }
        }
    }
}