// FUNC_NAME: TNLConnection::sendReliableStream
// Address: 0x00669c80
// Reconstructed C++ for The Godfather 2 (EA EARS engine) network layer.
// This function builds and sends a reliable packet with a payload from a stream handler.

int TNLConnection::sendReliableStream(undefined4 this_ptr, undefined4 seqNum, int needAck, void* streamDescriptor)
{
    // unaff_EDI likely holds mPayloadSize (member variable from this object) passed in EDI
    int payloadSize = unaff_EDI; // guess: size of packet payload
    if (payloadSize < 1) {
        return -3;
    }

    unsigned char* buffer = (unsigned char*)_malloc(payloadSize + 1);
    if (buffer == nullptr) {
        return -2;
    }

    // First byte is command/type identifier (1 = reliable?)
    buffer[0] = 1;

    while (true) {
        // Use stream handler to read payload into buffer+1.
        // Stream table at DAT_01206418, entries of 20 bytes each.
        // Index = streamDescriptor->streamIndex (offset +0x04)
        int streamIdx = *(int*)((char*)streamDescriptor + 4);
        int (*readStreamFunc)(unsigned char*) = (int (*)(unsigned char*))DAT_01206418[streamIdx * 0x14];
        int bytesRead = readStreamFunc(buffer + 1);
        if (bytesRead != payloadSize) {
            _free(buffer);
            return -3;
        }

        // Set flags at end: if needAck, set bit 1 (value 3), else value 1.
        buffer[payloadSize] = buffer[payloadSize] | (needAck ? 2 : 0) + 1;

        // Validate/checksum the buffer (likely CRC or signature check)
        int validateResult = FUN_0066a010(buffer);
        if (validateResult != 0) break; // validation succeeded, exit loop

        // Send the packet; if function returns non-zero or pending flag set, break
        int sendStatus;
        int sendResult = FUN_00669570(this_ptr, seqNum, &sendStatus);
        if (sendResult != 0 || sendStatus != 0) break;
    }

    _free(buffer);
    return validateResult; // note: iVar1 holds the last returned value from validate or send
}