// FUNC_NAME: MemoryPool::compactMemory
// Address: 0x00626ac0
// This function manages two parallel arrays: one with 0x18-byte elements (first array)
// and one with 8-byte elements (second array). It attempts to shrink the allocated memory
// if either array is significantly underutilized. It also clears stale entries in the
// second array and triggers a debug/consistency check function (FUN_00626640) under
// specific conditions.

#include <cstdint>

// Allocation functions (likely from EARS memory system)
extern void* reallocMemory(void*, uint32_t newSize);   // DAT_012059dc
extern void freeMemory(void* ptr);                     // DAT_012059e0
extern void handleAllocationFailure();                 // FUN_00635a80
extern void handleOutOfMemory();                       // FUN_00633920
extern void checkMemoryConsistency();                  // FUN_00626640
extern void finalizeMemoryUpdate();                    // FUN_00635b50

class MemoryPool {
public:
    // Offsets inferred from decompiler:
    // +0x08: int* m_firstArray         - base of first array (stride 0x18)
    // +0x14: int m_firstArrayEnd       - end pointer (as integer) of first array
    // +0x28: int m_firstArrayCurrent   - current allocation pointer (for realloc)
    // +0x2c: ushort m_firstArrayCapacity - capacity of first array in elements
    // +0x24: uint m_totalAllocated     - total memory allocated (tracked by allocator)
    // +0x1c: int* m_secondArray        - base of second array (stride 8)
    // +0x20: int m_secondArrayCapacity - capacity of second array in elements
    // +0x18: int m_secondArrayEnd      - end pointer of second array (integer)
    // +0x10: void* m_allocator         - pointer to allocator with +0x24 field for total bytes
    // +0x40: int m_debugThreshold      - threshold for debug check
    // +0x44: uint8_t* m_debugFlags     - pointer to debug flags byte (offset 5 checked)

private:
    // Internal fields (relative to 'this' in ESI)
    // Actually these are member variables; we'll just use offsets for clarity.

public:
    void compactMemory() {
        // --- Initial debug/consistency check ---
        // If the threshold is > 3 and the debug byte at offset 5 has bits 0 and 4 clear,
        // call the consistency check function.
        int* thisPtr = reinterpret_cast<int*>(this);
        int threshold = thisPtr[0x40 / 4];           // +0x40
        uint8_t* debugFlags = reinterpret_cast<uint8_t*>(thisPtr[0x44 / 4]); // +0x44
        if (threshold > 3 && (debugFlags[5] & 0x11) == 0) {
            checkMemoryConsistency();   // FUN_00626640
        }

        // --- Process first array: find the maximum pointer stored in elements ---
        uint32_t firstArrayCurrent = static_cast<uint32_t>(thisPtr[0x28 / 4]); // +0x28
        int* firstArray = reinterpret_cast<int*>(thisPtr[0x08 / 4]);           // +0x08
        int* maxPointerInFirst = firstArray;
        int* scan = firstArray;

        uint32_t firstArrayEnd = static_cast<uint32_t>(thisPtr[0x14 / 4]); // +0x14 (end pointer as uint)
        if (firstArrayCurrent <= firstArrayEnd) {
            do {
                int* element = reinterpret_cast<int*>(static_cast<uintptr_t>(firstArrayCurrent + 4));
                // Actually the element is at firstArrayCurrent, and we compare its content as a pointer.
                // The decompiler shows: piVar7 = *(int **)(uVar4 + 4); meaning at offset +4 from current index.
                // This suggests each 0x18-byte element stores a pointer at offset 4.
                // We'll treat firstArray as an array of structs with a pointer at +4.
                // For simplicity, we just get the pointer from the element.
                int* elementPtr = *reinterpret_cast<int**>(firstArrayCurrent + 4);
                if (scan < elementPtr) {
                    scan = elementPtr;
                    maxPointerInFirst = elementPtr;
                }
                firstArrayCurrent += 0x18;
            } while (firstArrayCurrent <= firstArrayEnd);
        }

        // --- Process second array: clear stale entries and check consistency ---
        int* secondArray = reinterpret_cast<int*>(thisPtr[0x1c / 4]); // +0x1c
        int* secondArrayScan = secondArray;
        if (secondArray < firstArray) {
            do {
                if (secondArrayScan[0] > 3 && 
                    (reinterpret_cast<uint8_t*>(secondArrayScan[1])[5] & 0x11) == 0) {
                    checkMemoryConsistency();   // FUN_00626640
                }
                secondArrayScan += 2; // stride 8 bytes = 2 ints
            } while (secondArrayScan < firstArray);
        }

        // Zero out second array entries from current scan pointer up to maxPointerInFirst
        for (; secondArrayScan <= maxPointerInFirst; secondArrayScan += 2) {
            *secondArrayScan = 0;
        }

        // --- Optionally shrink the first array capacity ---
        uint32_t firstCap = static_cast<uint32_t>(thisPtr[0x2c / 4]); // +0x2c (ushort)
        int firstSize = thisPtr[0x14 / 4] - static_cast<int>(firstArrayCurrent);
        // firstSize is the difference between end and current, divided by 0x18 gives element count.
        // The condition: (firstSize / 0x18) * 4 < firstCap  and  firstCap > 0x10
        if ((firstSize / 0x18) * 4 < static_cast<int>(firstCap) && firstCap > 0x10) {
            uint16_t newCap = static_cast<uint16_t>(firstCap >> 1);
            uint32_t newSize = newCap * 0x18;
            int* newFirstArray = firstArray;
            if (newSize == 0) {
                if (firstArray != nullptr) {
                    freeMemory(firstArray);
                    newFirstArray = nullptr;
                }
            } else {
                newFirstArray = reinterpret_cast<int*>(reallocMemory(firstArray, newSize));
                if (newFirstArray == nullptr) {
                    handleAllocationFailure();   // FUN_00635a80
                    return;
                }
                // Handle memory tracking: update the allocator's total
                int* allocTotal = reinterpret_cast<int*>(thisPtr[0x10 / 4] + 0x24); // +0x10 -> allocator, +0x24
                *allocTotal = *allocTotal - static_cast<int>(firstCap) * 0x18; // subtract old capacity
                *allocTotal = *allocTotal + newSize;                          // add new size
            }
            // Update first array metadata
            thisPtr[0x14 / 4] = reinterpret_cast<int>(newFirstArray) + (firstSize / 0x18) * 0x18;
            thisPtr[0x2c / 4] = newCap;
            thisPtr[0x28 / 4] = reinterpret_cast<int>(newFirstArray);
            thisPtr[0x24 / 4] = reinterpret_cast<uint32_t>(newFirstArray) + newCap * 0x18; // new end
            maxPointerInFirst = scan; // update local max pointer because firstArray may have moved
        }

        // --- Optionally shrink the second array capacity ---
        int secondSize = (reinterpret_cast<int>(maxPointerInFirst) - reinterpret_cast<int>(secondArray)) >> 3; // in 8-byte units
        int secondCap = thisPtr[0x20 / 4]; // +0x20
        if (secondSize * 4 <= secondCap && secondCap >= 0x79) {
            int newSecondCap = secondCap / 2;
            uint32_t newSecondSize = newSecondCap * 8;
            int* newSecondArray = secondArray;
            if (newSecondSize == 0) {
                if (secondArray != nullptr) {
                    freeMemory(secondArray);
                    newSecondArray = nullptr;
                }
            } else {
                newSecondArray = reinterpret_cast<int*>(reallocMemory(secondArray, newSecondSize));
                if (newSecondArray == nullptr) {
                    handleAllocationFailure();   // FUN_00635a80
                    return;
                }
                // Update allocator total
                int* allocTotal = reinterpret_cast<int*>(thisPtr[0x10 / 4] + 0x24);
                *allocTotal = *allocTotal - secondCap * 8;
                *allocTotal = *allocTotal + newSecondSize;
            }
            // Update second array metadata
            thisPtr[0x18 / 4] = reinterpret_cast<int>(newSecondArray) - 0xa8 + newSecondCap * 8; // magic offset
            thisPtr[0x1c / 4] = reinterpret_cast<int>(newSecondArray);
            thisPtr[0x20 / 4] = newSecondCap;
        }

        finalizeMemoryUpdate(); // FUN_00635b50 (possibly debug assertion or final sync)
    }
};