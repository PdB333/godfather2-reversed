// FUNC_NAME: MemoryPool::allocate
int* MemoryPool::allocate(void)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int in_EAX;
    int *piVar5;
    int *piVar6;
    int unaff_ESI;
    
    // Calculate aligned size (round up to multiple of 4)
    iVar1 = ((int)(in_EAX + -1 + (in_EAX + -1 >> 0x1f & 3U)) >> 2) * 4;
    iVar2 = iVar1 + 4;
    
    // Try to find a free block in the free list (linked list at +0x10)
    piVar5 = *(int **)(unaff_ESI + 0x10);
    if (piVar5 != (int *)0x0) {
        do {
            if (iVar1 + 0x10 <= *piVar5) goto LAB_00672dab;
            piVar5 = (int *)piVar5[1];
        } while (piVar5 != (int *)0x0);
    }
    
    // No suitable free block found, need to allocate from the pool
    iVar3 = *(int *)(unaff_ESI + 0x18);
    while( true ) {
        if (iVar3 == 0) {
            return (int *)0x0; // Pool exhausted
        }
        iVar3 = *(int *)(unaff_ESI + 0x18);
        
        // Remove block from the pool's linked list
        if (*(int *)(iVar3 + 8) == 0) {
            // No previous block, update the hash table (at +0x0C)
            *(undefined4 *)(*(int *)(unaff_ESI + 0xc) +
                ((uint)*(ushort *)(iVar3 + 0x60) * 0x10 + (uint)*(ushort *)(iVar3 + 0x62) +
                 *(int *)(iVar3 + 100) & 0x7f) * 4) = *(undefined4 *)(iVar3 + 4);
        }
        else {
            *(undefined4 *)(*(int *)(iVar3 + 8) + 4) = *(undefined4 *)(iVar3 + 4);
        }
        if (*(int *)(iVar3 + 4) != 0) {
            *(undefined4 *)(*(int *)(iVar3 + 4) + 8) = *(undefined4 *)(iVar3 + 8);
        }
        
        iVar4 = *(int *)(iVar3 + 0xc);
        *(int *)(unaff_ESI + 0x18) = iVar4;
        if (*(int *)(iVar3 + 0xc) == 0) {
            *(undefined4 *)(unaff_ESI + 0x14) = 0;
        }
        else {
            *(undefined4 *)(iVar4 + 0x10) = 0;
        }
        
        piVar5 = (int *)FUN_00672dc0(); // Get the free list head
        if (iVar1 + 0x10 <= *piVar5) break;
        iVar3 = *(int *)(unaff_ESI + 0x18);
    }
    
LAB_00672dab:
    // Split the free block: allocate from the end
    piVar6 = (int *)((*piVar5 - iVar2) + (int)piVar5);
    *piVar6 = iVar2; // Store size in allocated block header
    *piVar5 = *piVar5 - iVar2; // Reduce free block size
    *(int **)(unaff_ESI + 8) = piVar6; // Store allocated block pointer at +0x08
    return piVar6;
}