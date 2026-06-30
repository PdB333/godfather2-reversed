// FUNC_NAME: processBufferEntryLoop
void processBufferEntryLoop(uint32_t *descriptor) {
    uint8_t *buffer = (uint8_t *)*descriptor;
    if (buffer == (uint8_t *)0x0) {
        buffer = &DAT_0120546e;  // default buffer
    }
    uint8_t *bufferEnd = buffer + descriptor[1];  // +4 offset: size of buffer

    for (uint8_t *current = buffer; current < bufferEnd; ) {
        uint16_t entryFlag;
        int entrySize = getNextEntrySize();  // FUN_004dd960
        current += entrySize;
    }
}