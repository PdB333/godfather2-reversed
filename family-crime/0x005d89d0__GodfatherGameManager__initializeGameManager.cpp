// FUNC_NAME: GodfatherGameManager::initializeGameManager
void __thiscall GodfatherGameManager::initializeGameManager(void* this) {
    // +0x10: pointer to some subsystem A
    // +0x14: pointer to some subsystem B
    void* subsystemA = FUN_0060a380();                          // allocates/creates object
    *(void**)((int)this + 0x10) = subsystemA;
    void* subsystemB = FUN_0060a2e0(&PTR_DAT_00f1747c);         // creates with config data
    *(void**)((int)this + 0x14) = subsystemB;

    FUN_006127d0();                                             // global initialization

    // Registers/managers initialization with static data
    FUN_005d87b0(&PTR_DAT_00f1753c, &DAT_00f175e8);

    // Call virtual function at vtable offset 4 (likely start/run)
    // vtable pointer is at +0xB0
    (*(void (__thiscall**)(void))(**(int**)((int)this + 0xB0) + 4))(this);
}