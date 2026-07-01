// FUNC_NAME: NetPacket::calculateTotalSize
// Function address: 0x008c17a0
// Calculates the total serialized size of a network packet or data buffer.
// The object contains two arrays: one at +0x130 (28-byte elements) and one at +0x1a8 (variable-size elements).
// The size is computed from various fields and multiplied by 4 (likely byte alignment).
// If the type ID at +0x54 equals 0x637b907, an extra size is added.

int __fastcall NetPacket::calculateTotalSize(int this)
{
    int *pElement;          // pointer to current element in first array
    int elementSize;        // size returned by getElementSize for second array
    int totalSize;          // accumulated total size
    int sumFirstArray;      // sum of sizes from first array's +0x14 fields
    uint index;             // loop counter for second array

    // First array: count at +0x134, base at +0x130, each element is 28 bytes (7 ints)
    // Sum the value at offset +0x14 within each element.
    int count1 = *(int *)(this + 0x134);
    sumFirstArray = 0;
    if (count1 != 0) {
        pElement = (int *)(*(int *)(this + 0x130) + 0x14); // start at first element's +0x14
        do {
            sumFirstArray += *pElement;
            pElement += 7; // advance to next element (7 ints = 28 bytes)
            count1--;
        } while (count1 != 0);
    }

    // Second array: count at +0x1a8, each element's size obtained via getElementSize()
    int count2 = *(int *)(this + 0x1a8);
    int sumSecondArray = 0;
    index = 0;
    if (count2 != 0) {
        do {
            elementSize = getElementSize(); // FUN_008c8390
            sumSecondArray += elementSize;
            index++;
        } while (index < (uint)count2);
    }

    // Complex size calculation:
    // base = (field at +0x190) + 0xc + (sumFirstArray + count2*5 + count1) * 2
    // then multiply by 2, add field at +0x118, field at +0x10c, and sumSecondArray
    // finally multiply by 4
    int base = *(int *)(this + 0x190) + 0xc + (sumFirstArray + count2 * 5 + count1) * 2;
    totalSize = (*(int *)(this + 0x118) + base * 2 + *(int *)(this + 0x10c) + sumSecondArray) * 4;

    // If the object's type ID matches a specific class (0x637b907), add extra size
    if (*(int *)(this + 0x54) == 0x637b907) {
        int extraSize = getExtraSizeForType(); // FUN_00892740
        totalSize += extraSize;
    }

    return totalSize;
}