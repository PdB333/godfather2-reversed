// FUNC_NAME: PlayerStateMachine::evaluateCondition
uint __thiscall PlayerStateMachine::evaluateCondition(int* thisPtr, uint conditionIndex)
{
    int iVar1;
    int iVar2;
    uint uVar3;

    switch (conditionIndex) {
    case 0:
        // +0x00: pointer to a state or flag
        return (uint)(*thisPtr != 0);
    case 1:
        // +0x70 (0x1c * 4): another pointer/flag
        return (uint)(thisPtr[0x1c] != 0);
    case 2:
        // +0x08 (2 * 4): pointer/flag
        return (uint)(thisPtr[2] != 0);
    case 3:
        // +0x34 (0xd * 4): timestamp or counter
        iVar2 = getCurrentTime();               // FUN_0095ca40
        iVar1 = thisPtr[0xd];                   // +0x34
        uVar3 = getStateTimeout();              // FUN_0095c9f0
        return (uint)(uVar3 <= (uint)(iVar1 - iVar2));
    case 4:
        // +0x24 (9 * 4): flag
        return (uint)(thisPtr[9] != 0);
    case 5:
        // +0x28 (10 * 4): flag
        return (uint)(thisPtr[10] != 0);
    case 6:
        // +0x14 (5 * 4): flag
        return (uint)(thisPtr[5] != 0);
    case 7:
        // +0x20 (8 * 4): flag
        return (uint)(thisPtr[8] != 0);
    case 8:
        // +0x7a: byte flag (checked for zero)
        return (uint)(*(char*)((int)thisPtr + 0x7a) == '\0');
    case 9:
        // +0x1c (7 * 4): flag
        return (uint)(thisPtr[7] != 0);
    default:
        // unknown condition index, returns high byte of index
        return conditionIndex & 0xffffff00;
    }
}