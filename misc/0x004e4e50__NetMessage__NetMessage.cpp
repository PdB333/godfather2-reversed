// FUNC_NAME: NetMessage::NetMessage
void __thiscall NetMessage::NetMessage(int param_1, int param_2, int param_3, short param_4, unsigned char param_5, int param_6, int param_7, int param_8)
{
    // Set vtable pointer (+0x00)
    this->vtable = (void*)0x00e371d8;

    // Store parameters into fields
    this->field_0x04 = param_1;                  // +0x04
    this->field_0x08 = param_7;                  // +0x08
    this->field_0x0C = param_8;                  // +0x0C
    this->field_0x18 = param_3;                  // +0x18
    *(unsigned char*)((uintptr_t)this + 0x1E) = param_5; // +0x1E (byte)
    *(short*)((uintptr_t)this + 0x1C) = param_4; // +0x1C (short)
    this->field_0x24 = param_2;                  // +0x24
    this->field_0x28 = param_6;                  // +0x28

    // Initialize control/status fields
    this->field_0x80 = 0xFFFFFFFF;               // +0x80
    this->field_0x84 = 0;                        // +0x84
    this->field_0x88 = 0;                        // +0x88
    this->field_0x8C = 0;                        // +0x8C
    this->field_0x10 = 0;                        // +0x10
    this->field_0x20 = 0;                        // +0x20
    this->field_0x90 = 0;                        // +0x90
    this->field_0x94 = 0;                        // +0x94
    *(unsigned char*)((uintptr_t)this + 0x98) = 0; // +0x98 (byte)

    // Clear a block of 20 dwords from +0x30 to +0x7C
    this->field_0x30 = 0;  // +0x30
    this->field_0x34 = 0;  // +0x34
    this->field_0x38 = 0;  // +0x38
    this->field_0x3C = 0;  // +0x3C
    this->field_0x40 = 0;  // +0x40
    this->field_0x44 = 0;  // +0x44
    this->field_0x48 = 0;  // +0x48
    this->field_0x4C = 0;  // +0x4C
    this->field_0x50 = 0;  // +0x50
    this->field_0x54 = 0;  // +0x54
    this->field_0x58 = 0;  // +0x58
    this->field_0x5C = 0;  // +0x5C
    this->field_0x60 = 0;  // +0x60
    this->field_0x64 = 0;  // +0x64
    this->field_0x68 = 0;  // +0x68
    this->field_0x6C = 0;  // +0x6C
    this->field_0x70 = 0;  // +0x70
    this->field_0x74 = 0;  // +0x74
    this->field_0x78 = 0;  // +0x78
    this->field_0x7C = 0;  // +0x7C
}