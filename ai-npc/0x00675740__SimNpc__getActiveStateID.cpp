// FUNC_NAME: SimNpc::getActiveStateID
uint __thiscall SimNpc::getActiveStateID(uint param1)
{
    // +0x20: pointer to state machine component (e.g. AnimationStateMachine)
    void* pStateMachine = *(void**)(this + 0x20);
    if (pStateMachine != 0) {
        uint localId = 0;
        // FUN_0067bb50 returns a value and also sets localId through pointer
        uint result = FUN_0067bb50(&localId);
        // Write low byte of result into state machine at +0x1ec (e.g. current animation ID)
        *(uint*)((uint)pStateMachine + 0x1ec) = result & 0xff;
        // Return lower 16 bits of localId as the state ID
        return localId & 0xffff;
    }
    // +0x48: pointer to AI brain/controller component
    void* pAIController = *(void**)(this + 0x48);
    if (pAIController != 0) {
        // FUN_00675200 directly returns the state ID based on param1
        return FUN_00675200(param1);
    }
    return 0;
}