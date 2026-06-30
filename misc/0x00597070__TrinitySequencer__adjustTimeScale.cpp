// FUNC_NAME: TrinitySequencer::adjustTimeScale
void TrinitySequencer::adjustTimeScale(float deltaTime)
{
    float fVar1;
    bool bFoundTwo = false;
    uint entryIndex = 0;

    // Only adjust if deltaTime > 0 and audio sync is enabled
    if ((deltaTime > 0.0f) && (gAudioSyncEnabled != '\0'))
    {
        do
        {
            // Check if this sequence entry is active (bit 0)
            if ((gSequenceEntryFlags[entryIndex] & 1) != 0)
            {
                // Get the sequence object pointer from the entry
                Sequence* seq = gSequenceEntries[entryIndex].sequencePtr;

                // Call virtual function at vtable+0x0C: getTotalDuration()? returns int (samples?)
                int totalDuration = seq->vtable->getTotalDuration(seq);

                if (totalDuration > 0)
                {
                    if (bFoundTwo)
                    {
                        // Warning: two sequences trying to sync with audio
                        gTrinitySequencer->vtable->printWarning(gTrinitySequencer,
                            "TrinitySequencer::adjustTimeScale found two sequences trying to sync with audio");
                    }

                    // Convert total duration to time using a factor (maybe samples to seconds?)
                    float totalTime = (float)totalDuration * gSampleToTimeFactor; // DAT_00e2e210

                    bFoundTwo = true;

                    // Get current playback position from sequence (vtable+0x10)
                    float currentTime = seq->vtable->getCurrentTime(seq);

                    // Calculate remaining time
                    float remainingTime = totalTime - currentTime;

                    // Compute new time scale: remainingTime / deltaTime + baseTimeScale
                    float newTimeScale = remainingTime / deltaTime + gBaseTimeScale; // DAT_00e2b1a4

                    // Clamp the time scale based on thresholds
                    if (remainingTime <= gRemainingTimeThreshold) // DAT_00e446b4
                    {
                        gAppliedTimeScale = gBaseTimeScale;
                        if ((remainingTime < gRemainingTimeLowerThreshold) && // DAT_00e446b0
                            (newTimeScale < gMinTimeScale)) // DAT_00e2cd54
                        {
                            gAppliedTimeScale = gMinTimeScale;
                        }
                    }
                    else
                    {
                        gAppliedTimeScale = newTimeScale;
                        if (gMaxTimeScale < newTimeScale) // DAT_00e2b04c
                        {
                            gAppliedTimeScale = gMaxTimeScale;
                        }
                    }
                }
            }
            entryIndex += 0x1D0; // Stride per sequence entry (464 bytes)
        } while (entryIndex < 0x1D00); // 16 entries total (0x1D00 / 0x1D0 = 16)
    }
}