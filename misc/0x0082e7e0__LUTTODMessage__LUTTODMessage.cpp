// FUNC_NAME: LUTTODMessage::LUTTODMessage
// Constructor for LUTTODMessage class (network message type)
// Address: 0x0082e7e0
// Initializes vtable pointers, allocates data buffer, registers message type

class LUTTODMessage : public BaseMessage {
public:
    // Vtable pointers (multiple inheritance)
    void* m_vtable;          // +0x00
    int m_field4;            // +0x04
    int m_field8;            // +0x08
    int m_fieldC;            // +0x0C
    int m_field10;           // +0x10
    int m_field14;           // +0x14
    int m_field18;           // +0x18
    int m_field1C;           // +0x1C
    uint8_t m_flag;          // +0x20 (byte)
    int m_sequence;          // +0x24
    void* m_interfaceVtable; // +0x30 (second vtable)
    // ... padding ...
    int m_field7C;           // +0x7C
    int m_field80;           // +0x80
    int m_field84;           // +0x84
    int m_field88;           // +0x88
    int m_field8C;           // +0x8C
    int m_field90;           // +0x90
    int m_globalValue;       // +0x94
    void* m_thirdVtable;     // +0xA0 (third vtable)
    int m_fieldA4;           // +0xA4
    uint8_t* m_buffer;       // +0xA8 (allocated 0x40 bytes)
    int m_bufferOffset;      // +0xAC
    int m_bufferSize;        // +0xB0 (initialized to 0x10)
};

LUTTODMessage* __fastcall LUTTODMessage::LUTTODMessage(LUTTODMessage* this) {
    // Initialize base class fields
    this->m_field4 = 0;
    this->m_field8 = 0;
    this->m_fieldC = 0;
    this->m_field10 = 0;
    this->m_field14 = 0;
    this->m_field18 = 0;
    this->m_field1C = 0;
    this->m_flag = 1;
    this->m_vtable = &PTR_FUN_00d737b4; // Base vtable
    this->m_sequence = 1;

    // Call base class constructor
    FUN_008334a0(this); // BaseMessage::BaseMessage()

    // Set up interface vtable
    this->m_interfaceVtable = &PTR_FUN_00d7343c;

    // Zero out fields from 0x7C to 0x90
    this->m_field7C = 0;
    this->m_field80 = 0;
    this->m_field84 = 0;
    this->m_field88 = 0;
    this->m_field8C = 0;
    this->m_field90 = 0;

    // Set global value
    this->m_globalValue = _DAT_00d5780c;

    // Set third vtable
    this->m_thirdVtable = &PTR_FUN_00d737b0;
    this->m_fieldA4 = 0;

    // Allocate data buffer (64 bytes)
    this->m_buffer = (uint8_t*)FUN_009c8e80(0x40);
    this->m_bufferOffset = 0;
    this->m_bufferSize = 0x10;

    // Register message type with cleanup
    int local_10[3] = {0, 0, 0};
    code* cleanupFunc = nullptr;
    // This block is a try/finally for cleanup
    FUN_004d4ad0(local_10, &DAT_00e2f0b0, "LUTTODMessage", "Sequence");
    FUN_004d3e20(local_10);

    // Copy message name string
    const char* nameStr = (this->m_fieldC != 0) ? (const char*)this->m_fieldC : &DAT_0120546e;
    this->m_fieldC = FUN_004dafd0(nameStr);

    // Execute cleanup if needed
    if (local_10[0] != 0) {
        cleanupFunc(local_10[0]);
    }

    return this;
}