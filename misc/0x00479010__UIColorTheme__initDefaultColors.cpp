// FUNC_NAME: UIColorTheme::initDefaultColors
void UIColorTheme::initDefaultColors(int this) {
    // +0x70: flag indicating default theme initialized
    *(int *)(this + 0x70) = 1;

    // ===== First color palette (offsets 0xa4 to 0xb3) =====
    // Four 4-byte color entries (RGBA or ARGB? Values: R,G,B,A where A=0xff = opaque)
    // Colors: dark blue-ish, gray-blue, dark, very dark (pressed/disabled states?)
    *(char *)(this + 0xa4) = 0x48;  // R
    *(char *)(this + 0xa5) = 0x46;  // G
    *(char *)(this + 0xa6) = 0x56;  // B
    *(char *)(this + 0xa7) = 0xff;  // A
    *(char *)(this + 0xa8) = 0x62;
    *(char *)(this + 0xa9) = 0x77;
    *(char *)(this + 0xaa) = 0x88;
    *(char *)(this + 0xab) = 0xff;
    *(char *)(this + 0xac) = 0x32;
    *(char *)(this + 0xad) = 0x40;
    *(char *)(this + 0xae) = 0x59;
    *(char *)(this + 0xaf) = 0xff;
    *(char *)(this + 0xb0) = 0x23;
    *(char *)(this + 0xb1) = 0x2b;
    *(char *)(this + 0xb2) = 0x38;
    *(char *)(this + 0xb3) = 0xff;

    // ===== Integer palette parameters (offsets 0x74 to 0x90) =====
    // Probably border/shadow/glow colors, packed as 32-bit RGBA
    *(int *)(this + 0x74) = DAT_00e44700;       // color A
    *(int *)(this + 0x78) = DAT_00e446f4;       // color B
    *(int *)(this + 0x7c) = DAT_00e44700;       // color A again
    *(int *)(this + 0x80) = DAT_00e446f0;       // color C
    *(int *)(this + 0x84) = DAT_00e446fc;       // color D
    *(int *)(this + 0x88) = DAT_00e446ec;       // color E
    *(int *)(this + 0x8c) = DAT_00e446f8;       // color F
    *(int *)(this + 0x90) = DAT_00e446e4;       // color G

    // +0xc4: another flag (maybe for second UI element)
    *(int *)(this + 0xc4) = 1;

    // ===== Second color palette (offsets 0xf8 to 0x107) =====
    // Same four colors as first palette
    *(char *)(this + 0xf8) = 0x48;
    *(char *)(this + 0xf9) = 0x46;
    *(char *)(this + 0xfa) = 0x56;
    *(char *)(this + 0xfb) = 0xff;
    *(char *)(this + 0xfc) = 0x62;
    *(char *)(this + 0xfd) = 0x77;
    *(char *)(this + 0xfe) = 0x88;
    *(char *)(this + 0xff) = 0xff;
    *(char *)(this + 0x100) = 0x32;
    *(char *)(this + 0x101) = 0x40;
    *(char *)(this + 0x102) = 0x59;
    *(char *)(this + 0x103) = 0xff;
    *(char *)(this + 0x104) = 0x23;
    *(char *)(this + 0x105) = 0x2b;
    *(char *)(this + 0x106) = 0x38;
    *(char *)(this + 0x107) = 0xff;

    // ===== Integer palette parameters for second element (offsets 0xcc to 0xe4) =====
    // 7 entries (possible missing one at 0xc8?)
    *(int *)(this + 0xcc) = DAT_0110ae44;       // same as uVar2
    *(int *)(this + 0xd0) = DAT_0110ae44;
    *(int *)(this + 0xd4) = DAT_0110ae44;
    *(int *)(this + 0xd8) = DAT_00e446e8;       // same as uVar1
    *(int *)(this + 0xdc) = DAT_00e446e8;
    *(int *)(this + 0xe0) = DAT_00e446e8;
    *(int *)(this + 0xe4) = DAT_00e446e8;

    // +0x118: flag for third element
    *(int *)(this + 0x118) = 1;

    // ===== Third color palette (offsets 0x14c to 0x15b) =====
    *(char *)(this + 0x14c) = 0x48;
    *(char *)(this + 0x14d) = 0x46;
    *(char *)(this + 0x14e) = 0x56;
    *(char *)(this + 0x14f) = 0xff;
    *(char *)(this + 0x150) = 0x62;
    *(char *)(this + 0x151) = 0x77;
    *(char *)(this + 0x152) = 0x88;
    *(char *)(this + 0x153) = 0xff;
    *(char *)(this + 0x154) = 0x32;
    *(char *)(this + 0x155) = 0x40;
    *(char *)(this + 0x156) = 0x59;
    *(char *)(this + 0x157) = 0xff;
    *(char *)(this + 0x158) = 0x23;
    *(char *)(this + 0x159) = 0x2b;
    *(char *)(this + 0x15a) = 0x38;
    *(char *)(this + 0x15b) = 0xff;

    // ===== Integer palette parameters for third element (offsets 0x11c to 0x138) =====
    // 8 entries
    *(int *)(this + 0x11c) = DAT_0110ae44;
    *(int *)(this + 0x120) = DAT_0110ae44;
    *(int *)(this + 0x124) = DAT_0110ae44;
    *(int *)(this + 0x128) = DAT_0110ae44;
    *(int *)(this + 0x12c) = DAT_00e446e8;
    *(int *)(this + 0x130) = DAT_00e446e8;
    *(int *)(this + 0x134) = DAT_00e446e8;
    *(int *)(this + 0x138) = DAT_00e446e8;

    // These globals are read from game data (likely default color values):
    // DAT_00e44700 = color1 (0x??)
    // DAT_00e446f4 = color2
    // DAT_00e446f0 = color3
    // DAT_00e446fc = color4
    // DAT_00e446ec = color5
    // DAT_00e446f8 = color6
    // DAT_00e446e4 = color7
    // DAT_00e446e8 = color8
    // DAT_0110ae44 = color9
    return;
}