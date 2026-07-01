// FUNC_NAME: ControllerSlot::assign
// 0x00807950 - Copies a 0x44-byte slot structure representing XInput controller state
// Layout matches a custom EA structure: 4 dwords, 1 qword, 1 dword, 1 qword, 8 dwords = 68 bytes
struct ControllerSlot {
    int32_t field0;     // +0x00
    int32_t field1;     // +0x04
    int32_t field2;     // +0x08
    int32_t field3;     // +0x0C
    uint64_t field4_5;  // +0x10 (fields 4 and 5 combined)
    int32_t field6;     // +0x18
    uint64_t field7_8;  // +0x1C (fields 7 and 8 combined)
    int32_t field9;     // +0x24
    int32_t field10;    // +0x28
    int32_t field11;    // +0x2C
    int32_t field12;    // +0x30
    int32_t field13;    // +0x34
    int32_t field14;    // +0x38
    int32_t field15;    // +0x3C
    int32_t field16;    // +0x40
};

void __thiscall ControllerSlot::assign(ControllerSlot* this, const ControllerSlot* other)
{
    this->field0 = other->field0;
    this->field1 = other->field1;
    this->field2 = other->field2;
    this->field3 = other->field3;
    this->field4_5 = other->field4_5;
    this->field6 = other->field6;
    this->field7_8 = other->field7_8;
    this->field9 = other->field9;
    this->field10 = other->field10;
    this->field11 = other->field11;
    this->field12 = other->field12;
    this->field13 = other->field13;
    this->field14 = other->field14;
    this->field15 = other->field15;
    this->field16 = other->field16;
}