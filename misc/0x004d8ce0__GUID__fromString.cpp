// FUNC_NAME: GUID::fromString
// Address: 0x004d8ce0
// Role: Parses a GUID from a string, with special handling for the null/invalid GUID.
// The null GUID string "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}" maps to a hardcoded binary value.

class GUID {
public:
    // GUID data as four 32-bit values (total 16 bytes)
    // Offsets: +0x00, +0x04, +0x08, +0x0C
    unsigned int data[4];

    // Sets this GUID from the given string representation.
    // Returns this pointer to allow chaining.
    // If the string is null or does not match the null GUID, delegates to the parser function.
    GUID* fromString(const char* str) {
        int cmpResult;

        if (str == nullptr) {
            cmpResult = 1; // treat null as not matching
        } else {
            cmpResult = __stricmp(str, "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}");
        }

        if (cmpResult != 0) {
            // Not the null GUID string – parse normally.
            parseGUIDString(str); // FUN_004d9500
            return this;
        }

        // Special null GUID: set to hardcoded binary representation.
        data[0] = 0xbadbadba;
        data[1] = 0xbeefbeef;
        data[2] = 0xeac15a55;
        data[3] = 0x91100911;
        return this;
    }

private:
    // Actual GUID parser from string (address 0x004d9500).
    // Assumes it fills data[0..3] based on the string.
    void parseGUIDString(const char* str);
};