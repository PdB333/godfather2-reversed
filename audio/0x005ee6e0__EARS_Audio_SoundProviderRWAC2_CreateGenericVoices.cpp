// Xbox PDB: EARS::Audio::SoundProviderRWAC2::CreateGenericVoices
// FUNC_NAME: AudioManager::initializeAudioChannels
// Address: 0x005ee6e0
// This function initializes 128 audio processing chains (channels) for the sound system.
// Each chain consists of: RAMGENERIC (memory buffer), SndPlayer, Rechannel, Resample, Gainfader,
// GeneralPurposeLowpass, AuxSend1, AuxSend2, AuxSend3, and SendToMaster.
// It also connects auxiliary sends to external bus objects stored in the manager.

int AudioManager::initializeAudioChannels()
{
    int *channelData;
    int tempInt;
    int nodeHandle;
    uint fourCC;
    uint *tempPtr;
    int loopCounter;
    uint auxSendParams[2];
    uint sendToMasterParams[2];
    uint tempParam;
    uint tempParam2;

    // Check if audio engine and mixer are initialized
    if ((*(int *)(this + 0x580) != 0) && (*(int *)(this + 0x56c) != 0)) {
        channelData = (int *)(this + 0x674); // Pointer to array of channel data blocks
        loopCounter = 0x80; // 128 channels

        do {
            // Create a RAMGENERIC node (memory buffer for audio data)
            nodeHandle = getAudioNodeHandle("RAMGENERIC");
            channelData[5] = nodeHandle;

            // If channel flags indicate less than 16, perform some initialization
            if ((uint)channelData[1] < 0x10) {
                resetAudioChain();
                resetAudioChain2();
            }

            beginAudioGraphBuild(); // Start building the audio graph for this channel

            // Add SndPlayer node
            pushAudioNodeName("SndPlayer");
            nodeHandle = *channelData;
            tempInt = channelData[-1];
            fourCC = hashFourCC(0x536e5031); // 'SnP1'
            *(uint *)(tempInt + nodeHandle * 0xc - 8) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 6;

            // Add Rechannel node
            pushAudioNodeName("Rechannel");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x52636830); // 'Rch0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add Resample node
            pushAudioNodeName("Resample");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x52737030); // 'Rsp0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add Gainfader node
            pushAudioNodeName("Gainfader");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x47614630); // 'Gaf0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add GeneralPurposeLowpass node
            pushAudioNodeName("GeneralPurposeLowpass");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x4c493230); // 'LI20'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add AuxSend1 node
            pushAudioNodeName("AuxSend1");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x53656e30); // 'Sen0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add AuxSend2 node
            pushAudioNodeName("AuxSend2");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x53656e30); // 'Sen0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add AuxSend3 node
            pushAudioNodeName("AuxSend3");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x53656e30); // 'Sen0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 2;

            // Add SendToMaster node and connect it to the master bus
            pushAudioNodeName("SendToMaster");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x506e3231); // 'Pn21'
            tempPtr = sendToMasterParams;
            *(uint *)(this + 4) = fourCC;
            fourCC = hashFourCC(0x506e3231);
            connectAudioNodes(*(uint *)(this + 0x580), fourCC, tempPtr);
            tempParam2 = 0;
            sendToMasterParams[0] = DAT_0110ae38; // Some global data
            tempParam = DAT_00e44720; // Another global
            *(uint **)(channelData[-1] - 0xc + *channelData * 0xc) = sendToMasterParams;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 6;

            // Finalize the audio graph for this channel
            pushAudioNodeName("SendToMaster");
            this = channelData[-1] - 0xc + *channelData * 0xc;
            fourCC = hashFourCC(0x53656e30); // 'Sen0'
            *(uint *)(this + 4) = fourCC;
            *(int *)(channelData[-1] - 0xc + *channelData * 0xc) = 0;
            *(byte *)(channelData[-1] - 4 + *channelData * 0xc) = 6;

            // Create the audio graph and store handles
            nodeHandle = createAudioGraph(*(uint *)(this + 0x580), 0, *channelData, channelData[-1], 0);
            channelData[-6] = nodeHandle;
            channelData[-5] = nodeHandle + 0x50;

            if (nodeHandle == 0) {
                // Failed to create graph, clean up
                *channelData = 0;
                freeMemory(channelData[-1]);
                channelData[-1] = 0;
                channelData[1] = 0;
                channelData[-5] = 0;
            }
            else {
                // Connect AuxSend1 to external bus (stored at +0x39c)
                tempPtr = &this;
                this = 0;
                fourCC = getAudioNodeHandle("AuxSend1", tempPtr);
                nodeHandle = findAudioNodeByName(fourCC, tempPtr);
                if (((nodeHandle != 0) && (*(int *)(this + 0x28) == 0x53656e30)) &&
                    (*(int **)(this + 0x39c) != (int *)0x0) && (**(int **)(this + 0x39c) != 0)) {
                    getAudioNodeConnectionPoint(*(uint *)(this + 0x580), *(uint *)(nodeHandle + 0x10), 0, auxSendParams);
                    auxSendParams[0] = **(uint **)(this + 0x39c);
                    setAudioNodeParameter(0, auxSendParams);
                }

                // Connect AuxSend2 to external bus (stored at +0x3cc)
                tempPtr = &this;
                fourCC = getAudioNodeHandle("AuxSend2", tempPtr);
                nodeHandle = findAudioNodeByName(fourCC, tempPtr);
                if (((nodeHandle != 0) && (*(int *)(this + 0x28) == 0x53656e30)) &&
                    (*(int **)(this + 0x3cc) != (int *)0x0) && (**(int **)(this + 0x3cc) != 0)) {
                    getAudioNodeConnectionPoint(*(uint *)(this + 0x580), *(uint *)(nodeHandle + 0x10), 0, auxSendParams);
                    auxSendParams[0] = **(uint **)(this + 0x3cc);
                    setAudioNodeParameter(0, auxSendParams);
                }

                // Connect AuxSend3 to external bus (stored at +0x3fc)
                tempPtr = &this;
                fourCC = getAudioNodeHandle("AuxSend3", tempPtr);
                nodeHandle = findAudioNodeByName(fourCC, tempPtr);
                if (((nodeHandle != 0) && (*(int *)(this + 0x28) == 0x53656e30)) &&
                    (*(int **)(this + 0x3fc) != (int *)0x0) && (**(int **)(this + 0x3fc) != 0)) {
                    getAudioNodeConnectionPoint(*(uint *)(this + 0x580), *(uint *)(nodeHandle + 0x10), 0, auxSendParams);
                    auxSendParams[0] = **(uint **)(this + 0x3fc);
                    setAudioNodeParameter(0, auxSendParams);
                }

                // Connect SendToMaster to master bus (stored at +0x42c)
                tempPtr = &this;
                fourCC = getAudioNodeHandle("SendToMaster", tempPtr);
                nodeHandle = findAudioNodeByName(fourCC, tempPtr);
                if ((nodeHandle != 0) && (*(int *)(this + 0x28) == 0x53656e30)) {
                    getAudioNodeConnectionPoint(*(uint *)(this + 0x580), *(uint *)(nodeHandle + 0x10), 0, auxSendParams);
                    auxSendParams[0] = **(uint **)(this + 0x42c);
                    setAudioNodeParameter(0, auxSendParams);
                }
            }

            endAudioGraphBuild(); // Finish building the graph for this channel

            // Move to next channel data block (0x3e ints = 0xF8 bytes per block)
            channelData += 0x3e;
            loopCounter--;
        } while (loopCounter != 0);
    }

    return 1; // Success
}