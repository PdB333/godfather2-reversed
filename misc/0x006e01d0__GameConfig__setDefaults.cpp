// FUNC_NAME: GameConfig::setDefaults
void __fastcall GameConfig::setDefaults(GameConfig* this) {
    // Global default values (constants)
    // These are likely loaded from data or hardcoded defaults
    uint32_t default7 = DAT_00e445ac;      // gDefault7
    uint32_t default10 = DAT_00d5f6c0;     // gDefault10
    uint32_t default8 = DAT_00d5d740;      // gDefault8 (used for multiple fields)
    uint32_t default12 = _DAT_00d5cf70;    // gDefault12 (__underscore indicates alignment issue)
    uint32_t default0x28 = DAT_00d5f7ac;   // gDefault0x28
    uint32_t default0x2c = DAT_00d5f7a8;   // gDefault0x2c
    uint32_t default0x30 = DAT_00d5f7a4;   // gDefault0x30
    uint32_t default0x34 = DAT_00d5f7a0;   // gDefault0x34
    uint32_t default0x38 = DAT_00d5f18c;   // gDefault0x38
    uint32_t default0x3c = DAT_00d5f37c;   // gDefault0x3c
    uint32_t default0x40 = DAT_00d5efa8;   // gDefault0x40
    uint32_t default0x44 = DAT_00d5efa4;   // gDefault0x44
    uint32_t default0x48 = DAT_00d5ef90;   // gDefault0x48
    uint32_t default0x4c = DAT_00d5ef70;   // gDefault0x4c
    uint32_t default0x50 = DAT_00d5d7b8;   // gDefault0x50
    uint32_t default0x54 = DAT_00d5f79c;   // gDefault0x54
    uint32_t default0x58 = DAT_00d5779c;   // gDefault0x58
    uint32_t default0x5c = DAT_00d5efd0;   // gDefault0x5c
    uint32_t default0x60 = _DAT_00d5c458;  // gDefault0x60
    uint32_t default0x64 = DAT_00d5eee4;   // gDefault0x64
    uint32_t default0x68 = _DAT_00d5780c;  // gDefault0x68
    uint32_t default0x6c = DAT_00e44618;   // gDefault0x6c
    uint32_t default0x70 = DAT_00d5c454;   // gDefault0x70

    // Field assignments (offset index into 4-byte words)
    // Offsets: index * 4 = byte offset
    this->field_0x00 = 0;                   // [0] = 0
    this->field_0x04 = 0;                   // [1] = 0
    *(uint8_t*)(&this->field_0x08) = 0;    // [2] low byte = 0 (partial zero)
    *(uint8_t*)(&this->field_0x18) = 0;    // [6] low byte = 0 (partial zero)
    this->field_0x1c = default7;            // [7] = DAT_00e445ac
    this->field_0x20 = default8;            // [8] = DAT_00d5d740
    this->field_0x24 = default8;            // [9] = DAT_00d5d740
    this->field_0x28 = default0x28;         // [10]= DAT_00d5f7ac
    this->field_0x2c = default0x2c;         // [11]= DAT_00d5f7a8
    this->field_0x30 = default0x30;         // [12]= DAT_00d5f7a4
    this->field_0x34 = default0x34;         // [13]= DAT_00d5f7a0
    this->field_0x38 = default0x38;         // [14]= DAT_00d5f18c
    this->field_0x3c = default0x40;         // [15]= DAT_00d5efa8
    this->field_0x40 = default10;           // [16]= DAT_00d5f6c0
    this->field_0x44 = default0x48;         // [17]= DAT_00d5ef90
    this->field_0x48 = default12;           // [18]= _DAT_00d5cf70
    this->field_0x4c = default12;           // [19]= _DAT_00d5cf70
    this->field_0x50 = default0x50;         // [20]= DAT_00d5d7b8
    this->field_0x54 = default8;            // [21]= DAT_00d5d740
    this->field_0x58 = default0x58;         // [22]= DAT_00d5779c
    this->field_0x5c = default8;            // [23]= DAT_00d5d740
    this->field_0x60 = default0x58;         // [24]= DAT_00d5779c
    this->field_0x64 = default0x58;         // [25]= DAT_00d5779c
    this->field_0x68 = 0;                   // [26]= 0
    this->field_0x6c = default0x3c;         // [27]= DAT_00d5f37c
    this->field_0x70 = default10;           // [28]= DAT_00d5f6c0
    this->field_0x74 = default0x54;         // [29]= DAT_00d5f79c
    this->field_0x78 = default0x60;         // [30]= _DAT_00d5c458
    this->field_0x7c = default0x5c;         // [31]= DAT_00d5efd0
    this->field_0x80 = default0x5c;         // [32]= DAT_00d5efd0
    this->field_0x84 = default12;           // [33]= _DAT_00d5cf70
    this->field_0x88 = default0x60;         // [34]= _DAT_00d5c458
    this->field_0x8c = default0x58;         // [35]= DAT_00d5779c
    this->field_0x90 = default0x68;         // [36]= _DAT_00d5780c
    this->field_0x94 = default0x58;         // [37]= DAT_00d5779c
    this->field_0x98 = default0x60;         // [38]= _DAT_00d5c458
    this->field_0x9c = default0x60;         // [39]= _DAT_00d5c458
    this->field_0xa0 = default0x60;         // [40]= _DAT_00d5c458
    this->field_0xa4 = default0x60;         // [41]= _DAT_00d5c458
    this->field_0xa8 = default0x6c;         // [42]= DAT_00e44618
    this->field_0xac = default0x60;         // [43]= _DAT_00d5c458
    this->field_0xb0 = default0x60;         // [44]= _DAT_00d5c458
    this->field_0xb4 = default0x58;         // [45]= DAT_00d5779c
    this->field_0xb8 = default0x60;         // [46]= _DAT_00d5c458
    this->field_0xbc = default0x60;         // [47]= _DAT_00d5c458
}