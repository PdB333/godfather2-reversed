// FUNC_NAME: Player::updateTargetedVehicle
void __fastcall Player::updateTargetedVehicle(int thisPtr)
{
    int *piVar1;
    int iVar2;
    bool bVar3;
    
    iVar2 = DAT_0112b9b4; // Global: gPlayerManager or gPlayerPtr
    bVar3 = DAT_0112b9b4 != 0;
    *(undefined4 *)(thisPtr + 0x10) = 0; // m_targetedEntity +0x10
    
    if (((bVar3) && (*(uint *)(thisPtr + 0x70) < *(uint *)(iVar2 + 8))) &&
        (piVar1 = *(int **)(*(int *)(iVar2 + 4) + *(uint *)(thisPtr + 0x70) * 4), piVar1 != (int *)0x0
        )) && (iVar2 = *piVar1, iVar2 != 0)) {
        *(undefined4 *)(thisPtr + 0x10) = *(undefined4 *)(iVar2 + 0x70); // m_targetedVehicle = vehicle->m_someProperty
    }
    return;
}