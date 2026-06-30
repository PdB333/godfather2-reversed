// FUNC_NAME: ResourceSlotContainer::releaseAllBlocks

void ResourceSlotContainer::releaseAllBlocks(void)
{
    int *blockPtr;
    int blockCount;
    
    blockPtr = (int *)((char *)this + 0x1c);
    blockCount = 4;
    do {
        // +0x04 (blockPtr[-6]): pointer to resource 0
        if (blockPtr[-6] != 0) {
            // +0x10 (blockPtr[-3]): cleanup function for resource 0
            (*(void (**)(void *))(blockPtr + -3))((void *)blockPtr[-6]);
        }
        blockPtr[-6] = 0;   // clear pointer
        blockPtr[-4] = 0;   // +0x0C: unknown field
        blockPtr[-5] = 0;   // +0x14? actually blockPtr[-5] is at +0x14? Wait: blockPtr is base, -5 -> offset 0x1c-20=0x08? Actually careful: 
        // The clearing sequence is: blockPtr[-6], [-4], [-5] — that's three consecutive ints? No: -6, -5, -4 are consecutive indices: -6, -5, -4. So they clear offsets -24, -20, -16 bytes from blockPtr. So the slot's three words are at offsets -24, -20, -16 from blockPtr. That matches the pattern: pointer at -24, then unknown1 at -20, unknown2 at -16.
        // For clarity, we keep the original logic.

        // +0x14 (blockPtr[-2]): pointer to resource 1
        if (blockPtr[-2] != 0) {
            // +0x20 (blockPtr[1]): cleanup function for resource 1
            (*(void (**)(void *))(blockPtr + 1))((void *)blockPtr[-2]);
        }
        blockPtr[-2] = 0;   // clear pointer
        *blockPtr = 0;      // +0x1c: unknown field
        blockPtr[-1] = 0;   // +0x18: unknown field

        // +0x24 (blockPtr[2]): pointer to resource 2
        if (blockPtr[2] != 0) {
            // +0x30 (blockPtr[5]): cleanup function for resource 2
            (*(void (**)(void *))(blockPtr + 5))((void *)blockPtr[2]);
        }
        blockPtr[2] = 0;    // clear pointer
        blockPtr[4] = 0;    // +0x2C? Actually +4*4=16 => offset +0x2C from base? No: blockPtr[4] is at base+16 bytes = 0x1c+16=0x2C? Wait base is at 0x1c, so blockPtr[4] is at 0x1c+16=0x2C. But the cleared order is [2], [4], [3] — indices 2,3,4 are consecutive. So they clear offsets +0x08, +0x0C, +0x10 from blockPtr? Actually indices: 2,3,4 -> offsets 8,12,16 from base. So it clears three words at +8, +12, +16 (pointer at +8, then unknown1 at +12, unknown2 at +16).
        blockPtr[3] = 0;    // +0x28? Actually 3*4=12 => offset +0x28? No: base+12 = 0x1c+12=0x28.

        // +0x34 (blockPtr[6]): pointer to resource 3
        if (blockPtr[6] != 0) {
            // +0x40 (blockPtr[9]): cleanup function for resource 3
            (*(void (**)(void *))(blockPtr + 9))((void *)blockPtr[6]);
        }
        blockPtr[6] = 0;    // clear pointer
        blockPtr[8] = 0;    // +0x4C? indices 6,7,8 consecutive: offsets +24, +28, +32 from base.
        blockPtr[7] = 0;    // +0x44? index 7 = offset 28 from base = 0x1c+28=0x38

        // +0x44 (blockPtr[10]): pointer to resource 4
        if (blockPtr[10] != 0) {
            // +0x50 (blockPtr[13]): cleanup function for resource 4
            (*(void (**)(void *))(blockPtr + 13))((void *)blockPtr[10]);
        }
        blockPtr[10] = 0;   // clear pointer
        blockPtr[12] = 0;   // indices 10,11,12 consecutive: offsets +40, +44, +48 from base.
        blockPtr[11] = 0;   // +0x4C? index 11 = offset 44 from base = 0x1c+44=0x48

        blockPtr += 27;     // advance to next block (27 ints = 108 bytes)
        blockCount--;
    } while (blockCount != 0);
}