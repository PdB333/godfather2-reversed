// FUN_004dfd00: GameSystem::GameSystem

GameSystem* __thiscall GameSystem::GameSystem(GameSystem* this, byte constructorFlags) {
    *this = &GameSystem::vtable;                // +0x00: set vtable pointer to GameSystemVTable
    this->field_0xC = &unknownData;            // +0x0C: set some pointer (first assignment)
    this->field_0xC = &otherData;              // +0x0C: overwrite with another pointer (intentional double set)
    g_globalStatusFlag = 0;                    // reset singleton flag (DAT_012234c4)
    initCoreSubsystem();                       // base initialization (FUN_004083d0)
    if (constructorFlags & 1) {                // if heap-allocated flag is set
        deallocateThis(this);                  // (FUN_009c8eb0) likely operator delete or destructor call
    }
    return this;
}