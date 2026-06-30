// FUNC_NAME: rsaDecryptData
// Function at 0x006683b0: RSA decryption of a buffer using modular exponentiation. 
// The input is a pointer to a descriptor structure containing data size and data pointer.
// Returns 0 on success, -2 (0xFFFFFFFE) on failure.
// Uses custom big integer library (BigNum) with allocation/mod/addition/shift operations.

struct BigNum {
    int* digits;      // +0x00: pointer to limb array
    int size;         // +0x04: number of limbs used
    int capacity;     // +0x08: allocated limbs
};

// Forward declarations of helper functions (assumed from context)
int validateState();               // FUN_006678c0: returns 0 on success
void* getDecryptContext();         // FUN_00665b10: returns RSA key context
int bigNumAlloc(BigNum* out);      // FUN_0066a660: allocate big number (size from param)
int bigNumModule(const BigNum* a, int* out); // FUN_0066a780: a mod out (out is scalar)
int bigNumAdd(const BigNum* a, const BigNum* b); // FUN_0066bb40: a += b
int freeBigNum(int count);         // FUN_006687e0: free temporary big numbers (count given)
int clearBigNum(BigNum* a);        // FUN_006657c0: clear (zero) and free a big number

// Main decryption function
int decryptionRoutine(int* pDescriptor) {
    int* pSrc;                  // piVar1
    unsigned int halfSize;      // uVar7
    unsigned int alignedHalf;   // uVar2
    size_t allocSize;           // _Size
    unsigned int* tempBuf;      // local_28 (first half buffer)
    unsigned int* tempBuf2;     // local_38 (second half buffer)
    unsigned int firstHalfSize; // local_34
    int secondHalfSize;         // local_44[0]
    BigNum bigA;                // local_24 (three ints)
    BigNum bigB;                // local_54
    BigNum bigC;                // local_64
    BigNum bigD;                // local_14
    void* context;              // local_48 / local_18 / local_8 / local_58 - used for temporary big nums
    int retVal;                 // param_1 cast to int*

    pSrc = pDescriptor;
    halfSize = *pDescriptor / 2;

    // Align halfSize to multiple of 64? (bitwise trick)
    alignedHalf = halfSize & 0x8000003f;
    if ((int)alignedHalf < 0) {
        alignedHalf = (alignedHalf - 1 | 0xffffffc0) + 1;
    }
    allocSize = (halfSize - alignedHalf) + 0x80;   // expected number of uint32s

    // Allocate temporary buffer for first half
    tempBuf = (unsigned int*)_calloc(4, allocSize);
    if (tempBuf == nullptr) {
        return 0xfffffffe;    // allocation failure
    }

    firstHalfSize = 0;
    // secondHalfSize initialized later

    // Validate internal state 5 times (e.g., check seed, key availability)
    if (validateState() == 0 &&
        validateState() == 0 &&
        validateState() == 0 &&
        validateState() == 0 &&
        validateState() == 0) {

        // Copy first half of data from descriptor[3] (pointer to data) into tempBuf
        unsigned int* srcData = (unsigned int*)pDescriptor[3];
        for (unsigned int i = 0; i < halfSize; i++) {
            tempBuf[i] = srcData[i];
        }

        // Copy second half of data into tempBuf2? Actually it's local_38 which is uninitialized here.
        // But the decompiler shows that after the first copy, it copies the rest into local_38.
        // local_38 is not allocated yet; it's used but will be freed later. Possibly it's the same buffer?
        // Actually it looks like it writes to local_38 before allocation? That's a bug in decompilation.
        // We need to allocate local_38 first. However, the code allocates tempBuf and then does the copy.
        // The second copy loop uses local_38 which is uninitialized. That suggests local_38 might be allocated elsewhere.
        // Reread: The second copy uses "puVar6 = local_38;" but local_38 is a local variable (undefined4*).
        // It's not initialized. Possibly it was meant to be the same as tempBuf? Or it's a second buffer allocated later?
        // Looking at the cleanup: there's "if (local_38 != (undefined4 *)0x0)" so it may have been allocated by one of the helper functions.
        // Actually, the loop condition "if ((int)uVar2 < *piVar1)" implies it copies remaining part into a buffer that is already allocated.
        // Since local_38 is not allocated before the copy, this is suspicious. Possibly the decompiler confused the order.
        // Given the pattern, it's likely that after copying first half, we allocate a second buffer and copy remaining.
        // But the code shows the copy before allocation? Let's reorder: The copy happens after the calloc, but before the helper calls.
        // Actually, the copy loops are before the validateState()? No, they are inside the validateState() block.
        // Wait: The copy loops are placed right after the first validation? The decompiled code shows:
        // if (iVar3 == 0) { ... } block contains the copy loops. So the copy happens after validateState returns 0.
        // At that point, local_38 might still be uninitialized. This could be a decompilation artifact due to variable reuse.
        // Possibly local_38 is actually a pointer inside the allocated tempBuf? Or it's from a previous allocation?
        // To make it consistent, I'll assume that local_38 is a pointer to the second half starting at tempBuf + halfSize.
        // But the code treats local_38 as a separate pointer and frees it separately. So it must be a separate allocation.
        // The most likely explanation is that the second copy actually uses tempBuf2 which is allocated later.
        // But the code doesn't show allocation for tempBuf2 before the copy. Unless local_38 is actually the same as tempBuf? No.
        // Let's trust the decompiler and treat local_38 as a separate buffer that is assumed to be allocated before the copy.
        // Since the prototype shows it's freed later, I'll assume it was allocated by a previous call or is part of the context.
        // For reconstruction, I'll add an allocation for local_38 (tempBuf2) before the copy, based on the size calculation.
        // This is necessary for correctness.

        // Allocate second half buffer (size = secondHalf)
        secondHalfSize = pDescriptor[0] - halfSize;
        tempBuf2 = (unsigned int*)_calloc(4, secondHalfSize);
        if (tempBuf2 == nullptr) {
            // cleanup tempBuf
            _memset(tempBuf, 0, firstHalfSize * 4);
            _free(tempBuf);
            return 0xfffffffe;
        }

        // Now copy second half
        for (int i = halfSize; i < pDescriptor[0]; i++) {
            tempBuf2[i - halfSize] = srcData[i];
        }

        // Set sizes
        firstHalfSize = halfSize;
        // secondHalfSize already set

        // Get decryption key/context
        context = getDecryptContext();

        // Allocate big numbers for computation
        retVal = bigNumAlloc(&bigA);    // bigA = first half? Actually uses local_24 (bigA)
        if (retVal == 0) {
            retVal = bigNumAlloc(&bigB); // bigB = second half? Uses local_54
        }
        // ... (continue as decompiled)
        if (retVal == 0) {
            // Perform modular reduction: second half mod first half size?
            retVal = bigNumModule(&bigB, &firstHalfSize);
        }
        if (retVal == 0) {
            // More arithmetic: copy bigA to bigC? And then bigC = bigA + bigB?
            retVal = bigNumAlloc(&bigC);
            if (retVal == 0) {
                retVal = bigNumAdd(&bigA, &bigB);
                if (retVal == 0) {
                    retVal = bigNumModule(&bigD, &bigC); // bigD = bigC mod something?
                }
            }
            // Free intermediate big numbers
            if (retVal == 0) {
                retVal = freeBigNum(halfSize);
                if (retVal == 0) {
                    retVal = freeBigNum(halfSize * 2);
                    if (retVal == 0) {
                        retVal = clearBigNum(&bigA);
                        if (retVal == 0) {
                            retVal = clearBigNum(&bigC);
                        }
                    }
                }
            }
        }

        // Cleanup tempBuf2
        if (tempBuf2 != nullptr) {
            _memset(tempBuf2, 0, secondHalfSize * 4);
            _free(tempBuf2);
            tempBuf2 = nullptr;
            // Reset secondHalfSize? The code sets local_44[0..2] to 0.
            // But local_44 is an int[3] array. We can ignore.
        }
    }

    // Cleanup bigD if allocated
    if (/* local_18 != nullptr */) {
        _memset(/* local_18 */, 0, /* bigA size */);
        _free(/* local_18 */);
        // Clear bigA
    }
    // ... other cleanup blocks follow decompiled pattern

    // Final cleanup of tempBuf
    if (tempBuf != nullptr) {
        _memset(tempBuf, 0, firstHalfSize * 4);
        _free(tempBuf);
    }

    return retVal;   // 0 on success, -2 on failure
}