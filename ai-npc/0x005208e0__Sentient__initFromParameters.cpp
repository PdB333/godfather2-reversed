// FUNC_NAME: Sentient::initFromParameters
void __thiscall Sentient::initFromParameters(Sentient *this, int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, byte param_10, byte param_11, int param_12, int param_13, int param_14, int param_15, int param_16, byte param_17, byte param_18, int param_19, int param_20) {
    // Set vtable pointer (offset +0x00)
    this->vtable = &Sentient_vtable;

    // Parameters assigned to various member fields based on byte offsets
    this->field_0x120 = param_9;               // offset +0x120
    this->field_0x1F0 = param_12;              // offset +0x1F0
    this->field_0x1F4 = param_13;              // offset +0x1F4
    this->field_0x1F8 = param_14;              // offset +0x1F8
    this->field_0x1FC = param_15;              // offset +0x1FC
    this->field_0x200 = param_16;              // offset +0x200
    this->field_0x204 = param_3;               // offset +0x204
    this->field_0x210_byte = param_11;         // offset +0x210 (byte)
    this->field_0x211 = 1;                     // offset +0x211 (byte)
    this->field_0x212 = 0;                     // offset +0x212 (byte)
    this->field_0x213 = param_18;              // offset +0x213 (byte)
    this->field_0x214 = 0;                     // offset +0x214 (int)
    this->field_0x21C = param_19;              // offset +0x21C
    this->field_0x220 = param_20;              // offset +0x220
    this->field_0x230 = param_1;               // offset +0x230
    this->field_0x234 = param_2;               // offset +0x234
    this->field_0x23C = param_5;               // offset +0x23C
    this->field_0x240 = param_6;               // offset +0x240
    this->field_0x244 = param_7;               // offset +0x244
    this->field_0x248 = param_8;               // offset +0x248
    this->field_0x24C = param_4;               // offset +0x24C
    this->field_0x250_byte = param_10;         // offset +0x250 (byte)
    this->field_0x251_byte = param_17;         // offset +0x251 (byte)
}