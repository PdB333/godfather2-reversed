// FUNC_NAME: AudioDataManager::AudioDataManager
// Address: 0x006ea650
// Role: Constructor for AudioDataManager singleton, sets vtable, initializes fields,
// stores global pointer, and copies initial data buffer (0x8000 bytes) if preloaded.

// Forward declaration of memory copy function (likely memcpy or engine-specific)
void * __cdecl engineMemCpy(void *dest, const void *src, size_t size);

// Global singleton pointer
AudioDataManager * gAudioDataManager; // originally DAT_01129880

// Global pre-initialized data buffer (32KB)
extern uint8_t gInitialAudioData[0x8000]; // originally DAT_01206a20

class AudioDataManager {
public:
    // Vtable pointer (offset 0x00)
    void *vtable;

    // Fields (offsets relative to this)
    // +0x04: some flag (initialized to 1)
    uint32_t field_04;
    // +0x08: another flag (initialized to 0)
    uint32_t field_08;
    // +0x0C: pointer to some sub-structure (initialized twice)
    void *field_0C;
    // +0x10 to +0x38: zero-initialized fields
    uint32_t field_10;
    uint32_t field_14;
    uint32_t field_18;
    uint32_t field_1C;
    uint32_t field_20;
    uint32_t field_24;
    uint32_t field_28;
    uint32_t field_2C;
    uint32_t field_30;
    uint32_t field_34;
    uint32_t field_38;
    // +0x3C: data buffer of 0x8000 bytes follows (if class layout includes it)
    // The constructor copies gInitialAudioData into the data area.

    __thiscall AudioDataManager() {
        // Set up vtable
        this->vtable = &PTR_FUN_00d5fd40;  // vtable for AudioDataManager

        // Initialize header fields
        this->field_04 = 1;
        this->field_08 = 0;
        this->field_0C = &PTR_LAB_00d5fd38; // first assignment

        // Store global singleton pointer
        gAudioDataManager = this;

        // Reassign the same pointer? Possibly a two-phase initialization
        this->field_0C = &PTR_LAB_00d5fd3c; // second assignment

        // Zero out remaining fields (offset 0x10 to 0x38)
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;
        this->field_20 = 0;
        this->field_24 = 0;
        this->field_28 = 0;
        this->field_2C = 0;
        this->field_30 = 0;
        this->field_34 = 0;
        this->field_38 = 0;

        // If pre-loaded data exists, copy 32KB into the data buffer (starting at offset 0x3C)
        // Note: The copy begins from the start of this object; the header fields are small,
        // so the bulk of the data overwrites the buffer area.
        if (gInitialAudioData != nullptr) {
            engineMemCpy(this, gInitialAudioData, 0x8000);
        }
    }
};