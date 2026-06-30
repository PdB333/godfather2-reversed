// FUNC_NAME: NetPacketHeader::init
// Address: 0x005dbdf0
// Initializes a network packet header structure with magic numbers, version, and size.

// External globals (likely set from other initialization code)
extern unsigned int g_netMagic1;   // DAT_00e2eff4
extern unsigned int g_netMagic2;   // DAT_00e2b1a4

struct NetPacketHeader {
    unsigned int m_unk0;          // +0x00
    unsigned int m_unk4;          // +0x04
    unsigned int m_unk8;          // +0x08
    unsigned int m_version;       // +0x0C
    unsigned int m_unk10;         // +0x10
    unsigned int m_zero1;         // +0x14
    unsigned int m_zero2;         // +0x18
    unsigned int m_flag;          // +0x1C (set to 1)
    unsigned int m_sig1;          // +0x20 (0xBADBADBA)
    unsigned int m_sig2;          // +0x24 (0xBEEFBEEF)
    unsigned int m_sig3;          // +0x28 (0xEAC15A55)
    unsigned int m_sig4;          // +0x2C (0x91100911)
    unsigned char m_pad;          // +0x30 (byte, set to 0)
    // implicit padding to align m_packetSize
    unsigned int m_packetSize;    // +0x34 (set to 96000)
};

void __thiscall NetPacketHeader::init(void) {
    // Decompiled order retained; first assignments to m_sig1/m_sig2 are likely
    // a compiler artifact and are repeated later.
    m_sig1 = 0xBADBADBA;
    m_sig2 = 0xBEEFBEEF;
    m_unk0 = g_netMagic1;
    m_unk4 = g_netMagic1;
    m_unk8 = g_netMagic1;
    m_version = g_netMagic2;
    m_unk10 = g_netMagic2;
    m_zero1 = 0;
    m_zero2 = 0;
    m_packetSize = 96000;
    m_flag = 1;
    m_sig1 = 0xBADBADBA;
    m_sig2 = 0xBEEFBEEF;
    m_sig3 = 0xEAC15A55;
    m_sig4 = 0x91100911;
    m_pad = 0;  // byte at offset 0x30
}