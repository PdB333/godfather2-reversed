// FUNC_NAME: NetConnection::sendPacketWithRetry
// Address: 0x00669c80
// Role: Sends a packet with retry logic, using a packet builder from a dispatch table.
// The function allocates a buffer, calls a packet builder function (indexed by param_4+4),
// validates the packet, and attempts to send it. Retries until success or failure.

#include <cstdlib> // for malloc, free

// Forward declarations of helper functions
int validatePacket(char* buffer); // FUN_0066a010
int transmitPacket(int param1, int param2, int* outPending); // FUN_00669570

// Dispatch table for packet builders (each entry 0x14 bytes)
// DAT_01206418
extern void* g_packetBuilderTable[];

// Function: sendPacketWithRetry
// Parameters:
//   param_1 - Connection or session handle
//   param_2 - Additional data (e.g., destination address)
//   param_3 - Flag: non-zero for reliable delivery
//   param_4 - Packet descriptor (offset +4 contains builder index)
//   packetSize - Size of the packet payload (passed in EDI register)
// Returns: 0 on success, negative error code on failure
int NetConnection::sendPacketWithRetry(int param_1, int param_2, int param_3, int param_4, int packetSize) {
    if (packetSize < 1) {
        return -3; // Invalid size
    }

    char* buffer = (char*)malloc(packetSize + 1);
    if (buffer == nullptr) {
        return -2; // Allocation failed
    }

    buffer[0] = 1; // Packet type marker (e.g., sequence number or protocol version)

    int result;
    while (true) {
        // Retrieve the packet builder function from the dispatch table
        // param_4+4 holds an index into the table (each entry 0x14 bytes)
        int builderIndex = *(int*)(param_4 + 4);
        int (*buildPacket)(char*) = (int (*)(char*))(&g_packetBuilderTable[builderIndex * 0x14]);

        // Call the builder to fill the buffer (starting at offset 1)
        int written = buildPacket(buffer + 1);
        if (written != packetSize) {
            free(buffer);
            return -3; // Builder wrote incorrect amount of data
        }

        // Set flags in the last byte of the buffer
        // If param_3 is non-zero (reliable), OR with 3; otherwise OR with 1
        buffer[packetSize] = buffer[packetSize] | ((param_3 != 0) ? 3 : 1);

        // Validate the packet (e.g., checksum or integrity check)
        result = validatePacket(buffer);
        if (result != 0) {
            break; // Validation succeeded (or returned a non-zero result)
        }

        // Attempt to send the packet
        int pending;
        int sendResult = transmitPacket(param_1, param_2, &pending);
        if (sendResult != 0 || pending != 0) {
            result = sendResult;
            break; // Send completed or pending data remains
        }
        // Otherwise, retry the loop
    }

    free(buffer);
    return result;
}