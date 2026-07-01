// FUNC_NAME: DateTime::setFromArray
void __thiscall DateTime::setFromArray(int thisPtr, int* sourceArray)
{
    // Check for self-assignment: if source is not the same as the destination member array
    if ((int*)(thisPtr + 0x34) != sourceArray) {
        // Copy 6 integer fields: likely year, month, day, hour, minute, second
        *(int*)(thisPtr + 0x34) = sourceArray[0]; // +0x34: year
        *(int*)(thisPtr + 0x38) = sourceArray[1]; // +0x38: month
        *(int*)(thisPtr + 0x3c) = sourceArray[2]; // +0x3c: day
        *(int*)(thisPtr + 0x40) = sourceArray[3]; // +0x40: hour
        *(int*)(thisPtr + 0x44) = sourceArray[4]; // +0x44: minute
        *(int*)(thisPtr + 0x48) = sourceArray[5]; // +0x48: second
    }

    // Compute total seconds from hour, minute, second
    int totalSeconds = sourceArray[5] + (sourceArray[4] + sourceArray[3] * 60) * 60;

    float floatSeconds = (float)totalSeconds;
    // Handle potential negative totalSeconds (should not happen in normal usage)
    if (totalSeconds < 0) {
        floatSeconds = floatSeconds + DAT_00e44578; // Bias to convert to unsigned-like float
    }

    *(float*)(thisPtr + 0x54) = floatSeconds; // +0x54: total seconds as float
}