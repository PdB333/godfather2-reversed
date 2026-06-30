// FUNC_NAME: NetConnection::processMessage
// Function at 0x00626180: Processes a message from the incoming packet buffer.
// Returns 1 if a message of type 6 was successfully read, 0 otherwise.
// The buffer pointer at this+0x8 is decremented by 8 (message header size) and the header is examined.
// If the message type is 6 and a flag at data+0x6 is zero, two DWORDs are copied from the buffer to data+0x10 and data+0x14.

#include <cstdint>

// Forward declaration of the helper function that retrieves the next message header.
// Returns a pointer to a structure containing message type and data pointer.
struct MessageHeader* getNextMessageHeader(void);

// Structure for the message header returned by getNextMessageHeader.
struct MessageHeader {
    int32_t type;       // +0x00: message type identifier
    void* data;         // +0x04: pointer to message-specific data
};

// Structure for the data of message type 6.
struct MessageType6Data {
    uint8_t unknown[6]; // +0x00..0x05: unknown fields
    uint8_t flag;       // +0x06: flag byte (must be zero to process)
    uint8_t pad[9];     // +0x07..0x0F: padding
    uint32_t value1;    // +0x10: first copied value
    uint32_t value2;    // +0x14: second copied value
};

class NetConnection {
public:
    // Buffer pointer for incoming packet data. Points to the current read position.
    // The buffer is managed externally; this pointer is decremented by 8 before reading a message header.
    uint32_t* bufferPtr; // +0x08

    // Process the next message from the buffer.
    // Returns 1 on success (message type 6 processed), 0 otherwise.
    int32_t __thiscall processMessage(void) {
        MessageHeader* header = getNextMessageHeader();
        // Decrement buffer pointer by 8 (size of a message header?).
        bufferPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(bufferPtr) - 8);
        uint32_t* messageData = bufferPtr; // Pointer to the message data after header.

        // Check if the message type is 6 and the flag at data+0x6 is zero.
        if (header->type == 6) {
            MessageType6Data* msgData = static_cast<MessageType6Data*>(header->data);
            if (msgData->flag == 0) {
                // Copy two DWORDs from the buffer into the message data structure.
                msgData->value1 = messageData[0];
                msgData->value2 = messageData[1];
                return 1;
            }
        }
        return 0;
    }
};