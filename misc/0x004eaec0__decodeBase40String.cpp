// FUNC_NAME: decodeBase40String
void decodeBase40String(byte *input, char *output)
{
    int outputIndex = 0;
    byte *pInput = input;
    
    do {
        byte inputByte = *pInput;
        // Lookup table: input byte -> valid character (base-40)
        // s_abcdefghijklmnopqrstuvwxyz012345_010c2531 is at address 0x010c2531
        // The table maps bytes to base-40 digits (0-39). Values > 0x27 are invalid (0x28+)
        byte lookupValue = s_abcdefghijklmnopqrstuvwxyz012345_010c2531[inputByte + 0x27];
        
        if (lookupValue > 0x27) {
            // Invalid character found - this terminates the encoding block
            int blockSize = outputIndex + 1;
            int shift = 0x18 - (blockSize >> 1);
            
            // Pad remaining output with null terminator
            output[shift] = 0;
            
            // Shift existing output bytes to the right by (shift - outputIndex)?
            // This is a reverse shift: we move bytes from the end of the output buffer back
            if (outputIndex >= 0) {
                char *pOut = output + outputIndex;
                int shiftAmount = shift - outputIndex;
                do {
                    char *pPrev = pOut - 1;
                    pOut = pOut - 1;
                    outputIndex = outputIndex - 1;
                    pOut[shiftAmount] = *pPrev;
                } while (outputIndex >= 0);
            }
            
            // First output byte is from DAT_010c24b0 lookup (another table)
            output[0] = DAT_010c24b0[lookupValue];
            
            if (blockSize > 15) {
                return; // Buffer full, exit
            }
            
            // Process remaining bytes in pairs, converting 2 input bytes to 3 output bytes
            // This is base-40 decoding: 2 bytes (0-39 each) encode 3 base-40 digits
            char *pOut = output + 1;
            do {
                pInput = input + blockSize;
                outputIndex = blockSize + 1;
                blockSize = blockSize + 2;
                
                // Combine two bytes into a single value
                uint combined = CONCAT11(input[outputIndex], *pInput);
                uint encodedValue = combined / 0x28;
                
                // Decode 2 base-40 bytes into 3 output bytes
                pOut[0] = DAT_010c2530[combined % 0x28]; // First decoded digit
                pOut[1] = DAT_010c2530[encodedValue % 0x28]; // Second decoded digit
                pOut[2] = DAT_010c2530[encodedValue / 0x28]; // Third decoded digit
                pOut = pOut + 3;
            } while (blockSize < 16);
            
            return;
        }
        
        // Valid character - check for null terminator
        if (inputByte == 0) break;
        
        // Copy character to output at same offset
        // This is doing: output[offset] = input[offset] (where offset = (int)output - (int)input)
        pInput[(int)output - (int)pInput] = inputByte;
        outputIndex = outputIndex + 1;
        pInput = pInput + 1;
    } while (outputIndex < 16);
    
    // Null-terminate the output
    output[outputIndex] = 0;
    return;
}