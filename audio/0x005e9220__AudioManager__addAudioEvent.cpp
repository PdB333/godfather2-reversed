// FUNC_NAME: AudioManager::addAudioEvent

int AudioManager::addAudioEvent(int *this, const char *soundName, void *data, int unkParam)
{
    int soundState = this[0x121]; // +0x484: sound play state
    if ((soundState > 0) && ((soundState < 3) || (soundState == 4))) {
        resetSilentMode(); // Reset silent mode when state is 1,2, or 4
    }

    if (soundName != nullptr) {
        // Compare soundName with "silent"
        bool isSilent = false;
        const char *silentStr = "silent";
        const char *p = soundName;
        const char *q = silentStr;
        int cmpResult = 0;
        while (*p == *q) {
            if (*p == '\0') {
                isSilent = true;
                break;
            }
            p++;
            q++;
        }
        if (!isSilent) {
            // Circular buffer index (max 3 entries)
            int index = this[0];
            int nextIndex = index + 1;
            if (nextIndex > 3) {
                nextIndex = 0;
            }
            this[0] = nextIndex; // Update head index

            // Entry pointer: base + index * 0x1b (size per entry in ints)
            int *entry = this + 1 + index * 0x1b; // each entry is 0x1b*4 = 108 bytes

            // Copy sound metadata from data
            entry[0x15] = *(int *)((char *)data + 0x48); // +0x48: likely volume or pitch
            entry[0x16] = *(int *)((char *)data + 0x30); // +0x30: position X or frequency
            entry[0x17] = *(int *)((char *)data + 0x34); // +0x34: position Y or something
            entry[0x14] = (*(char *)((char *)data + 0x4) == '\0') ? 1 : 0; // +0x4: isLooping? (0 = not looping)

            // Store sound name internally
            storeAudioEventName(soundName); // copies string to internal buffer

            // Clamp entry[0x15] using global threshold
            extern float globalAudioThreshold; // DAT_00e2b1a4
            if (entry[0x15] > globalAudioThreshold || entry[0x15] < 0.0f) {
                entry[0x15] = (int)globalAudioThreshold;
            }

            // Process the event
            processAudioEvent(entry, data, unkParam);

            // Notify audio system of change
            updateAudioEngine();

            return 1;
        }
    }

    // Silent sound handling: reset silent state counters
    this[0x7f] = 0; // +0x1FC: silent sound count?
    this[0x80] = 0; // +0x200: another silent counter?
    updateAudioEngine();
    return 1;
}