// FUNC_NAME: GlobalCameraBounds::updateMaxBounds
void __fastcall updateMaxBounds(float *inputArray)
{
    uint flags;

    // Update maximum X value (global at +0x0)
    if (globalMaxX < inputArray[0]) {
        globalMaxX = inputArray[0];
    }
    // Update maximum Y value (global at +0x4)
    if (globalMaxY < inputArray[1]) {
        globalMaxY = inputArray[1];
    }
    // Copy 4 floats from indices 4-7 to globals at +0x10, +0x14, +0x18, +0x1C
    globalData0 = inputArray[4];
    globalData1 = inputArray[5];
    globalData2 = inputArray[6];
    globalData3 = inputArray[7];
    // Update flags byte (at +0x20) from input[8] using bitwise merge (bits 0 and 1)
    flags = globalFlags ^ ( (byte)inputArray[8] ^ globalFlags ) & 1;
    globalFlags = flags ^ ( ((uint)(inputArray[8] >> 1) & 0xff) * 2 ^ flags ) & 2;
}