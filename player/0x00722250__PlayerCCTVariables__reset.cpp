// FUNC_NAME: PlayerCCTVariables::reset
class PlayerCCTVariables {
public:
    int m_field0;       // +0x00
    char m_field1;      // +0x04
    int m_field2;       // +0x08
    int m_field3;       // +0x0C
    int m_field4;       // +0x10
    int m_field5;       // +0x14
    int m_field6;       // +0x18
    int m_field7;       // +0x1C
    int m_field8;       // +0x20
    int m_field9;       // +0x24
};

extern int g_globalVar;  // _DAT_00d5780c, likely a singleton pointer or constant

void __fastcall PlayerCCTVariables::reset() {
    m_field0 = 0;
    m_field1 = 0;  // single byte at offset 4
    m_field2 = 0;
    m_field3 = g_globalVar;  // copy global value
    m_field4 = 0;
    m_field5 = 0;
    m_field6 = 0;
    m_field7 = 0;
    m_field8 = 0;
    m_field9 = 0;
}