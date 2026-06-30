// FUNC_NAME: TNLConnection::establishConnection
// Address: 0x006696f0
// Role: Initializes and performs the connection handshake loop, allocating a packet window and sending/receiving handshake packets.

int TNLConnection::establishConnection(int socketHandle, ConnectionParameters *params, int *result)
{
    int ret;
    int count;
    int step;
    int advanceResult;
    int packetResult;
    int extraout_ECX; // decompiler artifact for loop increment
    void *packetWindow;
    int windowDescriptor[3]; // actually a struct: flags, size, etc.
    char handshakeData[16];
    char packetBuffer[16];

    *result = 0;

    // Check if connection parameters are valid
    if ((params->mode == 1) || ((params->version < 2 && (*(uint *)params->bufferSizePtr < 2)))) {
        return -3;
    }

    // Allocate 256-byte packet window buffer
    packetWindow = calloc(4, 0x40);
    if (packetWindow == NULL) {
        return -2;
    }

    // Set up window descriptor
    windowDescriptor[0] = 0; // flags
    windowDescriptor[1] = 0x40; // size
    windowDescriptor[2] = 0; // offset

    // Initialize the connection system
    ret = SystemStart();
    if (ret != 0) {
        return ret;
    }

    // Initialize packet window
    ret = WindowInitialize(&windowDescriptor, 1, &windowDescriptor);
    if (ret != 0) {
        goto cleanup;
    }

    // Begin handshake setup
    ret = HandshakeBegin();
    if (ret != 0) {
        goto cleanup;
    }

    // Get number of handshake steps
    count = GetHandshakeSteps();

    // Generate handshake data (e.g., random nonce)
    ret = GenerateHandshakeData(handshakeData, count, handshakeData, 0);
    if (ret == 0) {
        // Continue handshake processing
        ret = HandshakeContinue();
        if (ret == 0) {
            // Build and process the initial connection packet
            ret = BuildConnectionPacket(params, handshakeData, socketHandle, packetBuffer);
            if (ret == 0) {
                // Check if connection is alive
                step = IsConnectionAlive();
                if ((step != 0) && (step = AdvanceHandshakeState(), step != 0)) {
                    // Loop through handshake steps
                    step = 1;
                    if (count > 1) {
                        do {
                            advanceResult = AdvanceHandshakeState();
                            if (advanceResult == 0) break;

                            packetResult = WindowAddPacket(packetBuffer, socketHandle, packetBuffer);
                            if ((packetResult != 0) || (advanceResult = IsConnectionAlive(), advanceResult == 0)) {
                                goto cleanupAndSetResult;
                            }
                            step = step + 1; // corrected increment
                        } while (step <= count - 1);
                    }

                    // Final handshake step check
                    advanceResult = AdvanceHandshakeState();
                    if (advanceResult != 0) {
                        goto cleanupAndSetResult;
                    }
                }
                *result = 1; // success
            }
        }
    }

cleanupAndSetResult:
    // Cleanup connection resources
    SystemStop();

cleanup:
    SystemStop(); // final cleanup
    return ret;
}