// FUNC_NAME: getTwoFieldValues
// Function address: 0x00926810
// Role: Simple getter returning two fields at offsets 0x3ac and 0x3b0.
// Likely a 2D position or target pair (e.g., floating-point coordinates).
void __thiscall getTwoFieldValues(int thisPtr, float* outX, float* outY)
{
    // +0x3ac: first field (e.g., x coordinate)
    *outX = *(float *)(thisPtr + 0x3ac);
    // +0x3b0: second field (e.g., y coordinate)
    *outY = *(float *)(thisPtr + 0x3b0);
}