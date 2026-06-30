// FUNC_NAME: EventManager::registerCoreSignals

// Register all core game event signals with the event system.
// Called during engine initialization, parameters are likely the command ID and argument.
void EventManager::registerCoreSignals(uint8_t commandId, uint32_t commandArg)
{
    // Store the command parameters for later use.
    s_commandId = commandId;                     // DAT_012053ca
    s_commandParam = commandArg;                 // DAT_012053fc
    s_commandHandler = FUN_0045d070;             // Default handler function pointer

    // Register "audio: play" signal if the string is not empty.
    if (s_audioPlaySignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("audio: play");
        registerSignalHandler(&s_audioPlayHandler, signalId);   // +0x? (DAT_0120ead4)
    }

    // Register "vfx: play" signal
    if (s_vfxPlaySignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("vfx: play");
        registerSignalHandler(&s_vfxPlayHandler, signalId);     // +0x? (DAT_0120eaa0)
    }

    // Register "vfx: stop" signal
    if (s_vfxStopSignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("vfx: stop");
        registerSignalHandler(&s_vfxStopHandler, signalId);     // +0x? (DAT_0120eac4)
    }

    // Register "rws: send message" signal
    if (s_rwsSendMessageSignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("rws: send message");
        registerSignalHandler(&s_rwsSendMessageHandler, signalId); // +0x? (DAT_0120eab4)
    }

    // Register "motion_blur_on" signal
    if (s_motionBlurOnSignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("motion_blur_on");
        registerSignalHandler(&s_motionBlurOnHandler, signalId);   // +0x? (DAT_0120eacc)
    }

    // Register "motion_blur_off" signal
    if (s_motionBlurOffSignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("motion_blur_off");
        registerSignalHandler(&s_motionBlurOffHandler, signalId);  // +0x? (DAT_0120ea98)
    }

    // Register "set_metamodel_var" signal
    if (s_setMetamodelVarSignal[0] != '\0') {
        uint32_t signalId = signalLookupByName("set_metamodel_var");
        registerSignalHandler(&s_setMetamodelVarHandler, signalId); // +0x? (DAT_0120eaa8)
    }

    // Register "delete_entity" signal
    if (s_deleteEntitySignal[0] != '\0') {
        signalLookupByName("delete_entity");
        registerSignalHandler();                                     // Note: call appears to omit some arguments?
        return;                                                      // early return after this signal
    }
}