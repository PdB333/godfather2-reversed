// FUNC_NAME: ScriptEngine::processTable
// Address: 0x0062fd80
// This function processes a table/function chunk from a data stream, likely part of EA's EARS engine scripting system.
// It reads a buffer (param_1+0xC) and writes structured records (param_1+0x8), expecting magic codes 5 (table) and 6 (function).
// On success returns 1, else 0.

__declspec(naked) void ScriptEngine::processTable(int param_1) {
    // This is reconstructed from the decompiled code; __thiscall is implied.
    // param_1 is the 'this' pointer.
}

// Actual reconstruction:
int ScriptEngine::processTable() {
    int *readPtr = *(int **)(this + 0xC);   // source data pointer
    int *writePtr = *(int **)(this + 0x8);  // destination write pointer

    // Validate first entry: expected type 5 (table)
    if ((writePtr <= readPtr) || (readPtr == 0) || (*readPtr != 5)) {
        // Fallback: lookup "table" symbol
        readPtr = (int *)lookupSymbol("table");   // FUN_00627ac0(PTR_s_table_00e2a8b0)
        writePtr = (int *)readPtr;               // extraout_ECX (return value used as writePtr)
    }

    // Advance past the table type marker
    readPtr += 2;

    // Validate second entry: expected type 6 (function)
    if ((writePtr <= readPtr) || (readPtr == 0) || (*readPtr != 6)) {
        lookupSymbol("function");                 // FUN_00627ac0(PTR_s_function_00e2a8b4)
        writePtr = (int *)readPtr;               // extraout_ECX_00 (reused)
    }

    // Initialize first output slot to 0
    *writePtr = 0;
    *(int *)(this + 0x8) = (int)writePtr + 8;   // advance write pointer by 8 (two ints)

    while (true) {
        int token = checkTokenAvailability();   // FUN_00637650
        if (token == 0) {
            // Not enough data; undo the last advancement
            *(int *)(this + 0x8) -= 8;
            return 0;
        }

        // Reserve space for a record (8 bytes)
        *(int *)(this + 0x8) += 8;

        // Read 8 bytes from source (readPtr+8 and +0xC) into current write location
        int *src = *(int **)(this + 0xC);
        int *dst = *(int **)(this + 0x8);
        dst[0] = src[2];   // source offset +0x8
        dst[1] = src[3];   // source offset +0xC
        *(int *)(this + 0x8) += 8;

        // Duplicate the first two written ints (from the start of the buffer) into next slot
        dst = *(int **)(this + 0x8);
        dst[0] = dst[-6];  // this is the value written at buffer start+0 (offset -24)
        dst[1] = dst[-5];  // buffer start+4
        *(int *)(this + 0x8) += 8;

        // Duplicate the second two ints (from previous copy) into next slot
        dst = *(int **)(this + 0x8);
        dst[0] = dst[-6];  // buffer start+8
        dst[1] = dst[-5];  // buffer start+12
        *(int *)(this + 0x8) += 8;

        // Process the record: call readRecordData with address of the copied data (24 bytes back)
        readRecordData(this, (int *)((int)*(int *)(this + 0x8) - 0x18), 1); // FUN_006362d0

        int result = executeFunction(); // FUN_00625740
        if (result != 0) {
            return 1;
        }

        // Execution failed; undo the last 16 bytes (two 8-byte slots)
        *(int *)(this + 0x8) -= 0x10;
    }
}