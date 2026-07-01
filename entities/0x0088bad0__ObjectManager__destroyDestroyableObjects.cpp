// FUNC_NAME: ObjectManager::destroyDestroyableObjects
void __fastcall ObjectManager::destroyDestroyableObjects(int this)
{
    byte *pbVar1;
    int iVar2;
    int iVar3;
    int *pObjectNode;
    int local_8[1];
    
    pObjectNode = *(int **)(this + 0x1c4); // +0x1c4: pointer to linked list of destroyable object nodes
    while (pObjectNode != (int *)0x0) {
        iVar2 = *pObjectNode; // object ID
        iVar3 = *(int *)(iVar2 + 0x14); // +0x14: pointer to object base data
        if ((*(byte *)(iVar3 + 0x51) & 0x10) == 0) { // check if not already destroyed
            // Check if all minimum bounds are <= maximum bounds (object is within valid range)
            if ((((*(float *)(iVar3 + 0x30) < *(float *)(iVar3 + 0x40) || // minX < maxX
                   *(float *)(iVar3 + 0x30) == *(float *)(iVar3 + 0x40)) && // or equal
                 (*(float *)(iVar3 + 0x34) < *(float *)(iVar3 + 0x44) || // minY < maxY
                  *(float *)(iVar3 + 0x34) == *(float *)(iVar3 + 0x44))) &&
                (*(float *)(iVar3 + 0x38) < *(float *)(iVar3 + 0x48) || // minZ < maxZ
                 *(float *)(iVar3 + 0x38) == *(float *)(iVar3 + 0x48))) &&
               ((*(byte *)(iVar3 + 0x54) & 8) == 0)) { // +0x54: flags, bit 3 = not destroyed
                FUN_00429460(*(undefined4 *)(iVar2 + 8)); // Queue removal from game
            }
            FUN_0088af60(iVar2, 1, 0); // Mark object as destroyed
            FUN_00888480(local_8, &pObjectNode); // Advance to next node, removing current
        }
        else {
            pObjectNode = (int *)pObjectNode[1]; // Already destroyed, skip to next
        }
        pbVar1 = (byte *)(*(int *)(iVar2 + 0x14) + 0x51); // +0x51: flags byte
        *pbVar1 = *pbVar1 & 0xef; // Clear bit 4 (mark as no longer pending destruction)
    }
    return;
}