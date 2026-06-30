// FUNC_NAME: AudioManager::updateActiveStreams
// Function address: 0x00491d70
// Role: Updates all active audio streams (music, ambient, effects) for the EARS audio engine

// ============================================================
// Assumed struct layout for AudioManager (partial)
// Offsets are relative to this pointer:
// +0x14: uint32_t audioDevice;         // Audio system handle/device ID
// +0x1C0: int musicStreamHandle;       // Handle for background music stream
// +0x1D0: void* musicStreamBuffer;     // Buffer or state for music stream
// +0x1E0: int tempStreamHandle;        // Handle for a secondary/one-shot stream
// +0x1E8: int ambientStreamHandle;     // Handle for ambient/environment stream
// +0x1F0: void* ambientStreamBuffer;   // Buffer or state for ambient stream
// +0x200: int fxStreamHandle;          // Handle for effects stream (e.g., SFX)
// +0x210: void* fxStreamBuffer;        // Buffer or state for effects stream
// ============================================================

// External functions (from EARS engine)
void __cdecl baseUpdate(void);                                 // FUN_00490b20
void __cdecl updateLinearStream(uint32_t device, int handle, void* buffer); // FUN_0060ad20
void __cdecl stopStream(void);                                 // FUN_006063b0
void __cdecl update3DStream(uint32_t device, int handle, void* buffer);    // FUN_0060add0

void __thiscall AudioManager::updateActiveStreams(void)
{
    // Perform base engine update (timers, frame counters, etc.)
    baseUpdate();

    // Update music stream if active
    if (this->musicStreamHandle != 0) {
        updateLinearStream(this->audioDevice, this->musicStreamHandle, &this->musicStreamBuffer);
    }

    // If a temporary stream handle exists, stop it (no parameters – likely uses internal state)
    if (this->tempStreamHandle != 0) {
        stopStream();
    }

    // Update ambient/3D stream if active
    if (this->ambientStreamHandle != 0) {
        update3DStream(this->audioDevice, this->ambientStreamHandle, &this->ambientStreamBuffer);
    }

    // Update effects stream (linear) if active
    if (this->fxStreamHandle != 0) {
        updateLinearStream(this->audioDevice, this->fxStreamHandle, &this->fxStreamBuffer);
    }
}