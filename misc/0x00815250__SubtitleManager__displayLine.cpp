// FUNC_NAME: SubtitleManager::displayLine
class SubtitleManager {
public:
    // +0x10: flags (bit 0 = hasActiveCaption)
    // +0x14: returnValue (handle or previous caption ID)
    // +0x18: unknown (set to 0 when starting)
    // +0x1c: subtitleData (allocated structure for subtitles)
    // +0x20: titleData (allocated structure for titles)
    // +0x24: subtitleState (sub-object controlling subtitles)
    // +0x5c: titleState (sub-object controlling titles)

    int displayLine(const char* speaker, int lineId, int titleDuration);
};

// Decompiled function at 0x00815250
int SubtitleManager::displayLine(const char* speaker, int lineId, int titleDuration) {
    char buffer[16]; // local_10, 16-byte buffer for string assembly

    // Initialize caption context with speaker and line ID
    initCaptionContext(speaker, lineId);

    int subtitleIndex = -1;
    // Look up string index for subtitles
    subtitleIndex = lookupStringIndex("subtitles"); // returns -1 if not found

    if (subtitleIndex >= 0) {
        // Check global subtitle enabled flag at DAT_01129938 + 0x14 (bit0)
        if ((*(byte*)(DAT_01129938 + 0x14) & 1) != 0) {
            int subtitlesOn = 1;
            // If subtitles forced off flag at DAT_0112af90 + 0x48
            if (*(char*)(DAT_0112af90 + 0x48) != '\0') {
                char voiceActive = isVoiceoverActive();
                if (voiceActive == '\0') {
                    subtitlesOn = 0; // hide subtitles if voiceover is not playing
                }
            }
            // Set subtitle state at offset 0x24 (enable, style 0)
            setCaptionState(this + 0x24, subtitlesOn, 0);

            int subtitleData = 0;
            // Allocate subtitle data (size 0x1c = 28 bytes)
            int alloc = allocate(0x1c);
            if (alloc != 0) {
                subtitleData = initCaptionData(this + 0x24, 0);
            }

            // Setup the subtitle string buffer from the index
            setupCaptionString(buffer, subtitleIndex);
            startCaption();
            finalizeCaption();
        }
    }

    int titleIndex = -1;
    // Look up string index for titles
    titleIndex = lookupStringIndex("titles");
    if (titleIndex >= 0) {
        // Set title state at offset 0x5c (type=3, duration from parameter)
        setCaptionState(this + 0x5c, 3, titleDuration);

        int titleData = 0;
        int alloc = allocate(0x1c);
        if (alloc != 0) {
            titleData = initCaptionData(this + 0x5c, 500); // 500ms default? 
        }

        setupCaptionString(buffer, titleIndex);
        startCaption();
        finalizeCaption();
    }

    int result = 0;
    if (subtitleData != 0 || titleData != 0) {
        // If we already had an active caption (bit0), cancel previous
        if ((*(byte*)(this + 0x10) & 1) != 0) {
            cancelPreviousCaption();
        }
        // Store new data pointers and set active flag
        *(int*)(this + 0x1c) = subtitleData;
        *(int*)(this + 0x20) = titleData;
        *(uint*)(this + 0x10) |= 1;
        result = *(int*)(this + 0x14); // return previous caption ID or handle
        *(int*)(this + 0x18) = 0;
    }

    cleanupCaptionContext();
    return result;
}