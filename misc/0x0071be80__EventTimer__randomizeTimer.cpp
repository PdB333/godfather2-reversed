// FUNC_NAME: EventTimer::randomizeTimer
// Function at address 0x0071be80 (Member function, __thiscall)
// Sets a randomized timer value at offset +0x24.
// Combines a random value scaled by DAT_00e44590 with param_2 (base time)
// and a global offset _DAT_00d61de4.

void __thiscall EventTimer::randomizeTimer(int this, float baseTime) {
    // rand() returns an integer between 0 and RAND_MAX
    int randomInt = _rand();
    // DAT_00e44590 is likely a scaling factor to convert random int to float range
    // _DAT_00d61de4 might be a minimum timer offset (e.g., 0.0 or ~0.5)
    *(float *)(this + 0x24) = (float)randomInt * DAT_00e44590 + baseTime + _DAT_00d61de4;
    return;
}