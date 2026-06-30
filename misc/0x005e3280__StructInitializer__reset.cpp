// FUNC_NAME: StructInitializer::reset
// Address: 0x005e3280
// Role: Initializes a small 13-byte structure with default values.
// Likely used for a state/flag struct: first field=1 (active/true), others zero.

struct UnknownStruct {
    int field_00;  // +0x00: Set to 1 (likely boolean or state indicator)
    int field_04;  // +0x04: Zeroed
    int field_08;  // +0x08: Zeroed
    byte field_0C; // +0x0C: Zeroed (single byte)
};

void __fastcall UnknownStruct::reset(UnknownStruct* this) {
    this->field_00 = 1;
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
}
