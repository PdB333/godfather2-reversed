// FUNC_NAME: MusicPlayer::setTrackParameter(int trackId, int fadeTime)

bool __thiscall MusicPlayer::setTrackParameter(int trackId, int fadeTime)
{
    // Array of track IDs at this+0x82b0, each entry 0x5c bytes, up to 10 tracks.
    int *trackIdArray = (int *)(this + 0x82b0);
    int trackIndex = 0;

    // Search for the track with matching ID
    while (true) {
        if (trackIdArray[0] >= 0 && trackIdArray[0] == trackId) {
            break;
        }
        trackIndex++;
        trackIdArray += 0x5c / sizeof(int); // stride 0x5c bytes
        if (trackIndex > 9) {
            return false;
        }
    }

    // Found track slot, get pointer to full track data at this+0x8210 + trackIndex*0x170
    int trackData = this + 0x8210 + trackIndex * 0x170;

    // Lock or begin audio update
    FUN_00ab4db0(&DAT_00e2aea0);

    // Check if a flag in an array indexed by trackData+0x9c is non-zero
    // Array at this+0x81c4, each element 0x10 bytes
    int flagIndex = *(int *)(trackData + 0x9c);
    if (*(int *)(this + 0x81c4 + flagIndex * 0x10) != 0) {
        // Get audio system pointer
        int iVar2 = FUN_005e9d10();

        // Set up audio parameter (channel 4, pointer to local_18)
        FUN_00c9cbe0(*(void **)(this + 0x580), *(void **)(iVar2 + 0x10), 4, &local_18);

        int local_10 = *(int *)(trackData + 0x134); // Save current float value

        FUN_00c9eac0();

        double dVar4;
        if (fadeTime >= 0) {
            // Calculate fade time from given parameter and global constants
            if (DAT_00e2af60 <= (double)fadeTime * DAT_00e446c8) {
                dVar4 = *(double *)(*(int *)(this + 0x580) + 8) + (double)fadeTime * DAT_00e446c8;
            } else {
                dVar4 = 0.0;
            }
        } else {
            dVar4 = DAT_00e2af58;
        }

        // Apply target value, conditionally immediate
        if ((*(int *)(trackData + 0xa4) != 0) ||
            (*(float *)(trackData + 0x134) <= 0.0f && *(float *)(trackData + 0x134) != 0.0f)) {
            // Just set the target, no immediate application
            *(double *)(trackData + 0x80) = dVar4;
        } else {
            // Set target and apply immediately
            *(double *)(trackData + 0x80) = dVar4;
            local_18 = dVar4;
            FUN_00c9cd40(4, &local_18);
        }

        FUN_00c9eae0();
        FUN_00ab4e70();
        return true;
    }

    FUN_00ab4e70();
    return false;
}