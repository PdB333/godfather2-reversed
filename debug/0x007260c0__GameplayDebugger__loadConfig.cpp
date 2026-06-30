// FUNC_NAME: GameplayDebugger::loadConfig
// Address: 0x007260c0
// Role: Deserializes a configuration block from a stream for the GameplayDebugger class.
// Uses EA EARS serialization primitives (block types, property reading).

class Stream; // forward declaration for serialization helpers

class GameplayDebugger {
public:
    // Offsets relative to this:
    // +0x54: int m_debugFlag1
    // +0x5c: int m_debugFlag2
    // +0x64: float m_debugFloat1
    // +0x6c: float m_debugFloat2
    // +0x74: float m_rangeSquared (clamped squared value)
    // +0x78: float m_someFloat
    // +0x7c: float m_otherRangeSquared
    // +0x80: int m_unknown1
    // +0x84: int m_unknown2
    // +0x8c: short m_clampedShort (0..4)
    // +0x90: int m_extraInt
    // +0x94: float m_colorR (converted from int)
    // +0x98: float m_colorG
    // +0x9c: float m_colorB
    // +0xa0: int m_packedRGBA (four 8-bit values shifted and packed)
    // +0xa4..+0xb0: float m_quad[4] (four floats)
    // +0xb8: DebugBlock* m_debugBlock (allocated 16 bytes with magic)
    // +0xe4: float m_arr1
    // +0xe8: float m_arr2
    // +0xec: float m_arr3
    // +0xf0: float m_arr4
    // +0xf4: float m_arr5
    // +0xf8: float m_arr6
    // +0xfc: float m_arr7
    // +0x100: float m_arr8
    // +0x110: int m_miscInt1
    // +0x115: byte m_miscByte
    // +0x116: byte m_miscFlag
    // +0x118: int m_miscInt2
    // +0x11c: int m_miscInt3
    // +0x120: char m_packedArray[76] (derived from vector)
    // +0x130: float m_originX
    // +0x134: float m_originY
    // +0x138: float m_originZ

    void loadConfig(Stream& stream);
};

// Forward declarations for serialization helper functions (EARS engine)
void beginStreamRead(Stream& stream);
void beginBlock(Stream& stream, uint blockId);
void setBlockVersion(int version);
// ... other prototypes would be here

