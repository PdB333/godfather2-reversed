// FUNC_NAME: CStringTable::RegisterStringFromUnicode

#include <cstdint>

// Class representing the game's string table (likely for networking or resource hashing)
class CStringTable {
public:
    // Registers a string from a Unicode (UTF-16) source, converting to ASCII and hashing.
    // Returns a handle/index to the registered string.
    // @param unicodeSource: Pointer to the Unicode string (16-bit per char) to register.
    //                     The string is expected to be null-terminated and at most 64 characters.
    // @return: Handle to the registered string (likely a 32-bit hash or index).
    uint32_t RegisterStringFromUnicode(const uint16_t* unicodeSource);

private:
    // Internal: retrieves the string table singleton or context from a global offset.
    static void* GetStringTableInstance(uint32_t contextId);

    // Converts a Unicode string to ASCII (copying low bytes) into a fixed-size buffer.
    static void ConvertUnicodeToAscii(const uint16_t* src, char* dst, uint32_t maxLen);

    // Hashes an ASCII string and registers it in the table.
    uint32_t HashAndRegister(const char* asciiString, uint32_t flags, void* context);
};

// Implementation based on decompiled function at 0x005cf2d0
void __fastcall CStringTable::RegisterStringFromUnicode(uint32_t contextId) // param_1 is contextId? Actually param_1 is likely 'this'? But signature shows one param. We'll treat as method with this.
{
    // Global address with offset 0xc used to get some manager/singleton
    // DAT_01205668 + 0xc points to a string table context object?
    void* stringTableContext = *(void**)(*(uint32_t*)0x01205668 + 0xc);

    // Retrieve instance (maybe a singleton manager)
    void* instance = FUN_00670250(stringTableContext, contextId); // Returns some object

    // Buffer for Unicode string (128 bytes = 64 wide chars)
    uint16_t unicodeBuffer[64]; // local_80
    FUN_00670490(unicodeBuffer); // Fills unicodeBuffer with a Unicode string from some source

    // Convert Unicode to ASCII by taking low byte of each 16-bit character
    char asciiBuffer[64]; // local_c0
    for (int32_t i = 0; i < 64; i++) {
        asciiBuffer[i] = (char)(unicodeBuffer[i] & 0xFF);
    }

    // Register the ASCII string with flag=1
    FUN_005ce110(asciiBuffer, 1, instance);
}