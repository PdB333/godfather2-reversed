// FUNC_NAME: ResourceManager::rebuildTable
void ResourceManager::rebuildTable(void)
{
    char cVar1;
    int *piVar2;
    int iVar3;
    int *piVar4;
    undefined4 *puVar5;
    undefined4 uVar6;
    undefined4 *puVar7;
    int iVar8;
    char *pcVar9;
    int *piVar10;
    uint uVar11;

    // Allocate new descriptor block (8 bytes: maxSize and arrayPtr)
    piVar4 = (int *)heapAlloc(8);
    piVar10 = (int *)0x0;
    if (piVar4 != (int *)0x0) {
        piVar4[1] = 0x3ff8;  // +4: max entries
        puVar5 = (undefined4 *)heapAlloc(0xc);  // allocate first array element
        if (puVar5 == (undefined4 *)0x0) {
            puVar5 = (undefined4 *)0x0;
        }
        else {
            uVar6 = heapAllocArray(0x3ff8);  // allocate actual array storage? Unclear
            puVar5[1] = uVar6;
        }
        *piVar4 = (int)puVar5;  // +0: array base
        *puVar5 = 0;            // first element zeroed
        *(undefined4 *)(*piVar4 + 8) = 0;
        piVar10 = piVar4;
    }

    uVar11 = 1;
    iVar8 = s_globalArrayBase;  // DAT_01205a34
    if (1 < s_globalCount) {    // DAT_01205a40
        do {
            puVar5 = *(undefined4 **)(iVar8 + uVar11 * 4);
            if ((((uint)puVar5 & 1) == 0) && (puVar5 != (undefined4 *)0x0)) {
                // Clone the entry: allocate space for header (0x14) + actual string length
                puVar7 = (undefined4 *)cloneStringNode(*(ushort *)(puVar5 + 3) + 0x14);
                *(undefined2 *)(puVar7 + 3) = *(undefined2 *)(puVar5 + 3);   // +12: string length
                *(undefined2 *)((int)puVar7 + 0xe) = *(undefined2 *)((int)puVar5 + 0xe); // +14: ? 
                *puVar7 = *puVar5;              // +0: first dword
                puVar7[1] = puVar5[1];          // +4: second dword
                pcVar9 = (char *)(puVar5 + 4);  // +16: string start
                puVar7[2] = puVar5[2];          // +8: third dword
                iVar3 = 0x10 - (int)pcVar9;     // Calculate destination offset (likely artifact)
                do {
                    cVar1 = *pcVar9;
                    pcVar9[(int)puVar7 + iVar3] = cVar1;  // Copy character to new buffer
                    iVar8 = s_globalArrayBase;
                    pcVar9 = pcVar9 + 1;
                } while (cVar1 != '\0');
                *(undefined4 **)(s_globalArrayBase + uVar11 * 4) = puVar7;
            }
            uVar11 = uVar11 + 1;
        } while (uVar11 < s_globalCount);
    }

    // Free old linked list
    piVar4 = s_freeListHead;  // DAT_01205a4c
    if (s_freeListHead != (int *)0x0) {
        iVar8 = *s_freeListHead;
        while (iVar8 != 0) {
            piVar2 = (int *)*piVar4;
            iVar8 = *piVar2;
            if (piVar2 != (int *)0x0) {
                heapFreeBuffer(piVar2[1]);
                heapFree(piVar2);
            }
            *piVar4 = iVar8;
        }
        heapFree(piVar4);
    }
    s_freeListHead = piVar10;  // Set new descriptor
    s_resetFlag = 0;           // DAT_01205a50
    return;
}