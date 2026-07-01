// Xbox PDB: EARS::Modules::TurnSeekStateMachine::BuildSeekTargetStateTable
// FUNC_NAME: registerSeekTargetTableBehavior
void registerSeekTargetTableBehavior()
{
    uint32_t stringId = GetStringId("seekTargetTable");
    int32_t existingPtr = GetGlobalPointer(stringId);
    
    if (existingPtr == 0) {
        // Not yet registered – create and register the behavior
        void* newBehavior = CreateSomeGameObject();
        RegisterNamedObject("seekTargetTable", newBehavior);
        SetNamedIntegerParameter("seekToTargetNoAnims", 0xffffffff);
        SetBehaviorFlags(0x14);
        RegisterStateMachine(0x1b2d5c51, reinterpret_cast<void*>(&LAB_00755af0), "TurnSeekStateMachine");
        FinalizeRegistration();
    }
}