// FUNC_NAME: ConvertToBase3
// This function converts a big integer represented as an array of 32-bit words (in 28-bit chunks?) into base-3 digits.
// param1: pointer to structure { uint32_t size; uint32_t unknown; uint32_t unknown2; uint32_t* digits; }
// param2: optional output pointer to receive { size, pointer } pair (two 64-bit values)
// param3: optional remainder output (mod 3)
// Returns 0 on success, -2 on allocation failure.
int ConvertToBase3(uint32_t* inputData, uint64_t* output, uint32_t* remainder)
{
    uint32_t uVar1;
    uint64_t uVar2;
    uint64_t lVar3;
    uint32_t uVar4;
    uint32_t uVar5;
    int32_t* piVar6;
    int32_t iVar7;
    int32_t iVar8;
    size_t _Size;
    uint64_t uVar9;
    uint64_t local_10; // 64-bit temp
    uint64_t local_8;  // 64-bit temp (lower 32 = input[2], upper 32 = allocated ptr)

    // Extract size and sign-extend low 6 bits? This is odd but preserved.
    uVar4 = inputData[0] & 0x8000003f;
    if ((int32_t)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xffffffc0) + 1;
    }
    // Allocate buffer for base-3 digits. Size = originalSize + (128 - signExtended6bit)
    _Size = inputData[0] + (0x80 - uVar4);
    local_8._4_4_ = (uint32_t*)_calloc(4, _Size); // allocate _Size uint32s
    if (local_8._4_4_ == nullptr) {
        return -2;
    }
    local_10._0_4_ = inputData[0]; // original size
    iVar8 = (int32_t)local_10 - 1; // index from size-1 down to 0
    uVar4 = 0;
    // Store pointer and other data in 64-bit temp: low = inputData[2], high = allocated buffer
    local_8 = (uint64_t)(uintptr_t)local_8._4_4_ | ((uint64_t)inputData[2] << 32);

    while (iVar8 >= 0) {
        uVar1 = uVar4 >> 4; // high 28 bits of previous remainder
        // Combine 4 bits from previous remainder with next 28-bit chunk from input
        uVar4 = inputData[3][iVar8] | (uVar4 << 0x1c);

        // Divide combined 28+4 bits by 3 using multiply by reciprocal (0x5555555 = 2^28 / 3 approx)
        uVar9 = __allmul(uVar4, uVar1, 0x5555555, 0);
        uVar5 = (uint32_t)(uVar9 >> 0x1c); // quotient estimate (28 bits)
        iVar7 = (int32_t)((uVar9 >> 0x1c) >> 0x20); // high part of quotient (unused?)

        // Correction for integer division
        iVar7 = (uVar1 - ((iVar7 << 1 | (uint32_t)((int32_t)(uVar9 >> 0x20) << 4) >> 0x1f) + iVar7 +
                           (uint32_t)((uVar5 * 2 + uVar5) < 0x100000000 ? 0 : 1))) - (uint32_t)(uVar4 < uVar5 * 3);
        // This complex expression approximates the exact quotient adjustment
        for (uVar4 = uVar4 - uVar5 * 3; iVar7 != 0 || uVar4 > 2; uVar4 -= 3) {
            uVar5 = uVar5 + 1;
            iVar7 = iVar7 - 1 + (uint32_t)(uVar4 > 2);
        }

        // Store quotient digit into output buffer (starting at offset 4)
        *(uint32_t*)((uintptr_t)(local_8._4_4_) + iVar8 * 4 + 4) = uVar5;
        iVar8--;
    }

    // If remainder output requested, store final remainder
    if (remainder != nullptr) {
        *remainder = uVar4;
    }

    // Prepare output if requested
    if (output != nullptr) {
        // Trim leading zeros: find first non-zero digit from the end
        if ((int32_t)(uint32_t)local_10 > 0) {
            uint32_t* ptr = (uint32_t*)((uintptr_t)(local_8._4_4_) + (uint32_t)local_10 * 4 - 4);
            do {
                if (*ptr != 0) break;
                local_10._0_4_ = (uint32_t)local_10 - 1;
                ptr--;
            } while ((int32_t)(uint32_t)local_10 > 0);
        }
        // Pack trimmed length and total allocation size into 64-bit
        local_10 = (uint64_t)_Size << 32 | (uint32_t)local_10;
        uVar2 = local_10;
        if ((uint32_t)local_10 == 0) {
            // If no data, zero out pointer (low part)
            local_8 = (uint64_t)(uintptr_t)local_8._4_4_ << 32;
        }
        lVar3 = local_8;
        // Set output: first 64-bit = (trimmedLength, allocationSize), second 64-bit = (inputData[2], pointer)
        output[0] = uVar2;
        output[1] = lVar3;
    }

    // Cleanup: zero and free the allocated buffer (Note: this invalidates the pointer returned via output)
    if (local_8._4_4_ != nullptr) {
        _memset(local_8._4_4_, 0, (uint32_t)local_10 * 4);
        _free(local_8._4_4_);
    }
    return 0;
}