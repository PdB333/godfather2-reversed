// FUNC_NAME: GodfatherGameManager::initGameState
void __thiscall GodfatherGameManager::initGameState(void) {
    int buffer;
    int manager;
    int stateStruct;

    // Get thread-local storage base (required for allocation)
    TlsGetValue(DAT_01139810);

    // Allocate 28-byte buffer from memory pool 0xB
    // +0x04: size field (16-bit)
    buffer = allocateMemory(0x1c, 0xb);
    *(short*)(buffer + 4) = 0x1c;

    // Obtain singleton manager from FUN_00549900 (likely this)
    manager = getManager(); // FUN_00549900 returns pointer to GodfatherGameManager
    stateStruct = *(int*)(manager + 0x18); // +0x18: pointer to internal game state

    // Reset state fields:
    // +0x10: active flag (byte) set to 1
    // +0x11: secondary flag (byte) set to 0
    // +0x14: int field cleared
    // +0x18: int field cleared
    // +0x08: int field cleared
    *(int*)(stateStruct + 0x14) = 0;
    *(int*)(stateStruct + 0x18) = 0;
    *(byte*)(stateStruct + 0x10) = 1;
    *(byte*)(stateStruct + 0x11) = 0;
    *(int*)(stateStruct + 0x8) = 0;
}