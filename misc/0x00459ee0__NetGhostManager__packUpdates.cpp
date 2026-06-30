// FUNC_NAME: NetGhostManager::packUpdates
__thiscall size_t NetGhostManager::packUpdates(uint pairCount, uint* pairArray, uint8* outputBuffer)
{
    // this fields:
    // +0x2c: uint16 activeItemCount
    // +0x38: uint16 maxItemCount
    // +0x90: uint* itemIdList
    // +0x84: uint8* scratchBuffer
    // +0x06: uint8  packetType (0..4)
    // +0x08: uint32 flags (bit 0x4000 = someFlag)

    size_t result = 0;

    if (this->activeItemCount != 0) {
        uint16 maxCount = this->maxItemCount;
        uint16 activeCount = this->activeItemCount;
        uint matchCount = 0;

        // local arrays for matched pairs (pointer to itemId and associated value)
        uint* matchedItemPtr[64];
        uint  matchedValue[64];

        uint* currentIdPtr = this->itemIdList;
        for (uint i = 0; i < activeCount; i++) {
            uint id = *currentIdPtr;

            // Process 4 pairs per iteration (unrolled for speed)
            uint processed = 0;
            if (pairCount > 3) {
                uint* pairPtr = pairArray + 7; // point to end of first 4 pairs? Actually base+0x14?
                // Let's re-derive from decompiled:
                // puVar7 = (undefined4 *)(param_3 + 0x14);
                // That points to the 5th element (index 4) of first pair? Actually each pair is 8 bytes (2 uints).
                // param_3 is base of pairs. param_3+0x14 = param_3+20 = 20 bytes = 2.5 pairs, odd.
                // The decompiled shows puVar7 = param_3 + 0x14, then uses puVar7[-5],[-4],[-3],[-2],[-1],[0],[1],[2] etc.
                // That suggests puVar7 points to the start of the 3rd pair (since each pair 8 bytes, offset 20 = 2*8 + 4, so mid-pair? Actually 20/8=2.5, so it's offset halfway into the third pair? That seems buggy.
                // Possibly param_3+0x14 is a pointer to a structure of 4 uints? The disassembly in Ghidra might be misleading.
                // Let's assume the pairArray is an array of uint pairs (8 bytes each). The unrolled loop checks 4 consecutive pairs: the pairs at indices [0..3] but using negative offsets.
                // Actually puVar7 starts at param_3+0x14, then puVar7[-5] = param_3+0x14-20 = param_3-6 = ? That doesn't make sense.
                // The decompiled uses puVar7[-5], puVar7[-4], puVar7[-3], puVar7[-2], puVar7[-1], puVar7[0], puVar7[1], puVar7[2] etc.
                // Possibly puVar7 is a uint* pointing into the middle of the pair array, and the offsets are relative to a 4*8=32 byte block?
                // Given complexity, I'll simplify to a sequential loop.
            }

            // Straightforward loop through pairs
            for (uint j = 0; j < pairCount; j++) {
                if (id == pairArray[j*2]) {
                    if (matchCount < 64) {
                        matchedItemPtr[matchCount] = currentIdPtr;
                        matchedValue[matchCount] = pairArray[j*2+1];
                        matchCount++;
                    }
                }
            }

            currentIdPtr++;
        }

        if ((matchCount != 0) && (maxCount != 0)) {
            bool someFlag = (this->flags & 0x4000) == 0x4000;

            // Initialize a global temporary buffer (DAT_01174080) of maxCount * 16 bytes
            uint32* tempBuf = &DAT_01174080;
            for (uint k = 0; k < maxCount; k++) {
                tempBuf[0] = uVar2;
                tempBuf[1] = uVar3;
                tempBuf[2] = uVar4;
                tempBuf[3] = uVar5;
                tempBuf += 4;
            }

            // Call some processing for each matched item
            for (uint m = 0; m < matchCount; m++) {
                FUN_004cd420();
            }

            // Obtain a buffer pointer from the temporary buffer
            void* src = (void*)FUN_004cd4b0(&DAT_01174080, this->scratchBuffer, maxCount);

            // Calculate packet size per item
            int perItemSize;
            if (this->packetType == 0) {
                perItemSize = (!someFlag) * 8 + 12; // if !someFlag => 20, else 12
            } else if (this->packetType >= 1 && this->packetType < 5) {
                perItemSize = ((-(int)someFlag) & 0xFFFFFFF0) + 32; // if someFlag => 16+32=48? Actually -(uint)someFlag is 0 or -1 (0xFFFFFFFF). &0xFFFFFFF0 => if someFlag true then 0xFFFFFFF0, else 0. Then +32 => either 32 or 0xFFFFFFF0+32? That overflows. Possibly it's (-(int)someFlag) & 0xFFFFFFF0 => if someFlag true, -1 & 0xFFFFFFF0 = 0xFFFFFFF0 (4294967280) +32 = 0x100000010? Overflow? Something wrong.
                // Let's trust decompiled: iVar8 = (-(uint)bVar13 & 0xfffffff0) + 0x20
                // If bVar13 true: -1 & 0xfffffff0 = 0xfffffff0, +0x20 = 0x100000010? That's huge. Possibly int overflow? Actually it's uint, then assigned to int iVar8, then used as size_t? Might be intended as negative? But later used in multiplication and memcpy. Might be compiler optimization.
                // Common pattern: if bVar13 then perItemSize=16+32=48? Actually (-1 & 0xfffffff0) = 0xfffffff0, which is -16 as signed. Then +32 = 16. If bVar13 false, 0 & 0xfffffff0 = 0, +32 = 32. So perItemSize = (bVar13 ? 16 : 32). That makes sense: (-(uint)1) = 0xFFFFFFFF, &0xFFFFFFF0 = 0xFFFFFFF0 = -16 signed, +32 = 16. Good.
                perItemSize = someFlag ? 16 : 32;
            } else {
                perItemSize = 0;
            }

            size_t copySize = perItemSize * maxCount;
            _memcpy(outputBuffer + 0x84, src, copySize);
            return copySize;
        }
    }
    return 0;
}