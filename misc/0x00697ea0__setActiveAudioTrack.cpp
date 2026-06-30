// FUNC_NAME: setActiveAudioTrack
// Address: 0x00697ea0
// Role: Setter for a global audio track handle; returns previous handle value.

// Global variable at 0x00e506ac, likely holds current active audio track handle.
static uint32_t g_activeAudioTrackHandle = 0;

// Replaces the current active audio track handle with the provided one.
// Returns the previous handle value for potential restoration or comparison.
uint32_t setActiveAudioTrack(uint32_t newTrackHandle)
{
    uint32_t oldTrackHandle = g_activeAudioTrackHandle;
    g_activeAudioTrackHandle = newTrackHandle;
    return oldTrackHandle;
}