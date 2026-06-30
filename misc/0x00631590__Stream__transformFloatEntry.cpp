// FUNC_NAME: Stream::transformFloatEntry
// Function address: 0x00631590
// Role: Reads a numeric entry (type 3 or 4) from input stream, optionally converts type 4, and writes a transformed float to output stream. Skips invalid entries while printing debug messages.

// Known offsets in Stream (or similar class):
//   +0x08 : current write pointer (int*)
//   +0x0C : current read pointer  (int*)

int Stream::transformFloatEntry() {
    int* readPos = *(int**)(this + 0x0C);
    int* writePos = *(int**)(this + 0x08);

    // If buffer is empty, jump to skip and zero out value
    if (writePos <= readPos || readPos == nullptr) {
        goto skipEntry;
    }

    // Check entry type: 3 (float) or 4 (needs conversion)
    int entryType = *readPos;
    if (entryType != 3) {
        if (entryType != 4) {
            goto skipEntry;
        }

        // Type 4: attempt to convert via external function
        float converted;
        if (FUN_00636850(&converted) == 0) {
            goto skipEntry;
        }

        // Create temporary type-3 entry on stack
        int tempType = 3;
        float tempValue = converted;
        readPos = &tempType; // points to tempType, then tempValue follows
    }

    float value = *(float*)(readPos + 1); // second int interpreted as float

    // Special handling: if value equals a global constant, skip matching entries
    if (value == DAT_00e2b05c) {
        while (true) {
            // Re-read input pointer (should advance in a correct implementation)
            readPos = *(int**)(this + 0x0C);
            if (writePos <= readPos || readPos == nullptr) {
                // Buffer empty or null pointer
                FUN_00627ac0("number");
                value = 0.0f;
                continue;
            }

            int nextType = *readPos;
            if (nextType == 3) {
                break; // valid type 3
            }
            if (nextType == 4) {
                int ok;
                float dummy; // not used in original, maybe ignore
                ok = FUN_00636850(&dummy);
                if (ok != 0) {
                    break; // valid type 4 after conversion
                }
            }
            // Invalid entry: print debug and continue
            FUN_00627ac0("number");
            // In the original, there is no pointer advance – this would be infinite.
            // Assuming the real code advances readPos by 2 (8 bytes) here.
            // *(int**)(this + 0x0C) += 2; // <-- added for correctness
            value = 0.0f;
        }
    }

skipEntry:
    // At this point, value holds the float to be written (possibly 0.0 if skipped)
    int* outputPos = *(int**)(this + 0x08);

    // Compute transformed value using bitwise rounding
    uint rawBits = *(uint*)&value;
    float addend = (float)(DAT_00e44648 | (DAT_00e44564 & rawBits));
    float temp = (value + addend) - addend; // round to a certain precision
    float adjust = (float)(-(uint)((float)(DAT_00e44564 & rawBits) < temp - value) & DAT_00e2b1a4);
    float finalValue = temp - adjust;

    // Write new entry to output stream
    *outputPos = 3;                // type = float
    *(float*)(outputPos + 1) = finalValue;
    *(int**)(this + 0x08) = outputPos + 2; // advance write pointer (8 bytes)

    return 1;
}