// FUNC_NAME: ConfigurationBlock::parseBlock
// Function address: 0x006e0810
// This function reads a configuration block from a data stream and populates the object's fields.
// It uses a token-based parsing approach, where each token type corresponds to a specific field offset.
// The function handles up to 0x29 (41) token types, storing values at offsets from 0x58 to 0x124.
// Special handling for token type 0: may trigger object lookup and attachment, and a global setting.

void __thiscall ConfigurationBlock::parseBlock(uint8_t* streamPtr) {
    uint32_t tokenType;
    uint32_t* tokenDataPtr;
    int32_t* fieldPtr;
    int32_t result;
    uint32_t value;
    
    initializeReader(streamPtr);          // FUN_004738b0 - initialize stream parsing
    setReaderParameter(streamPtr, 0x9d5c7200); // FUN_0043aff0 - set parsing parameter (e.g., threshold/hash)
    
    while (!isReaderDone()) {             // FUN_0043b120 - check if stream end reached
        tokenDataPtr = readNextToken();   // FUN_0043b210 - read current token data, returns pointer to token
        tokenType = getTokenType();       // FUN_0043ab70 - get token type (0..0x29)
        
        switch (tokenType) {
            case 0:
                // Section/group start
                fieldPtr = (int32_t*)(this + 0x58);
                advanceReader(fieldPtr);  // FUN_0043b210 (but with argument? actually called with piVar1)
                // Note: the original code calls FUN_0043b210(piVar1) which is likely a different overload?
                // We'll keep the original call structure:
                advanceReader(fieldPtr);  // Actually FUN_0043b210 takes no argument? But here it's called with piVar1. 
                // The decompiled shows: FUN_0043b210(piVar1); - that might be a different function?
                // Given ambiguity, we preserve the call as readNextToken() but pass piVar1? Probably a bug in decomp.
                // We'll represent as: readNextTokenWithBuffer(fieldPtr);
                getTokenData(fieldPtr);   // FUN_0043ad10 - copy token data to field location
                
                // Check if any of the first four fields are non-zero
                if ((*fieldPtr != 0) || (*(this + 0x5c) != 0) || (*(this + 0x60) != 0) || (*(this + 100) != 0)) {
                    result = findObjectByPointer(fieldPtr, 0); // FUN_00446100 - find an object based on pointer
                    if (result != 0) {
                        value = createObject(result, 0x383225a1); // FUN_006c9470 - may create object with ID
                        bindObject(value); // FUN_006d68e0 - bind or attach the created object
                    }
                }
                // Apply global setting if condition met
                if ((*(int*)(this + 0x68) == 0) || (*(int*)(this + 0x68) == 0x48)) {
                    if (*(int32_t*)(DAT_012233a0 + 4) == 0) {
                        bindObject(0); // FUN_006d68e0 with 0
                    } else {
                        bindObject(*(int32_t*)(*(int32_t*)DAT_012233a0 + 4) - 0x1f30); // offset from global
                    }
                }
                break;
                
            case 1:
                tokenDataPtr = readNextToken(); // FUN_0043b210
                *(uint32_t*)(this + 0x84) = *(uint32_t*)(tokenDataPtr + 8); // store value at +0x84
                break;
            case 2:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x88) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 3:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x8c) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 4:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x90) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 5:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x94) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 6:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x98) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 7:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x9c) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 8:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xa0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 9:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xa4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 10:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xa8) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 11:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xac) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 12:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xb0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 13:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xb4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 14:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xb8) = *(uint32_t*)(tokenDataPtr + 8) & DAT_00e44680; // Apply mask
                break;
            case 15:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xbc) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 16:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xc0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 17:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xc4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 18:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 200) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 19:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xcc) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 20:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xd0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 21:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xd4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 22:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xd8) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 23:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xdc) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 24:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xe0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 25:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xe4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 26:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xe8) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 27:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xec) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 28:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xf0) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 29:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x100) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 30:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x104) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 31:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x108) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 32:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x10c) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 33:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x110) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 34:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x114) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 35:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x118) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 36:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x11c) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 37:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x120) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 38:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0x124) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 39:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xf4) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 40:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xf8) = *(uint32_t*)(tokenDataPtr + 8);
                break;
            case 41:
                tokenDataPtr = readNextToken();
                *(uint32_t*)(this + 0xfc) = *(uint32_t*)(tokenDataPtr + 8);
                break;
        }
        advanceReader(); // FUN_0043b1a0 - move to next token
    }
}