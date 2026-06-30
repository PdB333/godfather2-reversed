// FUNC_NAME: AudioManager::processSilentCommand
// Address: 0x005e9220
// Role: Handles "silent" command for audio system, stores event data in circular buffer

int __thiscall AudioManager::processSilentCommand(AudioManager* this, const char* command, int data, int param4)
{
    int* entry;
    int i;
    int cmpResult;
    bool less, equal;
    float value;

    // Check current audio state (offset 0x484 = this->audioState)
    if ((this->audioState > 0) && ((this->audioState < 3) || (this->audioState == 4))) {
        FUN_005e9440(); // Reset or handle state transition
    }

    if (command != nullptr) {
        // Compare command to "silent" string
        cmpResult = 0;
        less = false;
        equal = true;
        const char* pCmd = command;
        const char* pSilent = "silent";
        do {
            if (cmpResult == 7) break; // max 7 chars (including null?)
            cmpResult++;
            less = *pCmd < *pSilent;
            equal = *pCmd == *pSilent;
            pCmd++;
            pSilent++;
        } while (equal);

        if (!equal) {
            // Compute comparison result (1 if command > "silent", -1 if less)
            cmpResult = (1 - (uint)less) - (uint)(less != 0);
        }

        if (cmpResult == 0) { // command equals "silent"
            // Circular buffer of 4 entries (each 0x1b ints = 108 bytes)
            int index = this->bufferIndex; // this[0] is the index
            this->bufferIndex = index + 1;
            if (this->bufferIndex > 3) {
                this->bufferIndex = 0;
            }
            entry = &this->buffer[index * 0x1b]; // this + 1 + index*0x1b

            // Copy data from source (param3)
            entry[0x15] = *(int*)(data + 0x48); // float value? offset 0x48
            entry[0x16] = *(int*)(data + 0x30); // int at offset 0x30
            entry[0x17] = *(int*)(data + 0x34); // int at offset 0x34
            entry[0x14] = (uint)(*(char*)(data + 4) == '\0'); // bool: isNull?

            FUN_004d3d90(command); // Likely string copy or logging

            // Clamp value to [0.0, DAT_00e2b1a4]
            value = (float)entry[0x15];
            if (DAT_00e2b1a4 < value) {
                entry[0x15] = (int)DAT_00e2b1a4;
            } else if (value < 0.0f) {
                entry[0x15] = 0;
            }

            FUN_005e9380(entry, data, param4); // Process the stored entry
            FUN_005e86e0(); // Update audio system
            return 1;
        }
    }

    // Reset silent flags (offsets 0x1FC and 0x200)
    this->silentFlag1 = 0;
    this->silentFlag2 = 0;
    FUN_005e86e0();
    return 1;
}