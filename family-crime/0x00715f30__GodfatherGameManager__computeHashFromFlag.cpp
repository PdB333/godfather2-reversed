// FUNC_NAME: GodfatherGameManager::computeHashFromFlag
int __thiscall GodfatherGameManager::computeHashFromFlag(void* thisObj) {
    // Call to external function returning a state/mode
    int gameState = someGlobalStateFunction(); // FUN_00800b60

    // Dereference: thisObj+0x18 points to another structure (e.g., a manager or data block)
    // That structure has a 32-bit flag field at offset +0x8e0
    // Bit 1 (value 2) is checked
    bool flag = (*(uint32_t*)(*(int*)((char*)thisObj + 0x18) + 0x8e0) & 2) != 0;

    uint32_t mask;
    if (gameState == 1) {
        mask = 0x54edc530;
    } else {
        mask = 0x4f96496f;
    }
    // Produces constant hash based on flag and game state
    // Effectively: return (flag ? mask : 0) + 0xce5a7723
    return (flag ? 0xFFFFFFFF & mask : 0) + 0xce5a7723;
}