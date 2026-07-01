// FUNC_NAME: BNKStreamManager::processStreamUpdate
void __fastcall BNKStreamManager::processStreamUpdate(int* thisPtr)
{
    // thisPtr +0x58 = m_pMultiTrackStream
    int* streamPtr = reinterpret_cast<int*>(thisPtr[0x16]);

    if (streamPtr != nullptr) {
        int* mixerPtr = nullptr;
        int* temp = reinterpret_cast<int*>(streamPtr[0x3FF]); // +0xFFC = pointer to large structure (maybe mixer)
        if (temp != nullptr) {
            int* base = reinterpret_cast<int*>(reinterpret_cast<int>(temp) - 0x48); // subtract offset to get base
            if (base != nullptr) {
                mixerPtr = base;
            }
        }

        if (streamPtr != nullptr && mixerPtr != nullptr) {
            uint8_t playState = reinterpret_cast<uint8_t*>(mixerPtr)[0x1B8C]; // +0x1B8C = current streaming state (0=stopped,1=paused)
            uint32_t trackIndex = streamPtr[0x404]; // +0x1010 = track/sound ID (max 0x5B=91)
            uint32_t currentTime = FUN_007f95d0(); // returns system time / frame counter

            if (playState < 2 && trackIndex < 0x5B) {
                // Look up parameter block from global table (2D array: playState x trackIndex, plus low byte of time for variation)
                int tableEntry = g_parameterTable[(currentTime & 0xFF) + (playState * 0x5B + trackIndex) * 2];
                // Virtual call at vtable index 0x0B (offset 0x2C): setStreamParameters(AudioData*, loop, fade, spatial, volume, pan)
                (thisPtr->vtable[0x2C])(reinterpret_cast<AudioData*>(tableEntry), 1, 1, 0, 1.0f, 1.0f);
                // Virtual call on the stream object at vtable index 0x59 (offset 0x164): play()
                streamPtr->vtable[0x59]();
            }
        }
    }
}