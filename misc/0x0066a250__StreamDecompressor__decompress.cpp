// FUNC_NAME: StreamDecompressor::decompress
int StreamDecompressor::decompress(undefined4 param_1, int *param_2, int param_3)
{
    void *buffer;
    uint uVar1;
    int result;
    int offset;
    int decodedSize;
    undefined4 local_14;
    undefined4 local_10;
    void *allocated;

    // Allocate a temporary buffer (256 bytes)
    allocated = _calloc(4, 0x40); // 4 * 64 = 256 bytes
    if (allocated == (void *)0x0) {
        return -2; // Allocation failure
    }

    result = *param_2; // First field of param_2: maybe original size or count
    decodedSize = 0;
    local_14 = 0x40; // Buffer size hint
    local_10 = 0;

    if (result == 0) {
        offset = 0;
    }
    else {
        // Compute offset based on result (size? count?) 
        offset = result * 0x1c + -0x1c;
        // Count leading bits to add extra bytes?
        for (uVar1 = *(uint *)(param_2[3] + -4 + result * 4); uVar1 != 0; uVar1 = uVar1 >> 1) {
            offset = offset + 1;
        }
    }

    // First decompression/transformation step
    result = FUN_00666300(param_1, offset, &decodedSize, param_1);
    
    while (((result == 0 &&
            ((param_3 == 1 || (result = FUN_00668f50(&decodedSize, param_3, &decodedSize), result == 0)) &&
             (result = FUN_0066bb40(param_1, &decodedSize), result == 0)))) &&
           (int iVar3 = FUN_00665c30(), iVar3 != -1)) {
        // If more data available, continue processing
        FUN_0066c8d0(param_1);
        result = FUN_00666300(param_1, offset, &decodedSize, param_1);
    }

    buffer = allocated;
    if (allocated != (void *)0x0) {
        _memset(allocated, 0, decodedSize * 4); // Clear output buffer
        _free(buffer);
    }

    return result; // 0 on success, negative on error
}