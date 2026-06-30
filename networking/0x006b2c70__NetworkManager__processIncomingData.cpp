// FUNC_NAME: NetworkManager::processIncomingData
int __fastcall NetworkManager::processIncomingData(int thisPtr)
{
    int result;
    uint8_t buffer[68]; // +0x44 bytes

    // Enable or set mode on a sub-object at offset 0x40 (likely a buffer or state pointer)
    enableSubsystem(*(uint32_t*)(thisPtr + 0x40), 2);

    // Attempt to read or parse incoming data into the local buffer
    result = readNetworkMessage(buffer);

    if (result != 0) {
        // Notify that a packet was received (argument 1 may indicate success/type)
        notifyPacketReceived(1);

        // Process the received data using this object
        handleParsedData(thisPtr);
    }

    // Cleanup or disable the subsystem
    disableSubsystem();

    return result;
}