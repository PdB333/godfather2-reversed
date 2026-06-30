// Xbox PDB: EARS::Common::guidstr_t::Set
// FUNC_NAME: HexDisplay::HexDisplay
class HexDisplay {
public:
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: initialization flag or state
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xC;
};

// Global string constant (likely "\r\n" or similar)
extern const char g_logNewlineString[32];

// Forward declarations of engine print functions
void printChar(char c);
void printString(const char *str, int param2, int param3, int param4);

int __thiscall HexDisplay::HexDisplay(uint hexValue) {
    int i;

    // Print 8 hex digits (32-bit value as 8 hex characters)
    for (i = 8; i > 0; i--) {
        char digit = "0123456789ABCDEF"[hexValue & 0xF];
        printChar(digit);
        hexValue >>= 4;
    }

    // Initialize field at offset +0xC to 0
    this->field_0xC = 0;

    // Output a newline or flush to the log stream
    printString(g_logNewlineString, 2, 0, 0);

    return (int)this;
}