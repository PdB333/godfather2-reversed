// FUNC_NAME: DataProcessor::readStreamSegment
void DataProcessor::readStreamSegment(int param_1, int param_2)
{
    char local_20[12]; // buffer for 12-byte data segment
    int local_14;

    FUN_00414aa0(); // unknown initialization or lock
    local_14 = DAT_00e2b1a4; // global identifier, possibly a stream handle or key

    // Copy data from member at offset 0x24 (likely a pointer to a data buffer) 
    // plus offset 0x40, into the local buffer, using param_2 as size or flags
    FUN_0056b420(*(int *)(param_1 + 0x24) + 0x40, local_20, param_2); 

    return;
}