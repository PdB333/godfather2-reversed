// FUNC_NAME: AudioManager::setupTimestretchedChannels
// Address: 0x005eda70
// Role: Initializes timestretched audio channels for DSP effects chain

int AudioManager::setupTimestretchedChannels() {
    int channelIndex;
    int handle;
    int* channelPtr;
    int channelCount = 5;
    uint* hashPtr;
    uint hashVal;

    // Get token for " TIMESTRETCHED_CHANNELS" (note leading space)
    uint token = getAudioToken(" TIMESTRETCHED_CHANNELS");
    // Probably logs or stores token
    debugPrint(" TIMESTRETCHED_CHANNELS");

    // Initialize channel array pointer (assumed to be at this+0x?? but code uses in_EAX)
    // The original used a local pointer, we simplify as iterating over mChannels[5]
    for (channelIndex = 0; channelIndex < channelCount; channelIndex++) {
        channelPtr = &mChannels[channelIndex]; // each channel entry is 0x3C bytes? Actually stride 0xC*?)
        // Check if channel slot is unused and audio engine is valid
        if (channelPtr[-5] != 0) continue; // some flag (offset -0x14 if stride 0xC)
        if (mAudioEngine == 0) continue;
        if (mAudioBank == 0) continue;
        if (channelPtr[2] != 0x10) continue; // expected format ID

        // Begin audio transaction
        audioBeginTransaction();

        // --- Setup SndPlayer node ---
        debugPrintString("SndPlayer");
        int playerOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x536e5031); // 'SnP1'
        *(uint*)(playerOffset + 4) = hashVal;
        hashVal = audioHashFromFourCC(0x536e5031);
        uint playerNode[2];
        audioCreateNode(mAudioEngine, hashVal, (uint*)&playerNode);
        playerNode[0] = DAT_00e2dd14; // some global parameter
        *(uint**)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = &playerNode;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6; // node type?

        // --- Setup Rechannel node ---
        debugPrintString("Rechannel");
        int rechannelOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x52636830); // 'Rch0'
        *(uint*)(rechannelOffset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup Resample node ---
        debugPrintString("Resample");
        int resampleOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x52737030); // 'Rsp0'
        *(uint*)(resampleOffset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup Timestretch node ---
        debugPrintString("Timestretch");
        int timestretchOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x54537430); // 'TSt0'
        *(uint*)(timestretchOffset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup GeneralPurposeLowpass node ---
        debugPrintString("GeneralPurposeLowpass");
        int lowpassOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x4c493230); // 'LI20'
        *(uint*)(lowpassOffset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup AuxSend1 node ---
        debugPrintString("AuxSend1");
        int aux1Offset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x53656e30); // 'Sen0'
        *(uint*)(aux1Offset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup AuxSend2 node ---
        debugPrintString("AuxSend2");
        int aux2Offset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x53656e30); // 'Sen0'
        *(uint*)(aux2Offset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup AuxSend3 node ---
        debugPrintString("AuxSend3");
        int aux3Offset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x53656e30); // 'Sen0'
        *(uint*)(aux3Offset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Setup SendToMaster node (with Pn21 parameter) ---
        debugPrintString("SendToMaster"); // originally used &DAT_00e3f8e4 which is probably "SendToMaster"
        int sendMasterOffset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x506e3231); // 'Pn21'
        uint sendMasterNode[2];
        audioCreateNode(mAudioEngine, hashVal, (uint*)&sendMasterNode);
        sendMasterNode[0] = DAT_0110ae38;
        sendMasterNode[1] = DAT_00e44720; // Actually local_10 and local_8 were separate, but here local_8=0 and local_10=another
        // original: local_8 = 0; local_18[0] = DAT_0110ae38; local_10 = DAT_00e44720;
        // But we combine: sendMasterNode[0] = DAT_0110ae38; sendMasterNode[1] = DAT_00e44720?
        // Actually careful: local_18[0] and local_10, but the code writes *(undefined4 **)(...)=local_18, so only first element.
        // Then later assigns local_8=0? Actually after creating, it does:
        // local_8 = 0; local_18[0] = DAT_0110ae38; local_10 = DAT_00e44720;
        // Then writes local_18 pointer. That sets two values? But local_18 is array of 2 undefined4? So it sets local_18[0] and local_18[1]?
        // Actually the decompiled: local_18[2] means array of 2? But then local_10 and local_8 are separate. Let's check:
        // The code: 
        //     uVar2 = FUN_00c9cba0(mAudioEngine,uVar2,puVar3); // puVar3 = local_18
        //     local_8 = 0;
        //     local_18[0] = DAT_0110ae38;
        //     local_10 = DAT_00e44720;
        // So it sets two separate local variables, but the pointer written is &local_18. That means local_18[0] and local_18[1]? Actually local_18[2] means two elements? The declaration is "undefined4 local_18[2];" so local_18[0] and local_18[1]. Then local_10 and local_8 are separate. The assignment local_8 = 0; might be intended for local_18[1]? But that's unclear. We'll place the values accordingly.
        sendMasterNode[0] = DAT_0110ae38;
        sendMasterNode[1] = DAT_00e44720; // better: local_10
        // Note: there's also local_8 = 0; but that's separate.
        *(uint**)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = &sendMasterNode;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // --- Now set up the effect chain via audioCreateCustomChannel ---
        debugPrintString("SendToMaster"); // Actually the next call is "SendToMaster" again? No, the last string was "SendToMaster", but after the above it does another "SendToMaster". Let's see:
        // After the last "SendToMaster", the next line in decompiled is:
        // FUN_005e9ba0("SendToMaster");
        // Then again sets up a node with hash 0x53656e30 etc. That's a second SendToMaster? Actually it's setting up the "SendToMaster" node again? Wait, that's confusing. Let's re-read the decompiled carefully.
        // Actually after the "Pn21" node setup, it does:
        //   FUN_005e9ba0(&DAT_00e3f8e4); // likely "SendToMaster"
        //   then setup a node with hash 0x506e3231 (Pn21) and creates a node, sets local variables, then writes pointer.
        // Then after that, it does:
        //   FUN_005e9ba0("SendToMaster"); // explicit string
        //   then setup another node with hash 0x53656e30 (Sen0) and writes 0, type 6.
        // So there are two "SendToMaster" nodes? One with Pn21 parameters and one plain Sen0? Actually the first is with Pn21 (which might be a param for send level?), second is a plain send.
        // We'll follow the original sequence. We'll add the second SendToMaster after the Pn21 one.
        // But the decompiled after Pn21 does the "SendToMaster" again immediately. So we'll do:

        // Second "SendToMaster" node (plain Sen0)
        debugPrintString("SendToMaster");
        int sendMaster2Offset = channelPtr[0] - 0xC + channelPtr[1] * 0xC;
        hashVal = audioHashFromFourCC(0x53656e30); // 'Sen0'
        *(uint*)(sendMaster2Offset + 4) = hashVal;
        *(uint*)(channelPtr[0] - 0xC + channelPtr[1] * 0xC) = 0;
        *(byte*)(channelPtr[0] - 4 + channelPtr[1] * 0xC) = 6;

        // Now create the custom channel (effect chain)
        int result = audioCreateCustomChannel(mAudioEngine, 0, channelPtr[1], channelPtr[0], 0);
        // Store handles
        channelPtr[-5] = result;
        channelPtr[-4] = result + 0x50;

        if ((result != 0) && (result + 0x50 != 0)) {
            // --- Connect AuxSend1 bus ---
            // Get token for "AuxSend1"
            uint auxToken = getAudioToken("AuxSend1", 0);
            int auxNode = audioFindNode(auxToken, 0);
            if ((auxNode != 0) && (*(int*)(auxNode + 0x28) == 0x53656e30) && (mAuxSendBus1 != 0) && (*mAuxSendBus1 != 0)) {
                uint sendParam[2];
                audioNodeSetParameter(mAudioEngine, *(uint*)(auxNode + 0x10), 0, (uint*)&sendParam);
                sendParam[0] = *mAuxSendBus1;
                audioNodeSetFloat(0, (uint*)&sendParam);
            }

            // --- Connect AuxSend2 bus ---
            auxToken = getAudioToken("AuxSend2", 0);
            auxNode = audioFindNode(auxToken, 0);
            if ((auxNode != 0) && (*(int*)(auxNode + 0x28) == 0x53656e30) && (mAuxSendBus2 != 0) && (*mAuxSendBus2 != 0)) {
                uint sendParam[2];
                audioNodeSetParameter(mAudioEngine, *(uint*)(auxNode + 0x10), 0, (uint*)&sendParam);
                sendParam[0] = *mAuxSendBus2;
                audioNodeSetFloat(0, (uint*)&sendParam);
            }

            // --- Connect AuxSend3 bus ---
            auxToken = getAudioToken("AuxSend3", 0);
            auxNode = audioFindNode(auxToken, 0);
            if ((auxNode != 0) && (*(int*)(auxNode + 0x28) == 0x53656e30) && (mAuxSendBus3 != 0) && (*mAuxSendBus3 != 0)) {
                uint sendParam[2];
                audioNodeSetParameter(mAudioEngine, *(uint*)(auxNode + 0x10), 0, (uint*)&sendParam);
                sendParam[0] = *mAuxSendBus3;
                audioNodeSetFloat(0, (uint*)&sendParam);
            }

            // --- Connect SendToMaster bus ---
            auxToken = getAudioToken("SendToMaster", 0);
            auxNode = audioFindNode(auxToken, 0);
            if ((auxNode != 0) && (*(int*)(auxNode + 0x28) == 0x53656e30)) {
                uint sendParam[2];
                audioNodeSetParameter(mAudioEngine, *(uint*)(auxNode + 0x10), 0, (uint*)&sendParam);
                sendParam[0] = *mMasterSendBus;
                audioNodeSetFloat(0, (uint*)&sendParam);
            }
        }

        // End audio transaction
        audioEndTransaction();
    }

    return 1;
}