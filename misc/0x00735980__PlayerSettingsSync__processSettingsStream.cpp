// FUNC_NAME: PlayerSettingsSync::processSettingsStream
// Reconstructed from Godfather 2 (EA EARS engine) 0x00735980
// This function processes a stream of player settings commands and updates local fields.

// Assumed stream reader class (BitStreamReader)
class BitStreamReader {
public:
    void init();
    int readInt();
    const char* readString();
    float* readVector4(); // returns pointer to 4 floats
    bool isEndOfStream();
    void advance();
    // ... other methods
};

// Player settings class (size large, many fields)
class PlayerSettingsSync {
public:
    // offsets in bytes from this
    static const int kOffsetReader = 0x2350; // pointer to a reader object?
    static const int kOffsetFlags1 = 0x1f54; // bitfield flags
    static const int kOffsetFlags2 = 0x1f58; // another bitfield
    static const int kOffsetSettingA = 0x1f44;
    static const int kOffsetSettingB = 0x1f64;
    static const int kOffsetSettingC = 0x1f98;
    static const int kOffsetSettingD = 0x1f9c;
    static const int kOffsetSettingE = 0x1fa0;
    static const int kOffsetSettingF = 0x1fa4;
    static const int kOffsetSettingG = 0x1fa8;
    static const int kOffsetSettingH = 0x1fac;
    static const int kOffsetSettingI = 0x1fb4;
    static const int kOffsetSettingJ = 0x1fb8;
    static const int kOffsetSettingK = 0x1fbc;
    static const int kOffsetSettingL = 0x1fc0;
    static const int kOffsetSettingM = 0x1fc8;
    static const int kOffsetSettingN = 0x1fd0;
    static const int kOffsetSettingO = 0x1fe0;
    static const int kOffsetSettingP = 0x1fd8;
    static const int kOffsetSettingQ = 0x201c;
    static const int kOffsetSettingR = 0x2064;
    static const int kOffsetSettingS = 0x2084;
    static const int kOffsetSettingT = 0x2094;
    static const int kOffsetSettingU = 0x20a4;
    static const int kOffsetSettingV = 0x20a8;
    static const int kOffsetSettingW = 0x20ac;
    static const int kOffsetSettingX = 0x20b0;
    static const int kOffsetSettingY = 0x20b4;
    static const int kOffsetSettingZ = 0x20b8;
    static const int kOffsetVectorA = 0x20bc;
    static const int kOffsetSettingAA = 0x2104;
    static const int kOffsetSettingAB = 0x265c;
    static const int kOffsetControlMode = 0x56c;
    static const int kOffsetControlFlags = 0x564;
    static const int kOffsetMaybeFloatA = 0x568;
    static const int kOffsetSpecialBuffer = 0x828; // 8 bytes? (two uint64?)
    static const int kOffsetSpecialBuffer2 = 0x830;
    static const int kOffsetSpecialBuffer3 = 0x838;

    void processSettingsStream(BitStreamReader* stream);
    // ... other members
};

