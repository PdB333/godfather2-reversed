// FUNC_NAME: EARSStream::advanceTime
void __thiscall EARSStream::advanceTime(int thisPtr, StreamManager* streamMgr, uint deltaTime, bool applyVolume) 
{
    // +0x140: accumulated time counter (in samples/frames?)
    *(int*)(thisPtr + 0x140) += deltaTime;

    // Get the audio device or stream device from the manager
    // FUN_006b0ee0 likely returns a device pointer
    AudioDevice* device = reinterpret_cast<AudioDevice*>(FUN_006b0ee0(streamMgr));
    // +100 in device: maximum playable time? (e.g., buffer size)
    uint maxTime = *(uint*)(device + 100);

    // Get current time from the scheduler or hardware (FUN_006b18a0)
    uint currentTime = FUN_006b18a0(); // e.g., audio clock time

    uint remaining = maxTime - currentTime;
    if (remaining < deltaTime) {
        deltaTime = remaining;
    }

    // +0x54: a 4-byte type identifier (often an EARS class hash)
    // 0x637b907 = likely "EARSStream" or similar
    if (*(int*)(thisPtr + 0x54) == 0x637b907 && applyVolume) {
        float volumeScale = 0.0f;
        // +0x1d0: pointer to an optional volume source (e.g., a linked volume envelope)
        if (*(int*)(thisPtr + 0x1d0) != 0) {
            // +0x54 in the volume source: base volume factor
            // +0x188 in this: global volume multiplier
            volumeScale = *(float*)(*(int*)(thisPtr + 0x1d0) + 0x54) * *(float*)(thisPtr + 0x188);
        }

        float timeDeltaFloat = static_cast<float>(static_cast<int>(deltaTime));
        // Handle negative delta? (the cast with INT_MIN trick)
        if (static_cast<int>(deltaTime) < 0) {
            timeDeltaFloat += DAT_00e44578; // likely 0.0f or a small epsilon? (note: DAT_00e44578 is a global float)
        }
        // FUN_008c09a0: applies a volume adjustment over time (negative = fade out?)
        // Parameter 6 might indicate a specific audio channel or ramp type
        FUN_008c09a0(-(timeDeltaFloat * volumeScale), 6);
    }

    // FUN_006b6440: finalizes the time advancement (e.g., commits to hardware buffer)
    FUN_006b6440(deltaTime);
}