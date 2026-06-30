// FUNC_NAME: GenericFSM::updateState
// Address: 0x0056ec90
// Role: Update the current state machine dispatching to state-specific handlers (0,1,3,4) based on a masked value.
// This function assumes 'this' in ECX (__thiscall). Fields:
//   +0x08: m_pConfig (pointer to a per-instance config block)
//   +0x0C: m_pActiveFlag (non-zero if the state machine is active)
// Config block (at m_pConfig):
//   +0x04: m_nTypeByte (byte, used to select between two sets of state table pointers)
//   +0x20: m_statesLow [index < 10] (masked state value)
//   +0x24: m_stateTableLow (pointer to state table for indices <10)
//   +0x28: m_statesHigh [index >=10] (masked state value)
//   +0x2C: m_stateTableHigh (pointer to state table for indices >=10)

void __fastcall GenericFSM::updateState(void) // this in ECX
{
    int iVar1;
    int in_EAX = this; // decompiler misnamed 'this' as in_EAX
    uint uVar2;
    int iVar3;

    iVar1 = *(int *)(in_EAX + 8); // m_pConfig
    if ((*(uint *)(iVar1 + 4) & 0xff) < 10) {
        iVar3 = *(int *)(iVar1 + 0x24); // m_stateTableLow
    } else {
        iVar3 = *(int *)(iVar1 + 0x2c); // m_stateTableHigh
    }
    if ((iVar3 != 0) && (*(int *)(in_EAX + 0xc) != 0)) { // m_pActiveFlag non-zero
        if ((*(uint *)(iVar1 + 4) & 0xff) < 10) {
            uVar2 = *(uint *)(iVar1 + 0x20); // m_statesLow
        } else {
            uVar2 = *(uint *)(iVar1 + 0x28); // m_statesHigh
        }
        uVar2 = uVar2 & 0xfffffff; // Mask to 28 bits, likely current state ID
        if (uVar2 == 0) {
            FUN_00580380(); // e.g., handleStateEnter
            return;
        }
        if (uVar2 == 1) {
            FUN_0057ece0(); // e.g., handleStateUpdate
            return;
        }
        if (uVar2 == 3) {
            FUN_0057b8b0(); // e.g., handleStateExit
            return;
        }
        if (uVar2 == 4) {
            FUN_0057d140(this); // e.g., handleStateSpecial, passes 'this' as argument
        }
    }
    return;
}