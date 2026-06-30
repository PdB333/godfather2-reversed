// FUNC_NAME: UIElementColor::InitDefault
class UIElementColor {
public:
    uint32_t field_0x00; // +0x00: likely R or X
    uint32_t field_0x04; // +0x04: likely G or Y
    uint32_t field_0x08; // +0x08: likely B or Width
    uint32_t field_0x0C; // +0x0C: likely A or Height (same as blue)
    uint32_t field_0x10; // +0x10: padding/flag
    uint32_t field_0x14; // +0x14: padding/flag
    uint32_t field_0x18; // +0x18: padding/flag
    uint32_t field_0x1C; // +0x1C: padding/flag
    uint32_t field_0x20; // +0x20: padding/flag
};

// Initializes the color/state from global constants
void __thiscall UIElementColor::InitDefault() {
    this->field_0x00 = DAT_00d5e288;      // global constant
    this->field_0x04 = _DAT_00d5780c;     // global constant
    uint32_t uVar1 = _DAT_00d5cf70;       // global constant
    this->field_0x08 = uVar1;             // set blue/width
    this->field_0x0C = uVar1;             // set alpha/height (same as blue)
    this->field_0x1C = 0;                 // clear field[7]
    this->field_0x18 = 0;                 // clear field[6]
    this->field_0x14 = 0;                 // clear field[5]
    this->field_0x10 = 0;                 // clear field[4]
    this->field_0x20 = 0;                 // clear field[8]
}