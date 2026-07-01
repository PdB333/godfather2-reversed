// FUNC_NAME: MessageRouter::routeFormattedMessage
void MessageRouter::routeFormattedMessage(uint32_t id, uint32_t param2, uint32_t param3) {
    // Temporary buffer structure: holds formatted string, status, and callback
    struct {
        int status;          // +0x00
        int reserved1;       // +0x04
        int reserved2;       // +0x08
        void (*callback)(int); // +0x0C
    } msgContext;

    // Format the ID into a string like "{#1234}"
    // FUN_004d4a60 is likely a string format helper (e.g., snprintf with size=1? but used as buffer init)
    stringFormat((char*)&msgContext, 1, "{#%u}", id);

    // Route the formatted message with two extra parameters
    // FUN_008c0f50 processes the message and may set msgContext.status and msgContext.callback
    routeMessage(&msgContext, param2, param3);

    // If the routing returned a non-zero status, invoke the callback
    if (msgContext.status != 0) {
        msgContext.callback(msgContext.status);
    }
}