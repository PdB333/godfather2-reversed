// Xbox PDB: EARS::Modules::LuaToEarsAudioGlue::Open
// FUNC_NAME: EARSCommandTable::registerCommands
void EARSCommandTable::registerCommands(EARSCommandTable *thisClass) {
    int *stackPtr;
    int newCommand;
    int tempStackBase;
    
    // Register "PlayEmx" command
    EARSCommandTable::addCommandString(thisClass, "PlayEmx");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PlayEmxHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "PlayEntityEmx" command
    EARSCommandTable::addCommandString(thisClass, "PlayEntityEmx");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PlayEntityEmxHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "StopEmx" command
    EARSCommandTable::addCommandString(thisClass, "StopEmx");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &StopEmxHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEmxVolume" command
    EARSCommandTable::addCommandString(thisClass, "SetEmxVolume");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetEmxVolumeHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEmxPitch" command
    EARSCommandTable::addCommandString(thisClass, "SetEmxPitch");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetEmxPitchHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEmxPosition" command
    EARSCommandTable::addCommandString(thisClass, "SetEmxPosition");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetEmxPositionHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEmxAzimuth" command
    EARSCommandTable::addCommandString(thisClass, "SetEmxAzimuth");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetEmxAzimuthHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "PlayStream" command
    EARSCommandTable::addCommandString(thisClass, "PlayStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PlayStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "PrimeStream" command
    EARSCommandTable::addCommandString(thisClass, "PrimeStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PrimeStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "StartStream" command
    EARSCommandTable::addCommandString(thisClass, "StartStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = StartStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "StopStream" command
    EARSCommandTable::addCommandString(thisClass, "StopStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = StopStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamMixCategory" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamMixCategory");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetStreamMixCategoryHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamEmitterLocation" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamEmitterLocation");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetStreamEmitterLocationHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamVolume" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamVolume");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetStreamVolumeHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamChannelVolume" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamChannelVolume");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetStreamChannelVolumeHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamEffect" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamEffect");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetStreamEffectHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetGlobalEffect" command
    EARSCommandTable::addCommandString(thisClass, "SetGlobalEffect");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetGlobalEffectHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetPluginEffect" command
    EARSCommandTable::addCommandString(thisClass, "SetPluginEffect");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetPluginEffectHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetAuxEnabled" command
    EARSCommandTable::addCommandString(thisClass, "SetAuxEnabled");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetAuxEnabledHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamChannelEffectSend" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamChannelEffectSend");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetStreamChannelEffectSendHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "GetStreamStatus" command
    EARSCommandTable::addCommandString(thisClass, "GetStreamStatus");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = GetStreamStatusHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "GetStreamDuration" command
    EARSCommandTable::addCommandString(thisClass, "GetStreamDuration");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = GetStreamDurationHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetStreamPrimeFunction" command
    EARSCommandTable::addCommandString(thisClass, "SetStreamPrimeFunction");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetStreamPrimeFunctionHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "PrimeEarsAudioStream" command
    EARSCommandTable::addCommandString(thisClass, "PrimeEarsAudioStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PrimeEarsAudioStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "PlayEarsAudioStream" command
    EARSCommandTable::addCommandString(thisClass, "PlayEarsAudioStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = PlayEarsAudioStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "StopEarsAudioStream" command
    EARSCommandTable::addCommandString(thisClass, "StopEarsAudioStream");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &StopEarsAudioStreamHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEarsAudioStreamStopMessage" command
    EARSCommandTable::addCommandString(thisClass, "SetEarsAudioStreamStopMessage");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &SetEarsAudioStreamStopMessageHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "SetEnvelopeMap" command
    EARSCommandTable::addCommandString(thisClass, "SetEnvelopeMap");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(code **)(newCommand + 0xC) = SetEnvelopeMapHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;

    // Register "GetEnvelopeValue" command
    EARSCommandTable::addCommandString(thisClass, "GetEnvelopeValue");
    if (*(unsigned int *)(*(int *)(thisClass + 0x10) + 0x20) <= 
        *(unsigned int *)(*(int *)(thisClass + 0x10) + 0x24)) {
        EARSAbort();
    }
    newCommand = EARSAllocCommand(0);
    *(undefined1 **)(newCommand + 0xC) = &GetEnvelopeValueHandler;
    stackPtr = *(int **)(thisClass + 8);
    stackPtr[1] = newCommand;
    *stackPtr = 6;
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) + 8;
    EARSCommandTable::stackCommit(thisClass + 0x40,
        *(int *)(thisClass + 8) - 0x10,
        *(int *)(thisClass + 8) - 8);
    *(int *)(thisClass + 8) = *(int *)(thisClass + 8) - 0x10;
    return;
}