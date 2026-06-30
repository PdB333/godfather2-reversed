//FUNC_NAME: getGlobalVector
// Address: 0x00613fb0
// Role: Copies a 16-byte vector from global memory to the provided output buffer.
// The global variables are likely part of a larger engine state structure.
void getGlobalVector(int *outVector) {
    outVector[0] = _DAT_011f6b50;   // +0x00
    outVector[1] = uRam011f6b54;    // +0x04
    outVector[2] = uRam011f6b58;    // +0x08
    outVector[3] = uRam011f6b5c;    // +0x0C
}