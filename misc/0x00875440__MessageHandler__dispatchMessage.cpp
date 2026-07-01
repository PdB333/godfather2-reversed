// FUNC_NAME: MessageHandler::dispatchMessage
int __thiscall MessageHandler::dispatchMessage(uint* messageType, int messageData) {
    uint type = *messageType;
    int result = 0;
    // Range [6,9] inclusive
    if ((type > 5) && (type < 10)) {
        if ((type != 6) && (type != 8)) {
            // Call virtual function at vtable offset 0x1d4 (used for types 7 and 9)
            ((void (__thiscall *)(MessageHandler*, uint*, int))(*(int**)this)[0x1d4 / 4])(this, messageType, messageData);
            return 1;
        }
        // Types 6 and 8 call virtual function at vtable offset 0x1d0
        ((void (__thiscall *)(MessageHandler*, uint*, int))(*(int**)this)[0x1d0 / 4])(this, messageType, messageData);
        result = 1;
    }
    return result;
}