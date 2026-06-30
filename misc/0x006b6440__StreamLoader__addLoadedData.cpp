// FUNC_NAME: StreamLoader::addLoadedData
void __thiscall StreamLoader::addLoadedData(int this, int bytesAdd) {
    uint current = *(uint *)(this + 0x5c);   // +0x5c current loaded bytes
    uint total = *(uint *)(this + 0x60);     // +0x60 total expected bytes

    // If total is less than current, cap total to current (no overflow)
    if (total <= current) {
        total = current;
    }

    uint newCurrent = current + bytesAdd;
    *(uint *)(this + 0x5c) = newCurrent;

    // If new total exceeds old total, advance buffer offsets
    if (total < newCurrent) {
        int delta = newCurrent - total;
        *(int *)(this + 0x58) += delta;   // +0x58 buffer offset / bytes read from source
        *(int *)(this + 0x74) += delta;   // +0x74 stream position / processed bytes

        // Check global load priority threshold and a specific flag (bit 29, 0x20000000)
        if ((g_loadPriorityThreshold < *(float *)(this + 0x80)) ||   // +0x80 loading priority float
            ((*(uint *)(this + 0x34) >> 0x1d & 1) != 0)) {            // +0x34 flags, bit 29 set = high priority
            // High priority: request more data immediately
            FUN_006b2f70();  // likely StreamLoader::requestMoreData
        } else {
            // Normal priority: process loaded data
            FUN_006b59f0();  // likely StreamLoader::processLoadedData
        }

        // Specific asset type detection (magic number 0x637b907)
        if (*(int *)(this + 0x40) == 0x637b907) {
            *(undefined4 *)(this + 0x70) = gDefaultAssetId;   // +0x70 asset handle
            *(uint *)(this + 0x34) |= 0x8000000;               // +0x34 flags set bit 27 (loaded complete?)
        }
    }
}