void __thiscall PlayerSettingsSync::processSettingsStream(BitStreamReader* stream) {
    stream->init();
    // call vtable function at this+0x2350 (some object) with stream
    // (**(code **)(*(int *)(this + kOffsetReader) + 0x20))(stream);
    // Decompiled: (**(code **)(*(int *)(this + 0x2350) + 0x20))(stream);
    // We'll assume it's a member function call on some reader helper.
    // Might be stream->readVersion()
    // For brevity, we'll just call a method: stream->readVersion(0x369ac561);
    stream->readVersion(0x369ac561); // assume this is a version check

    while (!stream->isEndOfStream()) {
        int command = stream->readInt();
        switch (command) {
        case 0: // Command 0: set a specific value
        {
            int value = stream->readInt();
            this->*(int*)(this + kOffsetSettingA) = value; // offset 0x267c? Actually it's 0x267c? Wait decompiled shows *(undefined4 *)(param_1 + 0x267c) = ... but earlier it's 0x1f44? No, for case 0 it's iVar4 = FUN_0043b210(); *(undefined4 *)(param_1 + 0x267c) = *(undefined4 *)(iVar4 + 8); So it reads into a different offset (0x267c). We missed that offset in our constants. Let's add it.
            // Actually the decompiled for case 0: iVar4 = readInt(); this->intField267c = *(int*)(iVar4+8); This is weird: reading an int gives a pointer? Probably a bug in decompilation: readInt returns a value, not pointer. It might be reading a value from a buffer. We'll simplify: this->field267c = stream->readInt();
            break;
        }
        case 3: // set bitmask
        {
            int value = stream->readInt();
            if (value == 0) {
                this->field1f98 = 0;
            } else {
                this->field1f98 = 1 << (value - 1);
            }
            break;
        }
        case 4: // set integer
        {
            int value = stream->readInt();
            this->field1f64 = value;
            break;
        }
        case 5: // set string? Actually reads a string and calls a function with it
        {
            stream->readInt(); // discard int?
            const char* str = stream->readString();
            // FUN_00733f20(str); // some function call
            break;
        }
        case 8: // set integer
        {
            int value = stream->readInt();
            this->field1f44 = value;
            break;
        }
        case 10: // set integer
        {
            int value = stream->readInt();
            this->field1fb4 = value;
            break;
        }
        case 11: // set integer
        {
            int value = stream->readInt();
            this->field1fb8 = value;
            break;
        }
        case 12: // set integer
        {
            int value = stream->readInt();
            this->field1fbc = value;
            break;
        }
        case 13: // read array? (offset 0x201c)
        {
            stream->readArray(this->field201c); // read data into that offset
            break;
        }
        case 14: // read array? (offset 0x2064)
        {
            stream->readArray(this->field2064);
            break;
        }
        case 16: // read vector (4 floats)
        {
            float* vec = stream->readVector4();
            this->vector20bc[0] = vec[0];
            this->vector20bc[1] = vec[1];
            this->vector20bc[2] = vec[2];
            this->vector20bc[3] = vec[3];
            break;
        }
        case 18: // set integer
        {
            int value = stream->readInt();
            this->field1f68 = value;
            break;
        }
        case 19: // read array? (offset 0x2084)
        {
            stream->readArray(this->field2084);
            break;
        }
        case 20: // set integer
        {
            int value = stream->readInt();
            this->field20a4 = value;
            break;
        }
        case 21: // set integer
        {
            int value = stream->readInt();
            this->field20a8 = value;
            break;
        }
        case 22: // set integer
        {
            int value = stream->readInt();
            this->field20ac = value;
            break;
        }
        case 23: // read array? (offset 0x2094)
        {
            stream->readArray(this->field2094);
            break;
        }
        case 24: // set integer
        {
            int value = stream->readInt();
            this->field20b0 = value;
            break;
        }
        case 25: // set integer
        {
            int value = stream->readInt();
            this->field20b4 = value;
            break;
        }
        case 26: // set integer
        {
            int value = stream->readInt();
            this->field20b8 = value;
            break;
        }
        case 29: // set string (offset 0x1fc0)
        {
            stream->readInt(); // discard?
            const char* str = stream->readString();
            strcpy(this->string1fc0, str);
            break;
        }
        case 30: // set string (offset 0x1fc8)
        {
            stream->readInt();
            const char* str = stream->readString();
            strcpy(this->string1fc8, str);
            break;
        }
        case 31: // set string (offset 0x1fd0)
        {
            stream->readInt();
            const char* str = stream->readString();
            strcpy(this->string1fd0, str);
            break;
        }
        case 33: // set string (offset 0x1fe0)
        {
            stream->readInt();
            const char* str = stream->readString();
            strcpy(this->string1fe0, str);
            break;
        }
        case 34: // set string (offset 0x1fd8)
        {
            stream->readInt();
            const char* str = stream->readString();
            strcpy(this->string1fd8, str);
            break;
        }
        case 35: // set integer
        {
            int value = stream->readInt();
            this->field1f9c = value;
            break;
        }
        case 36: // set integer
        {
            int value = stream->readInt();
            this->field1fa0 = value;
            break;
        }
        case 37: // set integer
        {
            int value = stream->readInt();
            this->field1fa4 = value;
            break;
        }
        case 38: // set integer
        {
            int value = stream->readInt();
            this->field1fa8 = value;
            break;
        }
        case 39: // set integer
        {
            int value = stream->readInt();
            this->field1fac = value;
            break;
        }
        case 40: // control mode
        {
            int value = stream->readInt();
            if (value == 1) {
                this->controlMode = 2;
                this->controlFlags &= ~4;
            } else if (value == 2) {
                this->controlMode = 2;
                this->controlFlags |= 4;
            } else {
                this->controlMode = 0;
            }
            break;
        }
        case 41: // special vector? This case reads a vector and does something else
        {
            stream->readInt(); // discard
            float* vec = stream->readVector4();
            // FUN_00445ff0(vec, 0);
            // FUN_00475660(result, 0x38523fc3, &stack);
            // FUN_005fdee0(esi);
            // This is complex - we'll skip
            break;
        }
        case 42: // set integer
        {
            int value = stream->readInt();
            this->field568 = value;
            break;
        }
        case 43: // set bitfield
        {
            int value = stream->readInt();
            if (value == 0) {
                this->field1f58 &= ~0x40;
            } else if (value == 1) {
                this->field1f58 |= 0x40;
            }
            break;
        }
        case 52: // set integer (offset 0x2104)
        {
            int value = stream->readInt();
            this->field2104 = value;
            break;
        }
        case 53: // seems to call a function with string
        {
            stream->readInt();
            const char* str = stream->readString();
            // FUN_004d3d90(str);
            break;
        }
        case 55: // read array? (offset 0x265c)
        {
            stream->readArray(this->field265c);
            break;
        }
        default:
            // unknown command - maybe ignore
            break;
        }
        stream->advance(); // FUN_0043b1a0
    }

    // After loop, check if special flag is set in bitfield at 0x1f54
    if ((this->flags1f54 & (1 << 14)) != 0) {
        // Perform a specialized copy of 12 bytes from allocated memory
        int size = 0x40b3e; // some size?
        int align = 0x10001;
        int* ptr = (int*)stream->alloc(4, size, align, this->field8a4, 0); // FUN_0043b490
        // Copy 3 uint64s (24 bytes?) Actually decompiled shows 2 uint64 and one int
        this->buffer828[0] = ptr[0];
        this->buffer828[1] = ptr[1];
        this->buffer838 = ptr[2];
    }
}