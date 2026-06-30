// FUNC_NAME: AudioDataManager::playStreamCommand
void AudioDataManager::playStreamCommand(const char* commandString)
{
    char streamName[32];
    char loopString[32];
    char volumeString[32];
    char* builtPath;

    // Parse the command string into three tokens: stream name, loop flag, volume
    if (!parseCommandTokens(commandString, streamName, loopString, volumeString))
    {
        return;
    }

    // Get the sound system singleton from global data (+0x24 offset)
    int* soundSystemPtr = *(int**)(*(int*)&g_GlobalData + 0x24);
    if (soundSystemPtr == nullptr)
    {
        return;
    }

    // Build the full path to the audio stream file
    builtPath = nullptr;
    buildAudiostreamsPath(&builtPath, "audiostreams\\%s", streamName);

    // Check for .aif extension and handle accordingly
    char* extension = getFileExtension();
    if (extension != nullptr)
    {
        int compareResult = 5;
        bool match = true;
        char* extPtr = ".aif";
        do
        {
            if (compareResult == 0) break;
            compareResult--;
            match = (*extension == *extPtr);
            extension++;
            extPtr++;
        } while (match);

        if (match)
        {
            handleAifExtension();
            handleGlobalAifCleanup(&DAT_00e31a8c);
        }
    }

    // Determine loop flag and volume
    bool loop = (__stricmp(loopString, "true") == 0);
    float volume = (float)_atof(volumeString);

    // Use default path if none built
    const char* pathToUse = (builtPath != nullptr) ? builtPath : (const char*)&defaultPathString;

    // Call the virtual function (index 1) on the sound system to play the stream
    (*(void (**)(const char*, bool, float))(*soundSystemPtr + 4))(pathToUse, loop, volume);

    // Cleanup if needed (the original code calls a function pointer, assumed to be a deallocator)
    if (builtPath != nullptr)
    {
        (*builtPath)(builtPath); // This is likely a custom deallocation; simplified here
    }
}