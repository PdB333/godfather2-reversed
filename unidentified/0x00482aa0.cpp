// FUN_NAME: CRenderQueue::submitSortedDraws

void __thiscall CRenderQueue::submitSortedDraws(CRenderQueue *this, int pRenderListData, int hRenderContext)
{
    int iVar1;
    int iVar2;
    uint *puVar3;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    uint uVar7;
    int aiStack_40[4];
    int local_24[2];       // +0x00: hRenderDevice, +0x04: clipFlags (unused?)
    undefined local_1c;    // 0
    uint local_18;         // count
    uint local_14;         // sort key
    undefined4 local_10;   // handle copy
    uint local_c;          // loop index
    uint *local_8;         // pointer to sorted slot

    // Number of renderables to process (from this->+0x0C)
    local_18 = (uint)*(ushort *)(this + 0xc);
    uVar5 = local_18;

    // Allocate stack space for an array of (sortKey, handle) pairs (8 bytes each)
    iVar1 = uVar5 * -8;
    uVar7 = 0;
    local_c = 0;
    if (uVar5 != 0) {
        local_8 = (uint *)(&stack0xffffffd0 + iVar1);
        do {
            // Fetch handle from the render list data array (starts at pRenderListData+4)
            uVar6 = *(uint *)(pRenderListData + 4 + local_c * 4);
            local_10 = uVar6;

            if (g_pRenderDevice != 0) {
                // Get renderable info; returns pointer to a structure with sort priority at +0x16
                iVar2 = FUN_00407da0();   // e.g., getRenderableInfo(uVar6)
                if (iVar2 != 0) {
                    local_14 = (uint)*(ushort *)(iVar2 + 0x16); // sort key

                    // Insert the (key,handle) pair into the sorted array (ascending)
                    uVar4 = 0;
                    if (uVar7 != 0) {
                        do {
                            if (*(int *)(&stack0xffffffd0 + uVar4 * 8 + iVar1) < (int)local_14) {
                                if (uVar4 < uVar7) {
                                    // Shift elements right to insert
                                    iVar2 = uVar7 - uVar4;
                                    puVar3 = local_8;
                                    do {
                                        *puVar3 = puVar3[-2];
                                        puVar3[1] = puVar3[-1];
                                        puVar3 = puVar3 + -2;
                                        iVar2 = iVar2 + -1;
                                        uVar6 = local_10; // re-read handle (might be optimized away)
                                    } while (iVar2 != 0);
                                }
                                break;
                            }
                            uVar4 = uVar4 + 1;
                        } while (uVar4 < uVar7);
                    }

                    uVar7 = uVar7 + 1;
                    local_8 = local_8 + 2;
                    // Write new pair
                    *(uint *)(&stack0xffffffd0 + uVar4 * 8 + iVar1) = local_14;
                    *(uint *)(&stack0xffffffd4 + uVar4 * 8 + iVar1) = uVar6;
                }
            }
            local_c = local_c + 1;
        } while (local_c < local_18);
    }

    // Submit sorted handles to renderer
    if (uVar7 != 0) {
        puVar3 = (uint *)(&stack0xffffffd4 + iVar1);
        do {
            uVar6 = *puVar3; // handle

            // Build a local struct for submission (g_pRenderDevice, something, 0)
            local_24[0] = g_pRenderDevice;
            local_24[1] = 0;
            local_1c = 0;

            // Call render submission (context, handle, &local_24)
            FUN_00408bf0(); // e.g., submitRenderable(hRenderContext, uVar6, &local_24)
            puVar3 = puVar3 + 2;
            uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
    }
    return;
}