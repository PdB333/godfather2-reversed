// FUNC_NAME: AudioManager::setupDiscreteChannels
// Function address: 0x005ed560
// Description: Sets up audio processing graph for discrete (e.g., 5.1) output channels.
// Creates a chain: SndPlayer -> Rechannel -> Resample -> GeneralPurposeLowpass -> 3x AuxSend -> SendToMaster
// Then connects the chain and configures auxiliary sends.

int AudioManager::setupDiscreteChannels() {
    // Get configuration array for discrete channels (pointer to array of 5 entries, each 12 bytes)
    DiscreteChannelEntry* channelEntries = (DiscreteChannelEntry*)FUN_004dafd0("DISCRETE_CHANNELS");
    
    // Copy the first entry's ID to all 5 slots (initialization?)
    DiscreteChannelEntry* copyDst = channelEntries + 4; // offset 0x10 in bytes from start? Actually byte offset 16
    for (int i = 0; i < 5; i++) {
        copyDst->channelId = channelEntries->channelId;
        copyDst = (DiscreteChannelEntry*)((uint8_t*)copyDst + 0xC);
    }

    // Iterate over 5 channel entries starting from entry at byte offset 10 from base
    DiscreteChannelEntry* entry = (DiscreteChannelEntry*)((uint8_t*)channelEntries + 10); // offset 10 bytes
    for (int count = 5; count > 0; count--) {
        // Condition: entry->field0 == 0, sound system exists, something else exists, and entry->flags == 0x10
        if (entry->field0 == 0 &&
            mSoundSystem != 0 &&
            mUnknownPtr != 0 &&
            entry->flags == 0x10) {

            // Lock audio system
            FUN_00c9eac0();

            // Create SndPlayer node
            FUN_005e9ba0("SndPlayer");
            AudioNode* playerNode = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC); // Calculate node address
            uint32_t playerId = FUN_00c9cd50(0x536e5031); // 'SnP1' fourCC
            playerNode->typeFourCC = playerId;
            
            // Connect player to output? 
            FUN_00c9cba0(mSoundSystem, playerId, &localOutputSlot); // localOutputSlot is something
            localOutputSlot = DAT_00e2dd14; // global data
            // Link the node
            *(uint32_t**)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = localOutputSlot;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6; // node type?

            // Create Rechannel node
            FUN_005e9ba0("Rechannel");
            AudioNode* rechannelNode = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            uint32_t rechannelId = FUN_00c9cd50(0x52636830); // 'Rch0'
            rechannelNode->typeFourCC = rechannelId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0; // Some field
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create Resample node
            FUN_005e9ba0("Resample");
            uint32_t resampleId = FUN_00c9cd50(0x52737030); // 'Rsp0'
            AudioNode* resampleNode = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            resampleNode->typeFourCC = resampleId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create GeneralPurposeLowpass
            FUN_005e9ba0("GeneralPurposeLowpass");
            uint32_t lowpassId = FUN_00c9cd50(0x4c493230); // 'LI20'
            AudioNode* lowpassNode = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            lowpassNode->typeFourCC = lowpassId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create AuxSend1
            FUN_005e9ba0("AuxSend1");
            uint32_t auxId = FUN_00c9cd50(0x53656e30); // 'Sen0'
            AudioNode* aux1Node = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            aux1Node->typeFourCC = auxId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create AuxSend2
            FUN_005e9ba0("AuxSend2");
            AudioNode* aux2Node = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            aux2Node->typeFourCC = auxId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create AuxSend3
            FUN_005e9ba0("AuxSend3");
            AudioNode* aux3Node = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            aux3Node->typeFourCC = auxId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Create SendToMaster
            FUN_005e9ba0("SendToMaster");
            AudioNode* masterNode = (AudioNode*)((uint8_t*)entry + entry->field1 * 0xC - 0xC);
            masterNode->typeFourCC = auxId;
            *(uint32_t*)((uint8_t*)entry + entry->field1 * 0xC - 0xC) = 0;
            *(uint8_t*)((uint8_t*)entry + entry->field1 * 0xC - 4) = 6;

            // Connect the chain starting from output index to the nodes
            int result = FUN_00ca55a0(mSoundSystem, 0, entry->field1, entry->channelId, 0);
            entry->field0 = result;
            entry->field1_5 = result + 0x50; // some offset

            if (result != 0 && result + 0x50 != 0) {
                // Configure AuxSend1: look up the aux bus by name
                int paramDummy = 0;
                void* auxConfig1 = FUN_004dafd0("AuxSend1", &paramDummy);
                int auxNode1 = FUN_005e9d90(auxConfig1, &paramDummy);
                if (auxNode1 != 0 && *(uint32_t*)(paramDummy + 0x28) == 0x53656e30 && // 'Sen0'
                    mAuxBus1 != 0 && *mAuxBus1 != 0) {
                    FUN_00c9cbe0(mSoundSystem, *(void**)(auxNode1 + 0x10), 0, &sendValue);
                    sendValue = *mAuxBus1;
                    FUN_00c9cd40(0, &sendValue); // Set aux send level
                }

                // Configure AuxSend2
                void* auxConfig2 = FUN_004dafd0("AuxSend2", &paramDummy);
                int auxNode2 = FUN_005e9d90(auxConfig2, &paramDummy);
                if (auxNode2 != 0 && *(uint32_t*)(paramDummy + 0x28) == 0x53656e30 &&
                    mAuxBus2 != 0 && *mAuxBus2 != 0) {
                    FUN_00c9cbe0(mSoundSystem, *(void**)(auxNode2 + 0x10), 0, &sendValue);
                    sendValue = *mAuxBus2;
                    FUN_00c9cd40(0, &sendValue);
                }

                // Configure AuxSend3
                void* auxConfig3 = FUN_004dafd0("AuxSend3", &paramDummy);
                int auxNode3 = FUN_005e9d90(auxConfig3, &paramDummy);
                if (auxNode3 != 0 && *(uint32_t*)(paramDummy + 0x28) == 0x53656e30 &&
                    mAuxBus3 != 0 && *mAuxBus3 != 0) {
                    FUN_00c9cbe0(mSoundSystem, *(void**)(auxNode3 + 0x10), 0, &sendValue);
                    sendValue = *mAuxBus3;
                    FUN_00c9cd40(0, &sendValue);
                }

                // Configure SendToMaster
                void* masterConfig = FUN_004dafd0("SendToMaster", &paramDummy);
                int masterNodeIdx = FUN_005e9d90(masterConfig, &paramDummy);
                if (masterNodeIdx != 0 && *(uint32_t*)(paramDummy + 0x28) == 0x53656e30) {
                    FUN_00c9cbe0(mSoundSystem, *(void**)(masterNodeIdx + 0x10), 0, &sendValue);
                    sendValue = *mMasterBus; // +0x42c
                    FUN_00c9cd40(0, &sendValue);
                }
            }

            // Unlock audio system
            FUN_00c9eae0();
        }

        // Move to next channel entry (12 bytes forward)
        entry = (DiscreteChannelEntry*)((uint8_t*)entry + 0xC);
    }

    return 1;
}