// FUNC_NAME: BigInt::multiplyAndNormalize28
// Function at 0x00665340: Performs 28-bit polynomial multiplication (base 2^28) with carry propagation,
// used in EA EARS engine for large integer arithmetic (likely RSA/encryption).
// Parameters: a and b are input polynomials (with degree and coefficient array pointers), 
// result is output structure, shiftAmount is starting index for b (for convolution offset).

struct Polynomial28 {
    int degree;          // +0x00
    int capacity;        // +0x04  (unused here)
    int reserved;        // +0x08
    int* coefficients;   // +0x0C
};

struct BigIntResult28 {
    uint degree;         // +0x00
    uint allocatedSize;  // +0x04 (max allowed degree+1)
    uint flags;          // +0x08
    uint* coefficients;  // +0x0C
};

__declspec(noinline) int __alloca_probe(int size); // stack allocation

int multiplyAndNormalize28(Polynomial28* a, Polynomial28* b, BigIntResult28* result, uint shiftAmount)
{
    uint i, j;
    uint* tempBuf;              // local_1008 pointer from alloca
    int tempDegree;             // local_1014
    uint aDegree = a->degree;
    uint bDegree = b->degree;
    uint maxDegree = aDegree + 1 + bDegree; // product max length

    // Allocate temporary space for 64-bit intermediate coefficients (pairs)
    // The alloca probe allocates (maxDegree + 1) * 8 bytes (two uints per coeff)
    __try {
        tempBuf = (uint*)__alloca_probe((maxDegree + 1) * 8 + 8);
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return 0;
    }

    // Check if result buffer is large enough, or if memory allocation can be done
    if (maxDegree > result->allocatedSize) {
        // Try to allocate larger buffer externally
        if (FUN_00667740() == 0) {
            return 0;
        }
    }

    // Initialize temp buffer: first word stores maxDegree, rest zeroed
    tempBuf[0] = maxDegree;
    int offset = shiftAmount;
    int numA = aDegree;
    int zeroLen = (numA - (int)shiftAmount) + (int)numA; // unclear, but memset region
    _memset(tempBuf + 2 + shiftAmount * 2, 0, (zeroLen - (int)shiftAmount + numA) * 8 + 8);

    // Convolution: multiply a by b (with shift)
    tempDegree = 0;
    uint curBIdx = shiftAmount;
    if (numA > 0) {
        do {
            uint* bCoeffs = b->coefficients + curBIdx;
            uint* outStart = tempBuf + shiftAmount * 2 + 2;
            uint startOutIdx = curBIdx;
            if ((int)curBIdx < 0) {
                int adjust = (curBIdx ^ (int)curBIdx >> 31) - ((int)curBIdx >> 31);
                bCoeffs += adjust;
                outStart += adjust * 2;
                startOutIdx = 0;
            }
            uint aCoeff = *(a->coefficients + tempDegree);
            int count = numA - (int)startOutIdx;
            if (count > 0) {
                do {
                    __int64 prod = __allmul(*bCoeffs, 0, aCoeff, 0); // 32x32 -> 64
                    uint lowSum = *outStart;
                    *outStart = lowSum + (uint)prod;
                    outStart[1] += (uint)(prod >> 32) + (uint)CARRY4(lowSum, (uint)prod);
                    bCoeffs++;
                    outStart += 2;
                    count--;
                } while (count != 0);
            }
            tempDegree++;
            curBIdx--;
        } while (tempDegree < numA);
    }

    // Normalize: propagate carries and store 28-bit coefficients
    uint currentDegree = tempBuf[0];
    result->degree = currentDegree;
    int writeIdx = shiftAmount + 1;
    while (writeIdx < (int)currentDegree) {
        uint lowWord = tempBuf[writeIdx * 2];
        uint highWord = tempBuf[writeIdx * 2 + 1];
        uint carry = (lowWord >> 28) | (highWord << 4);
        uint* nextPtr = tempBuf + writeIdx * 2 + 2;
        uint nextLow = *nextPtr;
        *nextPtr = nextLow + carry;
        uint carryHigh = (highWord >> 28) + (uint)CARRY4(nextLow, carry);
        tempBuf[writeIdx * 2 + 3] += carryHigh;
        // Store 28-bit coefficient
        result->coefficients[writeIdx] = lowWord & 0x0FFFFFFF;
        writeIdx++;
    }
    // Store last coefficient
    result->coefficients[currentDegree] = tempBuf[currentDegree * 2] & 0x0FFFFFFF;

    // Zero out remaining coefficients
    while (writeIdx < (int)result->degree) {
        result->coefficients[writeIdx] = 0;
        writeIdx++;
    }

    // Trim leading zeros from result degree
    uint* coeffs = result->coefficients;
    uint deg = result->degree;
    while (deg > 0 && coeffs[deg] == 0) {
        deg--;
    }
    result->degree = deg;
    if (deg == 0) {
        result->flags = 0;
    }

    return 0;
}