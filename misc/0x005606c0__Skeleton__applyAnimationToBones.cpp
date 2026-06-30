// FUNC_NAME: Skeleton::applyAnimationToBones
// Address: 0x005606c0
// Updates bone transforms from source animation buffer to destination skeleton buffer,
// applying per-bone transformations and populating mapping pairs.

void Skeleton::applyAnimationToBones(int param_1)
{
    int numBones;
    int* pSourceBone;
    int* pDestBone;
    int* pMappingPair;
    int i;
    int* pMappingBase;
    int* pResult;

    // Call a function on some subsystem (maybe a memory barrier or flush)
    FUN_00bf0850(*(int*)(this + 0x18) + 0xe0);

    // Virtual call: call function at offset 0xc in the vtable pointed to by this+0x3c
    // The argument is param_1 + 8 (likely a pointer to additional data)
    (**(code**)(**(int**)(this + 0x3c) + 0xc))(*(undefined4*)(param_1 + 8));

    numBones = *(int*)(this + 0x4c);  // Number of bones to process
    i = 0;
    if (numBones > 0)
    {
        pMappingBase = (int*)(this + 0x150);  // Array of pairs (2 ints each) for mapping
        pSourceBone = (int*)(*(int*)(this + 0x118));  // Source bone buffer (stride 0x40)
        pDestBone = (int*)(*(int*)(this + 0x48));     // Destination bone buffer (stride 0xC0)

        do
        {
            // Copy a 4-byte value from source offset +0x2c to dest offset +0x50
            *(int*)((int)pDestBone + 0x50) = *(int*)((int)pSourceBone + 0x2c);

            // Copy the first 32 bytes (8 dwords) from source to dest
            *(int*)((int)pDestBone) = *(int*)((int)pSourceBone);
            *(int*)((int)pDestBone + 4) = *(int*)((int)pSourceBone + 4);
            *(int*)((int)pDestBone + 8) = *(int*)((int)pSourceBone + 8);
            *(int*)((int)pDestBone + 0xc) = *(int*)((int)pSourceBone + 0xc);
            *(int*)((int)pDestBone + 0x10) = *(int*)((int)pSourceBone + 0x10);
            *(int*)((int)pDestBone + 0x14) = *(int*)((int)pSourceBone + 0x14);
            *(int*)((int)pDestBone + 0x18) = *(int*)((int)pSourceBone + 0x18);
            *(int*)((int)pDestBone + 0x1c) = *(int*)((int)pSourceBone + 0x1c);

            // Copy additional 12 bytes from source offsets 0x20,0x24,0x28 to dest offsets 0x20,0x24,0x28
            *(int*)((int)pDestBone + 0x20) = *(int*)((int)pSourceBone + 0x20);
            *(int*)((int)pDestBone + 0x24) = *(int*)((int)pSourceBone + 0x24);
            *(int*)((int)pDestBone + 0x28) = *(int*)((int)pSourceBone + 0x28);

            // Clear the mapping pair for this bone
            pMappingPair[0] = 0;
            pMappingPair[1] = 0;

            // If the value at dest offset 0x24 is non-zero, perform a lookup
            if (*(int*)((int)pDestBone + 0x24) != 0)
            {
                pResult = (int*)FUN_005566a0(*(int*)((int)pDestBone + 0x24) + 0x10, *(int*)((int)pDestBone + 0x28));
                if (pResult != (int*)0x0)
                {
                    pMappingPair[0] = pResult[1];
                    pMappingPair[1] = pResult[0];
                }
            }

            // Advance to next bone
            pSourceBone = (int*)((int)pSourceBone + 0x40);  // Stride 0x40 (64 bytes)
            pDestBone = (int*)((int)pDestBone + 0xC0);      // Stride 0xC0 (192 bytes)
            pMappingPair += 2;  // Each pair is 2 ints
            i++;
        } while (i < numBones);
    }
    return;
}