// FUNC_NAME: NetReflectable::readFields
// Function address: 0x006dbc90
// Role: Deserializes object fields from a bitstream; reads type-tagged values into member offsets.

// Assuming these are helper functions from a BitStreamReader class
extern void readStreamInit(BitStreamReader& stream);
extern void readStreamHeader(BitStreamReader& stream, uint32 magic);
extern bool readStreamHasMore(BitStreamReader& stream);
extern void* readStreamReadValue(BitStreamReader& stream); // returns pointer to raw value
extern uint32 readStreamGetType(BitStreamReader& stream);
extern void readStreamNext(BitStreamReader& stream);

extern float g_fDefaultFloat; // 0x00e44598

class NetReflectable {
public:
    void readFields(BitStreamReader& stream);
    // Member fields (offsets relative to this):
    // +0x78 : field0     (unknown)
    // +0x7c : field1
    // ... up to +0x1c4
};

void NetReflectable::readFields(BitStreamReader& stream) {
    // Initialize stream reading
    readStreamInit(stream);
    // Read header with magic constant
    readStreamHeader(stream, 0xa1da5924);

    while (!readStreamHasMore(stream)) {
        void* valuePtr;
        uint32 typeTag = readStreamGetType(stream);

        switch (typeTag) {
        case 0: // field at +0x78
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x78) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 1: // field at +0x7c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x7c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 2: // field at +0x80
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x80) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 3: // field at +0x84
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x84) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 4: // field at +0x88
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x88) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 5: // field at +0x8c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x8c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 6: // field at +0x90
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x90) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 7: // field at +0x94
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x94) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 8: // field at +0x98
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x98) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 9: // field at +0x9c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x9c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 10: // field at +0xa0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xa0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 11: // field at +0xb4 (float with default clamp)
        {
            valuePtr = readStreamReadValue(stream);
            float readVal = *(float*)((char*)valuePtr + 8);
            float usedVal = g_fDefaultFloat;
            if (g_fDefaultFloat < readVal || g_fDefaultFloat == readVal) {
                valuePtr = readStreamReadValue(stream);
                usedVal = *(float*)((char*)valuePtr + 8);
            }
            *(float*)(this + 0xb4) = usedVal;
            break;
        }
        case 12: // field at +0xa4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xa4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 13: // field at +0xa8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xa8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 14: // field at +0xac
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xac) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 15: // field at +0xb0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xb0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 16: // field at +0xb8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xb8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 17: // field at +0xc0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xc0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 18: // field at +0xbc
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xbc) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 19: // field at +0xc4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xc4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 20: // field at +0xc8 (offset 200)
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 200) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 21: // field at +0xcc
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xcc) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 22: // field at +0xd0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xd0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 23: // field at +0xd4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xd4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 24: // field at +0xd8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xd8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 25: // field at +0xe0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xe0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 26: // field at +0xdc
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xdc) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 27: // field at +0xe4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xe4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 28: // field at +0xe8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xe8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 29: // field at +0xec
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xec) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 30: // field at +0xf0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xf0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 31: // field at +0xf4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xf4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 32: // field at +0xf8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xf8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 33: // field at +0xfc
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0xfc) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 34: // field at +0x100
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x100) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 35: // field at +0x104
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x104) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 36: // field at +0x108
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x108) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 37: // field at +0x10c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x10c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 38: // field at +0x110
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x110) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 39: // field at +0x114
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x114) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 40: // field at +0x118
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x118) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 41: // field at +0x11c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x11c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 42: // field at +0x120
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x120) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 43: // field at +0x124
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x124) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 44: // field at +0x128
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x128) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 45: // field at +0x12c (offset 300)
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 300) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 46: // field at +0x130
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x130) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 47: // field at +0x134
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x134) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 48: // field at +0x138
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x138) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 49: // field at +0x13c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x13c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 50: // field at +0x140
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x140) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 51: // field at +0x144
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x144) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 52: // field at +0x148
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x148) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 53: // field at +0x14c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x14c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 54: // field at +0x150
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x150) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 55: // field at +0x154
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x154) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 56: // field at +0x158
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x158) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 57: // field at +0x15c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x15c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 58: // field at +0x160
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x160) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 59: // field at +0x164
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x164) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 60: // field at +0x168
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x168) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 61: // field at +0x16c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x16c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 62: // field at +0x170
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x170) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 63: // field at +0x174
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x174) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 64: // field at +0x178
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x178) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 65: // field at +0x17c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x17c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 66: // field at +0x180
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x180) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 67: // field at +0x184
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x184) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 68: // field at +0x188
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x188) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 69: // field at +0x18c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x18c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 70: // field at +0x190 (offset 400)
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 400) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 71: // field at +0x194
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x194) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 72: // field at +0x198
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x198) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 73: // field at +0x19c
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x19c) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 74: // field at +0x1a0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1a0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 75: // field at +0x1a4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1a4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 76: // field at +0x1a8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1a8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 77: // field at +0x1ac
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1ac) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 78: // field at +0x1b0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1b0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 79: // field at +0x1b4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1b4) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 80: // field at +0x1b8
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1b8) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 81: // field at +0x1bc
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1bc) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 82: // field at +0x1c0
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1c0) = *(uint32*)((char*)valuePtr + 8);
            break;
        case 83: // field at +0x1c4
            valuePtr = readStreamReadValue(stream);
            *(uint32*)(this + 0x1c4) = *(uint32*)((char*)valuePtr + 8);
            break;
        }
        readStreamNext(stream);
    }
    return;
}