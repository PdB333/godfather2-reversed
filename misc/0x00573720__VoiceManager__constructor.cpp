// FUNC_NAME: VoiceManager::constructor
// Address: 0x00573720
// Role: Initialize voice manager, allocate buffer for 64 voice channels, initialize each channel
void __thiscall VoiceManager::constructor(VoiceManager* this) {
    // +0x00: pointer to allocated voice data buffer
    // +0x04: number of voice entries (0x280 = 640, each entry 4 bytes)
    // +0x08: unknown
    // +0x0C: unknown
    // +0x10: unknown
    // +0x14: unknown byte

    this->voiceEntryCount = 0x280;          // 640 entries
    this->voiceBuffer = 0;                  // will be set after allocation
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->field_0x10 = 0;
    this->field_0x14 = 0;

    // Allocate buffer for 640 entries * 4 bytes = 2560 bytes (0xA00)
    void* buffer = (void*)FUN_009c8e80(0xA00);
    this->voiceBuffer = buffer;
    memset(buffer, 0, this->voiceEntryCount * 4);

    // Initialize 64 voice channels
    for (int i = 0; i < 64; i++) {
        FUN_00573a00(); // initialize one voice channel (internal, likely updates a current channel pointer)
    }
}