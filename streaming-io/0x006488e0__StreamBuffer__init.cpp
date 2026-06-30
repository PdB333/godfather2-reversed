// FUNC_NAME: StreamBuffer::init
void __thiscall StreamBuffer::init(void) {
    // Reset all internal fields
    this->readPos = 0;          // +0x54 – current read position
    this->writePos = 0;         // +0x58 – current write position
    this->bufferSize = 0x1000;  // +0x5c – buffer size (4096 bytes)
    this->bufferPtr = 0;        // +0x60 – pointer to allocated buffer
    this->field_0x64 = 0;       // +0x64 – likely another pointer/count
    this->field_0x68 = 0;       // +0x68 – unknown
    this->field_0x6c = 0;       // +0x6c – unknown
    this->field_0x70 = 0;       // +0x70 – unknown
    this->byteFlag = 0;         // +0x74 – single byte flag

    // Call internal reset (possibly buffer allocation or state machine init)
    FUN_00648930();

    // Initialize with global data pointers (network manager or memory allocator)
    FUN_00648b00(DAT_01205410, DAT_01205418);
}