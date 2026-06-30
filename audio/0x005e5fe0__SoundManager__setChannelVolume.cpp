// FUNC_NAME: SoundManager::setChannelVolume
// Address: 0x005e5fe0
// Sets volume (or similar float parameter) for a sound channel. Returns 1 on success, 0 on failure.

#include <cstdint>

// Structure for a single sound slot (0x74 bytes each)
struct SoundChannel {
    int32_t field_0x00;   // +0x00: seems to be non-zero check
    int32_t field_0x04;   // +0x04
    void* somePointer;    // +0x08: pointer used later (iVar1 = piVar2[2])
    // ... other fields ...
    float volume;         // +0x60: set to the float value (cast to int then stored)
    // 0x60 = 0x18 * sizeof(int32_t) = 24 * 4 = 96? Actually 0x60 = 96, but 0x18*4=96. OK.
    // The offset is 0x60 from the start of the struct.
};

// The owning manager class (offsets from this)
class SoundManager {
public:
    // +0x603c: pointer to array of SoundChannel slots (max 0x200 entries)
    SoundChannel* channelArray;  // at offset 0x603c

    bool __thiscall setChannelVolume(uint32_t channelIndex, float volume) {
        // Check preconditions
        if (channelArray == nullptr) return false;
        if (channelIndex >= 0x200) return false;

        SoundChannel* channel = &channelArray[channelIndex];
        if (channel == nullptr) return false;
        if (channel->field_0x00 == 0) return false;

        // Save original pointer for later update
        void* somePtr = channel->somePointer;  // iVar1 = piVar2[2]

        // Store the float value as raw integer bits at offset +0x60
        *reinterpret_cast<int32_t*>(&channel->volume) = *reinterpret_cast<int32_t*>(&volume);

        // Call internal function with double version of volume
        FUN_005dbc10(channelIndex, static_cast<double>(volume));

        // If the saved pointer is valid, update the volume there as well
        if (somePtr != nullptr) {
            *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(somePtr) + 0x4c) = volume;
            return true;
        }

        return false;
    }
};

// External function: likely updates the audio engine with the new volume as double
extern void __cdecl FUN_005dbc10(uint32_t channelIndex, double volume);