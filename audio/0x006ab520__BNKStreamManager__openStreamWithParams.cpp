// FUNC_NAME: BNKStreamManager::openStreamWithParams
int BNKStreamManager::openStreamWithParams(uint8_t streamType, int bufferSize) {
    // Static initializer for stream system (FUN_005e30c0)
    globalStreamInit();

    // Set stream parameters
    this->field_0x68 = streamType;      // +0x68: stream type identifier (1 byte)
    this->field_0x24 = bufferSize;      // +0x24: buffer size
    this->field_0x18 = 10;              // +0x18: default priority (kNormalPriority)

    // Clear output handle
    this->field_0x70 = 0;               // +0x70: output handle

    // Core stream opening function
    // Parameters: output handle pointer, this pointer, output identifier array (4 bytes at +0x6C)
    coreOpenStream(&this->field_0x70, this, this->field_0x6C);

    return this->field_0x70;
}