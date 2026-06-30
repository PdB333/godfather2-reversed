// FUNC_NAME: GetPairValues

// Function at 0x0060db00: Retrieves a pair of DWORD values from a global array of 8-byte pairs.
// The index (param_1) selects a pair; returns the first DWORD, and optionally writes the second DWORD to *outSecondValue.

int GetPairValues(int index, int* outSecondValue)
{
    // gPairFirst and gPairSecond are actually the same global array; the compiler treats them as two separate base addresses.
    // Offset: 0x011f38f0 for first DWORD, 0x011f38f4 for second DWORD.
    extern int gPairFirst[];   // Array of first elements, base 0x011f38f0
    extern int gPairSecond[];  // Array of second elements, base 0x011f38f4

    int firstValue = gPairFirst[index * 2];      // Actually reads from offset index*8
    int secondValue = gPairSecond[index * 2];    // Reads next DWORD

    if (outSecondValue != nullptr)
    {
        *outSecondValue = secondValue;
    }

    return firstValue;
}