// FUNC_NAME: MessageStream::processMessages

void MessageStream::processMessages()
{
    // This function processes a stream of messages from a buffer.
    // The buffer is stored at this+0x20 (remaining size) and this+0x24 (current read pointer).
    // Each message has a 12-byte header:
    //   [4 bytes: type ID] [4 bytes: unknown] [4 bytes: payload size]
    // Payload follows, aligned to 4 bytes.

    bool keepProcessing = true; // local_15, default true

    do {
        uint32_t remainingSize = *(uint32_t *)(this + 0x20); // uVar5

        if (remainingSize == 0) {
            // Buffer exhausted
            *(uint32_t *)(this + 0x20) = 0;
            *(uint32_t *)(this + 0x24) = 0;
            context.reset(this + 0x28);      // FUN_004086d0 - likely flush the context
            context.clear(this + 0x28);      // FUN_00408310 - clear context
            if (*(void **)(this + 0x30) != nullptr) {
                // Send the fallback message (first dword of the pointed-to message)
                uint32_t fallbackType = **(uint32_t **)(this + 0x30);
                sendMessage(&fallbackType, 0); // FUN_00408a00
            }
            return;
        }

        if (remainingSize < 13) { // Not enough data for a full header (12 bytes + at least 1 byte payload?)
            // Incomplete message, treat same as empty buffer
            *(uint32_t *)(this + 0x20) = 0;
            *(uint32_t *)(this + 0x24) = 0;
            context.reset(this + 0x28);
            context.clear(this + 0x28);
            if (*(void **)(this + 0x30) != nullptr) {
                uint32_t fallbackType = **(uint32_t **)(this + 0x30);
                sendMessage(&fallbackType, 0);
            }
            return;
        }

        // Read message header (12 bytes)
        uint32_t *header = *(uint32_t **)(this + 0x24); // puVar2
        uint32_t messageType = header[0];               // uVar4
        // header[1] is unknown (skipped)
        int32_t payloadSize = header[2];                // iVar3

        // Advance read pointer past the header (3 dwords = 12 bytes)
        uint32_t *newReadPtr = header + 3;              // puVar1
        *(uint32_t **)(this + 0x24) = newReadPtr;
        remainingSize -= 12;
        *(uint32_t *)(this + 0x20) = remainingSize;

        // Align payload size to 4 bytes
        uint32_t alignedSize = (payloadSize + 3) & 0xFFFFFFFC; // uVar7

        if (remainingSize < alignedSize) {
            // Not enough data for the payload, handle error
            handleMessageError(); // FUN_004c0b40
            return;
        }

        // Advance read pointer past the payload
        uint32_t *payload = newReadPtr;                      // puVar1 points to start of payload
        *(uint32_t **)(this + 0x24) = (uint32_t *)((uint32_t)newReadPtr + alignedSize);
        *(uint32_t *)(this + 0x20) = remainingSize - alignedSize;

        // Look up the message type to get its mask and associated object
        uint32_t messageMask; // local_10
        int *messageObject = (int *)getMessageTypeMask(messageType, &messageMask); // FUN_00463a80

        if (messageObject != nullptr && (*(uint32_t *)(this + 0x34) & messageMask) != 0) {
            // Dispatch the message
            if (*(void **)(this + 0x38) == nullptr) {
                // Use default handler from message's vtable (offset 0xc)
                keepProcessing = ((char (*)(uint32_t, uint32_t*, int32_t, void*))(*(uint32_t **)(*messageObject + 0xc)))(
                    messageType, payload, payloadSize, (void *)(this + 0x28));
            } else {
                // Use custom handler stored at this+0x38
                keepProcessing = ((char (*)(int*, uint32_t, uint32_t*, int32_t, void*))(*(uint32_t *)(this + 0x38)))(
                    messageObject, messageType, payload, payloadSize, (void *)(this + 0x28));
            }
        }

        if (!keepProcessing) {
            return;
        }
    } while (true);
}