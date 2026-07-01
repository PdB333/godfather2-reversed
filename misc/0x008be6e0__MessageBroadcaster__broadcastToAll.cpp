// FUNC_NAME: MessageBroadcaster::broadcastToAll
// Function address: 0x008be6e0
// Role: Iterates over a list of object pointers and calls a dispatch function with a stored message type byte.
// Offsets:
//   +0x0c: messageType (byte) - type of message to broadcast
//   +0x10: objectArray (int**) - pointer to array of object pointers
//   +0x14: objectCount (uint) - number of entries in array

// External dispatch function (likely sends a message to a specific object)
void sendMessageToObject(void* object, byte messageType);

void MessageBroadcaster::broadcastToAll()
{
    uint i = 0;
    if (this->objectCount != 0) {
        do {
            sendMessageToObject(this->objectArray[i], this->messageType);
            i = i + 1;
        } while (i < this->objectCount);
    }
    return;
}