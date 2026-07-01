// FUNC_NAME: StreamReader::readDataBlock
void __thiscall StreamReader::readDataBlock(int thisPtr, undefined4 param_2)
{
    char isDone;
    int dataType;
    undefined4 *dataPtr;
    int extraCount;

    // Open file or initialize stream with given parameter
    FUN_0046c710(param_2);
    // Set read mode with magic identifier (0x99d00d70 likely a resource type tag)
    FUN_0043aff0(param_2, 0x99d00d70);

    extraCount = 0;
    isDone = FUN_0043b120(); // Check if data is available
    while (isDone == '\0') {
        FUN_0043b210(); // Advance to next data chunk
        dataType = FUN_0043ab70(); // Get type of current chunk
        if (dataType == 0) {
            // Read a 16-byte block (e.g., vector or matrix) into member at +0x50
            FUN_0043b210(); // Prepare for reading
            dataPtr = (undefined4 *)FUN_0043abc0(); // Read 4 dwords
            *(undefined4 *)(thisPtr + 0x50) = *dataPtr;
            *(undefined4 *)(thisPtr + 0x54) = dataPtr[1];
            *(undefined4 *)(thisPtr + 0x58) = dataPtr[2];
            *(undefined4 *)(thisPtr + 0x5c) = dataPtr[3];
        }
        else if (dataType == 1) {
            // Read an integer from offset 8 of some structure
            extraCount = FUN_0043b210(); // This returns a pointer? Actually it's a function call returning int? Wait: iVar4 = FUN_0043b210(); then iVar4 = *(int *)(iVar4 + 8);
            // So FUN_0043b210 returns a pointer to a structure, and we read offset 8
            extraCount = *(int *)(extraCount + 8);
        }
        FUN_0043b1a0(); // Advance to next chunk
        isDone = FUN_0043b120(); // Check again
    }
    // Finalize: process the 16-byte data with a count (2 if extraCount==0, else 1)
    FUN_00942a90(thisPtr + 0x50, 2 - (uint)(extraCount != 0));
    return;
}