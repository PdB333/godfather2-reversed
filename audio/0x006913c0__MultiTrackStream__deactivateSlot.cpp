// FUNC_NAME: MultiTrackStream::deactivateSlot

// Reconstructed from 0x006913c0 - Multi-track stream slot deactivation function
// Manages stopping/releasing audio tracks for a given slot, recording transitions into a history queue.

#include <cstdint>

// Forward declarations for global data
struct MusicStreamObj; // Contains vtable with method at offset 8

// Global singleton pointer to a manager struct with channel state fields
struct AudioManagerState {
    char padding_0x564[0x564];
    char track1State;  // +0x564
    char track2State;  // +0x565
};
extern AudioManagerState* g_audioManager; // = DAT_012233b4

// Arrays of 16 entries each
extern int g_track1HistoryIndex;    // DAT_00e50698
extern int g_track1History[16];     // DAT_00e50658
extern int g_track2HistoryIndex;    // DAT_00e50650
extern int g_track2History[16];     // DAT_00e50610

// Arrays indexed by slotIndex*2 (likely pairs of handles per slot)
extern uint32_t g_slotTrack1Handle[]; // DAT_01129bd4 (array of 32-bit values)
extern uint32_t g_slotTrack2Handle[]; // DAT_01129bd0

// Helper functions (stubs)
extern void* getStreamObject(char channelId);         // FUN_00411070
extern int  generateTrackHandle(void);                // FUN_004958a0

// Entry point for stopping both tracks for a given slot
void MultiTrackStream::deactivateSlot(int slotIndex) {
    char track1State = g_audioManager->track1State;  // save because global may be modified? Actually used after check.
    char track2State = g_audioManager->track2State;

    // Handle track1 (channel at +0x564)
    if (g_audioManager->track1State != 0x12) {
        // Get the stream object for this channel
        void* streamObj = getStreamObject(g_audioManager->track1State);
        int handle = generateTrackHandle();

        // Store the handle into the history queue (circular buffer, max 16 entries)
        if (g_track1HistoryIndex < 16) {
            g_track1History[g_track1HistoryIndex] = handle;
            g_track1HistoryIndex++;
        }

        // Call method at vtable offset 8 on the stream object with the slot's track handle
        uint32_t slotHandle = g_slotTrack1Handle[slotIndex * 2];
        MusicStreamObj* obj = static_cast<MusicStreamObj*>(streamObj);
        obj->vtable[2](slotHandle); // offset 0x8 = index 2
    }

    // Handle track2 (channel at +0x565)
    if (g_audioManager->track2State != 0x12) {
        void* streamObj = getStreamObject(g_audioManager->track2State);
        int handle = generateTrackHandle();

        if (g_track2HistoryIndex < 16) {
            g_track2History[g_track2HistoryIndex] = handle;
            g_track2HistoryIndex++;
        }

        uint32_t slotHandle = g_slotTrack2Handle[slotIndex * 2];
        MusicStreamObj* obj = static_cast<MusicStreamObj*>(streamObj);
        obj->vtable[2](slotHandle);
    }
}