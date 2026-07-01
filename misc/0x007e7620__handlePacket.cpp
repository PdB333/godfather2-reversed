// FUNC_NAME: handlePacket
void handlePacket(uint param_1, uint param_2) {
    uint8 buffer[20]; // +0x00: temporary packet header buffer (20 bytes)
    uint32* dataPtr = nullptr; // +0x14: pointer to parsed data (originally local_8 as int[2], but likely a pointer)

    FUN_00892af0(0); // log/assert with level 0, possibly debug info
    FUN_00892ce0(param_1, 3); // set connection state or channel ID (param_1) to mode 3
    FUN_00894c40(param_2, buffer); // copy packet header from param_2 into buffer
    if (dataPtr) {
        FUN_004daf90(dataPtr); // process the data referenced by dataPtr
    }
}