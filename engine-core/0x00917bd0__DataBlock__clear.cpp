// FUNC_NAME: DataBlock::clear
// Address: 0x00917bd0
// Role: Initializes a DataBlock object by zeroing most of its fields (offsets 0x00–0x28), skipping offset 0x10.
// Called from constructor at 0x0091aee0.

void __thiscall DataBlock::clear(DataBlock* this) {
    this->field_0 = 0;          // +0x00
    this->field_4 = 0;          // +0x04
    this->field_8 = 0;          // +0x08
    this->field_C = 0;          // +0x0C
    // offset 0x10 (field_10) is intentionally left unchanged — likely a pointer set elsewhere
    this->field_14 = 0;         // +0x14
    this->field_18 = 0;         // +0x18
    this->field_1C = 0;         // +0x1C
    this->field_20 = 0;         // +0x20
    this->field_24 = 0;         // +0x24
    this->field_28 = 0;         // +0x28
}