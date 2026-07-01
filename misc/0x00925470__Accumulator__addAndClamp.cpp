// FUNC_NAME: Accumulator::addAndClamp
// Function address: 0x00925470
// Role: Adds a rate (float at +0xac) to an accumulator (float at +0x1398) and clamps the result to a maximum (+0xa4).
// This is likely a timer or speed accumulator update used within a game object (e.g., movement, state timer).

void __fastcall Accumulator::addAndClamp(int thisPtr)
{
    // +0xac: rate or delta to add each frame
    // +0x1398: accumulator/timer value
    // +0xa4: maximum allowed value (cap)
    float accumulated = *(float *)(thisPtr + 0x1398) + *(float *)(thisPtr + 0xac);
    *(float *)(thisPtr + 0x1398) = accumulated;

    // Clamp to maximum if exceeded
    if (*(float *)(thisPtr + 0xa4) < accumulated) {
        *(float *)(thisPtr + 0x1398) = *(float *)(thisPtr + 0xa4);
    }
}