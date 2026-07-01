// FUNC_NAME: AnimationController::loadAnimationState

void __fastcall AnimationController::loadAnimationState(void *this)
{
    int index = *(int *)((char *)this + 0x74);           // +0x74: mCurrentAnimStateIndex
    void *array = *(void **)((char *)this + 0xb8);       // +0xB8: mpAnimDataTable (array of AnimEntry, size 0x28)
    AnimEntry *entry = (AnimEntry *)((char *)array + index * 0x28);

    // Update internal animation state from offset 0x04 of the entry
    updateAnimation((AnimEntryData *)((char *)entry + 4));

    // Apply texture resource; uses entry field at +0x14 and the member at +0x90 as override
    applyTexture(*(uint32 *)((char *)entry + 0x14),       // +0x14: mTextureID
                 (int *)((char *)this + 0x90),            // +0x90: mpOverrideTexture
                 1);

    // Copy core animation data from entry to this object
    *(uint32 *)((char *)this + 0x78) = entry->name;      // +0x78: mAnimNameID
    *((char *)this + 0xAC) = entry->flags1;              // +0xAC: mFlagByte1
    *((char *)this + 0xAD) = entry->flags2;              // +0xAD: mFlagByte2
    *(uint32 *)((char *)this + 0xA4) = entry->startTime; // +0xA4: mStartTime
    *(uint32 *)((char *)this + 0xA8) = entry->endTime;   // +0xA8: mEndTime
    *(uint32 *)((char *)this + 0xB0) = entry->speed;     // +0xB0: mSpeed

    // Assign default texture pointer if none provided
    void *texturePtr = *(void **)((char *)this + 0x7C);  // +0x7C: mpDefaultTexture
    if (texturePtr == NULL)
        texturePtr = &DAT_0120546e;                       // Static fallback texture string
    *(void **)((char *)this + 0x8C) = texturePtr;        // +0x8C: mpCurrentTextureBase

    // Override texture if present
    int override = *(int *)((char *)this + 0x90);        // +0x90: mpOverrideTexture
    if (override != 0)
    {
        *(int *)((char *)this + 0xA0) = override;       // +0xA0: mpFinalTexture
        return;
    }
    *(void **)((char *)this + 0xA0) = &DAT_0120546e;     // +0xA0: mpFinalTexture
}