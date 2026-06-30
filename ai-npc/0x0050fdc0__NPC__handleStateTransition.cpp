// FUNC_NAME: NPC::handleStateTransition
void NPC::handleStateTransition(int *param_1) // 0x0050fdc0
{
    int iVar1;
    char state;
    int iVar3;
    int iVar4;
    int someIndex;
    int ediBase;
    int fsOffset;

    // fs:0x2c points to thread-local storage, +8 gets some base
    // +someIndex*0x50 + 0x20 likely accesses an array of NPC state structs
    iVar1 = *(int *)(**(int **)(fsOffset + 0x2c) + 8) + someIndex * 0x50 + 0x20 + *param_1;
    
    iVar3 = *(int *)(ediBase + 0xac); // +0xAC: npcStateArray pointer
    if ((iVar3 != 0) && 
        (iVar4 = (uint)*(ushort *)(iVar1 + 0x36) * 4, *(int *)(iVar4 + iVar3) != 0)) 
    {
        state = *(char *)(ediBase + 0x5b); // +0x5B: transitionTargetState
        if (state == '\x01') // STATE_1 - likely active/playing
        {
            iVar1 = *(int *)(iVar4 + iVar3);
            if (iVar1 != 0) 
            {
                if ((*(byte *)(*(int *)(ediBase + 0x24) + 0x104) & 0x10) != 0) // +0x24: some component pointer
                {
                    // Special condition met - force cancel and reset
                    FUN_0051b250(iVar1);  // NPC::cancelCurrentAction?
                    FUN_004f98d0();        // NPC::resetStateMachine?
                    return;
                }
                FUN_0051b340(); // NPC::executeStateTransition?
            }
        }
        else 
        {
            if (state == '\x02') // STATE_2 - abort/exit
            {
                FUN_004e97b0(); // NPC::abortCurrentState?
                *(undefined4 *)(*(int *)(ediBase + 0xac) + (uint)*(ushort *)(iVar1 + 0x36) * 4) = 0;
                return;
            }
            if (state == '\x06') // STATE_6 - reset/clear
            {
                *(undefined4 *)(iVar1 + 0x30) = 0; // +0x30: stateTimer or nextState
                FUN_0050a750(); // NPC::clearStateData?
                *(undefined4 *)(*(int *)(ediBase + 0xac) + (uint)*(ushort *)(iVar1 + 0x36) * 4) = 0;
                return;
            }
        }
    }
    return;
}