// FUNC_NAME: AudioSystem::updateSoundState
void __fastcall AudioSystem::updateSoundState(void *this, SoundObject *soundObj, 
    AudioParams *params, int param4, int param5, int param6, int param7, 
    int param8, int param9, int param10, uint flags)
{
    float timeDelta = gTimeDelta; // DAT_00e2b1a4
    float timeThreshold = gTimeThreshold; // DAT_00e2af44

    // Check if enough time has passed (soundObj +0x0C is likely some timer/state)
    if (timeThreshold < *(float *)(soundObj + 0x0C)) {
        // Save global audio state
        pushAudioState(); // FUN_00414aa0

        // Save all current global audio parameters
        int saved[18]; // Matching the 18 global DATs (b0..f0, c0..cc, f4..fc)
        saved[0] = gAudioParams1; // DAT_012192b0
        saved[1] = gAudioParams2; // DAT_012192b4
        saved[2] = gAudioParams3; // DAT_012192b8
        saved[3] = gAudioParams4; // _DAT_012192bc
        saved[4] = gAudioParams5; // _DAT_012192c0
        saved[5] = gAudioParams6; // _DAT_012192c4
        saved[6] = gAudioParams7; // _DAT_012192c8
        saved[7] = gAudioParams8; // _DAT_012192cc
        saved[8] = gAudioParams9; // DAT_012192d0
        saved[9] = gAudioParams10; // DAT_012192d4
        saved[10] = gAudioParams11; // _DAT_012192d8
        saved[11] = gAudioParams12; // DAT_012192dc
        saved[12] = gAudioParams13; // DAT_012192e0
        saved[13] = gAudioParams14; // DAT_012192e4
        saved[14] = gAudioParams15; // _DAT_012192e8
        saved[15] = gAudioParams16; // DAT_012192ec
        saved[16] = gAudioParams17; // DAT_012192f0
        saved[17] = gAudioParams18; // _DAT_012192f4

        // Build internal flags from input bits
        uint internalFlags = flags & 0x10000000;
        if ((flags & 0x1800) == 0) {
            internalFlags |= 3;
        }
        if (flags & 0x800) {
            internalFlags |= 2;
        }
        if (flags & 0x1000) {
            internalFlags |= 1;
        }
        if (flags & 0x2000000) {
            internalFlags |= 4;
        }
        if (flags & 0x8000000) {
            internalFlags |= 8;
        }

        // If 'immediate' flag is set, apply parameters directly
        if (flags & 1) {
            // Set new global audio parameters
            gAudioParams9 = param4;  // DAT_012192d0
            gAudioParams10 = param5; // DAT_012192d4
            gAudioParams11 = param6; // _DAT_012192d8
            gAudioParams12 = param7; // DAT_012192dc
            gAudioParams13 = param9; // DAT_012192e0
            gAudioParams14 = param10; // DAT_012192e4
            gAudioParams15 = timeDelta; // _DAT_012192e8 (float)
            gAudioParams16 = timeDelta; // DAT_012192ec (float)
            gAudioParams1 = timeDelta; // DAT_012192b0 (float)
            gAudioParams2 = timeDelta; // DAT_012192b4 (float)
            gAudioParams3 = timeDelta; // DAT_012192b8 (float)
            gAudioParams4 = 0; // _DAT_012192bc (int)
            gAudioParams18 = internalFlags; // _DAT_012192f4 (uint)
            // param_8 is pointer to 4 ints (vector/color?)
            gAudioParams5 = param8[0]; // _DAT_012192c0
            gAudioParams6 = param8[1]; // _DAT_012192c4
            gAudioParams7 = param8[2]; // _DAT_012192c8
            gAudioParams8 = param8[3]; // _DAT_012192cc
            gAudioParams17 = flags & 0x400000e; // DAT_012192f0

            // Apply the new audio state
            applyAudioState(); // FUN_00517d50

            // Restore previously saved global state
            gAudioParams1 = (float)saved[0];     // DAT_012192b0
            gAudioParams2 = (float)saved[1];     // DAT_012192b4
            gAudioParams3 = (float)saved[2];     // DAT_012192b8
            gAudioParams4 = saved[3];             // _DAT_012192bc
            gAudioParams5 = saved[4];             // _DAT_012192c0
            gAudioParams6 = saved[5];             // _DAT_012192c4
            gAudioParams7 = saved[6];             // _DAT_012192c8
            gAudioParams8 = saved[7];             // _DAT_012192cc
            gAudioParams9 = saved[8];             // DAT_012192d0
            gAudioParams10 = saved[9];            // DAT_012192d4
            gAudioParams11 = saved[10];           // _DAT_012192d8
            gAudioParams12 = saved[11];           // DAT_012192dc
            gAudioParams13 = saved[12];           // DAT_012192e0
            gAudioParams14 = saved[13];           // DAT_012192e4
            gAudioParams15 = (float)saved[14];    // _DAT_012192e8
            gAudioParams16 = (float)saved[15];    // DAT_012192ec
            gAudioParams17 = saved[16];           // DAT_012192f0
            gAudioParams18 = saved[17];           // _DAT_012192f4

            return;
        }

        // Non-immediate path: accumulate time and process
        processDelayedAudio(); // FUN_00517540
        gAccumulatedTime += gTimeDelta; // DAT_012192a0 += DAT_00e2b1a4
    }
}