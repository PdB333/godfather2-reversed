// FUNC_NAME: QuantizedFloatDecoder::decode
byte* DecodeQuantizedFloat(byte* inputBuffer, float baseValue, uint bitIndex, float* outValue) {
    byte firstByte = *inputBuffer;
    uint opcode = firstByte & 0xF;                // +0x0: low nibble = opcode
    uint length = ((uint)inputBuffer[1] << 4) | ((uint)(firstByte >> 4)); // 12-bit length

    switch (opcode) {
        case 5: { // Nested element: read subtree
            // Read a 16-bit relative offset from inputBuffer+2
            byte* subtreePtr = (byte*)((uint)(inputBuffer + 2) + ((*(uint16*)(inputBuffer + 2) - 2)));
            inputBuffer += 4; // skip header (1 byte opcode + 1 byte length/opcode? Actually 4 bytes: first 2 bytes + 2 offset bytes)
            if (length != 0) {
                while (true) {
                    byte currentByte = *inputBuffer;
                    uint elementLength = ((uint)inputBuffer[1] << 4) | ((uint)(currentByte >> 4));
                    uint remainingElements = length - 1;
                    uint childOpcode = currentByte & 0xF;
                    uint adjustedLength = elementLength - 1; // used for index check

                    if (bitIndex < elementLength) {
                        // Found the target element
                        if (childOpcode == 0xC) {
                            *outValue = 0.0f;
                            return subtreePtr;
                        }
                        if (childOpcode == 0xD) {
                            *outValue = DAT_00e2b1a4; // constant ~1.0f?
                            return subtreePtr;
                        }
                        if (childOpcode == 0) {
                            FUN_0057c0f0(); // error handler
                            *outValue = baseValue;
                            return subtreePtr;
                        }
                        if (childOpcode == 0xE) {
                            // Bitfield test: check bit at position bitIndex+2 in inputBuffer
                            uint testBit = (inputBuffer[(bitIndex >> 3) + 2] >> (bitIndex & 7)) & 1;
                            *outValue = (testBit != 0) ? DAT_00e2b1a4 : 0.0f;
                            return subtreePtr;
                        }
                        // Unknown opcode -> delegate to handler
                        FUN_0057c260(childOpcode, baseValue);
                        inputBuffer = subtreePtr;
                        break;
                    }

                    // Skip this element
                    uint elementSize;
                    if (childOpcode == 0xE) {
                        elementSize = (elementLength + 7) >> 3; // in bytes
                    } else {
                        elementSize = *(int*)(&DAT_00e2c2e0 + childOpcode * 4) * elementLength; // scale factor
                    }
                    inputBuffer += *(int*)(&DAT_00e2c2a4 + childOpcode * 4) + elementSize;
                    bitIndex -= adjustedLength;
                    baseValue -= (*(float*)(&DAT_00e2c320 + (adjustedLength >> 8) * 4) * DAT_00e445d0 +
                                   *(float*)(&DAT_00e2c320 + (adjustedLength & 0xFF) * 4));
                    length = remainingElements;
                    if (remainingElements == 0) {
                        return inputBuffer;
                    }
                }
            }
            return inputBuffer;
        }

        case 0xC: // Constant zero
            *outValue = 0.0f;
            break;
        case 0xD: // Constant one
            *outValue = DAT_00e2b1a4;
            break;
        case 0xE: { // Bitfield test
            uint testBit = (inputBuffer[(bitIndex >> 3) + 2] >> (bitIndex & 7)) & 1;
            *outValue = (testBit != 0) ? DAT_00e2b1a4 : 0.0f;
            return inputBuffer + DAT_00e2c2dc + ((length + 7) >> 3); // skip header + payload
        }
        case 0: // Unhandled -> error
            *outValue = (float)((uint)*(uint3*)(inputBuffer + 2) << 8); // read 3-byte value?
            break;
        default:
            FUN_0057c260(opcode, baseValue); // unsupported opcode
            break;
    }

    // Standard skip: advance by offset + scaled length
    return inputBuffer + *(int*)(&DAT_00e2c2a4 + opcode * 4) + *(int*)(&DAT_00e2c2e0 + opcode * 4) * length;
}