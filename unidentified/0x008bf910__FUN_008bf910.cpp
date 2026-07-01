// FUNC_NAME: UnknownClass::calculateSerializedSize
// Function address: 0x008bf910
// Role: Calculates the total serialized size of a data structure (likely a ghost update packet).
// The class has fields at offsets: +0x00 (magic/classID), +0x24 (count1), +0x28 (offset1), +0x2c (count2), +0x30 (arrayCount), +0x34 (extraSize1), +0x38 (extraSize2), +0x3c (extraSize3).
// Each array element is 0x50 bytes (20 ints) and contains various data fields.

int __thiscall UnknownClass::calculateSerializedSize(int* thisPtr)
{
    int* elementPtr;
    int index;
    uint loopCount;
    int* currentElement;
    int* runningSumPtr;
    int localArray[4]; // 16 bytes, used for temporary storage

    // Compute base offset from fields at +0x28, +0x2c, +0x24
    int baseOffset = thisPtr[10] + 0x18 + thisPtr[11] * 2 + thisPtr[9]; // +0x28, +0x2c, +0x24

    // Call some initialization function (likely resets a global state)
    FUN_008b0170();

    // Pointer to the end of the array (after all elements)
    int* arrayEnd = thisPtr + baseOffset + thisPtr[12] * 0x14; // +0x30: array count, each element is 0x14 ints? Actually 0x14 * 4 = 0x50 bytes per element

    // Start of the array (first element)
    currentElement = thisPtr + baseOffset + 0x12; // +0x12 ints = 0x48 bytes into first element

    loopCount = 0;
    if (thisPtr[12] != 0) // +0x30: array count
    {
        do
        {
            // Call a function that processes the element's fields.
            // The element structure (20 ints, 0x50 bytes) is accessed via negative indices from currentElement.
            // Fields are passed in a specific order (likely the order they appear in the serialized data).
            FUN_008afc90(
                currentElement[-0x12], // offset 0x00
                currentElement[-0x11], // offset 0x04
                currentElement[-0x10], // offset 0x08
                currentElement[-0x0f], // offset 0x0c
                currentElement[-8],    // offset 0x28
                currentElement[-0x0e], // offset 0x10
                currentElement[-6],    // offset 0x30
                currentElement[-4],    // offset 0x38
                currentElement[-0x0b], // offset 0x1c
                currentElement[-5],    // offset 0x34
                currentElement[-9],    // offset 0x24
                currentElement[-3],    // offset 0x3c
                // Last argument: if field at offset 0x3c is non-zero, pass arrayEnd, else 0
                -(uint)(currentElement[-3] != 0) & (uint)arrayEnd
            );

            // Store two fields from the element into local variables (used by FUN_008b0f20)
            localArray[2] = currentElement[-1]; // offset 0x44
            localArray[3] = currentElement[-2]; // offset 0x40
            localArray[0] = currentElement[0];  // offset 0x48
            localArray[1] = currentElement[1];  // offset 0x4c

            // Call another function with the local array (likely processes these fields)
            FUN_008b0f20(localArray);

            // Update running sum pointer: points to the field at offset 0x3c of the current element
            int* fieldPtr = currentElement + -3; // offset 0x3c
            loopCount++;
            currentElement += 0x14; // Move to next element (0x14 ints = 0x50 bytes)
            arrayEnd += *fieldPtr;  // Accumulate the field value into arrayEnd (used as a running total)
        } while (loopCount < (uint)thisPtr[12]);
    }

    // After processing the array, compute the final pointer based on additional fields
    int* finalPtr = thisPtr + baseOffset + thisPtr[13] + (thisPtr[15] + thisPtr[14] + thisPtr[12] * 5) * 4; // +0x34, +0x3c, +0x38, +0x30

    // If the class ID matches a specific value, call a function that may adjust the pointer
    if (*thisPtr == 0x637b907) // Magic number (class ID)
    {
        int adjustment = FUN_008921c0(finalPtr);
        finalPtr = (int*)((int)finalPtr + adjustment);
    }

    // Return the total size (difference between final pointer and start)
    return (int)finalPtr - (int)thisPtr;
}