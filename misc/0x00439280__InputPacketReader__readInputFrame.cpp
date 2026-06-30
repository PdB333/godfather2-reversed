// FUNC_NAME: InputPacketReader::readInputFrame
typedef unsigned int uint;

// Global arrays for player input storage (64 players, each up to 65 entries)
extern int gPlayerInputCounts[64][65];        // +0x00 count per player slot
extern int gPlayerInputInts[64][65];           // stored integers (e.g. digital actions)
extern float gPlayerInputFloats[64][65];       // stored floats (e.g. analog values)

// Forward declarations of helper functions (likely stream readers)
int FUN_006259b0(void* stream, int mode);      // reads int or float?
int FUN_00636850(float* out);                  // reads float from stream
int FUN_00b9a1c0();                            // returns current player index (0-63)
int FUN_00637650();                            // checks if more data available in stream

// Class representing a packet stream reader
class InputPacketReader {
public:
    // Layout:
    // +0x00 : unknown?
    // +0x08 : current read pointer
    // +0x0C : end of buffer pointer (or remaining size?)
    // ...
    int readInputFrame();
};

int InputPacketReader::readInputFrame() {
    int* piVar5;                 // current token pointer
    bool bSuccess = true;
    int local_20;                // counter for items read
    float local_18;              // temporary float
    int local_14;                // temporary int for token type?
    float local_10;              // temporary float copy
    int* local_c[2];             // used to store pointer to player count

    // Get current read pointer (stored at +0x0C)
    piVar5 = *(int**)(this + 0x0C);
    // Validate: read pointer must be non-null and within bounds (<= pointer at +0x08)
    if ((*(int**)(this + 0x08) <= piVar5) || (piVar5 == 0)) goto end_failure;

    // First token must be type 3 or 4
    if (*piVar5 != 3) {
        if (*piVar5 != 4) goto end_failure;
        // Token type 4: attempt to read a float
        int status = FUN_00636850(&local_18);
        if (status == 0) goto end_failure;
    }

    piVar5 = (int*)(*(int*)(this + 0x0C) + 8);
    // Validate next two tokens: must be type 5 at offsets +8 and +0x10
    if ((((*(int**)(this + 0x08) <= piVar5) || (piVar5 == 0)) || (*piVar5 != 5)) ||
       (((piVar5 = (int*)(*(int*)(this + 0x0C) + 0x10)), 
         (*(int**)(this + 0x08) <= piVar5) || (piVar5 == 0)) || (*piVar5 != 5))) goto end_failure;

    // Consume a byte (maybe mode=1?)
    FUN_006259b0(this, 1);

    // Get the target player slot
    uint playerSlot = FUN_00b9a1c0();
    if (playerSlot >= 0x40) {
        bSuccess = false;
        goto end_failure;
    }

    // Pointer to the count field for this player slot
    local_c[0] = &gPlayerInputCounts[playerSlot][0];
    *local_c[0] = 0;                          // reset count

    // Write a null token to output stream? (possibly part of packet building)
    **(int**)(this + 0x08) = 0;
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    // --- First pass: read integer values ---
    local_20 = 0;
    while (1) {
        int status = FUN_00637650();
        if (status == 0) break;

        // Advance read pointer by 8 bytes (token size)
        *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;
        piVar5 = (int*)(*(int*)(this + 0x08) - 8);   // pointer to current token

        if (piVar5 == 0) {
            status = 0;              // no token
        } else if (*piVar5 == 3) {
            // Token type 3: immediate integer value at piVar5[1]
            status = piVar5[1];
        } else if (*piVar5 == 4) {
            // Token type 4: float value, need to parse
            status = FUN_00636850(&local_18);
            if (status != 0) {
                // Reconstruct: treat float as integer? Or store float's bits?
                // The decompiler shows local_14=3; local_10=local_18; then reads piVar5[1] = local_10
                // This likely means the float is stored as an int (bitwise cast)
                local_14 = 3;
                local_10 = local_18;
                piVar5 = &local_14;   // point to fake token {3, reinterpreted float}
                status = piVar5[1];    // float bits as int
            }
        } else {
            status = 0;   // invalid token type
        }

        if (local_20 < 0x20) {    // limit to 32 entries
            int idx = playerSlot * 0x41 + local_20;
            local_20++;
            gPlayerInputInts[idx] = status;
            // Rewind read pointer by 8 (since we consumed but stored the value)
            *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
        } else {
            *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
            bSuccess = false;
        }
    }

    // Rewind by 8 after loop
    *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;

    // Save count of integers read
    local_14 = local_20;   // Will be used later for comparison

    if (!bSuccess) goto end_failure;

    // Write another null token to output stream
    **(int**)(this + 0x08) = 0;
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    // --- Second pass: read float values ---
    local_20 = 0;
    while (1) {
        int status = FUN_00637650();
        if (status == 0) break;

        *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;
        float fVal = (float)FUN_006259b0(this, 0xFFFFFFFF);
        local_18 = fVal;

        if (local_20 < 0x20) {
            int idx = playerSlot * 0x41 + local_20;
            local_20++;
            gPlayerInputFloats[idx] = local_18;
            *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
        } else {
            *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
            bSuccess = false;
        }
    }

    // Adjust read pointer by -0x10 (two tokens)
    *(int*)(this + 0x08) = *(int*)(this + 0x08) - 0x10;

    if (!bSuccess) goto end_failure;

    // Check that integer and float counts match
    if (local_14 == local_20) {
        *local_c[0] = local_20;    // store final count in global
        goto end_failure;          // intentionally go to success path? (note: returns 1)
    }

    bSuccess = false;

end_failure:
    // Write return value token: type 1, value = bSuccess (bool)
    puVar1 = *(undefined4**)(this + 0x08);
    *puVar1 = 1;                     // token type 1 = return
    puVar1[1] = (uint)bSuccess;      // success flag
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    return 1;   // always returns 1 (success was encoded in the output stream)
}