// FUNC_NAME: SoundDefaults::initialize
// Address: 0x005004f0
// Initializes a static default sound configuration structure and returns its pointer.
// The structure contains a vtable pointer, name string, extension ID, and buffer size.
// Likely used for .snd sound resources in EA's EARS engine.

#include <cstdint>

// Structure representing the sound defaults block (size at least 0x28)
struct SoundDefaults {
    void*   vtableOrPointer;    // +0x00: Pointer to function table or object
    const char* name;           // +0x04: Name string "Sound"
    uint32_t extID;             // +0x08: Extension identifier (".snd" as little-endian)
    int32_t  unk1;              // +0x0c: Unknown constant = 1
    int32_t  unk2;              // +0x10: Unknown constant = 2
    int32_t  unk3;              // +0x14: Zero
    int32_t  bufferSize;        // +0x18: Buffer size = 0x800 (2048)
    int32_t  unk4;              // +0x1c: Zero
    int32_t  unk5;              // +0x20: Zero
    int32_t  unk6;              // +0x24: Zero
};

// Global static instance of the sound defaults
static SoundDefaults s_SoundDefaults;

// External symbol from a different compilation unit
extern void* PTR_LAB_00e37cc0;

// The function initiates the global defaults and returns a pointer to the structure.
void* SoundDefaults::initialize()
{
    // Zero out unused fields
    s_SoundDefaults.unk3 = 0;
    s_SoundDefaults.unk4 = 0;
    s_SoundDefaults.unk5 = 0;
    s_SoundDefaults.unk6 = 0;

    // Set name and extension identifier
    s_SoundDefaults.name    = "Sound";
    s_SoundDefaults.extID   = 0x2e736e64;  // ".snd" in little-endian

    // Set unknown flags/buffer parameters
    s_SoundDefaults.unk1      = 1;
    s_SoundDefaults.unk2      = 2;
    s_SoundDefaults.bufferSize = 0x800;

    // Set vtable/function pointer from external label
    s_SoundDefaults.vtableOrPointer = &PTR_LAB_00e37cc0;

    return &s_SoundDefaults;
}