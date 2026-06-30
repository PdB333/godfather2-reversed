// FUNC_NAME: debugCompareEntityIndexAndLog
// Function: 0x006337e0
// Compares two entity indices from a global lookup table and always calls a logging function.
// Looks up each index in a global array of pointers to structures, then compares the third field (offset +0x08).
// Regardless of equality, calls FUN_00633920 (presumably a debug/log function) and returns 0.
// This is likely a debug routine used for validation or bookkeeping.

int __fastcall debugCompareEntityIndexAndLog(int* indexA, int* indexB) {
    // PTR_DAT_00e2a89c is a global array of pointers to structures
    // Each structure has at least 3 ints; we compare the third int (offset +0x08)
    if (((int**)PTR_DAT_00e2a89c)[*indexA][2] == ((int**)PTR_DAT_00e2a89c)[*indexB][2]) {
        // If equal, still call the same function
        FUN_00633920();
        return 0;
    }
    // If not equal, also call the same function
    FUN_00633920();
    return 0;
}