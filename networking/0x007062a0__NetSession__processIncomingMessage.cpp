// FUNC_NAME: NetSession::processIncomingMessage
char __thiscall NetSession::processIncomingMessage(int *message, uint senderId)
{
    char result;
    uint msgType;

    if (message == nullptr) {
        return '\0';
    }
    msgType = getMessageType(message); // FUN_00704860
    if (msgType < 5) {
        result = handleMessageSmall(msgType, message, senderId); // FUN_007051d0
    }
    else {
        switch(msgType) {
        case 5:
        case 9:
        case 10:
            result = handleMessageA(message, msgType); // FUN_007054d0
            break;
        case 6:
        case 7:
        case 8:
            result = handleMessageB(message, msgType); // FUN_00705590
            break;
        default:
            result = '\0';
            break;
        }
    }
    if (result == '\x01') {
        processPendingEvents(); // FUN_00707ea0
        if (this->pendingObject != nullptr) { // +0xf0
            // Call vtable method at offset 0x174 on message
            (*(void (__thiscall **)(void *))(*message + 0x174))(this->pendingObject);
            if (this->pendingObject != nullptr) {
                char check = isGamePaused((uint *)(this->pendingObject + 0x58)); // FUN_00454430
                if (check == '\0') {
                    triggerDebugAction(); // FUN_00481570
                }
            }
            char soundActive = isSoundActive(); // FUN_00705a70
            if (soundActive != '\0') {
                playSound(0x31, 0); // FUN_0079f100
            }
        }
    }
    return result;
}