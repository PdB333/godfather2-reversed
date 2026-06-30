// FUNC_NAME: NetPacketBuffer::NetPacketBuffer
// Constructor for a network packet buffer class (EARS/TNL networking layer)
// Initializes a large structure with packet management fields, buffer, and function callbacks.
// Address: 0x00643f20

class NetPacketBuffer {
public:
    // +0x00: Flags or state byte
    byte flags;
    // +0x04: Some integer count
    int32_t count;
    // +0x08: Double word pairs for timing/counters
    int64_t field_08;
    int64_t field_10;
    int64_t field_18;
    int64_t field_20;
    int64_t field_28;
    // +0x30: Main data buffer (0x400 bytes) – e.g., outgoing packet payload
    char dataBuffer[0x400];
    // +0x430: Additional 64-bit fields
    int64_t field_430;
    int64_t field_438;
    // +0x440: 32-bit fields
    int32_t field_440;
    int32_t field_444;
    int64_t field_448;
    int64_t field_450;
    int64_t field_458;
    int64_t field_460;
    // +0x468: Another 32-bit
    int32_t field_468;
    // +0x46c: Booleans/byte flags
    byte unk_46c;
    byte enableFlag;       // +0x46d: set to 1
    // +0x470:
    int32_t field_470;
    byte typeA;            // +0x474: set to 9
    byte typeB;            // +0x475: set to 10
    // +0x478: More ints
    int32_t field_478;
    int32_t field_47c;
    int32_t field_480;
    byte field_484;
    int32_t field_488;
    int32_t field_48c;
    int32_t field_490;
    int32_t field_494;
    byte field_498;
    int64_t field_49c[2];  // +0x49c / +0x4a4
    // +0x4ac: Parameters for data sizes
    int32_t field_4ac;
    int32_t field_4b0;
    int32_t maxPayloadSize; // +0x4b4: set to 0x100
    // +0x4b8: Function pointer (likely vtable or callback)
    void* pfnCallback1;
    // +0x4bc: Self pointer for thunk
    NetPacketBuffer* selfCallback1;
    // +0x4c0: Another function pointer
    void* pfnCallback2;
    // +0x4c4: Self pointer for thunk
    NetPacketBuffer* selfCallback2;
    // +0x4c8: More counters
    int32_t field_4c8;
    int32_t field_4cc;
    int32_t field_4d0;
    // +0x4d4: Buffer sizes
    int32_t bufferSize1;    // 0x1000
    int32_t bufferSize2;    // 0x1000
    // +0x4dc: Large numbers
    int32_t maxSegmentSize; // 0x1000000
    int32_t maxPacketSize;  // 0x400000
    // +0x4e4: byte flag
    byte field_4e4;
    int32_t field_4e8;
    // +0x4f0: More fields
    int64_t field_4f0[2];
    int64_t field_500[2];
    // +0x510: Magic signature bytes (0xdd,0xde,0xcd,0xab,0xfe)
    byte magicSignature[5];
    // +0x518: Another int
    int32_t field_518;
    // +0x51c: Byte flag
    byte field_51c;

    // Constructor
    __thiscall NetPacketBuffer(void* param_2, void* param_3, void* param_4,
                                void* param_5, void* param_6, void* param_7) {
        // Clear header fields
        flags = 0;
        count = 0;
        field_08 = 0;
        field_10 = 0;
        field_18 = 0;
        field_20 = 0;
        field_28 = 0;

        // Clear main data buffer
        _memset(&dataBuffer, 0, 0x400);

        // Clear extended fields
        field_430 = 0;
        field_438 = 0;
        field_440 = 0;
        field_444 = 0;
        field_448 = 0;
        field_450 = 0;
        field_458 = 0;
        field_460 = 0;
        field_468 = 0;
        unk_46c = 0;
        enableFlag = 1;
        field_470 = 0;
        typeA = 9;
        typeB = 10;
        field_478 = 0;
        field_47c = 0;
        field_480 = 0;
        field_484 = 0;
        field_488 = 0;
        field_48c = 0;
        field_490 = 0;
        field_494 = 0;
        field_498 = 0;
        field_49c[0] = 0;
        field_49c[1] = 0;
        field_4ac = 0;
        field_4b0 = 0;
        maxPayloadSize = 0x100;

        // Set up callbacks (function pointers)
        pfnCallback1 = (void*)0x006458f0; // vtable or callback address
        selfCallback1 = this;
        pfnCallback2 = (void*)0x0064ac80;
        selfCallback2 = this;

        field_4c8 = 0;
        field_4cc = 0;
        field_4d0 = 0;
        bufferSize1 = 0x1000;
        bufferSize2 = 0x1000;
        maxSegmentSize = 0x1000000;
        maxPacketSize = 0x400000;
        field_4e4 = 0;
        field_4e8 = 0;
        field_4f0[0] = 0;
        field_4f0[1] = 0;
        field_500[0] = 0;
        field_500[1] = 0;

        // Set magic signature
        magicSignature[0] = 0xdd;
        magicSignature[1] = 0xde;
        magicSignature[2] = 0xcd;
        magicSignature[3] = 0xab;
        magicSignature[4] = 0xfe;

        field_518 = 0;
        field_51c = 0;

        // Call additional initialization (likely base class or shared setup)
        FUN_00644120(param_2, param_3, param_4, param_5, param_6, param_7);
    }
};