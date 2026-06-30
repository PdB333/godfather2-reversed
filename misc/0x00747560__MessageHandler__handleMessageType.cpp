// FUNC_NAME: MessageHandler::handleMessageType
// Address: 0x00747560
// This function decodes a type identifier from a message buffer (pMessage).
// Based on the type, it either initializes a sub-object (this+0x60) and sets message fields,
// or performs cleanup logic (this+0x54) and resets the system.

enum EMessageType : unsigned int {
    kMsgType_Init    = 0x1b2d5c51,
    kMsgType_Cleanup = 0x485311a7
};

void __thiscall MessageHandler::handleMessageType(void* thisPtr, unsigned int* pMessage)
{
    // The message object's first vtable entry returns a type hash
    int typeHash = (*(int (**)())(*pMessage))();

    if (typeHash == kMsgType_Init)
    {
        // Initialize subcomponent at offset 0x60
        FUN_00755a10(reinterpret_cast<int>(thisPtr) + 0x60);

        // Populate message fields: global constant and completion flag
        pMessage[0x18] = DAT_00d64028;   // +0x60: some global value
        pMessage[0x1f] = 1;              // +0x7C: processing marker
    }
    else if (typeHash == kMsgType_Cleanup)
    {
        // Dereference member at +0x54, if non-zero adjust by -0x48
        int somePtr = *reinterpret_cast<int*>(reinterpret_cast<int>(thisPtr) + 0x54);
        int adjustedPtr = (somePtr != 0) ? (somePtr - 0x48) : 0;
        FUN_0075b920(adjustedPtr);
        FUN_0075b520(0);
        return;
    }
    // Unknown type: no action
    return;
}