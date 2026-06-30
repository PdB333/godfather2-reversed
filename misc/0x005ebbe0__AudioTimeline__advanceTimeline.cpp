// FUNC_NAME: AudioTimeline::advanceTimeline

// Function at 0x005ebbe0: Advances a sound event timeline for a given channel.
// The audio timeline is part of the EA EARS engine sound system.
// The channel index is passed in the low 16 bits of EAX (fastcall style).
// Param_1 is the this pointer (AudioTimeline*).
// Returns 1 (true) on success, always returns 1.

bool AudioTimeline::advanceTimeline(uint channelIndex)
{
    // Each timeline channel is a struct of size 0xF8.
    // Base of channel array is at offset 0x5A0 in the AudioTimeline object.
    int channelOffset = (channelIndex & 0xFFFF) * 0xF8;
    uint8_t* channelBase = reinterpret_cast<uint8_t*>(this) + 0x5A0 + channelOffset;

    // Check if this channel is currently playing (flag at +0xB8 within channel).
    if (*(char*)(channelBase + 0xB8) == '\0') {
        // Not playing mode: advance through event sequence.
        int currentEventIndex = *(int*)(channelBase + 0xAC);  // +0xAC
        int totalEvents = *(int*)(channelBase + 0xA8);        // +0xA8 (max index, exclusive)
        if (currentEventIndex < totalEvents - 1) {
            // Get current game time from clock pointer (stored at +0x580 in AudioTimeline)
            double currentTime = *(double*)(*(int*)(reinterpret_cast<uint8_t*>(this) + 0x580) + 8);
            double lastEventStartTime = *(double*)(channelBase + 0xB0); // +0xB0

            // Each event in the timeline is an 8-byte structure: { float startTime; float durationOrVolume; }
            // Array of these events starts at offset 0x20 within the channel.
            int nextEventIndex = currentEventIndex + 1;
            float nextEventStart = *(float*)(channelBase + 0x24 + currentEventIndex * 8); // start time of next event (currentEventIndex+1? Actually uses currentEventIndex for condition, but then nextEventIndex for data)
            // Condition: next event start time <= current time - last event start time
            if ((double)nextEventStart <= currentTime - lastEventStartTime) {
                // Call function to get an available sound slot (likely returns a handle or pointer)
                int soundSlot = sound_getNextAvailable();
                if (soundSlot != 0) {
                    // Set up sound playback parameters – calling with sound system functions
                    // FUN_00c9cbe0: likely sets world position or attaches sound to object?
                    sound_setPosition(*(int*)(reinterpret_cast<uint8_t*>(this) + 0x580), *(int*)(soundSlot + 0x10), 0, &currentTime);

                    // Determine volume/duration for the next event
                    float duration = 0.0f;
                    float nextDuration = *(float*)(channelBase + 0x20 + nextEventIndex * 8); // at +0x20[ index*8 ]
                    if (nextDuration > 0.0f) {
                        duration = nextDuration;
                        if (s_maxVolume <= duration) {
                            duration = s_maxVolume;
                        }
                    }

                    // Lock sound system for batch update (FUN_00c9eac0)
                    sound_beginWrite();
                    // Start playing sound with mode 0 (play? or set params?)
                    sound_controlSound(0, &currentTime); // FUN_00c9cd40(0, &local_20)
                    // Unlock sound system (FUN_00c9eae0)
                    sound_endWrite();

                    // Update last event start time and current event index
                    *(double*)(channelBase + 0xB0) = currentTime; // +0xB0
                    *(int*)(channelBase + 0xAC) = nextEventIndex; // +0xAC
                    return 1;
                }
            }
        }
    }
    else {
        // Playing mode: check if we need to start a new event (spontaneous?).
        int soundHandle = *(int*)(channelBase + 0xE0); // +0xE0 – currently playing sound handle
        if (soundHandle == 0) {
            // No current sound, check timing
            float triggerTime = *(float*)(channelBase + 0xA4); // +0xA4 – some threshold?
            double currentTime = *(double*)(*(int*)(reinterpret_cast<uint8_t*>(this) + 0x580) + 8);
            double lastEventStart = *(double*)(channelBase + 0xB0);
            if ((double)triggerTime <= currentTime - lastEventStart) {
                int soundSlot = sound_getNextAvailable();
                if (soundSlot != 0) {
                    // Start a new sound
                    sound_beginWrite();
                    sound_controlSound(1, 0); // mode 1: play?
                    int newHandle = sound_allocate(); // FUN_00c9eb20
                    *(int*)(channelBase + 0xE0) = newHandle;
                    sound_endWrite();
                    sound_release(); // FUN_005efb60 – release previous sound?
                    // Reset fields
                    *(int*)(channelBase + 0xDC) = 0;
                    *(int*)(channelBase + 0xE0) = 0;
                    *(int*)(channelBase + 0xE4) = 0;
                }
            }
        }
    }
    return 1;
}