// FUNC_NAME: MessageHandler::processMessage
// Address: 0x008948a0
// This function dispatches incoming messages based on type byte at offset +2 of the message structure.
// The message struct is passed as the first parameter (this), with additional data in param2.

struct Message {
    /* +0x00 */ uint8_t padding[2];
    /* +0x02 */ uint8_t type;          // Message type (0-0x21)
    /* +0x03 */ uint8_t flags;         // Bit flags (lower 2 bits used as sub-type)
    /* +0x04 */ void* data;            // Pointer to associated data/object
    /* +0x08 */ uint32_t paramA;       // Parameter A
    /* +0x0C */ uint32_t paramB;       // Parameter B
};

// Forward declarations of helper functions (names inferred)
bool stringToInteger(const char* str, int* outValue);               // 0x00408240
void formatString(int* buffer, const char* str, ...);              // 0x00440590
void freeString(int* buffer);                                       // 0x00408310
void destroyObject(void* object);                                   // 0x00894c90
void setObjectProperty(void* object, uint32_t value);               // 0x008938f0
uint32_t getObjectId(uint32_t objectHandle);                        // 0x00893410
bool sendMessage(uint32_t targetAddress, uint32_t sender, uint32_t param, uint32_t msgType, uint8_t subType, uint32_t extra); // 0x00893e70
void sendStaticMessage(uint8_t msgType, Message* msg, uint32_t param, uint32_t flag); // 0x00894280
void sendTargetedMessage(uint8_t msgType, Message* msg, uint32_t param, uint32_t flag); // 0x00894560
void sendDirectedMessage(uint8_t msgType, Message* msg, uint32_t param, uint32_t flag); // 0x008945d0
bool lookupObject(uint32_t id, uint32_t* outAddress);              // 0x008936b0
void enableObject(void* object);                                    // 0x008ddca0
void disableObject(void* object);                                   // 0x008ddcf0
void handleSendQueued(uint8_t msgType, Message* msg, uint32_t param); // 0x00894410

bool __fastcall MessageHandler::processMessage(Message* msg, uint32_t param2)
{
    bool handled = true; // Default to true for known types, except default fallthrough
    uint32_t sender = param2; // param2 is likely a sender reference

    switch (msg->type)
    {
    case 1: // String message with data
    {
        char* str = (char*)msg->data;
        if (str && *str != '\0')
        {
            int buffer[4]; // local_8, local_4, local_2
            buffer[0] = 0; // size
            buffer[1] = 0;
            buffer[2] = 0;
            stringToInteger(buffer, str);
            formatString(buffer, 0, msg->paramA, 0, 0);
            freeString(buffer);
            return true;
        }
        break;
    }
    case 2: // Destroy object
    {
        if (msg->data)
        {
            destroyObject(msg->data);
            return true;
        }
        break;
    }
    case 3: // Set property on object
    {
        if (msg->data)
        {
            setObjectProperty(msg->data, param2);
            return true;
        }
        break;
    }
    case 4: // Toggle flag on object
    {
        uint32_t objectHandle = getObjectId((uint32_t)msg->data);
        if (objectHandle != 0)
        {
            if (msg->paramA & 1)
            {
                *(uint32_t*)(objectHandle + 4) |= 2;
            }
            else
            {
                *(uint32_t*)(objectHandle + 4) &= ~2;
            }
            return true;
        }
        break;
    }
    case 5:
    case 6:
    case 7:
    {
        uint8_t subType = msg->flags & 3;
        uint32_t msgTypeID = getObjectId(msg->type);
        sendMessage(msg->paramA, (uint32_t)msg->data, param2, msgTypeID, subType, 0);
        return true;
    }
    case 8:
    case 9:
    {
        sendStaticMessage(msg->type, msg, param2, 0);
        return true;
    }
    case 10:
    case 11:
    case 12:
    {
        sendTargetedMessage(msg->type, msg, param2, 0);
        return true;
    }
    case 13:
    case 14:
    {
        sendDirectedMessage(msg->type, msg, param2, 0);
        return true;
    }
    case 15:
    case 16:
    case 17:
    {
        uint32_t targetAddr = 0;
        uint32_t originalSender = msg->paramB; // from +0xC
        bool res1 = sendMessage(&targetAddr, originalSender, param2, 1, 1, 0);
        if (res1)
        {
            uint32_t outAddr = 0;
            bool res2 = lookupObject(msg->paramA, &outAddr);
            if (res2)
            {
                uint8_t subType = msg->flags & 3;
                uint32_t msgTypeID = getObjectId(msg->type);
                sendMessage(&outAddr, (uint32_t)msg->data, sender, msgTypeID, subType, 0);
                return true;
            }
        }
        break;
    }
    case 18:
    case 19:
    case 20:
    {
        uint8_t subType = msg->flags & 3;
        uint32_t msgTypeID = getObjectId(msg->type);
        sendMessage(msg->paramA, (uint32_t)msg->data, param2, msgTypeID, subType, msg->paramB);
        return true;
    }
    case 21:
    case 22:
    {
        sendStaticMessage(msg->type, msg, param2, 1);
        return true;
    }
    case 23:
    case 24:
    case 25:
    {
        sendTargetedMessage(msg->type, msg, param2, 1);
        return true;
    }
    case 26:
    case 27:
    {
        sendDirectedMessage(msg->type, msg, param2, 1);
        return true;
    }
    case 28:
    case 31:
    case 32:
    {
        // No action, returns true via handled = true
        break;
    }
    case 29:
    {
        enableObject(msg->data);
        return true;
    }
    case 30:
    {
        disableObject(msg->data);
        return true;
    }
    case 33:
    {
        handleSendQueued(0x21, msg, param2);
        return true;
    }
    default:
        handled = false;
        break;
    }

    return handled;
}