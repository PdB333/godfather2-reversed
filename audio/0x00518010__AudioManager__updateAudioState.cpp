// FUNC_NAME: AudioManager::updateAudioState
void AudioManager::updateAudioState()
{
    int idx;
    uint32 tempFlags;
    uint32 tempFlags2;
    uint32 *pAlloc;
    uint32 sourceIdx;
    bool bVar6;
    char listenerData[44];  // stack buffer for listener position/orientation

    // Handle audio state transitions
    if ((currentState == targetState) && (transitionInProgress == 0)) {
        // No transition needed, set state to 1 (likely default/ambient)
        startTransitionToState(1);
    }
    else {
        // Update transition between current and target state
        updateTransition(currentState, targetState);
    }

    // Save and clear interrupt flags? 
    int iVar1 = interruptFlag2;
    bool bVar6 = interruptFlag1 != 0;
    interruptFlag1 = 0;
    interruptFlag2 = 0;
    if (bVar6 || iVar1 != 0) {
        // Call virtual function at offset 0x9C (likely clearSoundInterrupts)
        (**(code **)(*(uint32 *)pAudioManagerObj + 0x9c))(pAudioManagerObj, 0);
    }

    // Clamp master volume to at least 14 (0x0E)
    if (masterVolume < 0x0E) {
        masterVolume = 0x0E;
    }
    if (0x0E < maxMasterVolume) {
        maxMasterVolume = 0x0E;
    }
    channelVolume0 = 0;  // Probably SFX volume

    if (masterVolume < 0x16) {
        masterVolume = 0x16;
    }
    if (0x16 < maxMasterVolume) {
        maxMasterVolume = 0x16;
    }
    channelVolume5 = 1;  // Music volume

    if (masterVolume < 7) {
        masterVolume = 7;
    }
    if (7 < maxMasterVolume) {
        maxMasterVolume = 7;
    }
    channelVolume4 = 0;  // Voice volume

    if (masterVolume < 0x19) {
        masterVolume = 0x19;
    }
    if (0x19 < maxMasterVolume) {
        maxMasterVolume = 0x19;
    }
    channelVolume6 = 5;  // Ambient volume

    if (masterVolume < 0x18) {
        masterVolume = 0x18;
    }
    if (0x18 < maxMasterVolume) {
        maxMasterVolume = 0x18;
    }
    channelVolume7 = 0;  // Maybe UI volume

    if (masterVolume < 0x0F) {
        masterVolume = 0x0F;
    }
    if (0x0F < maxMasterVolume) {
        maxMasterVolume = 0x0F;
    }
    channelVolume1 = 0;

    if (masterVolume < 0x1B) {
        masterVolume = 0x1B;
    }
    if (0x1A < maxMasterVolume) {
        maxMasterVolume = 0x1B;
    }
    channelVolume8 = 0;

    // Set initial channel crossfade gains
    setChannelGains(1, 2, 1);  // parameters: group, fadeType, target?

    // Setup shader handles for fog effects
    fogShader = persistentFogShader;
    fogShader2 = 0;
    if (fogShaderTemp != storeFogShader) {
        fogShaderTemp = storeFogShader;
    }
    if ((storeFogShader == storeFogShader2) || (storeFogShader == storeFogShader3) || (storeFogShader == storeFogShader4)) {
        fogColorParam = getShaderParameter(storeFogShader, "fog_color");
        fogParamsParam = getShaderParameter(fogShaderTemp, "fog_params");
        depthTextureParam = getShaderParameter(fogShaderTemp, "depth_texture");
    }

    // Release shaders if render target matches
    if (renderTargetHandle == &someRenderTarget) {
        releaseShader(fogShaderTemp);
        releaseShader(fogShader);
    }

    // Update audio source flags for the current source
    sourceIdx = currentSourceIndex;
    if (pAudioSourceOwner != 0) {
        sourceIdx = *(uint32 *)(pAudioSourceOwner + 0x170);  // +0x170 likely currentSourceIndex
    }
    if ((sourceIdx != 0xFFFFFFFF) && (sourceIdx < 0x1000)) {
        idx = sourceIdx * 0x38;  // stride of AudioSource struct
        AudioSource* src = &audioSourceArray + idx;
        if ((src != 0) && (src->status < 4)) {
            if (src->soundDataPtr != 0) {
                clearSoundFlag(src->soundDataPtr, 0x210000);  // clear FLAG_FADE_IN?
            }
            src->flags = (src->flags & 0xFCAD8FFF) | 0x210000;  // Set fade-in flag
            updateSoundSystem();
        }
    }

    // Update audio source flags for the target state source
    if ((targetState != 0xFFFFFFFF) && (targetState < 0x1000)) {
        idx = targetState * 0x38;
        AudioSource* src = &audioSourceArray + idx;
        if ((src != 0) && (src->status < 4)) {
            if (src->soundDataPtr != 0) {
                clearSoundFlag(src->soundDataPtr, 0x200000);  // clear FLAG_FADE_OUT?
            }
            src->flags = (src->flags & 0xFCAC8FFF) | 0x200000;  // Set fade-out flag
            updateSoundSystem();
        }
    }

    // Update audio hardware
    updateAudioHardware();

    // Copy camera/viewport values
    viewportX = cameraViewportX;
    viewportY = cameraViewportY;
    viewportW = cameraViewportW;
    viewportH = cameraViewportH;
    viewport2 = viewportX;  // Possibly used for shadow or something

    // If using specific render target and fog shader is current, update shader parameters
    if ((renderTargetHandle == &someRenderTarget) && (fogShaderTemp == storeFogShader)) {
        setShaderParameters(storeFogShader, storeFogShader2, &viewportX);  // pass viewport data as shader constants
    }

    // Update camera and listener
    updateCamera();
    getListenerData(listenerData);  // fills 44-byte listener info (pos, orient, etc.)
    updateAudioListener();
    
    // Allocate 5 uint32s for some audio processing
    pAlloc = (uint32 *)allocateMemory(5, 4, 0, 1, 0);  // alloc size 20 bytes
    if (pAlloc != 0) {
        pAlloc[0] = someConstant1;
        pAlloc[1] = someConstant2;
        pAlloc[2] = someConstant3;
        pAlloc[3] = someConstant4;
        pAlloc[4] = someConstant5;
        pAlloc[5] = someConstant6;
        pAlloc[6] = someConstant7;
        pAlloc[7] = someConstant8;
        commitMemory();  // make allocation permanent
    }
    updateSoundEngine();

    // Second volume clamp and gain set (probably for final state after transition)
    if (masterVolume < 0x16) {
        masterVolume = 0x16;
    }
    if (0x16 < maxMasterVolume) {
        maxMasterVolume = 0x16;
    }
    channelVolume5 = 1;

    if (masterVolume < 7) {
        masterVolume = 7;
    }
    if (7 < maxMasterVolume) {
        maxMasterVolume = 7;
    }
    channelVolume4 = 1;  // Changed from 0 to 1

    if (masterVolume < 0x19) {
        masterVolume = 0x19;
    }
    if (0x19 < maxMasterVolume) {
        maxMasterVolume = 0x19;
    }
    channelVolume6 = 7;  // Changed from 5 to 7

    if (masterVolume < 0x18) {
        masterVolume = 0x18;
    }
    if (0x18 < maxMasterVolume) {
        maxMasterVolume = 0x18;
    }
    channelVolume7 = 0;

    if (masterVolume < 0x0F) {
        masterVolume = 0x0F;
    }
    if (0x0F < maxMasterVolume) {
        maxMasterVolume = 0x0F;
    }
    channelVolume1 = 0;

    if (masterVolume < 0x1B) {
        masterVolume = 0x1B;
    }
    if (0x1A < maxMasterVolume) {
        maxMasterVolume = 0x1B;
    }
    channelVolume8 = 0;

    setChannelGains(1, 5, 6);  // Second call with different parameters

    // Save current source index for next frame
    uint32 oldInterrupt1 = interruptFlag1;
    uint32 oldInterrupt2 = interruptFlag2;
    interruptFlag1 = currentSourceIndex;
    if (pAudioSourceOwner != 0) {
        interruptFlag1 = *(uint32 *)(pAudioSourceOwner + 0x170);
    }
    interruptFlag2 = 0;

    // Queue state change with old flags
    queueStateChange(4, oldInterrupt1, oldInterrupt2);
}