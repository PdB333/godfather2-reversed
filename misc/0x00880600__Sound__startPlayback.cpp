// FUNC_NAME: Sound::startPlayback
undefined1 __thiscall Sound::startPlayback(Sound* this, bool bDelayStart)
{
    int extraParam;
    unsigned int newStream;
    int sourceDataPtr;
    undefined1 result;
    undefined1 streamInfo[16]; // 16-byte stream creation info
    void* exceptionHandler; // SEH handler address (not used in logic)
    int exceptionData;      // SEH data

    result = 0;
    // If there's an existing stream, stop and release it
    if (this->mStreamHandle != 0)
    {
        AudioSystem::stopStream(this->mStreamHandle, 0, 0);    // FUN_005e6820
        AudioSystem::releaseStream(this->mStreamHandle);       // FUN_005e6660
        this->mStreamHandle = 0;
    }

    AudioSystem::prepare(); // FUN_005e3070

    // Exception handling setup (C++ try)
    exceptionHandler = &LAB_00880110;
    exceptionData = (int)this;

    // Decide which position data set to use based on a flag at offset 0x209
    if (this->field_0x209 == '\0')
    {
        sourceDataPtr = (int)&this->mPositionA; // +0x198
        // Check if all three components of set A are zero
        if ((this->mPositionA.x == 0) && (this->mPositionA.y == 0) && (this->mPositionA.z == 0))
        {
            extraParam = this->mExtraParamA; // +0x1a4
            goto checkExtra;
        }
    }
    else
    {
        sourceDataPtr = (int)&this->mPositionB; // +0x1a8
        // Check if all three components of set B are zero
        if ((this->mPositionB.x == 0) && (this->mPositionB.y == 0) && (this->mPositionB.z == 0))
        {
            extraParam = this->mExtraParamB; // +0x1b4
            checkExtra:
            if (extraParam == 0)
                goto skipCreation; // No valid data, skip stream creation
        }
    }

    // Create a new audio stream from the chosen position data
    newStream = AudioSystem::createStream(sourceDataPtr, streamInfo); // FUN_005e6500
    result = 1;
    this->mStreamHandle = newStream;

skipCreation:
    // If delay requested and stream was created, schedule playback with a 48ms delay
    if ((bDelayStart) && (this->mStreamHandle != 0))
    {
        unsigned int currentTime = Timer::getMilliseconds(); // FUN_00471610
        AudioSystem::setStartTime(this->mStreamHandle, currentTime + 48); // FUN_005e6580 (+0x30 = 48ms)
    }

    return result; // Returns 1 if a new stream was created, 0 otherwise
}