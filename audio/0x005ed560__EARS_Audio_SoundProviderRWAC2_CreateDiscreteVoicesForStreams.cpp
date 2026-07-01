// Xbox PDB: EARS::Audio::SoundProviderRWAC2::CreateDiscreteVoicesForStreams
// FUNC_NAME: AudioDataManager::setupAudioEffectChain
undefined4 __thiscall AudioDataManager::setupAudioEffectChain(AudioDataManager *this) {
    int slotIndex;
    int *channelBlock; // actually points to a channel configuration block
    int retVal;
    undefined4 *channelArray;
    undefined4 *pChannel;
    int i;
    undefined4 auxSendHandle[2];
    undefined4 auxSendSendParams[2]; // used for send level setting

    slotIndex = this;
    retVal = getAudioProperty("DISCRETE_CHANNELS");
    *channelBlock = retVal; // channelBlock passed in EAX (maybe a member pointer)
    releaseAudioProperty("DISCRETE_CHANNELS");
    
    // Initialize channel array (5 slots, each 0xC bytes, starting at channelBlock + 0x10)
    pChannel = channelBlock + 0x10;
    i = 5;
    do {
        *pChannel = *channelBlock;
        pChannel = pChannel + 0xC; // advance by 48 bytes per slot
        i = i - 1;
    } while (i != 0);
    
    // Process each of the 5 channel slots
    channelArray = channelBlock + 10; // pointer to slot array, adjusted for structure offsets
    int numSlots = 5;
    do {
        // Check if this slot is uninitialized and system is active
        if ( ((channelArray[-5] == 0) && (*(int *)(this + 0x580) != 0)) &&
             (*(int *)(this + 0x56C) != 0) &&
             (channelArray[2] == 0x10) ) {
            // Begin scoped audio graph construction
            beginAudioGraph();
            
            // Add sound player node
            addAudioNode("SndPlayer");
            int baseOffset = *channelArray + -0xC + channelArray[1] * 0xC;
            unsigned int nodeId = hashString("SndPlayer"); // 0x536e5031
            *(undefined4 *)(baseOffset + 4) = nodeId;
            
            // Add Rechannel node
            addAudioNode("Rechannel");
            nodeId = hashString("Rechannel"); // 0x52636830
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add Resample node
            addAudioNode("Resample");
            nodeId = hashString("Resample"); // 0x52737030
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add GeneralPurposeLowpass node
            addAudioNode("GeneralPurposeLowpass");
            nodeId = hashString("Lowpass"); // 0x4c493230
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add AuxSend1 node
            addAudioNode("AuxSend1");
            nodeId = hashString("AuxSend1"); // 0x53656e30
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add AuxSend2 node
            addAudioNode("AuxSend2");
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add AuxSend3 node
            addAudioNode("AuxSend3");
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Add SendToMaster node
            addAudioNode("SendToMaster");
            *(undefined4 *)(baseOffset + 4) = nodeId;
            *(undefined4 *)(*channelArray + -0xC + channelArray[1] * 0xC) = 0;
            *(undefined1 *)(*channelArray + -4 + channelArray[1] * 0xC) = 6;
            
            // Create the effect chain and register it
            retVal = createEffectChain(*(undefined4 *)(this + 0x580), 0, channelArray[1], *channelArray, 0);
            channelArray[-5] = retVal;
            channelArray[-4] = retVal + 0x50;
            
            if ((retVal != 0) && (retVal + 0x50 != 0)) {
                // Set up AuxSend1 send level
                int auxSendNode = getAudioProperty("AuxSend1", &baseOffset);
                int nodeInfo = findAudioNode(auxSendNode, &baseOffset);
                if ( (nodeInfo != 0) &&
                     (*(int *)(baseOffset + 0x28) == 0x53656e30) &&
                     (*(int **)(this + 0x39C) != (int *)0x0) &&
                     (**(int **)(this + 0x39C) != 0) ) {
                    getAudioSendInfo(*(undefined4 *)(this + 0x580), *(undefined4 *)(nodeInfo + 0x10), 0, auxSendHandle);
                    auxSendHandle[0] = **(undefined4 **)(this + 0x39C);
                    setAudioSendInfo(0, auxSendHandle);
                }
                
                // Set up AuxSend2 send level
                auxSendNode = getAudioProperty("AuxSend2", &baseOffset);
                nodeInfo = findAudioNode(auxSendNode, &baseOffset);
                if ( (nodeInfo != 0) &&
                     (*(int *)(baseOffset + 0x28) == 0x53656e30) &&
                     (*(int **)(this + 0x3CC) != (int *)0x0) &&
                     (**(int **)(this + 0x3CC) != 0) ) {
                    getAudioSendInfo(*(undefined4 *)(this + 0x580), *(undefined4 *)(nodeInfo + 0x10), 0, auxSendHandle);
                    auxSendHandle[0] = **(undefined4 **)(this + 0x3CC);
                    setAudioSendInfo(0, auxSendHandle);
                }
                
                // Set up AuxSend3 send level
                auxSendNode = getAudioProperty("AuxSend3", &baseOffset);
                nodeInfo = findAudioNode(auxSendNode, &baseOffset);
                if ( (nodeInfo != 0) &&
                     (*(int *)(baseOffset + 0x28) == 0x53656e30) &&
                     (*(int **)(this + 0x3FC) != (int *)0x0) &&
                     (**(int **)(this + 0x3FC) != 0) ) {
                    getAudioSendInfo(*(undefined4 *)(this + 0x580), *(undefined4 *)(nodeInfo + 0x10), 0, auxSendHandle);
                    auxSendHandle[0] = **(undefined4 **)(this + 0x3FC);
                    setAudioSendInfo(0, auxSendHandle);
                }
                
                // Set up SendToMaster send level
                auxSendNode = getAudioProperty("SendToMaster", &baseOffset);
                nodeInfo = findAudioNode(auxSendNode, &baseOffset);
                if ( (nodeInfo != 0) &&
                     (*(int *)(baseOffset + 0x28) == 0x53656e30) ) {
                    getAudioSendInfo(*(undefined4 *)(this + 0x580), *(undefined4 *)(nodeInfo + 0x10), 0, auxSendHandle);
                    auxSendHandle[0] = **(undefined4 **)(this + 0x42C);
                    setAudioSendInfo(0, auxSendHandle);
                }
            }
            
            endAudioGraph();
        }
        
        channelArray = channelArray + 0xC; // move to next slot (48 bytes)
        numSlots = numSlots - 1;
    } while (numSlots != 0);
    
    return 1;
}