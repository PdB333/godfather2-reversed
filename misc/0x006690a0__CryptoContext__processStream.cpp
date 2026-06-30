// FUNC_NAME: CryptoContext::processStream
int CryptoContext::processStream(CryptoContext* ctx, uint flags)
{
    uint8_t* buffer1;
    uint8_t* buffer2;
    uint8_t* buffer3;
    int result;
    uint32_t originalState; // saved state from ctx->state

    // Check if stream is already done and not in reset mode
    if (((flags & 1) == 0) && (ctx->state == 1)) {
        return -3; // Already processed
    }

    // Allocate three 64-byte working buffers
    buffer1 = (uint8_t*)_calloc(4, 0x40);
    if (buffer1 == NULL) {
        return -2; // Memory allocation failed
    }
    // Initialize buffer1 header-like structure
    buffer1[0x00] = 0;
    buffer1[0x04] = 0x40;
    buffer1[0x08] = 0;

    buffer2 = (uint8_t*)_calloc(4, 0x40);
    if (buffer2 == NULL) {
        deallocBuffer(); // FUN_00665b40
        return -2;
    }
    buffer2[0x00] = 0;
    buffer2[0x04] = 0x40;
    buffer2[0x08] = 0;

    buffer3 = (uint8_t*)_calloc(4, 0x40);
    if (buffer3 == NULL) {
        result = -2;
        goto cleanup;
    }
    buffer3[0x00] = 0x40;
    buffer3[0x04] = 0;
    buffer3[0x08] = 0;

    // Save and reset the state field
    originalState = ctx->state;
    ctx->state = 0;

    // Initialize crypto context
    initCryptoContext(); // FUN_0066a550

    do {
        // Check if we need to stop
        result = checkForStop(); // FUN_00665ce0
        if (result != 0) break;

        // Combine buffers with flag-1
        result = processBlock(buffer1, flags - 1); // FUN_006669a0
        if (result != 0) break;

        // Transform operation
        result = transformBuffers(buffer3, buffer1, buffer2); // FUN_00668ce0
        if (result != 0) break;

        // Copy buffer2 to context
        result = copyToContext(buffer2, ctx); // FUN_0066a780
        if (result != 0) break;

        // XOR buffer1 with flags
        result = xorWithFlags(buffer3, flags, buffer3); // FUN_00668f50
        if (result != 0) break;

        // Encrypt operation
        result = encryptBlock(buffer2, buffer3, buffer3, 0); // FUN_00665d70
        if (result != 0) break;

        // Copy buffer3 back to buffer1
        result = copyToContext(buffer1, buffer3); // FUN_0066a780
        if (result != 0) break;

    } while ((buffer1[0x08] != buffer2[0x08]) || (result = isBufferEmpty(), result != 0)); // FUN_00665c30

    // Process final block
    result = processBlock(buffer1, flags); // FUN_006669a0
    if (result == 0) {
        // Wait for input characters
        while (true) {
            int ch = getCharacter(); // FUN_00665bd0
            if (ch != 1) break;

            // Append character to buffer1
            result = appendData(buffer1, 1, buffer1); // FUN_0066a7f0
            if (result != 0) goto cleanup;

            result = processBlock(buffer1, flags); // FUN_006669a0
            if (result != 0) goto cleanup;
        }
        // Restore original state
        ctx->state = originalState;

        // Get final result and store it
        uint64_t finalResult = getFinalResult(); // FUN_00666970
        *(uint32_t*)((uint32_t)finalResult + 8) = (uint32_t)(finalResult >> 32);
        result = 0;
    }

cleanup:
    deallocBuffer(); // FUN_00665b40 for buffer3
    deallocBuffer(); // for buffer2
    deallocBuffer(); // for buffer1
    return result;
}