// FUNC_NAME: huffmanDecodeSymbol
// Address: 0x0057f330
// Role: Decodes a Huffman-like symbol from a bitstream using a state machine.
// Reads 2 bits from the current byte based on the current state (1,3,5,7),
// transitions to a new state, and advances the byte pointer by 0, 1, or 2 bytes.
// ESI holds the pointer to the current byte in the bitstream (bytePtr).
// param_1 (ECX) points to the state variable.

void __fastcall huffmanDecodeSymbol(uint8_t* state)
{
    uint8_t byte = *(uint8_t*)ESI; // Current byte from bitstream

    switch (*state)
    {
    case 1: // Bits 0-1
        switch (byte & 0x03)
        {
        case 0: *state = 3; ESI += 2; break;
        case 1: *state = 7; ESI += 2; break;
        case 2: *state = 3; ESI += 1; break;
        case 3: *state = 7; ESI += 1; break;
        }
        break;
    case 3: // Bits 2-3
        switch ((byte >> 2) & 0x03)
        {
        case 0: *state = 5; ESI += 2; break;
        case 1: *state = 1; ESI += 1; break;
        case 2: *state = 5; ESI += 1; break;
        case 3: *state = 1; break; // no advance
        }
        break;
    case 5: // Bits 4-5
        switch ((byte >> 4) & 0x03)
        {
        case 0: *state = 7; ESI += 2; break;
        case 1: *state = 3; ESI += 1; break;
        case 2: *state = 7; ESI += 1; break;
        case 3: *state = 3; break; // no advance
        }
        break;
    case 7: // Bits 6-7
        switch ((byte >> 6) & 0x03)
        {
        case 0: *state = 1; ESI += 1; break;
        case 1: *state = 5; ESI += 1; break;
        case 2: *state = 1; break; // no advance
        case 3: *state = 5; break; // no advance
        }
        break;
    }
}