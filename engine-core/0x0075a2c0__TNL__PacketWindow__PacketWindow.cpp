// FUNC_NAME: TNL::PacketWindow::PacketWindow

class TNL::PacketWindow : public TNL::Object
{
public:
    // +0x00: vtable pointer (TNL::PacketWindow vtable)
    void* m_vtable;
    // +0x48: pointer to some buffer base? (index 0x12)
    char* m_pSomeBuffer;
    // +0x50: pointer to the start of a data window (index 0x14)
    char* m_pWindowStart;
    // +0x54: (index 0x15)
    int m_field15;
    // +0x58: (index 0x16)
    int m_field16;
    // +0x5C: (index 0x17)
    int m_field17;
    // +0x60: (index 0x18)
    int m_field18;
    // +0x64: (index 0x19)
    int m_field19;
    // +0x68: (index 0x1A)
    int m_field1A;
    // +0x6C: pointer to end of data window? (index 0x1B)
    char* m_pWindowEnd;
    // +0x70: (index 0x1C)
    int m_field1C;
    // +0x74: (index 0x1D)
    int m_field1D;
    // +0x78: (index 0x1E)
    int m_field1E;
    // +0x7C: (index 0x1F)
    int m_field1F;
    // +0x80: (index 0x20)
    int m_field20;
    // +0x84: (index 0x21)
    int m_field21;
    // +0x88: (index 0x22)
    int m_field22;
    // +0x8C: (index 0x23)
    int m_field23;
    // +0x90: (index 0x24)
    int m_field24;
    // +0x94: (index 0x25) byte
    uint8_t m_byte25;
    // +0x98: (index 0x26)
    int m_field26;
    // +0x9C: (index 0x27)
    int m_field27;
    // +0xA0: (index 0x28)
    int m_field28;
    // +0xA4: (index 0x29)
    int m_field29;
    // +0xA8: (index 0x2A)
    int m_field2A;
    // ... (size at least 0xAC)
};

// Base constructor at 0x004ac120 (assumed TNL::Object constructor with two args)
void __thiscall TNL::Object::Object(void* arg1, void* arg2);

void* __thiscall TNL::PacketWindow::PacketWindow(void* param2, void* param3)
{
    // Call base class constructor
    TNL::Object::Object(param2, param3);

    // Set vtable
    this->m_vtable = (void*)0x00d65070;  // PTR_LAB_00d65070 - PacketWindow vtable

    // Zero-initialize many fields
    this->m_field15 = 0;
    this->m_field16 = 0;
    this->m_field1A = 0;
    this->m_field1C = 0;
    this->m_field1D = 0;
    this->m_field1E = 0;
    this->m_field1F = 0;
    this->m_field20 = 0;
    this->m_field21 = 0;
    this->m_field22 = 0;
    this->m_field23 = 0;
    this->m_field24 = 0;
    this->m_byte25 = 0;
    this->m_field26 = 0;
    this->m_field2A = 0;

    // Compute pointer offsets from a stored buffer pointer
    int offset;
    if (this->m_pSomeBuffer != nullptr)
    {
        // Subtract 0x48 to get base of the window buffer
        offset = (int)this->m_pSomeBuffer - 0x48;
    }
    else
    {
        offset = 0;
    }

    // Window start and end (0x3C0 = 960 bytes = 32 * 30)
    this->m_pWindowStart = (char*)offset;
    this->m_pWindowEnd   = (char*)(offset + 0x3C0);

    // Zero-initialize more fields
    this->m_field19 = 0;
    this->m_field18 = 0;
    this->m_field17 = 0;
    this->m_field29 = 0;
    this->m_field28 = 0;
    this->m_field27 = 0;

    return this;
}