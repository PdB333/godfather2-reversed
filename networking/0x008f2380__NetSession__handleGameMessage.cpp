// FUNC_NAME: NetSession::handleGameMessage

int NetSession::handleGameMessage(int *messageData, int messageSize, int *outType) {
    *outType = 6; // Default type
    if (messageData == nullptr || messageSize != 0x114) {
        return 0;
    }
    *outType = *messageData; // Actual message type from header
    if (*messageData == 6 && messageData[2] == 0x40000 && (uint)messageData[3] < 0x40001) {
        // Validate payload (skipping 4 integer header)
        if (FUN_00565530(messageData + 4) != 0) {
            return 1; // Validation passed, handled
        }
        // Call virtual function for further processing (likely a callback on validated packet)
        (*(void (*)())(*(int *)this + 0x3c))();
    }
    return 0;
}