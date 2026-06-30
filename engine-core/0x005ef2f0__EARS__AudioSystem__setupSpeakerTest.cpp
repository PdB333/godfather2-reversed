// FUNC_NAME: EARS::AudioSystem::setupSpeakerTest
void __thiscall EARS::AudioSystem::setupSpeakerTest(EARS::AudioSystem* this, void* param2, uint32_t* dataArray, int8_t flag, uint32_t value)
{
    uint32_t nodeId;
    uint32_t idx;
    int32_t* nodeArray;
    int32_t* currentNode;
    uint32_t local_14;
    uint32_t local_10[3];

    this->field_0xC = value;                                      // +0x0C
    this->field_0x8 = 1;                                          // +0x08   (bool)
    g_speakerTestFlags = flag;                                    // global byte

    FUN_004d3e20(param2);                                          // init some device

    // Copy 108 bytes from dataArray to offset 0x20
    uint32_t* dest = &this->field_0x20;
    for (int i = 0; i < 27; i++) {
        dest[i] = dataArray[i];
    }

    // Lookup string ID for "SPEAKER_TEST"
    nodeId = FUN_004dafd0("SPEAKER_TEST");                        // string to uint32 hash
    this->speakerTestId = nodeId;                                 // +0x58

    // Overwrite first word of copied data with function pointer
    this->field_0x20 = (uint32_t)&LAB_005ef250;                   // callback or vtable

    this->field_0x88 = (uint32_t)this;                            // +0x88   self pointer

    // Check if audio system is fully initialized
    if (this->audioHandle1 != 0 && this->audioHandle2 != 0) {    // +0x580, +0x56c
        FUN_00c9eac0();                                            // begin audio graph modification

        // Iterate over 5 sound graph groups (each 48 bytes at +0x480)
        int32_t* groupPtr = &this->soundGraphGroups;              // +0x480
        for (local_14 = 5; local_14 > 0; local_14--, groupPtr += 0xC) {
            idx = 0;
            if (groupPtr[1] != 0) {                                // group count
                currentNode = (int32_t*)(*groupPtr + 4);           // pointer to node list
                do {
                    // Check if current node is a Sensor node (type 'Sen0')
                    if (*(int32_t*)(*currentNode + 0x28) == 0x53656e30) {
                        // If index valid and corresponding output socket exists
                        if ((int32_t)idx >= 0 && this->sensorOutputs[idx] != 0) { // +0x42c? Actually used piVar6[-4]= groupPtr[-4] = this+0x? Probably offset 0x???
                            // Use local_10 buffer for output
                            uint32_t sensorId = FUN_00c9cd50(0x53656e30);   // create sensor node
                            FUN_00c9cbe0(this->audioHandle1, sensorId, 0, local_10);  // connect
                            idx = 0;
                            if (this->dacCount != 0) {             // +0x440
                                currentNode = (int32_t*)(*(this->dacListPtr) + 4);  // +0x43c
                                goto checkDac;
                            }
                        }
                        break;
                    }
                    idx++;
                    currentNode += 3;                               // each node info is 12 bytes
                } while (idx < (uint32_t)groupPtr[1]);             // iterate until group count
            }
            // Check for Dac nodes if sensor loop broke early?
            // The original code had a goto inside the if that jumped to a separate loop.
            // To avoid spaghetti, we'll restructure with a similar logic.
            // Actually, the goto leads to LAB_005ef400 which is a while loop.
            // Let's replicate the original control flow more closely.
            // After the sensor loop, it goes to label_005ef444 (end of group iteration).
            // But the sensor loop may jump to checkDac.
            // We'll use a flag to handle this.
            continue; // Placeholder - will restructure below
checkDac:
            // Loop over dac nodes
            while (true) {
                if (*(int32_t*)(*currentNode + 0x28) == 0x44616330) { // 'Dac0'
                    if ((int32_t)idx >= 0 && this->dacOutputs[idx] != 0) { // +0x42c? Actually uses this+0x42c?
                        local_10[0] = FUN_00c9ebd0();               // create dac node
                        FUN_00c9cd40(0, local_10);                  // register dac
                    }
                    break;
                }
                idx++;
                currentNode += 3;
                if (idx >= this->dacCount) break;                   // +0x440
            }
            // End of group iteration
        }
        FUN_00c9eae0();                                             // end audio graph modification
    }

    // Log speaker test info
    int8_t* name = this->speakerName;                              // +0x10
    if (name == 0) {
        name = &DAT_0120546e;                                      // default name string
    }
    if (*(int8_t*)(DAT_0122350c + 0x1744) != 0) {                 // global debug flag
        FUN_005e25f0(DAT_0122350c, &local_14, name, &this->field_0x20, 0xffffffff);
    }
    FUN_005e1fd0();                                                // post-init callback
    FUN_005ef5f0(this, this->field_0xC);                          // continue initialization
}