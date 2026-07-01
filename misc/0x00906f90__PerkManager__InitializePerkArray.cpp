// FUNC_NAME: PerkManager::InitializePerkArray
// Address: 0x00906f90
// This function fills an array of 5-dword structures (20 bytes each) with data from a global table.
// The table (DAT_00e547e0) contains 18 entries, each 3 dwords: [value2, functionPtr, value1].
// For each entry, it calls the function pointer (which returns a float), then stores:
//   destination[0] = value1
//   destination[2] = value2
//   destination[3] = (float) result of function call
//   destination[4] = 0
// Field at offset 4 (destination[1]) is left uninitialized.
// The function returns a pointer to the next unused slot (after the 18 entries).

// Destination structure (5 dwords = 20 bytes):
// +0x00: int field0 (value1 from table)
// +0x04: int field1 (unused, left as is)
// +0x08: int field2 (value2 from table)
// +0x0C: float field3 (result of function call)
// +0x10: int field4 (always 0)

// Global table at DAT_00e547e0 (18 entries, 12 bytes each):
// Entry layout:
//   +0x00: int value1 (stored in dest[0])
//   +0x04: int (function pointer) called to get float
//   +0x08: int value2 (stored in dest[2])

int* __thiscall PerkManager::InitializePerkArray(int* param_1)
{
    // Pointer to the global table (DAT_00e547e0)
    int* tablePtr = (int*)0x00e547e0;
    int count = 18; // 0x12

    do {
        // Call the function pointer stored at tablePtr[-1] (offset -4 from start)
        // The function returns a 80-bit extended precision float, cast to float.
        float result = (float)(*(float10 (__stdcall *)())(tablePtr[-1]))();

        // Store values from table into destination structure
        param_1[2] = tablePtr[-2]; // value2
        param_1[4] = 0;            // always 0
        param_1[3] = result;       // float from function call
        *param_1 = tablePtr[0];    // value1

        // Advance to next structure (5 dwords)
        param_1 += 5;
        // Advance table pointer to next entry (3 dwords)
        tablePtr += 3;

        count--;
    } while (count != 0);

    // Return pointer to the end of the filled array
    return param_1;
}