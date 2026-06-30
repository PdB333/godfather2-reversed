// FUNC_NAME: NetSession::processMessage
void __thiscall NetSession::processMessage(int* message) {
    int subMessagePtr;
    int subType;

    // Check if message type matches expected type
    if (*message == this->expectedType) {
        // Check flags and state conditions
        if (((((((this->flags & 2) != 0) && (subMessagePtr = message[1], subMessagePtr != 0)) &&
              (this->ptr1 == 0)) &&
             ((this->ptr2 == 0 && (this->ptr3 == 0)))) &&
            ((this->ptr4 == 0 &&
             ((this->state == -1 && (*(int*)(subMessagePtr + 4) != 0)))))) &&
           (*(int*)(subMessagePtr + 4) != 0x48)) {
            // Compute sub-type offset
            if (*(int*)(subMessagePtr + 4) == 0) {
                subType = 0;
            } else {
                subType = *(int*)(subMessagePtr + 4) - 0x48;
            }
            // Process the sub-message
            processSubMessage(subType);
        }
        // Update internal state
        updateState();
    }
    // Free the message structure
    freeMessage(message);
}