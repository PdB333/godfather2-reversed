// FUNC_NAME: DataReverser::reverseRanges
void DataReverser::reverseRanges(int this)
{
    int count = *(short *)(this + 0x36);        // number of range pairs
    short *startIndices = *(short **)(this + 0x3c); // array of start indices
    short *endIndices   = *(short **)(this + 0x40); // array of end indices
    short *data1        = *(short **)(this + 0x44); // first short array
    short *data2        = *(short **)(this + 0x48); // second short array
    byte  *data3        = *(byte  **)(this + 0x4c); // byte array

    for (int i = 0; i < count; i++)
    {
        short start = startIndices[i];
        short end   = endIndices[i];
        int halfLen = (end - start) / 2;        // number of swaps to perform

        // Loop: swaps between (start+1, end), (start+2, end-1), ...
        for (int j = 0; j < halfLen; j++)
        {
            int left  = start + 1 + j;
            int right = end - j;

            // Swap data1 elements
            short tmp1 = data1[left];
            data1[left]  = data1[right];
            data1[right] = tmp1;

            // Swap data2 elements
            short tmp2 = data2[left];
            data2[left]  = data2[right];
            data2[right] = tmp2;

            // Swap data3 elements
            byte tmp3 = data3[left];
            data3[left]  = data3[right];
            data3[right] = tmp3;
        }
    }
}