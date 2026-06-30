// FUNC_NAME: AudioManager::releaseSpeaker
// Address: 0x004929a0
// Role: Releases a speaker/channel assignment, clearing its busy flag and resetting state.
// Called when a sound finishes or is stopped, to free the speaker slot.

#include <cstdint>

class AudioManager {
public:
    // +0x14: speaker type/pan index (used to access global type availability table at 0x011eb8fc, 0x10 bytes per entry)
    int32_t m_speakerType; 
    // +0x220: speaker index (low byte is actual slot; possibly includes flags)
    uint32_t m_speakerIndex;
    // +0x224: flag or reservation state (reset to 0 on release)
    int32_t m_reserved;

    // External static global arrays (addresses from Ghidra)
    // 0x011eb8fc: byte table indexed by m_speakerType * 0x10; non-zero indicates that type is active
    // 0x011d912c: byte array indexed by the computed speaker slot; set to 0 to mark slot free

    // Unknown internal functions
    void stopSound();      // 0x00618d40 (probably stops audio playback)
    void clearSoundState(); // 0x00490c90 (resets additional sound state)

    // Main destructor/release method
    void __thiscall releaseSpeaker();
};

void __thiscall AudioManager::releaseSpeaker() {
    uint32_t uVar1;

    // If we have a valid speaker index
    if (m_speakerIndex != 0) {
        // Extract low byte as base slot index
        uVar1 = m_speakerIndex & 0xff;

        // Check if the speaker type (or mode) is currently active in the global availability table
        // The table is indexed by m_speakerType * 0x10 (size of each entry block?)
        if (*(uint8_t*)(0x011eb8fc + m_speakerType * 0x10) != 0) {
            // If active, add 0x10 to slot to get the actual busy flag index
            uVar1 += 0x10;
        }

        // Stop sound (likely plays a stop event or frees hardware channel)
        stopSound(); // 0x00618d40

        // Clear the busy flag in the global slot table
        *(uint8_t*)(0x011d912c + uVar1) = 0;
    }

    // Reset the reservation flag
    m_reserved = 0;

    // Clear any remaining sound state
    clearSoundState(); // 0x00490c90
}