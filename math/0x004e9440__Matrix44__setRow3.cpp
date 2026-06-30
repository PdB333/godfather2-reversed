// FUNC_NAME: Matrix44::setRow3
void __thiscall Matrix44::setRow3(void* thisPtr, float* rowData) {
    // TLS base (FS:[0x2c] -> array[2])
    int tlsBase = *(int*)(**(int**)(__readfsdword(0x2c) + 8));
    // Offset stored at +0x18 in the object (likely index or buffer offset)
    int offset = *(int*)((int)thisPtr + 0x18);
    // Destination/source buffer pointer
    int* buffer = (int*)(tlsBase + offset);
    
    // Save first 3 dwords from the original buffer (the 4th dword of first row is read later)
    int firstRow1 = buffer[1];
    int firstRow2 = buffer[2];
    int firstRow3 = buffer[3];
    
    // Read second row (offset 0x10)
    int* secondRowPtr = (int*)(tlsBase + 0x10 + offset);
    int secondRow0 = secondRowPtr[0];
    int secondRow1 = secondRowPtr[1];
    int secondRow2 = secondRowPtr[2];
    int secondRow3 = secondRowPtr[3];
    
    // Read third row (offset 0x20)
    int* thirdRowPtr = (int*)(tlsBase + 0x20 + offset);
    int thirdRow0 = thirdRowPtr[0];
    int thirdRow1 = thirdRowPtr[1];
    int thirdRow2 = thirdRowPtr[2];
    int thirdRow3 = thirdRowPtr[3];
    
    // Read fourth row from parameter
    int fourthRow0 = *(int*)rowData;
    int fourthRow1 = rowData[1];
    int fourthRow2 = rowData[2];
    int fourthRow3 = rowData[3];
    
    // Write all 16 dwords back to the same buffer
    buffer[0]  = buffer[0]; // First dword of first row (already at buffer[0])
    buffer[1]  = firstRow1;
    buffer[2]  = firstRow2;
    buffer[3]  = firstRow3;
    buffer[4]  = secondRow0;
    buffer[5]  = secondRow1;
    buffer[6]  = secondRow2;
    buffer[7]  = secondRow3;
    buffer[8]  = thirdRow0;
    buffer[9]  = thirdRow1;
    buffer[10] = thirdRow2;
    buffer[11] = thirdRow3;
    buffer[12] = fourthRow0;
    buffer[13] = fourthRow1;
    buffer[14] = fourthRow2;
    buffer[15] = fourthRow3;
}