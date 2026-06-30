// FUNC_NAME: PolynomialHash::update
// Address: 0x00664fa0
// Role: Updates a 28-bit polynomial hash state with new data using a multiplier.
// The hash state is stored as a dynamic array of 28-bit values (packed into 32-bit ints).
// param_1: HashState* (count at +0x00, capacity at +0x04, unknown at +0x08, buffer at +0x0C)
// param_2: DataBlock* (count at +0x00, buffer at +0x0C)
// param_3: Multiplier (polynomial coefficient)

#include <cstdint>

// Forward declarations of helper functions (from other modules)
int FUN_00667740();  // Possibly checks capacity or allocates
int FUN_00665c30();  // Possibly random or finalization check
int FUN_0066c8d0(int* param_1); // Finalize hash and return result

// 64-bit multiply helper (replaces __allmul)
static inline uint64_t mul64(uint32_t a, uint32_t b) {
    return static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
}

int PolynomialHash::update(int* hashState, int* dataBlock, int multiplier) {
    int count = *hashState;               // +0x00
    int dataCount = *dataBlock;           // +0x00
    int capacity = hashState[1];          // +0x04
    int* hashBuffer = reinterpret_cast<int*>(hashState[3]); // +0x0C
    int* dataBuffer = reinterpret_cast<int*>(dataBlock[3]); // +0x0C

    // Check if there's enough capacity or if we need to reallocate (via FUN_00667740)
    if ((dataCount + 1 <= capacity) || (FUN_00667740() != 0)) {
        // Local array for 64-bit intermediate values (pairs of uint32)
        // Allocated via alloca_probe due to large size
        uint32_t localArray[1023]; // Actually used as pairs: low, high
        uint32_t* localPtr = localArray;

        // Step 1: Copy existing hash values into local array as 64-bit (low word only)
        int i = 0;
        if (count > 0) {
            uint32_t* src = reinterpret_cast<uint32_t*>(hashBuffer);
            for (i = 0; i < count; i++) {
                *localPtr = *src;
                localPtr[1] = 0;
                localPtr += 2;
                src++;
            }
        }

        // Step 2: Extend local array to size (dataCount * 2 + 1) with zeros
        int targetSize = dataCount * 2 + 1;
        if (i < targetSize) {
            // Fill remaining with zeros
            *localPtr = 0;
            localPtr[1] = 0;
            uint32_t* fillStart = localPtr + 2;
            uint32_t* fillEnd = localArray + targetSize * 2;
            // Use memcpy-like loop to propagate zeros
            for (uint32_t* p = fillStart; p < fillEnd; p++) {
                *p = 0;
            }
            localPtr = localArray + targetSize * 2;
        }

        // Step 3: Multiply each data element by (multiplier * current local value) and add with carry
        int j = 0;
        if (dataCount > 0) {
            uint32_t* dataPtr = reinterpret_cast<uint32_t*>(dataBuffer);
            uint32_t* localRead = localArray;
            int remainingData = dataCount;
            do {
                uint32_t currentLocalLow = *localRead;
                uint32_t* dataIter = dataPtr;
                uint32_t* localWrite = localRead;
                int remainingInner = dataCount;
                if (dataCount > 0) {
                    do {
                        // 64-bit multiply: dataIter[0] * (currentLocalLow * multiplier) & 0x0FFFFFFF
                        uint64_t product = mul64(*dataIter, (currentLocalLow * static_cast<uint32_t>(multiplier)) & 0x0FFFFFFF);
                        uint32_t oldLow = *localWrite;
                        uint64_t sum = static_cast<uint64_t>(oldLow) + product;
                        *localWrite = static_cast<uint32_t>(sum);
                        localWrite[1] += static_cast<uint32_t>(sum >> 32) + (oldLow > static_cast<uint32_t>(sum) ? 1 : 0);
                        remainingInner--;
                        dataIter++;
                        localWrite += 2;
                    } while (remainingInner != 0);
                }
                // Carry propagation: shift right 28 bits from current pair to next
                uint32_t carryLow = *localRead >> 28;
                uint32_t carryHigh = localRead[1] << 4;
                uint32_t carry = carryLow | carryHigh;
                uint32_t* nextPair = localRead + 2;
                uint32_t nextLow = *nextPair;
                *nextPair = nextLow + carry;
                nextPair[1] += (localRead[1] >> 28) + (nextLow > (nextLow + carry) ? 1 : 0);
                localRead += 2;
                remainingData--;
                j = dataCount;
            } while (remainingData != 0);
        }

        // Step 4: Propagate carries across remaining elements
        uint32_t* current = localArray + j * 2;
        int idx = j + 1;
        uint32_t* next = localArray + idx * 2;
        if (idx <= targetSize) {
            int remaining = targetSize - idx + 1;
            do {
                uint32_t carryLow = current[1];
                uint32_t carryHigh = *current >> 28;
                uint32_t carry = carryLow << 4 | carryHigh;
                uint32_t nextLow = *next;
                *next = nextLow + carry;
                next[1] += (carryLow >> 28) + (nextLow > (nextLow + carry) ? 1 : 0);
                current += 2;
                next += 2;
                remaining--;
            } while (remaining != 0);
        }

        // Step 5: Truncate to 28 bits and store back to hash buffer
        uint32_t* src = localArray + dataCount * 2;
        uint32_t* dst = reinterpret_cast<uint32_t*>(hashBuffer);
        int written = 0;
        if (dataCount != -1 && dataCount + 1 > 0) {
            do {
                *dst = *src & 0x0FFFFFFF;
                written++;
                dst++;
                src += 2;
            } while (written < *dataBlock + 1);
        }

        // Step 6: Zero out remaining entries in hash buffer
        if (written < count) {
            for (int k = count - written; k > 0; k--) {
                *dst = 0;
                dst++;
            }
        }

        // Step 7: Update count and trim trailing zeros
        int newCount = *dataBlock;
        *hashState = newCount + 1;
        if (newCount + 1 > 0) {
            do {
                if (hashBuffer[*hashState - 1] != 0) break;
                newCount = *hashState - 1;
                *hashState = newCount;
            } while (newCount > 0);
        }

        // Step 8: If count became zero, clear unknown field
        if (*hashState == 0) {
            hashState[2] = 0; // +0x08
        }

        // Step 9: Check for finalization
        int result = FUN_00665c30();
        if (result != -1) {
            result = FUN_0066c8d0(hashState);
            return result;
        }
        return 0;
    }
    return 0;
}