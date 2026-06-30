// FUNC_NAME: handleToOffset
int handleToOffset(uint handle) {
    if ((handle & 0xc0000000) == 0x40000000) {
        // handle type 0x40000000 -> base offset 0, index * 4
        return handle * 4;
    }
    if ((handle & 0xc0000000) == 0xc0000000) {
        // handle type 0xc0000000 -> base offset 0x4c, index * 4
        return handle * 4 + 0x4c;
    }
    // Unknown handle type -> return 0
    return 0;
}