// FUNC_NAME: initCharacterSquareTable
// Address: 0x00659c80
// Role: Initializes a 256-byte lookup table with squared lowercase values for case-insensitive string processing.
// The table is used for obfuscation or hashing by converting uppercase to lowercase and storing the square.

#include <cstdint>

// External global table declared elsewhere, size 0x100 bytes
extern uint8_t g_characterSquareTable[0x100]; // DAT_01203640
extern uint8_t g_someFlag; // DAT_00f0ccb7

void __cdecl initCharacterSquareTable(void)
{
    uint32_t i = 0;
    do {
        char c = static_cast<char>(i);
        // Check if character is uppercase letter ('A'-'Z')
        if (static_cast<uint8_t>(c + 0xBFU) < 0x1A) {
            // Convert to lowercase by adding space (0x20)
            c = c + ' ';
        }
        // Store the square of the (possibly converted) character as a byte
        g_characterSquareTable[i] = static_cast<uint8_t>(c * c);
        i++;
    } while (i < 0x100);
    g_someFlag = 0;
}