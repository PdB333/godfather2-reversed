// FUNC_NAME: DataBlock44::assign
// Address: 0x00541640
// Copies 44 bytes (11 uint32 elements) from source to destination.
// This is a simple memcpy-like assignment, likely for a fixed-size game structure.
void __thiscall DataBlock44::assign(uint32* thisData, uint32* sourceData)
{
    thisData[0] = sourceData[0];
    thisData[1] = sourceData[1];
    thisData[2] = sourceData[2];
    thisData[3] = sourceData[3];
    thisData[4] = sourceData[4];
    thisData[5] = sourceData[5];
    thisData[6] = sourceData[6];
    thisData[7] = sourceData[7];
    thisData[8] = sourceData[8];
    thisData[9] = sourceData[9];
    thisData[10] = sourceData[10]; // last element
}