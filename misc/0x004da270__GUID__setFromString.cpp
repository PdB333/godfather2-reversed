// FUNC_NAME: GUID::setFromString
// Function address: 0x004da270
// Parses a GUID string (format "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX") into a 128-bit GUID.
// Returns 0 if the resulting GUID equals the default (empty) GUID, 1 otherwise.
// If input string is null or empty, sets to default GUID and returns 0.

#include <cstring>

// Magic numbers representing the default GUID (empty GUID)
const int GUID_DEFAULT_PART0 = 0xBABDBBBA;  // -0x45245246
const int GUID_DEFAULT_PART1 = 0xBEEFBEEF;  // -0x41104111
const int GUID_DEFAULT_PART2 = 0xEAC15A55;  // -0x153EA5AB
const int GUID_DEFAULT_PART3 = 0x91100911;  // -0x6EEFF6EF

// Forward declarations of internal helpers (from other functions)
void parseGuidString(const char* input);  // FUN_004da550 - validates/processes string
int* guidStringToInts(char* buffer);      // FUN_004da7e0 - converts string to 4 ints, may allocate
void freeGuidAllocation();                // FUN_004d8be0 - cleanup
void freeMemory(void* ptr);               // FUN_009c8eb0 - generic free

class GUID {
public:
    int parts[4];  // 128-bit GUID stored as four 32-bit integers

    // Sets this GUID from a string representation.
    // Returns 0 if the resulting GUID equals the default (empty) GUID, 1 otherwise.
    int setFromString(const char* str) {
        if (str == nullptr || *str == '\0') {
            // Empty string -> set to default GUID
            parts[0] = GUID_DEFAULT_PART0;
            parts[1] = GUID_DEFAULT_PART1;
            parts[2] = GUID_DEFAULT_PART2;
            parts[3] = GUID_DEFAULT_PART3;
            return 0;  // is default
        }

        int allocFlag = 0;  // local_c: tracks if allocation occurred
        char guidStringBuffer[36];  // local_30: buffer for GUID string (36 chars + null terminator?)

        parseGuidString(str);  // FUN_004da550 - likely copies/validates string into buffer
        int* parsedParts = guidStringToInts(guidStringBuffer);  // FUN_004da7e0 - returns pointer to 4 ints
        allocFlag = /* set by guidStringToInts? Actually local_c is set before call? */ 0; // In original, local_c is set to 0 initially, then after call it's used. We'll assume guidStringToInts may set it.

        // Copy parsed parts into this GUID
        parts[0] = parsedParts[0];
        parts[1] = parsedParts[1];
        parts[2] = parsedParts[2];
        parts[3] = parsedParts[3];

        int result;
        if (parts[0] == GUID_DEFAULT_PART0 &&
            parts[1] == GUID_DEFAULT_PART1 &&
            parts[2] == GUID_DEFAULT_PART2 &&
            parts[3] == GUID_DEFAULT_PART3) {
            result = 0;  // is default
        } else {
            result = 1;  // not default
        }

        if (allocFlag != 0) {
            freeGuidAllocation();  // FUN_004d8be0
            freeMemory((void*)allocFlag);  // FUN_009c8eb0 - note: allocFlag is used as pointer? Original uses iVar4 which is local_c after call.
        }

        return result;
    }
};