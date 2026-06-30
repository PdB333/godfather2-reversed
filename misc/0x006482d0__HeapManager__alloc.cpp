// FUNC_NAME: HeapManager::alloc
undefined4* __thiscall HeapManager::alloc(int size, char isLarge) {
    int iVar1;
    undefined4 *puVar2;
    LPVOID lpAddress;
    uint *puVar3;
    DWORD flAllocationType;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    uint uVar7;
    uint uVar8;
    bool bVar8;

    iVar1 = this->field_0x4d4; // alignment/page size
    uVar7 = (iVar1 - 1 + size) & ~(iVar1 - 1); // align size up to page boundary
    uVar5 = 1;
    uVar4 = uVar7;
    
    if (uVar7 < this->field_0x4dc) { // minimum allocation size
        uVar4 = (iVar1 - 1 + this->field_0x4dc) & ~(iVar1 - 1);
    }
    
    uVar6 = (uVar4 + 0xffff) & 0xffff0000; // round up to 64KB
    lpAddress = VirtualAlloc(NULL, uVar6, 0x2000, 4); // MEM_RESERVE, PAGE_READWRITE
    
    if (lpAddress != NULL) {
        if (uVar7 < this->field_0x4e0) { // maximum allocation size?
            uVar7 = (iVar1 - 1 + this->field_0x4e0) & ~(iVar1 - 1);
        }
        if ((uVar6 < uVar7) || (isLarge != '\0')) {
            uVar7 = uVar6;
        }
        puVar3 = (uint *)VirtualAlloc(lpAddress, uVar7, 0x1000, 4); // MEM_COMMIT, PAGE_READWRITE
        if (puVar3 != NULL) goto LAB_00648392;
    }
    
    // fallback: reserve and commit together, possibly large pages
    flAllocationType = 0x3000; // MEM_RESERVE|MEM_COMMIT
    if (this->field_0x498 != '\0') {
        flAllocationType = 0x103000; // with MEM_LARGE_PAGES
    }
    puVar3 = (uint *)VirtualAlloc(NULL, uVar4, flAllocationType, 4);
    if (puVar3 == NULL) {
        return NULL;
    }
    uVar5 = 3; // indicates this block came from the fallback path
    uVar6 = uVar4;
    uVar7 = uVar4;

LAB_00648392:
    // Initialize the memory block header
    *puVar3 = (uint)((int)puVar3 + 0x27) & 0xfffffff8; // user data pointer (aligned to 8)
    *(char *)(puVar3 + 3) = (char)(uVar5 >> 1); // size class or status?
    puVar3[2] = uVar7; // block size
    uVar4 = (int)this + 0x448; // pointer to sentinel node in free list
    puVar3[1] = uVar7; // also block size? maybe total size
    bVar8 = this->field_0x464 != uVar4; // free list not empty?
    puVar3[7] = uVar4; // next free node (points to sentinel)
    *(bool *)((int)puVar3 + 0xd) = bVar8;
    *(bool *)((int)puVar3 + 0xf) = bVar8;
    *(undefined *)((int)puVar3 + 0xe) = 1; // in-use flag
    puVar3[4] = 0;
    puVar3[5] = 0;
    puVar3[6] = this->field_0x460; // previous free node
    this->field_0x460 = puVar3; // update head
    *(uint **)(puVar3[6] + 0x1c) = puVar3; // link previous node's next to this
    puVar3[2] = uVar6; // set block size again? (maybe the aligned reserve size)

    // If the free list was empty and no other conditions, reset flags
    if ((this->field_0x46c == '\0') && (this->field_0x464 != this->field_0x460)) {
        this->field_0x46c = 1;
        this->field_0x468 = 0;
    }

    // Set up a free block representing remaining space after user data
    puVar2 = (undefined4 *)*puVar3; // user data area
    uVar7 = (uint)puVar2 - (uint)puVar3; // offset of user data from block start
    uVar8 = uVar7 & 0x7ffffff8; // align down to 8
    uVar6 = uVar8 - 0x10;
    puVar2[1] = (uVar7 & 0x80000007) | uVar5 | uVar6; // header for remainder
    *puVar2 = 0;
    *(uint *)(uVar6 + (int)puVar2) = uVar6;
    *(undefined4 *)((uVar8 - 0xc) + (int)puVar2) = 8;
    *(undefined4 *)((uVar8 - 8) + (int)puVar2) = 8;
    *(undefined4 *)((uVar8 - 4) + (int)puVar2) = 9;
    
    return puVar2;
}