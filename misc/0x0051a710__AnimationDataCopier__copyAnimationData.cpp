// FUNC_NAME: AnimationDataCopier::copyAnimationData

// Function at 0x0051a710: Copies an array of animation/data blocks from a source data structure to a destination array.
// The source structure (pointed to by dest+0x10) contains a count at offset 0x1c, and arrays of pointers (at offset 0x30)
// and dwords (at offset 0x38) with stride 0x24.
// The destination array starts at dest+0xf0, each element is 20 bytes (5 dwords): 
//   [0] = source dword at offset 0x38 + i*0x24
//   [1] = 0
//   [2] = first dword of the structure pointed to by source pointer at offset 0x30 + i*0x24 (or 0 if null)
//   [3] = pointer to the remainder of that structure (after first dword) (or 0 if null)
//   [4] = 0

void __fastcall copyAnimationData(void* /*unused*/, void* dest)
{
    // dest is a large structure containing:
    // +0x10: pointer to source data (int*)
    // +0x80: ushort count (from source + 0x1c byte)
    // +0xf0: start of output array (20 bytes per element)

    uint8_t countByte = *(uint8_t*)(*(int32_t*)((uint8_t*)dest + 0x10) + 0x1c);
    *(uint16_t*)((uint8_t*)dest + 0x80) = (uint16_t)countByte;

    if (countByte != 0)
    {
        int32_t srcOffset = 0;
        uint32_t* destEntry = (uint32_t*)((uint8_t*)dest + 0xfc); // Start writing at dest+0xfc, but first write goes to dest+0xf0

        do
        {
            int32_t* srcBase = *(int32_t**)((uint8_t*)dest + 0x10);

            // Copy source dword from offset 0x38 + srcOffset
            destEntry[-3] = *(uint32_t*)((uint8_t*)srcBase + srcOffset + 0x38); // writes to dest+0xf0 + i*20

            // Copy data from pointer at offset 0x30 + srcOffset
            uint32_t* srcPtr = *(uint32_t**)((uint8_t*)srcBase + srcOffset + 0x30);
            if (srcPtr == nullptr)
            {
                destEntry[-1] = 0; // writes to dest+0xf8 + i*20
                destEntry[0] = 0;  // writes to dest+0xfc + i*20
            }
            else
            {
                destEntry[-1] = *srcPtr;               // first dword of sub-structure
                destEntry[0] = (uint32_t)(srcPtr + 3); // pointer to after first dword (skip 12 bytes)
            }

            destEntry[-2] = 0; // writes to dest+0xf4 + i*20
            destEntry[1] = 0;  // writes to dest+0x100 + i*20

            countByte--;
            destEntry += 5;   // move to next output element (5 dwords = 20 bytes)
            srcOffset += 0x24; // move to next source element (0x24 bytes stride)
        } while (countByte > 0);
    }
}