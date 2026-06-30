// FUNC_NAME: Sentient::getMovementSpeed
// Function address: 0x007228c0
// Returns walk or run speed based on isRunning flag.
// Offsets: +0x10c = run speed, +0x110 = walk speed (relative to this pointer)
float __thiscall Sentient::getMovementSpeed(int thisPtr, char isRunning) {
    if (isRunning != '\0') {
        return *(float*)(thisPtr + 0x10c); // run speed
    } else {
        return *(float*)(thisPtr + 0x110); // walk speed
    }
}