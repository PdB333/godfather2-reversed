// FUNC_NAME: MathUtils::lerpAngle
void __fastcall MathUtils::lerpAngle(float* state)
{
    int count;
    float t;
    float result;

    count = *(int*)(state + 2); // +8: iteration count
    if (count == 0) {
        // No iterations: just call the interpolation function with start=state[0], end=state[4], factor=state[3]
        result = (float)FUN_004b9c30(*state, state[4], state[3]); // FUN_004b9c30 is likely a lerp or slerp function
        state[4] = result; // store result back to end
        return;
    }
    t = (float)count;
    if (count < 0) {
        t = t + DAT_00e44578; // handle negative count (add 0x80000000 as float? likely a bug or special case)
    }
    // Compute interpolation factor as state[1] / count
    result = (float)FUN_004b9c30(state[1] / t, state[4], state[3]);
    state[4] = result;
    return;
}