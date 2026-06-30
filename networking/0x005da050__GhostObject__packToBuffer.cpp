// FUNC_NAME: GhostObject::packToBuffer
void __fastcall GhostObject::packToBuffer(GhostObject *this, int count) {
    void *buffer;
    // Local stack buffer if internal buffer is null
    uint32_t localBuf[3] = {0, 0, 0};

    // Check internal buffer pointer at offset +0x04
    buffer = this->mBuffer;
    if (buffer == nullptr) {
        buffer = &localBuf;
    }

    // Call first virtual function (vtable[0]) with size = count * 0x28 and buffer
    // This likely serializes 'count' elements of size 0x28 (40 bytes) into the buffer
    this->vtbl->packData(count * 0x28, buffer);
}