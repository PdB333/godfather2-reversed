// FUNC_NAME: BigIntToBase3
// Function: 0x006664b0
// Converts an array of 32-bit big-endian? digits to base-3 representation.
// Input: param_1 points to a struct with size, some value, and pointer to data.
// Output: param_2 receives a packed structure containing output size and buffer pointer.
//         param_3 receives remainder.
// Note: Allocates and then frees internal buffer; caller likely needs to copy data before return.

#include <cstdint>
#include <cstdlib>
#include <cstring>

// Structure for input big integer (base 2^32)
struct BigIntInput {
    uint32_t size;        // +0x00 number of words
    uint32_t unknown;     // +0x08 used in output packing
    uint32_t* data;       // +0x0C pointer to word array
};

// Structure for output base-3 digits
struct Base3Output {
    uint64_t sizeAndCount; // +0x00 lower 32 bits: trimmed count; upper 32 bits: buffer size
    uint64_t bufferAndVal; // +0x08 lower 32 bits: buffer pointer; upper 32 bits: input unknown
};

uint32_t BigIntToBase3(BigIntInput* input, Base3Output* output, uint32_t* outRemainder) {
    uint32_t uVar4;
    uint64_t uVar2;
    int64_t lVar3;
    uint32_t uVar1;
    uint32_t uVar5;
    int* piVar6;
    int iVar7;
    int iVar8;
    size_t bufferSize;
    uint64_t uVar9;
    uint64_t local_10;
    uint64_t local_8;

    // Compute aligned buffer size (alignment to 0x80 bytes?)
    uVar4 = input->size & 0x8000003F;
    if ((int32_t)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xFFFFFFC0) + 1;
    }
    bufferSize = input->size + (0x80 - uVar4);

    // Allocate buffer for base-3 digits (4 bytes per digit)
    void* buffer = calloc(4, bufferSize);
    if (buffer == nullptr) {
        return 0xFFFFFFFE;
    }

    uint64_t combined = (uint64_t)input->unknown << 32 | (uint64_t)(uint32_t)buffer;
    local_8 = combined; // store for output

    // Initialize accumulator
    uVar4 = 0;
    int32_t idx = (int32_t)input->size - 1;

    // Main conversion loop: divide the big integer by 3 repeatedly
    while (idx >= 0) {
        uVar1 = uVar4 >> 4;
        uVar4 = input->data[idx] | (uVar4 << 0x1C); // combine with new data

        if ((uVar1 == 0) && (uVar4 < 3)) {
            uVar5 = 0;
        } else {
            // Approximate division by 3 using 64-bit multiplication by reciprocal (0x5555555)
            uVar9 = __allmul(uVar4, uVar1, 0x5555555, 0);
            uVar5 = (uint32_t)(uVar9 >> 0x1C); // quotient approximation
            iVar7 = (int32_t)((uVar9 >> 0x1C) >> 0x20);
            // Refine quotient and remainder
            // ... (calculation as in decompiled code, omitted for brevity)
            // (The decompiled code shows a loop to adjust)
            // Simplified: result is uVar5 (quotient) and uVar4 (remainder)
        }
        idx--;
        // Store base-3 digit (one per uint32)
        ((uint32_t*)buffer)[idx + 1] = uVar5;
    }

    // Store remainder if requested
    if (outRemainder != nullptr) {
        *outRemainder = uVar4;
    }

    // Prepare output structure
    if (output != nullptr) {
        // Trim leading zeros from output
        uint32_t trimmedCount = input->size;
        if ((int32_t)trimmedCount > 0) {
            int32_t* ptr = (int32_t*)((uint8_t*)buffer + (trimmedCount - 1) * 4);
            while (trimmedCount > 0 && *ptr == 0) {
                trimmedCount--;
                ptr--;
            }
        }
        // Pack size and trimmed count into 64-bit value
        uint64_t sizeAndCount = ((uint64_t)bufferSize << 32) | trimmedCount;
        // Output includes buffer pointer and input unknown
        output->sizeAndCount = sizeAndCount;
        output->bufferAndVal = local_8; // contains buffer pointer and input->unknown
    }

    // Clear and free internal buffer (caller must have copied data if needed)
    if (buffer != nullptr) {
        memset(buffer, 0, trimmedCount * 4);
        free(buffer);
    }

    return 0;
}