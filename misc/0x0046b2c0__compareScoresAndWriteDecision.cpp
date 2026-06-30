// FUNC_NAME: compareScoresAndWriteDecision
// Address: 0x0046b2c0
// Role: Compares two internally obtained scores and writes a decision (two ints) to an output buffer.
//   Uses FUN_0046af90 (unknown internal utility) to retrieve scores for two indices (1 and 2).
//   The output buffer is stored at offset +0x8 in the input structure (pointer to array of ints).
//   Always writes 1 to first slot, then writes 0 or 1 to second slot based on comparison result.
//   Advances the buffer pointer by 8 bytes (two ints) after writing.
int __thiscall compareScoresAndWriteDecision(void* thisPtr) {
    int score1 = getScore(1);   // FUN_0046af90(1)
    int score2 = getScore(2);   // FUN_0046af90(2)
    int* outputBuffer = *(int**)((char*)thisPtr + 8); // +0x8 pointer to output int array

    outputBuffer[0] = 1;        // Always set first decision to "true" (1)
    if (score1 <= score2) {
        outputBuffer[1] = 1;    // Decision: second slot is true
    } else {
        outputBuffer[1] = 0;    // Decision: second slot is false
    }

    // Advance buffer pointer by 2 ints (8 bytes)
    *(int**)((char*)thisPtr + 8) = outputBuffer + 2;

    return 1; // Always return success
}