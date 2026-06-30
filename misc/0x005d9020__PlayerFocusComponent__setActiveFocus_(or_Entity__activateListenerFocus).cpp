// FUNC_NAME: PlayerFocusComponent::setActiveFocus (or Entity::activateListenerFocus)

void __fastcall PlayerFocusComponent::setActiveFocus(PlayerFocusComponent* thisPtr)
{
    // +0x0A4: int32 m_isActiveFocus; flag indicating if this component is the global focus
    // +0x010: IUnknown* m_audioSource1; (e.g., a sound emitter handle)
    // +0x014: IUnknown* m_audioSource2;
    // +0x130: bool m_hasAudioData; whether audio data is attached
    // +0x174: audioSystemHandle? (used in FUN_0060add0)
    // +0x168, +0x164, +0x150, +0x140: various audio configuration pointers
    // +0x16C, +0x160: more audio data
    // +0x0B8: pointer to some array (indexed by +0x110)
    // +0x110: int32 m_currentSoundId; used to index into a table at DAT_011a0f28 (0x38 bytes per entry)
    // +0x100: int32 m_soundEntryIndex; used to index into the global sound table (max 0x1000)
    // +0x174: audio system pointer?
    // Global DAT_012058e8: pointer to the currently active PlayerFocusComponent

    int32* isActive = reinterpret_cast<int32*>(thisPtr + 0xA4);
    if (DAT_012058e8 == thisPtr) {
        *isActive = 0;      // this component is already active, just clear flag? strange.
    } else {
        *isActive = 1;
        DAT_012058e8 = thisPtr;
        // Release previous audio sources
        FUN_0060a460(*(int*)(thisPtr + 0x10)); // likely Release() on audio object
        FUN_0060a460(*(int*)(thisPtr + 0x14));
    }

    // If this component has audio data, configure audio spatialization
    if (*(uint8*)(thisPtr + 0x130) != 0) {
        // FUN_0060add0: set audio source position/orientation
        FUN_0060add0(*(int*)(thisPtr + 0x174),  // audio system
                     *(int*)(thisPtr + 0x168),  // some audio parameter
                     thisPtr + 0x150);          // position/transform
        FUN_0060add0(*(int*)(thisPtr + 0x174),
                     *(int*)(thisPtr + 0x164),
                     thisPtr + 0x140);
        // FUN_0060aa90: possibly set attenuation/volume
        FUN_0060aa90(*(int*)(thisPtr + 0x174),
                     *(int*)(thisPtr + 0x16C),
                     *(int*)(thisPtr + 0x160));
    }

    // Calculate and apply audio scale based on current sound entry
    int soundEntryOffset = thisPtr + 0xB8 + *(int*)(thisPtr + 0x110) * 0xC; // pointer to some structure
    int soundEntryPtr = *(int*)soundEntryOffset;
    if (soundEntryPtr != 0) {
        // Look up sound data from global table DAT_011a0f28 (each entry 0x38 bytes)
        uint32 entryIdx = *(uint32*)(thisPtr + 0x100);
        uint8* soundTableEntry = nullptr;
        if (entryIdx < 0x1000) {
            soundTableEntry = &DAT_011a0f28 + entryIdx * 0x38;
        }
        float scaleX = DAT_00e2cd54 / (float)*(uint16*)(soundTableEntry + 2); // width? radius?
        float scaleY = DAT_00e2cd54 / (float)*(uint16*)(soundTableEntry + 4);
        // FUN_0060ac80: set spatial scale on one of the audio sources
        FUN_0060ac80(*(int*)(thisPtr + 0x14), soundEntryPtr, &scaleX);
    }
}