// FUNC_NAME: TextColorPair::constructor
// Function at 0x00498f80: Default constructor for a text color pair structure (32 bytes).
// Initializes two BGR color fields to yellow (0x00FFFF00) and zeros the rest.

struct TextColorPair {
    uint32_t m_unknown00; // +0x00
    uint32_t m_unknown04; // +0x04
    uint32_t m_color1;    // +0x08 (BGR format, default 0x00FFFF00)
    uint32_t m_unknown0C; // +0x0C
    uint32_t m_unknown10; // +0x10
    uint32_t m_unknown14; // +0x14
    uint32_t m_color2;    // +0x18 (BGR format, default 0x00FFFF00)
    uint32_t m_unknown1C; // +0x1C

    void __thiscall constructor();
};

void __thiscall TextColorPair::constructor() {
    m_unknown00 = 0;
    m_unknown04 = 0;
    m_color1 = 0xFFFF00;
    m_unknown0C = 0;
    m_unknown10 = 0;
    m_unknown14 = 0;
    m_color2 = 0xFFFF00;
    m_unknown1C = 0;
}