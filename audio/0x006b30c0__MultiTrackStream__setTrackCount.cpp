// FUNC_NAME: MultiTrackStream::setTrackCount
void __thiscall MultiTrackStream::setTrackCount(uint newCount) {
    // Compare with current track count at +0x64
    if (currentTrackCount != newCount) {
        // If new count is less than maximum allowed (+0x58)
        if (newCount < maxTrackCount) {
            // Stop all active tracks using the manager handle at +0x40
            stopAllTracks(*(int*)(this + 0x40));
            // Adjust (reduce) the number of tracks; second param is the number to remove
            removeTracks(*(int*)(this + 0x38), maxTrackCount - newCount);
        }
        // Update current track count
        currentTrackCount = newCount;
    }
}