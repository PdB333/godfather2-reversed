// Xbox PDB: EARS::Audio::SoundProviderRWAC2::CreateEffectsSubmix1
// FUNC_NAME: AudioSubmixChain::buildDefaultChain

int AudioSubmixChain::buildDefaultChain(AudioManager* audioManager) {
    int* effectBufferPtr;
    int effectCount;
    int bufferIndex;
    int* chainBuffer;
    int result;
    int effectHandle;
    char** namePtr;
    undefined4* paramPtr;
    undefined4 paramValue[2];
    char* effectName[2];
    undefined4 tempVar[2];
    undefined4 value[2];

    // Initialization of submix chain structures
    SubmixChainInit();
    SubmixChainInit2();

    // Retrieve or create a submix bus named "SUBMIX1"
    this->submixID = FindOrCreateSubmix("SUBMIX1");

    // Begin defining the first submix effect: "Submix1"
    BeginSubmixDefinition("Submix1");

    effectCount = this->currentEffectCount;
    chainBuffer = this->chainBufferPtr;
    // Create effect node with hash 'Sub0' (0x53756230)
    effectHandle = CreateEffectNode(0x53756230); // 'Sub0' - likely submix effect
    // Store effect handle in the effect buffer array
    chainBuffer[effectCount * 3 - 2] = effectHandle;

    // Add the effect to the submix chain
    AddEffectToSubmix(audioManager->submixContext, effectHandle, &effectName);
    effectName[0] = "GlobalReverb";
    // Store name pointer in chain buffer
    *(char***)(chainBuffer + effectCount * 3 - 3) = effectName;
    // Enable effect (byte = 1)
    *(byte*)(chainBuffer + effectCount * 3 - 1) = 1;

    // Begin second submix: "Delay"
    BeginSubmixDefinition("Delay");

    effectCount = this->currentEffectCount;
    chainBuffer = this->chainBufferPtr;
    effectHandle = CreateEffectNode(0x44656c30); // 'Del0' - delay effect
    chainBuffer[effectCount * 3 - 2] = effectHandle;
    AddEffectToSubmix(audioManager->submixContext, effectHandle, &tempVar);
    tempVar[0] = DAT_00e2cd54;  // Likely a string constant "Delay"
    *(undefined4**)(chainBuffer + effectCount * 3 - 3) = tempVar;
    *(byte*)(chainBuffer + effectCount * 3 - 1) = 1;

    // Begin third submix: "GeneralPurposeBandpass"
    BeginSubmixDefinition("GeneralPurposeBandpass");

    effectCount = this->currentEffectCount;
    chainBuffer = this->chainBufferPtr;
    effectHandle = CreateEffectNode(0x42493230); // 'BI20' - bandpass effect
    chainBuffer[effectCount * 3 - 2] = effectHandle;
    // No name pointer (null)
    *(undefined4*)(chainBuffer + effectCount * 3 - 3) = 0;
    *(byte*)(chainBuffer + effectCount * 3 - 1) = 1;

    // Begin fourth submix: "SendWetToMaster"
    BeginSubmixDefinition("SendWetToMaster");

    effectCount = this->currentEffectCount;
    chainBuffer = this->chainBufferPtr;
    effectHandle = CreateEffectNode(0x53656e30); // 'Sen0' - send effect
    chainBuffer[effectCount * 3 - 2] = effectHandle;
    *(undefined4*)(chainBuffer + effectCount * 3 - 3) = 0;
    *(byte*)(chainBuffer + effectCount * 3 - 1) = 1;

    // Finalize the submix chain
    result = FinalizeSubmixChain(audioManager->submixContext, 0xFE, this->currentEffectCount, this->chainBufferPtr, 0);
    this->bufferStart = result;
    this->bufferEnd = result + 0x50;

    // Set the send wet level
    paramPtr = &audioManager;  // reinterpretation: actually address of audioManager parameter
    effectHandle = FindOrCreateSubmix("SendWetToMaster", &audioManager);
    int* param = GetNamedParameter(effectHandle, &audioManager);
    if (param != 0) {
        SetEffectParameter(audioManager->submixContext, *(int*)(param + 0x10), 0, &value);
        value[0] = **(int**)(audioManager + 0x42C);  // +0x42C likely a float value
        SetParameterValue(0, &value);
        return 1;
    }
    return 0;
}