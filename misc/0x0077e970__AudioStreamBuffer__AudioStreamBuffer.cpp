// FUNC_NAME: AudioStreamBuffer::AudioStreamBuffer

// Constructor for a buffer that holds a 0x8000-byte block of audio data.
// The buffer is initialized from a global pointer if set.
class AudioStreamBuffer {
public:
    void* vtable;                    // +0x00 vtable pointer
    void* field_0x3C;                // +0x3C pointer to buffer data (initialized to a static label)
    void* field_0x48;                // +0x48 pointer to another static label
    uint32_t field_0x50;             // +0x50 zeroed
    uint32_t field_0x54;             // +0x54 zeroed
    uint32_t field_0x58;             // +0x58 zeroed
    uint32_t field_0x5C;             // +0x5C zeroed
    uint32_t field_0x60;             // +0x60 zeroed
    uint32_t field_0x64;             // +0x64 zeroed
    uint32_t field_0x68;             // +0x68 zeroed
    uint32_t field_0x6C;             // +0x6C zeroed
    uint32_t field_0x70;             // +0x70 zeroed
    uint32_t field_0x74;             // +0x74 zeroed
    uint32_t field_0x78;             // +0x78 zeroed
    uint32_t field_0x7C;             // +0x7C zeroed
    uint32_t field_0x80;             // +0x80 zeroed
};

extern void* g_globalAudioData;      // DAT_0120e93c – global pointer to default audio data
extern void* PTR_FUN_00d6920c;       // vtable for AudioStreamBuffer
extern void* PTR_LAB_00d691fc;       // some static data label
extern void* PTR_LAB_00d691f8;       // another static data label

// External base constructor (likely for a stream base class)
void __fastcall FUN_0046c590(uint32_t param);
// External memory copy function (memcpy equivalent)
void __fastcall FUN_00408900(void* dest, void* src, uint32_t size);

AudioStreamBuffer* __thiscall AudioStreamBuffer::AudioStreamBuffer(AudioStreamBuffer* this, uint32_t baseInitParam) {
    // Call base class constructor
    FUN_0046c590(baseInitParam);

    // Set vtable for this class
    this->vtable = &PTR_FUN_00d6920c;

    // Initialize buffer pointers to static labels (likely pre-allocated static buffers)
    this->field_0x3C = &PTR_LAB_00d691fc;
    this->field_0x48 = &PTR_LAB_00d691f8;

    // Zero out control fields (counters, flags, etc.)
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x78 = 0;
    this->field_0x7C = 0;
    this->field_0x80 = 0;

    // If global audio data exists, copy 0x8000 bytes into the buffer
    if (g_globalAudioData != nullptr) {
        FUN_00408900(&this->field_0x3C, g_globalAudioData, 0x8000);
    }

    return this;
}