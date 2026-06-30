// FUNC_NAME: NetPacketHeader::copy
struct NetPacketHeader { // sizeof = 0x38 (56 bytes)
    int field0;    // +0x00
    int field1;    // +0x04
    int field2;    // +0x08
    int field3;    // +0x0C
    int field4;    // +0x10
    int field5;    // +0x14
    int field6;    // +0x18
    int field7;    // +0x1C
    int field8;    // +0x20
    int field9;    // +0x24
    int field10;   // +0x28
    int field11;   // +0x2C
    char flag;     // +0x30
    char pad[3];   // +0x31 padding to align next field
    int field12;   // +0x34
};

void __fastcall copyNetPacketHeader(NetPacketHeader *this, const NetPacketHeader *other)
{
    this->field0 = other->field0;
    this->field1 = other->field1;
    this->field2 = other->field2;
    this->field3 = other->field3;
    this->field4 = other->field4;
    this->field5 = other->field5;
    this->field6 = other->field6;
    this->field7 = other->field7;
    this->field8 = other->field8;
    this->field9 = other->field9;
    this->field10 = other->field10;
    this->field11 = other->field11;
    this->flag = other->flag;
    this->field12 = other->field12;
}