// FUNC_NAME: AIUpdateManager::processBatch
void __fastcall AIUpdateManager::processBatch(int thisPtr)
{
    int iVar5 = *(int *)(thisPtr + 0x78) - *(int *)(thisPtr + 0x98);  // budget remaining: m_nMaxPerFrame - m_nProcessedThisFrame

    if (iVar5 > 0) {
        int iVar2 = *(int *)(DAT_0112a694 + 0x98);  // g_pSimManager->m_numActiveSims (or numEntities)
        int *piBaseArray = (int *)(DAT_0112a694 + 0x94);  // g_pSimManager->m_pSimObjectArray

        do {
            do {
                iVar2--;
                if (iVar2 < 0) {
                    return;
                }

                int *pSubObj = (int *)(*piBaseArray + iVar2 * 8);  // each array entry is 8 bytes
                int iVar3 = *pSubObj;  // pointer to sub‑object offset +0x48 from entity base

            } while (
                (iVar3 == 0) ||
                ( (int *)(iVar3 - 0x48) == (int *)0x0 ) ||             // entity base is null
                ((*(uint *)(iVar3 + 0xc40) >> 0x15 & 1) == 0) ||       // bit21 (0x00200000) in flags at offset +0xc88 (entity+0x48+0xc40)
                ( (*(int *)(iVar3 + 0xee4) != 2) ||                    // state at offset +0xf2c (entity+0x48+0xee4) != 2
                  (iVar3 = FUN_00542d70(), iVar3 == 0) ||               // some validation function, returns 0 if invalid
                  (*(int *)(iVar3 + 0xc4) == 0) ||                      // flag at offset +0x10c (entity+0x48+0xc4) must be nonzero
                  (int iVar4 = FUN_008752d0(), iVar4 < 1) )             // some count must be >= 1
            );

            int *pEntity = (int *)(iVar3 - 0x48);  // entity base class pointer

            FUN_0083de30(pEntity);   // pre‑update step (AI reset?)
            FUN_0083f190(pEntity);   // mid‑update (pathfinding?)
            (**(code **)(*pEntity + 0x28c))(1);  // virtual call: vtable[0x28c] (e.g. processAI(bool))
            FUN_008fa520(pEntity);   // post‑update

            *(ushort *)(iVar3 + 200) |= 8;  // set bit 3 in short at entity+0x48+0xC8 (offset 0x110)

            iVar5--;
        } while (iVar5 > 0);
    }
}