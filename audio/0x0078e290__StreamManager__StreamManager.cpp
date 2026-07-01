// FUNC_NAME: StreamManager::StreamManager
void * __thiscall StreamManager::StreamManager(StreamManager *this) {
    this->field_4 = 1;                      // +0x04: some flag
    this->field_8 = 0;                      // +0x08: likely a pointer/null
    this->vtable2 = &g_vtable_00d69b90;     // +0x0C: second vtable pointer (temporary)
    g_pStreamManager = this;                // store global singleton pointer
    this->vtable = &g_vtable_00d69b98;      // +0x00: main vtable pointer
    this->vtable2 = &g_vtable_00d69b94;     // +0x0C: final second vtable
    this->field_10 = 0;                     // +0x10
    this->field_14 = 0;                     // +0x14
    this->field_18 = 0;                     // +0x18
    this->field_1C = 0;                     // +0x1C
    if (g_pStreamBuffer != 0) {
        copyDataBuffer(this, g_pStreamBuffer, 0x8000);  // copy 32KB stream data into this
    }
    return this;
}