void GameplayDebugger::loadConfig(Stream& stream) {
    char vecBuffer[12]; // temporary for reading vector components
    int local_f4, local_e4, local_d4; // not used meaningfully
    int local_c4 = *(int*)0x00d5780c; // global constant?

    beginStreamRead(stream);
    beginBlock(stream, 0xb390b11a);
    setBlockVersion(1);

    if (!isBlockEnd(stream)) {
        // Read a vector from stream and store it
        readProperty(vecBuffer, stream); // reads property into buffer
        readVector3(vecBuffer, &vecBuffer); // actually stores into temp locals
        // The vector components are placed into local_d0, uStack_cc, local_c8
        // which become this+0x130..0x138
        m_originX = *(float*)&local_d0;
        m_originY = *(float*)&uStack_cc;
        m_originZ = *(float*)&local_c8;

        char packedArray[76];
        packVectorToArray(vecBuffer, packedArray); // conversion
        copyArray(packedArray, m_packedArray); // copy 76 bytes to +0x120
    }

    beginBlock(stream, 0xba0142f7);

    while (!isBlockEnd(stream)) {
        readProperty(stream); // read property header
        uint propType = readPropertyType(stream);

        switch (propType) {
        case 1: {
            int val = readPropertyValueInt(stream);
            setDebugFlag1(val); // +0x54
            break;
        }
        case 2: {
            int val = readPropertyValueInt(stream);
            setDebugFlag2(val); // +0x5c
            break;
        }
        case 3: {
            float val = readPropertyValueFloat(stream);
            setDebugFloat1(val); // +0x64
            break;
        }
        case 4: {
            float val = readPropertyValueFloat(stream);
            setDebugFloat2(val); // +0x6c
            break;
        }
        case 5: {
            int raw = readPropertyValueInt(stream);
            m_colorR = convertColorToFloat(raw); // +0x94
            break;
        }
        case 6: {
            int raw = readPropertyValueInt(stream);
            m_colorG = convertColorToFloat(raw); // +0x98
            break;
        }
        case 7: {
            int raw = readPropertyValueInt(stream);
            m_colorB = convertColorToFloat(raw); // +0x9c
            break;
        }
        case 8: {
            int* quad = (int*)readPropertyArray(stream);
            // Pack four 8-bit values into one int via bit shifts
            m_packedRGBA = (*quad * 0x21 + quad[1]) * 0x21 + quad[2] * 0x21 + quad[3];
            break;
        }
        case 9: {
            float* quad = (float*)readPropertyArray(stream);
            m_quad[0] = quad[0];
            m_quad[1] = quad[1];
            m_quad[2] = quad[2];
            m_quad[3] = quad[3]; // +0xa4..0xb0
            break;
        }
        case 10: {
            int* prop = (int*)readPropertyRaw(stream);
            m_miscFlag = *(byte*)(prop + 2); // offset 8 in property struct -> byte at +0x116
            break;
        }
        case 11: {
            int* prop = (int*)readPropertyRaw(stream);
            m_miscInt1 = *(int*)(prop + 2); // offset 8 -> int at +0x110
            break;
        }
        case 12: {
            int* prop = (int*)readPropertyRaw(stream);
            m_miscByte = *(byte*)(prop + 2); // offset 8 -> byte at +0x115
            break;
        }
        case 13: {
            int* prop = (int*)readPropertyRaw(stream);
            m_unknown1 = *(int*)(prop + 2); // +0x80
            break;
        }
        case 14: {
            int* prop = (int*)readPropertyRaw(stream);
            m_unknown2 = *(int*)(prop + 2); // +0x84
            break;
        }
        case 15: {
            // Allocate debug block (16 bytes) with magic constants
            DebugBlock* block = (DebugBlock*)allocateMemory(0x10);
            if (block) {
                block->magic1 = 0xbadbadba;
                block->magic2 = 0xbeefbeef;
                block->magic3 = 0xeac15a55;
                block->magic4 = 0x91100911;
            }
            m_debugBlock = block; // +0xb8
            readPropertyRaw(block); // overwrite block contents from stream
            initializeDebugBlock(block); // may set additional fields
            break;
        }
        case 16: {
            int val = readPropertyValueInt(stream);
            short s = (short)val;
            if (s < 1) s = 0;
            else if (s > 4) s = 4;
            m_clampedShort = s; // +0x8c
            break;
        }
        case 17: {
            float val = readPropertyValueFloat(stream);
            m_rangeSquared = val * val; // +0x74
            break;
        }
        case 18: {
            float val = readPropertyValueFloat(stream);
            m_someFloat = val; // +0x78
            break;
        }
        case 19: {
            float val = readPropertyValueFloat(stream);
            m_otherRangeSquared = val * val; // +0x7c
            break;
        }
        case 20: {
            int val = readPropertyValueInt(stream);
            m_extraInt = val; // +0x90
            break;
        }
        case 21: {
            float val = readPropertyValueFloat(stream);
            m_arr1 = val; // +0xe4
            break;
        }
        case 22: {
            float val = readPropertyValueFloat(stream);
            m_arr2 = val; // +0xe8
            break;
        }
        case 23: {
            float val = readPropertyValueFloat(stream);
            m_arr3 = val; // +0xec
            break;
        }
        case 24: {
            float val = readPropertyValueFloat(stream);
            m_arr4 = val; // +0xf0
            break;
        }
        case 25: {
            float val = readPropertyValueFloat(stream);
            m_arr5 = val; // +0xf4
            break;
        }
        case 26: {
            float val = readPropertyValueFloat(stream);
            m_arr6 = val; // +0xf8
            break;
        }
        case 27: {
            float val = readPropertyValueFloat(stream);
            m_arr7 = val; // +0xfc
            break;
        }
        case 28: {
            float val = readPropertyValueFloat(stream);
            m_arr8 = val; // +0x100
            break;
        }
        case 29: {
            int val = readPropertyValueInt(stream);
            m_miscInt2 = val; // +0x118
            break;
        }
        case 30: {
            int val = readPropertyValueInt(stream);
            m_miscInt3 = val; // +0x11c
            break;
        }
        }
        advanceToNextProperty(stream);
    }
}