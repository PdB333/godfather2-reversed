// FUNC_NAME: TNLConnection::TNLConnection
// Address: 0x00643f20 - TNLConnection constructor, initializes all fields and sets up callback pointers.

class TNLConnection {
public:
    TNLConnection(int param2, int param3, int param4, int param5, int param6, int param7);
private:
    // Offset 0x00
    uint8_t     m_field00;
    uint32_t    m_field04;
    uint64_t    m_field08;
    uint64_t    m_field10;
    uint64_t    m_field18;
    uint64_t    m_field20;
    uint64_t    m_field28;
    // Offset 0x30
    uint8_t     m_buffer[0x400];
    // Offset 0x430
    uint64_t    m_field430;
    uint64_t    m_field438;
    uint32_t    m_field440;
    uint32_t    m_field444;
    uint64_t    m_field448;
    uint64_t    m_field450;
    uint64_t    m_field458;
    uint64_t    m_field460;
    uint32_t    m_field468;
    uint8_t     m_byte46c;
    uint8_t     m_byte46d;
    uint32_t    m_field470;
    uint8_t     m_byte474;
    uint8_t     m_byte475;
    uint32_t    m_field478;
    uint32_t    m_field47c;
    uint32_t    m_field480;
    uint8_t     m_byte484;
    uint32_t    m_field488;
    uint32_t    m_field48c;
    uint32_t    m_field490;
    uint32_t    m_field494;
    uint8_t     m_byte498;
    uint64_t    m_field49c;
    uint64_t    m_field4a4;
    uint32_t    m_field4ac;
    uint32_t    m_field4b0;
    // Offset 0x4b4
    uint32_t    m_maxPacketSize;          // default 0x100
    // Offset 0x4b8: callback pair 1 (function + this)
    void        (*m_onReceiveFunc)(void*);
    void*       m_onReceiveThis;
    // Offset 0x4c0: callback pair 2
    void        (*m_onSendFunc)(void*);
    void*       m_onSendThis;
    uint32_t    m_field4c8;
    uint32_t    m_field4cc;
    uint32_t    m_field4d0;
    // Offset 0x4d4
    uint32_t    m_sendBufferSize;         // default 0x1000
    uint32_t    m_recvBufferSize;         // default 0x1000
    // Offset 0x4dc
    uint32_t    m_bandwidthLimit;         // default 0x1000000
    uint32_t    m_bandwidthCurrent;       // default 0x400000
    uint8_t     m_byte4e4;
    uint32_t    m_field4e8;
    uint64_t    m_field4f0;
    uint64_t    m_field4f8;
    uint64_t    m_field500;
    uint64_t    m_field508;
    // Offset 0x510
    uint8_t     m_magic[5];              // {0xdd, 0xde, 0xcd, 0xab, 0xfe}
    uint32_t    m_field518;
    uint8_t     m_byte51c;
};

TNLConnection::TNLConnection(int param2, int param3, int param4, int param5, int param6, int param7) {
    m_field00 = 0;
    m_field04 = 0;
    m_field08 = 0;
    m_field10 = 0;
    m_field18 = 0;
    m_field20 = 0;
    m_field28 = 0;
    memset(m_buffer, 0, sizeof(m_buffer));
    m_field430 = 0;
    m_field438 = 0;
    m_field440 = 0;
    m_field444 = 0;
    m_field448 = 0;
    m_field450 = 0;
    m_field458 = 0;
    m_field460 = 0;
    m_field468 = 0;
    m_byte46c = 0;
    m_byte46d = 1;
    m_field470 = 0;
    m_byte474 = 9;
    m_byte475 = 10;
    m_field478 = 0;
    m_field47c = 0;
    m_field480 = 0;
    m_byte484 = 0;
    m_field488 = 0;
    m_field48c = 0;
    m_field490 = 0;
    m_field494 = 0;
    m_byte498 = 0;
    m_field49c = 0;
    m_field4a4 = 0;
    m_field4ac = 0;
    m_field4b0 = 0;
    m_maxPacketSize = 0x100;          // 256
    m_field4c8 = 0;
    m_field4cc = 0;
    m_field4d0 = 0;
    m_sendBufferSize = 0x1000;        // 4096
    m_recvBufferSize = 0x1000;        // 4096
    m_bandwidthLimit = 0x1000000;     // 16777216
    m_bandwidthCurrent = 0x400000;    // 4194304
    m_byte4e4 = 0;
    m_field4e8 = 0;
    m_field4f0 = 0;
    m_field4f8 = 0;
    m_field500 = 0;
    m_field508 = 0;
    m_magic[0] = 0xdd;
    m_magic[1] = 0xde;
    m_magic[2] = 0xcd;
    m_magic[3] = 0xab;
    m_magic[4] = 0xfe;
    m_field518 = 0;
    m_byte51c = 0;

    // Set up callback function pointers to known handlers (addresses from game binary)
    m_onReceiveFunc = reinterpret_cast<void(*)(void*)>(0x006458f0);
    m_onReceiveThis = this;
    m_onSendFunc = reinterpret_cast<void(*)(void*)>(0x0064ac80);
    m_onSendThis = this;

    // Call base class constructor with the remaining parameters
    BaseTNLConnection::BaseTNLConnection(param2, param3, param4, param5, param6, param7);
}