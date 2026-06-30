// FUNC_NAME: StreamDecompressor::initDecompress
int StreamDecompressor::initDecompress(void* sourceHandle, void* destHandle) {
    // Allocate decompression buffer (4 * 0x40 = 256 bytes, likely per-stream workspace)
    void* workspace = _calloc(4, 0x40);
    if (workspace == nullptr) {
        return -2; // Allocation failure
    }

    // Initialize temporary stream control block on stack
    struct DecompressCtrl {
        uint32_t state;    // +0x00
        uint32_t blockSize; // +0x04 (0x40 = 64 bytes)
        uint32_t flags;     // +0x08
    } ctrl;
    ctrl.state = 0;
    ctrl.blockSize = 0x40;
    ctrl.flags = 0;

    int result;
    result = openDecompressor(sourceHandle, &ctrl); // FUN_0066a660
    if (result == 0) {
        result = processDecompressedStream(&ctrl, destHandle); // FUN_00668850
    }
    cleanupDecompressor(); // FUN_00665b40 (likely flushes or frees internal state)

    return result;
}