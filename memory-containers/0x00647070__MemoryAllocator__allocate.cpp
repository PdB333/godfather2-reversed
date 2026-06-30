// FUNC_NAME: MemoryAllocator::allocate
uint* MemoryAllocator::allocate(uint size, uint alignment, uint flags)
{
    int iVar1;
    uint uVar2;
    uint uVar5;
    uint uVar6;
    int iVar7;
    int iVar8;
    uint uVar9;
    uint uVar10;
    uint* puVar11;
    uint uVar12;
    ulonglong uVar13;
    uint local_1c;
    int local_18;
    int local_10;
    int local_8;
    uint8_t local_4[4];

    iVar8 = this;

    // Fast path: small size, no alignment, no special flags
    if (((size < 9) && (alignment == 0)) && ((flags & 0x400) == 0)) {
        puVar4 = (uint*)FUN_00646620(this, in_EAX, flags); // allocate from OS?
        return puVar4;
    }

    uVar10 = size;
    if (size < 0x10) {
        uVar10 = 0x10; // minimum block size
    }

    // Compute next power-of-two alignment requirement (round up)
    uVar5 = uVar10 - 1;
    if ((uVar10 & uVar5) != 0) {
        uVar5 = uVar5 | uVar5 >> 1;
        uVar5 = uVar5 | uVar5 >> 2;
        uVar5 = uVar5 | uVar5 >> 4;
        uVar5 = uVar5 | uVar5 >> 8;
        uVar10 = (uVar5 >> 0x10 | uVar5) + 1;
    }

    // Align alignment to 8 (if non-zero)
    if ((alignment & 7) != 0) {
        alignment = alignment + 7 & 0xfffffff8;
    }

    // Determine actual block size (size + overhead) based on some internal value (in_EAX)
    // in_EAX is likely a saved argument register; it appears to be the original request size? Hard to know.
    if (in_EAX + 0xbU < 0x11) {
        size = 0x10;
    } else {
        size = in_EAX + 0xbU & 0xfffffff8;
    }

    uVar5 = flags & 1; // flag bit0

    // Try to allocate from free list if flags have bit1 and bit2 set
    if (((flags & 4) != 0) && ((flags & 2) != 0)) {
        // Search free lists
        this = 0;
        local_8 = 0;
        local_1c = 0;
        if (size < 0x200) {
            uVar13 = CONCAT44(flags, size >> 3) & 0x1ffffffff; // generate hash/index
        } else {
            uVar13 = FUN_00644820(); // get random or timestamp
        }
        uVar9 = (uint)(uVar13 >> 0x20);
        local_10 = (int)uVar13;
        local_18 = 0;
        uVar12 = 0;
        do {
            if (local_18 == 0) {
                local_18 = local_10 + -1;
                uVar6 = iVar8 + 0x30; // free list head at +0x30
            } else {
                uVar6 = iVar8 + 0x28 + local_18 * 8; // other free lists at +0x28..+0x30?
            }
            // Walk the doubly linked list
            for (uVar2 = *(uint*)(uVar6 + 0xc); uVar2 != uVar6; uVar2 = *(uint*)(uVar2 + 0xc)) {
                if ((size <= (*(uint*)(uVar2 + 4) & 0x7ffffff8)) &&
                    (iVar7 = FUN_00646cf0(size, local_4), iVar7 != 0)) {
                    // Found a suitable block
                    if ((uVar2 < *(uint*)(iVar8 + 0x440) + 0xfec00000) &&
                        ((this == 0 || (uVar2 < this)))) {
                        this = uVar2;
                        local_8 = iVar7;
                    }
                    if ((*(uint*)(iVar8 + 0x440) <= uVar2) && (local_1c < uVar2)) {
                        local_1c = uVar2;
                    }
                }
                uVar9 = uVar5;
                uVar12 = local_1c;
            }
            local_18 = local_18 + 1;
        } while (local_18 < 0x80); // iterate over up to 128 free lists

        if ((uVar12 != 0) && (uVar9 != 0)) {
            // If we found a candidate above the low-water mark and flags bit0 set, use it
            FUN_00646df0(iVar8, uVar12); // remove from free list?
            iVar8 = FUN_00646d90(iVar8, *(uint*)(uVar12 + 4) & 0x7ffffff8); // get block pointer?
            return (uint*)(iVar8 + 8);
        }

        // Check low-water mark
        iVar7 = *(int*)(iVar8 + 0x440); // low water mark pointer
        uVar9 = *(uint*)(iVar7 + 4) & 0x7ffffff8; // size of that block
        if (0x1400000 < uVar9) {
            flags = flags & 0xfffffeff; // clear bit8
        }
        if ((this != 0) && ((uVar5 == 0 || ((flags & 0x100) != 0)))) {
            // Use the previously found best block
            FUN_00646df0(iVar8, this);
            FUN_00646d90(iVar8, *(uint*)(this + 4) & 0x7ffffff8);
            return (uint*)(local_8 + 8);
        }

        // Try to allocate from the low-water mark block (split it)
        if ((((~(byte)(flags >> 8) & 1) != 0) && (size + uVar10 + 0x10 + alignment <= uVar9)) &&
            ((flags & 1) != 0)) {
            puVar11 = (uint*)((((*(uint*)(iVar7 + 4) & 0x7ffffff8) - size) + iVar7 + 8 + alignment &
                               -uVar10) - alignment);
            uVar9 = uVar9 - ((int)puVar11 + (-8 - iVar7));
            puVar11[-1] = uVar9; // set size of remainder
            puVar4 = (uint*)((int)puVar11 + (uVar9 - 4));
            *puVar4 = *puVar4 | 1; // mark as used?
            *(uint*)((int)puVar11 + (uVar9 - 8)) = uVar9;
            *(int*)(iVar8 + 0x440) = iVar7;
            FUN_00644ae0(iVar8); // insert remainder into free list?
            return puVar11;
        }
    }

    // Otherwise, allocate new block from OS
    iVar7 = FUN_00646620(iVar8, size + uVar10 + 0x10 + alignment, flags);
    if (iVar7 == 0) {
        return 0;
    }
    puVar4 = (uint*)(iVar7 + -8);
    puVar11 = puVar4;
    // Align the returned pointer to uVar10 (power-of-two alignment)
    if ((iVar7 + alignment) % uVar10 != 0) {
        puVar11 = (uint*)(((iVar7 + uVar10 + -1 + alignment & -uVar10) - alignment) + -8);
        if ((uint)((int)puVar11 - (int)puVar4) < 0x10) {
            puVar11 = (uint*)((int)puVar11 + uVar10); // adjust if too close
        }
        uVar5 = (int)puVar11 - (int)puVar4;
        uVar10 = (*(uint*)(iVar7 + -4) & 0x7ffffff8) - uVar5;
        if ((*(uint*)(iVar7 + -4) & 2) != 0) {
            // Previous block is the second-to-last? Then split
            *puVar11 = *puVar4 + uVar5;
            puVar11[1] = uVar10 | 2;
            *(uint*)((int)puVar11 + uVar10) = uVar10;
            return puVar11 + 2;
        }
        puVar11[1] = uVar10 | 1;
        puVar4 = (uint*)((int)puVar11 + uVar10 + 4);
        *puVar4 = *puVar4 | 1;
        *(uint*)((int)puVar11 + uVar10) = uVar10;
        *(uint*)(iVar7 + -4) = *(uint*)(iVar7 + -4) & 0x80000007 | uVar5;
        *puVar11 = uVar5;
        // Save/restore lock flag at +0x478
        uint oldFlag = *(uint*)(iVar8 + 0x478);
        *(uint*)(iVar8 + 0x478) = 0;
        FUN_00646ea0(iVar8); // coalesce?
        *(uint*)(iVar8 + 0x478) = oldFlag;
    }

    // Now we have a block at puVar11 with header
    if (((puVar11[1] & 2) == 0) && (uVar10 = puVar11[1] & 0x7ffffff8, size + 0x10 < uVar10)) {
        // Block bigger than needed, split it
        uVar10 = uVar10 - size;
        iVar7 = (int)puVar11 + size;
        *(uint*)(iVar7 + 4) = uVar10 | 1; // new block header
        puVar11[1] = puVar11[1] & 0x80000007 | size; // update old size
        iVar1 = uVar10 + iVar7;
        uVar5 = *(uint*)(uVar10 + 4 + iVar7) & 0x7ffffff8;
        if ((*(byte*)(uVar5 + 4 + iVar1) & 1) != 0) {
            // Next block is free, merge
            uint oldFlag2 = *(uint*)(iVar8 + 0x478);
            *(uint*)(iVar8 + 0x478) = 0;
            FUN_00646ea0(iVar8);
            *(uint*)(iVar8 + 0x478) = oldFlag2;
            return puVar11 + 2;
        }
        uVar10 = uVar10 + uVar5;
        // Unlink from free list
        *(uint*)(*(int*)(iVar1 + 8) + 0xc) = *(uint*)(iVar1 + 0xc);
        *(uint*)(*(int*)(iVar1 + 0xc) + 8) = *(uint*)(iVar1 + 8);
        *(uint*)(iVar7 + 4) = uVar10 | 1;
        *(uint*)(uVar10 + iVar7) = uVar10;
        // Insert remaining block into free list (if not the low-water mark)
        if ((iVar7 != *(int*)(iVar8 + 0x440)) && (iVar1 != *(int*)(iVar8 + 0x440))) {
            iVar1 = *(int*)(iVar8 + 0x3c);
            *(int*)(iVar7 + 8) = iVar8 + 0x30;
            *(int*)(iVar7 + 0xc) = iVar1;
            *(int*)(iVar8 + 0x3c) = iVar7;
            *(int*)(iVar1 + 8) = iVar7;
            return puVar11 + 2;
        }
        *(int*)(iVar8 + 0x440) = iVar7;
        FUN_00644ae0(iVar8);
    }
    return puVar11 + 2; // return pointer to user data (after header)
}