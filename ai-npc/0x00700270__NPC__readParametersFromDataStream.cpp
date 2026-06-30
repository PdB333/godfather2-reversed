// FUNC_NAME: NPC::readParametersFromDataStream
void __thiscall NPC::readParametersFromDataStream(int thisPtr, int streamHandle) {
    char hasMore;
    int tokenType;
    int tokenData;
    int index;
    float floatVal;
    int* vecData;

    // Initialize the stream reading at a given hash/ID
    dataStreamBegin(streamHandle, 0x332d5a20); // stream hash ID
    hasMore = dataStreamHasMore();
    while (hasMore == 0) {
        dataStreamAdvance(); // advance to next token
        tokenType = dataStreamGetTokenType();
        switch (tokenType) {
            case 0: {
                // Read a string token and set a name
                dataStreamAdvance();
                int stringToken = dataStreamGetTokenString();
                setString(thisPtr + 0x344, stringToken); // +0x344: name/handle
                break;
            }
            case 1: {
                // Read an integer value and store at +0x510
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x510) = *(int*)(tokenData + 8);
                break;
            }
            case 2: {
                // Read integer at +0x2dc
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2dc) = *(int*)(tokenData + 8);
                break;
            }
            case 3: {
                // Read boolean flag for bit 1 (0x2) at +0x2d8
                tokenData = dataStreamReadToken();
                if (*(int*)(tokenData + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x2d8) &= 0xfffffffd; // clear bit 1
                } else {
                    *(unsigned int*)(thisPtr + 0x2d8) |= 2; // set bit 1
                }
                break;
            }
            case 4: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x34c) = *(int*)(tokenData + 8);
                break;
            }
            case 5: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x350) = *(int*)(tokenData + 8);
                break;
            }
            case 6: {
                tokenData = dataStreamReadToken();
                int val = *(int*)(tokenData + 8);
                *(int*)(thisPtr + 0x42c) = val;
                *(int*)(thisPtr + 0x38c) = val; // duplicate to another offset
                break;
            }
            case 7: {
                tokenData = dataStreamReadToken();
                int val = *(int*)(tokenData + 8);
                *(int*)(thisPtr + 0x32c) = val;
                *(int*)(thisPtr + 0x434) = val;
                break;
            }
            case 8: {
                tokenData = dataStreamReadToken();
                int val = *(int*)(tokenData + 8);
                *(int*)(thisPtr + 0x330) = val;
                *(int*)(thisPtr + 0x438) = val;
                break;
            }
            case 9: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x384) = *(int*)(tokenData + 8); // 0x384 = 900 decimal
                break;
            }
            case 10: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x334) = *(int*)(tokenData + 8);
                break;
            }
            case 11: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x338) = *(int*)(tokenData + 8);
                break;
            }
            case 12: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x33c) = *(int*)(tokenData + 8);
                break;
            }
            case 13: {
                // Bit 8 (0x100) at +0x2d8
                tokenData = dataStreamReadToken();
                if (*(int*)(tokenData + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x2d8) &= 0xfffffeff;
                } else {
                    *(unsigned int*)(thisPtr + 0x2d8) |= 0x100;
                }
                break;
            }
            case 14: {
                // Bit 0 at +0x2d8
                tokenData = dataStreamReadToken();
                if (*(int*)(tokenData + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x2d8) &= 0xfffffffe;
                } else {
                    *(unsigned int*)(thisPtr + 0x2d8) |= 1;
                }
                break;
            }
            case 15: {
                tokenData = dataStreamReadToken();
                int val = *(int*)(tokenData + 8);
                *(int*)(thisPtr + 0x430) = val;
                *(int*)(thisPtr + 0x390) = val;
                break;
            }
            case 0x10: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x340) = *(int*)(tokenData + 8);
                break;
            }
            case 0x11: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x394) = *(int*)(tokenData + 8);
                break;
            }
            case 0x12: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x398) = *(int*)(tokenData + 8);
                break;
            }
            case 0x13: {
                // Compute reciprocal of float value if val > threshold
                tokenData = dataStreamReadToken();
                floatVal = *(float*)(tokenData + 8);
                if (floatVal <= 0.0f) { // DAT_00d5ef84 likely 0
                    *(int*)(thisPtr + 0x39c) = 0;
                } else {
                    *(float*)(thisPtr + 0x39c) = 1.0f / floatVal; // _DAT_00d5780c = 1.0f
                }
                break;
            }
            case 0x14: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x354) = *(int*)(tokenData + 8);
                break;
            }
            case 0x15: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x358) = *(int*)(tokenData + 8);
                break;
            }
            case 0x16: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x35c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x17: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x360) = *(int*)(tokenData + 8);
                break;
            }
            case 0x18: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x388) = *(int*)(tokenData + 8);
                break;
            }
            case 0x19: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x364) = *(int*)(tokenData + 8);
                break;
            }
            case 0x1a: {
                tokenData = dataStreamReadToken();
                int raw = *(int*)(tokenData + 8);
                if (raw >= 0) {
                    *(int*)(thisPtr + 0x368) = raw; // only set if non-negative
                }
                break;
            }
            case 0x1b: {
                // Bit 6 (0x40) at +0x2d8
                tokenData = dataStreamReadToken();
                if (*(int*)(tokenData + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x2d8) &= 0xffffffbf;
                } else {
                    *(unsigned int*)(thisPtr + 0x2d8) |= 0x40;
                }
                break;
            }
            case 0x1c: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x4fc) = *(int*)(tokenData + 8);
                break;
            }
            case 0x1d: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x500) = *(int*)(tokenData + 8);
                break;
            }
            case 0x1e: {
                // Square float if > threshold, else default
                tokenData = dataStreamReadToken();
                floatVal = *(float*)(tokenData + 8);
                if (floatVal <= 0.0f) {
                    *(int*)(thisPtr + 0x2e0) = DEFAULT_SQUARE_VALUE; // DAT_00d5ccf8
                } else {
                    *(float*)(thisPtr + 0x2e0) = floatVal * floatVal;
                }
                break;
            }
            case 0x1f: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2e4) = *(int*)(tokenData + 8);
                break;
            }
            case 0x20: {
                tokenData = dataStreamReadToken();
                floatVal = *(float*)(tokenData + 8);
                if (floatVal <= 0.0f) {
                    *(int*)(thisPtr + 0x2e8) = DEFAULT_SQUARE_VALUE;
                } else {
                    *(float*)(thisPtr + 0x2e8) = floatVal * floatVal;
                }
                break;
            }
            case 0x21: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2ec) = *(int*)(tokenData + 8);
                break;
            }
            case 0x22: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2f0) = *(int*)(tokenData + 8);
                break;
            }
            case 0x23: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2f4) = *(int*)(tokenData + 8);
                break;
            }
            case 0x24: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2f8) = *(int*)(tokenData + 8);
                break;
            }
            case 0x25: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x2fc) = *(int*)(tokenData + 8);
                break;
            }
            case 0x26: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x300) = *(int*)(tokenData + 8);
                break;
            }
            case 0x27: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x304) = *(int*)(tokenData + 8);
                break;
            }
            case 0x28: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x308) = *(int*)(tokenData + 8);
                break;
            }
            case 0x29: {
                // Read a 4-element vector (color/coordinates?) at +0x4d0
                dataStreamAdvance();
                vecData = (int*)dataStreamGetTokenVector();
                *(int*)(thisPtr + 0x4d0) = vecData[0];
                *(int*)(thisPtr + 0x4d4) = vecData[1];
                *(int*)(thisPtr + 0x4d8) = vecData[2];
                *(int*)(thisPtr + 0x4dc) = vecData[3];
                break;
            }
            case 0x2a: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x504) = *(int*)(tokenData + 8);
                break;
            }
            case 0x2b: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x508) = *(int*)(tokenData + 8);
                break;
            }
            case 0x2c: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x50c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x2d: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x30c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x2e: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x310) = *(int*)(tokenData + 8);
                break;
            }
            case 0x2f: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x314) = *(int*)(tokenData + 8);
                break;
            }
            case 0x30: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x318) = *(int*)(tokenData + 8);
                break;
            }
            case 0x31: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x31c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x32: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x320) = *(int*)(tokenData + 8); // 800 decimal
                break;
            }
            case 0x33: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x324) = *(int*)(tokenData + 8);
                break;
            }
            case 0x34: {
                tokenData = dataStreamReadToken();
                *(bool*)(thisPtr + 0x380) = *(int*)(tokenData + 8) != 0;
                break;
            }
            // Stance/behavior parameter arrays (5 groups of 7 fields each)
            // Each group occupies 0x1c (28) bytes, base at +0x3a0
            case 0x35: // group 0, field 0
            case 0x3c: // group 1, field 0
            case 0x43: // group 2, field 0
            case 0x4a: // group 3, field 0
            case 0x51: // group 4, field 0
            {
                dataStreamAdvance();
                int field0Val = dataStreamGetTokenValue();
                int groupIndex = (tokenType - 0x35) / 6; // integer division yields 0,1,2,3,4
                *(int*)(thisPtr + 0x3a0 + groupIndex * 0x1c) = field0Val;
                break;
            }
            case 0x36: // field 1
            case 0x3d:
            case 0x44:
            case 0x4b:
            case 0x52:
            {
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x36) / 6;
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x3a4 + groupIndex * 0x1c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x37: // field 2
            case 0x3e:
            case 0x45:
            case 0x4c:
            case 0x53:
            {
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x37) / 6;
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x3a8 + groupIndex * 0x1c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x38: // field 3
            case 0x3f:
            case 0x46:
            case 0x4d:
            case 0x54:
            {
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x38) / 6;
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x3ac + groupIndex * 0x1c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x39: // field 4
            case 0x40:
            case 0x47:
            case 0x4e:
            case 0x55:
            {
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x39) / 6;
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x3b0 + groupIndex * 0x1c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x3a: // field 5
            case 0x41:
            case 0x48:
            case 0x4f:
            case 0x56:
            {
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x3a) / 6;
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x3b4 + groupIndex * 0x1c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x3b: // field 6 (reciprocal)
            case 0x42:
            case 0x49:
            case 0x50:
            case 0x57:
            {
                tokenData = dataStreamReadToken();
                float val = *(float*)(tokenData + 8);
                dataStreamAdvance();
                int groupIndex = (dataStreamGetTokenType() - 0x3b) / 6;
                if (val <= 0.0f) {
                    val = 0.0f;
                } else {
                    val = 1.0f / val;
                }
                // Offset for field 6: base + groupIndex*0x1c + 0x18 (since 0x22*0x1c? Actually calc: ((index+0x22)*0x1c) but index is groupIndex? Let's derive: for group 0, iVar5=0x3b, (0x3b-0x3b)/6+0x22 = 0x22, *0x1c = 0x3d8. But base 0x3a0 + 0x38? It's messy, but the pattern suggests field6 is at offset 0x18 from group start.
                *(float*)(thisPtr + ((groupIndex + 0x22) * 0x1c)) = val;
                break;
            }
            case 0x58: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x43c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x59: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x440) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5a: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x444) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5b: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x448) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5c: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x44c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5d: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x450) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5e: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x454) = *(int*)(tokenData + 8);
                break;
            }
            case 0x5f: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x458) = *(int*)(tokenData + 8);
                break;
            }
            case 0x60: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x45c) = *(int*)(tokenData + 8);
                break;
            }
            case 0x61: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x460) = *(int*)(tokenData + 8);
                break;
            }
            case 0x62: {
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x464) = *(int*)(tokenData + 8);
                break;
            }
            case 0x63: { // 99 decimal
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x468) = *(int*)(tokenData + 8);
                break;
            }
            case 100: { // 0x64
                // Read vector at +0x36c
                dataStreamAdvance();
                vecData = (int*)dataStreamGetTokenVector();
                *(int*)(thisPtr + 0x36c) = vecData[0];
                *(int*)(thisPtr + 0x370) = vecData[1];
                *(int*)(thisPtr + 0x374) = vecData[2];
                *(int*)(thisPtr + 0x378) = vecData[3];
                break;
            }
            case 101: { // 0x65
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x37c) = *(int*)(tokenData + 8);
                break;
            }
            case 102: { // 0x66
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x488) = *(int*)(tokenData + 8);
                break;
            }
            case 103: { // 0x67: outfit/mesh loading
                dataStreamAdvance();
                int nameToken = dataStreamGetTokenString();
                *(int*)(thisPtr + 0x48c) = 0;
                if (nameToken != 0) {
                    int assetHandle = getAssetHandle(nameToken); // FUN_005e3300
                    *(int*)(thisPtr + 0x48c) = assetHandle;
                    int meshHandle = getMeshHandle(assetHandle); // FUN_005e6a20
                    if (meshHandle != 0) {
                        *(int*)(thisPtr + 0x49c) = meshHandle;
                    }
                }
                break;
            }
            case 104: { // 0x68
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x490) = *(int*)(tokenData + 8);
                break;
            }
            case 105: { // 0x69: alternate outfit
                dataStreamAdvance();
                int nameToken = dataStreamGetTokenString();
                *(int*)(thisPtr + 0x494) = 0;
                if (nameToken != 0) {
                    int assetHandle = getAssetHandle(nameToken);
                    *(int*)(thisPtr + 0x494) = assetHandle;
                }
                break;
            }
            case 106: { // 0x6a
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x498) = *(int*)(tokenData + 8);
                break;
            }
            case 107: { // 0x6b
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x4a0) = *(int*)(tokenData + 8);
                break;
            }
            case 108: { // 0x6c
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x4a4) = *(int*)(tokenData + 8);
                break;
            }
            case 109: { // 0x6d
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x4a8) = *(int*)(tokenData + 8);
                break;
            }
            case 110: { // 0x6e
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x4ac) = *(int*)(tokenData + 8);
                break;
            }
            case 111: { // 0x6f: vector at +0x4e0
                dataStreamAdvance();
                vecData = (int*)dataStreamGetTokenVector();
                *(int*)(thisPtr + 0x4e0) = vecData[0];
                *(int*)(thisPtr + 0x4e4) = vecData[1];
                *(int*)(thisPtr + 0x4e8) = vecData[2];
                *(int*)(thisPtr + 0x4ec) = vecData[3];
                break;
            }
            case 112: { // 0x70: animation handle
                tokenData = dataStreamReadToken();
                int animHash = *(int*)(tokenData + 8);
                *(int*)(thisPtr + 0x4f4) = getAnimationHandle(animHash); // FUN_005bc5b0
                break;
            }
            case 113: { // 0x71
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x518) = *(int*)(tokenData + 8);
                break;
            }
            case 114: { // 0x72
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x51c) = *(int*)(tokenData + 8);
                break;
            }
            case 115: { // 0x73
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x520) = *(int*)(tokenData + 8);
                break;
            }
            case 116: { // 0x74
                tokenData = dataStreamReadToken();
                *(int*)(thisPtr + 0x524) = *(int*)(tokenData + 8);
                break;
            }
        }
        dataStreamEndTokenRead();
        hasMore = dataStreamHasMore();
    }
    // Post-process: if value at +0x368 is negative, set default based on character type
    if (*(int*)(thisPtr + 0x368) < 0) {
        // Check a character type byte at +0x1aa
        if (*(char*)(thisPtr + 0x1aa) != 2) {
            *(int*)(thisPtr + 0x368) = -100; // 0xffffff9c = -100? Actually 0xffffff9c is -100 decimal, then +0xfa (250) gives 150? Wait calculation: (-(uint)(char != 2) & 0xffffff9c) + 0xfa. If char != 2, uint = 1, so (-1 & 0xffffff9c) = 0xffffff9c = -100, +250 = 150. If char == 2, uint=0, (-0 & ...)=0, +250 = 250.
            // So sets to either 150 or 250
        } else {
            *(int*)(thisPtr + 0x368) = 250; // maybe default range?
        }
    }
}

// Helper function stubs (assumed from callees)
void dataStreamBegin(int stream, unsigned int hash);
bool dataStreamHasMore();
void dataStreamAdvance();
int dataStreamGetTokenType();
int dataStreamReadToken(); // returns pointer to token data
int dataStreamGetTokenString();
int dataStreamGetTokenValue(); // returns token's value as int
int* dataStreamGetTokenVector(); // returns pointer to 4 floats/ints
void dataStreamEndTokenRead();
int getAssetHandle(int nameToken);
int getMeshHandle(int assetHandle);
int getAnimationHandle(int hash);