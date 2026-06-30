// FUNC_NAME: TNLConnection::storeReliablePacketSequence
// Function address: 0x00633f00
// Role: Validates packet types (5/7) against connection state (6) and stores 8 bytes from input buffer into sequence history at index param_4.

#include <cstdint>

// Forward declaration of singleton getter
int* getConnectionState(); // FUN_00637f90

// Forward declaration of main processing function
void processReliablePacket(int thisPtr, int* state, int* type1, int* type2); // FUN_00633ac0

int TNLConnection::storeReliablePacketSequence(int thisPtr, int* packetType1, int* packetType2, int sequenceIndex)
{
    int previousIndex = *(int *)(thisPtr + 0x1c); // +0x1c: base index into sequence history
    int* statePtr;

    // Check if first packet type is 5 (Reliable) or 7 (ReliableOrdered) and state is valid
    if ((*packetType1 != 5 && *packetType1 != 7) || (statePtr = getConnectionState(), *statePtr == 0))
    {
        // Fallback: check second packet type
        if (*packetType2 != 5 && *packetType2 != 7)
        {
            return 0;
        }
        statePtr = getConnectionState();
    }

    // Connection must be in state 6 (connected)
    if (*statePtr != 6)
    {
        return 0;
    }

    // Process the reliable packet
    processReliablePacket(thisPtr, statePtr, packetType1, packetType2);

    // Copy 8 bytes from input buffer into sequence history at computed offset
    uint32_t* srcBuffer = *(uint32_t **)(thisPtr + 0x8); // +0x8: pointer to input data buffer
    uint32_t* dstBuffer = (uint32_t *)(*(int *)(thisPtr + 0x1c) + (sequenceIndex - previousIndex)); // +0x1c: base of sequence history array
    dstBuffer[0] = srcBuffer[0];
    dstBuffer[1] = srcBuffer[1];

    return 1;
}