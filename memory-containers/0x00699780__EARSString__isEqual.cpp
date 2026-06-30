// FUNC_NAME: EARSString::isEqual
// Address: 0x00699780
// This function compares the string represented by `this` with a string identified by a hash or pointer in param_2.
// It first compares the internal integer hash (or pointer) at offset 0x4.
// If they are not equal, it performs a deeper comparison using a global empty string and param_3.
// Returns 0 if equal, non-zero otherwise.

class EARSString {
public:
    // Offset +0x04: internal string hash or pointer to string data
    int m_hashOrPtr;

    // Internal: lookup function that returns a pointer to an int (hash or string pointer)
    // FUN_00698c00: (INTPTR*)(int*)(param_2_addr, param_2)
    // Internal: function to access string data at offset 0x20
    // FUN_004d3e20: void (int*)
    // Internal: comparison function with global empty string and param_3
    // FUN_004d6e30: char (DAT_0120546e, param_3)

    char isEqual(int param_2, int param_3) {
        char result = 0;
        // Look up the string object corresponding to param_2
        int* foundPtr = (int*)FUN_00698c00(&param_2, param_2);
        // Compare the looked-up value with the stored hash/pointer at offset 0x4
        if (*foundPtr != m_hashOrPtr) {  // Note: decompiler shows *foundPtr != param_1+4, but likely a dereference is missing
            // Access the looked-up string data at offset 0x20
            FUN_004d3e20(*foundPtr + 0x20);
            // Compare using global empty string and param_3
            result = FUN_004d6e30(&DAT_0120546e, param_3);
        }
        return result;
    }
};