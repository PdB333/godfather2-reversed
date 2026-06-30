// FUNC_NAME: LoadManager::processMessages
void __thiscall LoadManager::processMessages(int param_1, int streamId)
{
    int *messageData;
    char isFinished;
    int messageType;
    int result;
    int *somePtr;
    int id;

    // Initialize stream
    setStream(streamId);
    setFormat(streamId, 0x9d5c7200); // set loading format (likely float/int)
    isFinished = isStreamFinished();
    while (isFinished == 0) {
        messageData = getNextData(); // pointer to next data block
        messageType = getMessageType();
        switch (messageType) {
        case 0:
            // Check if any flags at offsets 0x58, 0x5c, 0x60, 0x64 are set
            somePtr = (int *)(param_1 + 0x58);
            if (((*somePtr != 0) || (*(int *)(param_1 + 0x5c) != 0)) || 
                (*(int *)(param_1 + 0x60) != 0) || (*(int *)(param_1 + 0x64) != 0)) {
                id = findObject(somePtr, 0);
                if (id != 0) {
                    result = lookupById(id, 0x383225a1); // some ID hash
                    activateState(result);
                }
            }
            // Check additional flag at offset 0x68
            if ((*(int *)(param_1 + 0x68) == 0) || (*(int *)(param_1 + 0x68) == 0x48)) {
                if (*(int *)(*(int *)(globalPtr + 4)) == 0) {
                    activateState(0);
                } else {
                    activateState(*(int *)(*(int *)(globalPtr + 4)) + -0x1f30);
                }
            }
            break;
        case 1:
            *(int *)(param_1 + 0x84) = *(int *)(messageData + 8);
            break;
        case 2:
            *(int *)(param_1 + 0x88) = *(int *)(messageData + 8);
            break;
        case 3:
            *(int *)(param_1 + 0x8c) = *(int *)(messageData + 8);
            break;
        case 4:
            *(int *)(param_1 + 0x90) = *(int *)(messageData + 8);
            break;
        case 5:
            *(int *)(param_1 + 0x94) = *(int *)(messageData + 8);
            break;
        case 6:
            *(int *)(param_1 + 0x98) = *(int *)(messageData + 8);
            break;
        case 7:
            *(int *)(param_1 + 0x9c) = *(int *)(messageData + 8);
            break;
        case 8:
            *(int *)(param_1 + 0xa0) = *(int *)(messageData + 8);
            break;
        case 9:
            *(int *)(param_1 + 0xa4) = *(int *)(messageData + 8);
            break;
        case 10:
            *(int *)(param_1 + 0xa8) = *(int *)(messageData + 8);
            break;
        case 11:
            *(int *)(param_1 + 0xac) = *(int *)(messageData + 8);
            break;
        case 12:
            *(int *)(param_1 + 0xb0) = *(int *)(messageData + 8);
            break;
        case 13:
            *(int *)(param_1 + 0xb4) = *(int *)(messageData + 8);
            break;
        case 14:
            // Mask with global value DAT_00e44680
            *(uint *)(param_1 + 0xb8) = *(uint *)(messageData + 8) & 0x00e44680;
            break;
        case 15:
            *(int *)(param_1 + 0xbc) = *(int *)(messageData + 8);
            break;
        case 16:
            *(int *)(param_1 + 0xc0) = *(int *)(messageData + 8);
            break;
        case 17:
            *(int *)(param_1 + 0xc4) = *(int *)(messageData + 8);
            break;
        case 18:
            *(int *)(param_1 + 0xc8) = *(int *)(messageData + 8);
            break;
        case 19:
            *(int *)(param_1 + 0xcc) = *(int *)(messageData + 8);
            break;
        case 20:
            *(int *)(param_1 + 0xd0) = *(int *)(messageData + 8);
            break;
        case 21:
            *(int *)(param_1 + 0xd4) = *(int *)(messageData + 8);
            break;
        case 22:
            *(int *)(param_1 + 0xd8) = *(int *)(messageData + 8);
            break;
        case 23:
            *(int *)(param_1 + 0xdc) = *(int *)(messageData + 8);
            break;
        case 24:
            *(int *)(param_1 + 0xe0) = *(int *)(messageData + 8);
            break;
        case 25:
            *(int *)(param_1 + 0xe4) = *(int *)(messageData + 8);
            break;
        case 26:
            *(int *)(param_1 + 0xe8) = *(int *)(messageData + 8);
            break;
        case 27:
            *(int *)(param_1 + 0xec) = *(int *)(messageData + 8);
            break;
        case 28:
            *(int *)(param_1 + 0xf0) = *(int *)(messageData + 8);
            break;
        case 29:
            *(int *)(param_1 + 0x100) = *(int *)(messageData + 8);
            break;
        case 30:
            *(int *)(param_1 + 0x104) = *(int *)(messageData + 8);
            break;
        case 31:
            *(int *)(param_1 + 0x108) = *(int *)(messageData + 8);
            break;
        case 32:
            *(int *)(param_1 + 0x10c) = *(int *)(messageData + 8);
            break;
        case 33:
            *(int *)(param_1 + 0x110) = *(int *)(messageData + 8);
            break;
        case 34:
            *(int *)(param_1 + 0x114) = *(int *)(messageData + 8);
            break;
        case 35:
            *(int *)(param_1 + 0x118) = *(int *)(messageData + 8);
            break;
        case 36:
            *(int *)(param_1 + 0x11c) = *(int *)(messageData + 8);
            break;
        case 37:
            *(int *)(param_1 + 0x120) = *(int *)(messageData + 8);
            break;
        case 38:
            *(int *)(param_1 + 0x124) = *(int *)(messageData + 8);
            break;
        case 39:
            *(int *)(param_1 + 0xf4) = *(int *)(messageData + 8);
            break;
        case 40:
            *(int *)(param_1 + 0xf8) = *(int *)(messageData + 8);
            break;
        case 41:
            *(int *)(param_1 + 0xfc) = *(int *)(messageData + 8);
            break;
        }
        advanceStream();
        isFinished = isStreamFinished();
    }
}