// FUNC_NAME: getColorFromTable
// Function address: 0x0060dda0
// Role: Reads 6 consecutive floats (or ints) from a global color table indexed by a global variable.
// The table at 0x011f3918 has entries of 24 bytes (6 * 4). The index is stored at 0x012058b0.

void getColorFromTable(float* out0, float* out1, float* out2, float* out3, float* out4, float* out5)
{
    int index = *(int*)0x012058b0; // global index into color table
    int offset = index * 24;       // each entry is 24 bytes (6 floats)

    // Read 6 consecutive floats from the table
    *out0 = *(float*)(0x011f3918 + offset);
    *out1 = *(float*)(0x011f391c + offset);
    *out2 = *(float*)(0x011f3920 + offset);
    *out3 = *(float*)(0x011f3924 + offset);
    *out4 = *(float*)(0x011f3928 + offset);
    *out5 = *(float*)(0x011f392c + offset);
}