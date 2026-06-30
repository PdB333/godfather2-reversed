// FUNC_NAME: MessageRouter::routeMessage

struct MessageStruct {
    int type;   // +0x00
    int data;   // +0x04
    int flags;  // +0x08
};

// Global table of message handler functions
typedef void (*MessageHandler)(void* obj, MessageStruct* msg);

// Internal: returns pointer to first handler (index 0) in global table
extern MessageHandler* getGlobalMessageTable();

void MessageRouter::routeMessage(void* thisPtr, int msgData)
{
    // Fetch the global message handler table (first handler at index 0)
    MessageHandler* handlerTable = getGlobalMessageTable();

    // Build a message structure on the stack
    MessageStruct msg;
    msg.type  = 2;          // message opcode (e.g., "apply impulse", "set state")
    msg.data  = msgData;    // payload passed by caller
    msg.flags = 0;          // unused / reserved

    // Dispatch the message to the registered handler
    handlerTable[0](thisPtr, &msg);
}