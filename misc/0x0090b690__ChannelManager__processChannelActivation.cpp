// FUNC_NAME: ChannelManager::processChannelActivation
// Address: 0x0090b690
void __thiscall ChannelManager::processChannelActivation(uint channelId) {
    uint* firstEntry;
    bool isReady;
    uint* currentEntry;
    uint nextStage;
    int index;

    // Check if the channel is already in a ready state
    isReady = this->isChannelReady(channelId);
    if (!isReady) {
        firstEntry = (uint*)(this + 0x18); // +0x18: Array of 7 channel entries (each 0x24 bytes)
        index = 0;
        currentEntry = firstEntry;
        do {
            // Look for an entry matching the channel ID and where bit 1 of flags is clear
            if ((currentEntry[1] == channelId) && ((*currentEntry >> 1 & 1) == 0)) {
                isReady = false;
                while (true) {
                    if (isReady) {
                        return;
                    }
                    index = *(int*)(this + 0x14); // +0x14: Current activation stage (0-8)
                    nextStage = index + 1;
                    if (nextStage > 8) {
                        break; // Invalid stage, abort
                    }
                    *(uint*)(this + 0x14) = nextStage; // Advance to next stage
                    switch (index) {
                    case 7:
                        *(uint*)(this + 0xf0) |= 1; // +0xf0: Stage 7 flag
                    case 6:
                        *(uint*)(this + 0xcc) |= 1; // +0xcc: Stage 6 flag
                    case 4:
                    case 5:
                        *(uint*)(this + 0x84) |= 1; // +0x84: Stage 4/5 flag
                    case 3:
                        *(uint*)(this + 0xa8) |= 1; // +0xa8: Stage 3 flag
                    case 2:
                        *(uint*)(this + 0x60) |= 1; // +0x60: Stage 2 flag
                    case 1:
                        *(uint*)(this + 0x3c) |= 1; // +0x3c: Stage 1 flag
                    case 0:
                        *firstEntry |= 1; // +0x18: Set bit 0 of first entry in the array
                    default:
                        isReady = this->isChannelReady(channelId);
                    }
                }
                return;
            }
            index++;
            currentEntry += 9; // Move to next entry (9 * 4 = 0x24 bytes)
        } while (index < 7);
    }
    return;
}