// FUNC_NAME: StatsManager::addStatValue
void __thiscall StatsManager::addStatValue(int statId, int categoryIndex, int value)
{
    float fVar1;
    float fVar2;
    int iVar3;
    int iVar4;
    int *piVar5;

    iVar3 = statId;
    iVar4 = findStatEntry(&statId); // FUN_008d3190: returns index or -1
    if ((iVar4 < 0) ||
        (piVar5 = (int *)(*(int *)(this + 0x18) + 4 + iVar4 * 0x18), piVar5 == (int *)0x0)) {
        piVar5 = (int *)createStatEntry(&statId); // FUN_008d35f0: creates new entry
        logStatCreation(); // FUN_008d5df0: possibly logging
    }
    fVar2 = (float)value;
    if (value < 0) {
        fVar2 = fVar2 + DAT_00e44578; // adjust negative float (likely 0xFFFFFFFF as float)
    }
    fVar1 = (float)piVar5[4]; // multiplier at offset 0x10 of stat entry
    *piVar5 = *piVar5 + value; // increment count at offset 0x00
    *(float *)(this + 0x74) = fVar2 * fVar1 + *(float *)(this + 0x74); // update total accumulator
    if (iVar3 != 0x637b907) { // skip per-category update for total score stat
        *(float *)(this + 0x24 + categoryIndex * 0x14) =
             fVar2 * fVar1 + *(float *)(this + 0x24 + categoryIndex * 0x14); // update category accumulator
    }
    return;
}