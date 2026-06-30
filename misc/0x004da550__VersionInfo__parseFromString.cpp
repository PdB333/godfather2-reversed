// FUNC_NAME: VersionInfo::parseFromString
// Function at 0x004da550: Parses a version string in format "xxxxxxxx_xxxx_v3" or "xxxxxxxx_xxxx_v3/extra"
// Member fields: 
//   +0x00: char name[10]  (9 chars + null)
//   +0x0A: padding? (unused)
//   +0x0C: uint32 version1  (encoded as 7 nibbles: 24 bits + 7*4? Actually 7 calls for 28 bits? Let's see: 7 nibble shifts: <<24, <<20, <<16, <<12, <<8, <<4, then <<0 -> 28 bits, but stored as uint32)
//   +0x10: uint32 version2  (same pattern, 7 nibbles)
//   +0x14: char* extraData  (pointer to string after "/")
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Forward declarations of external functions
extern void cleanupObject(int flag);  // FUN_004d8c70
extern void freeMemory(void* ptr);    // FUN_009c8eb0
extern int parseHexNibble();          // FUN_004d9d20 - reads next hex nibble from input? Actually this function likely reads a single hex digit from a global stream or from the string. But in this function it's called repeatedly, so we assume it parses the next hex digit from the string being processed. We'll redefine it.
extern void* allocateMemory(size_t size); // FUN_009c8e50 - wrapper for malloc
extern char* copyString(const char* src); // FUN_004d8c00 - strdup-like

// Redefine parseHexNibble to depend on current position in the string.
// Since we don't have global state, we'll implement it inline.
class VersionInfo {
public:
    char name[10];      // +0x00
    // padding? +0x0A: 2 bytes - not used
    uint32_t version1;  // +0x0C
    uint32_t version2;  // +0x10
    char* extraData;    // +0x14

    void parseFromString(const char* inputStr) {
        // Clear previous extraData if present
        if (extraData != nullptr) {
            if (*(int*)(extraData + 0x14) != 0) {
                cleanupObject(1);
            }
            freeMemory(extraData);
        }
        extraData = nullptr;
        name[0] = '\0';  // Actually offsets 0x14-0x17 are extraData pointer, not name. Wait: The code sets param_1[0x14..0x17] to zero, which are the 4 bytes of the extraData pointer. So extraData is nulled.
        // Also bytes at 0x14,0x15,0x16,0x17 are zeroed. That's the pointer.
        // name is at 0x00.
        // So we need to zero the pointer, not the name. In the code, after clearing extraData, it sets param_1[0x14] = '\0' etc. That zeroes the pointer. So we set extraData = nullptr.
        // Also at the beginning, they set param_1[0x14] = '\0' etc. So we do that.

        if (inputStr == nullptr) {
            goto fail;
        }

        // Parse first part: up to 10 characters (name)
        const char* src = inputStr;
        char* dst = name;
        char ch = *src;
        // Check if first character is alphanumeric
        if ( !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) ) {
            goto fail;
        }
        while (ch != '\0' && ch != '_') {
            if (dst == name + 10) { // maximum 10 chars?
                goto fail;
            }
            // Check character validity
            if ( !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) ) {
                goto fail;
            }
            *dst++ = ch;
            src++;
            ch = *src;
        }
        // Now ch should be '_'
        if (ch != '_') {
            goto fail;
        }
        // Null-terminate name
        *dst = '\0';
        // After name, we have '_' then version string: parse 7 hex nibbles into version1
        src++; // skip underscore
        // version1 parsing: 7 nibbles
        version1 = 0;
        int nibble;
        for (int i = 0; i < 7; i++) {
            nibble = parseHexNibbleFromString(&src); // custom function that consumes one hex char and returns value
            if (nibble < 0) goto fail;
            version1 = (version1 << 4) | nibble;
        }
        // Expect underscore after version1
        if (*src != '_') goto fail;
        src++;
        // version2 parsing: 7 nibbles
        version2 = 0;
        for (int i = 0; i < 7; i++) {
            nibble = parseHexNibbleFromString(&src);
            if (nibble < 0) goto fail;
            version2 = (version2 << 4) | nibble;
        }
        // Expect "_v3" after version2
        if (src[0] != '_' || src[1] != 'v' || src[2] != '3') goto fail;
        src += 3;
        // Now either end of string or '/' followed by extra data
        if (*src == '\0') {
            return; // success
        }
        if (*src == '/' && *(src+1) != '\0') {
            // Allocate memory for extra data
            void* mem = allocateMemory(0x18); // 24 bytes - why 24? Might be a struct or a string buffer
            if (mem == nullptr) {
                extraData = nullptr;
            } else {
                // Copy the substring after '/' into the allocated memory
                char* copied = copyString(src + 1); // this function does a mem/strcpy
                *(char**)mem = copied; // Actually FUN_004d8c00 returns the new string, and it's stored at *(param_1+0x14) = return value.
                extraData = (char*)mem; // But wait: the code does *(char **)(param_1 + 0x14) = pcVar3; where pcVar3 = FUN_004d8c00(param_2+0x14); So extraData points to the result of copyString, not the allocated block. Actually FUN_004d8c00 is the copy function, not the allocation. The allocation is done by FUN_009c8e50(0x18). Let's re-analyze:
                // iVar4 = FUN_009c8e50(0x18);
                // if (iVar4 == 0) pcVar3 = (char *)0x0;
                // else pcVar3 = (char *)FUN_004d8c00(param_2 + 0x14);
                // *(char **)(param_1 + 0x14) = pcVar3;
                // So it allocates 0x18 bytes (maybe a struct), then uses that pointer to call copyString which returns a char*. Then stores that char* in the field. The allocated block might be discarded? That seems odd. Possibly FUN_009c8e50 returns a buffer that FUN_004d8c00 uses as destination? But the code shows that if allocation fails, pcVar3=0. Otherwise, pcVar3 = result of copyString. So copyString returns the pointer to the copied string (maybe the same buffer). So extraData points to the allocated buffer (which contains the copied string). So we simplify:
                extraData = copyString(src + 1); // but this might not allocate; we'll keep the allocation call.
            }
            // Check if copied string starts with byte 0x01
            if (extraData != nullptr && extraData[0] == '\x01') {
                // If so, something; but function returns after this?
                // Actually after the if (*pcVar3 != '\x01') condition, it returns if not 0x01. So if it is 0x01, it falls through to the end? No, see: after storing extraData, it checks if *pcVar3 != '\x01', then returns. So if it is 0x01, it continues? Actually the code: 
                // if (*pcVar3 != '\x01') { return; }
                // So if it's 0x01, it does not return immediately; it falls through to the end of the function (which is the normal return after successful parse). So we'll return.
                return;
            }
        }
        // If we reach here without successful end, fail.
        goto fail;

    fail:
        // On failure, set name[0] = 0x01 (error?), clean up extraData.
        // Actually the code sets *param_1 = '\x01'; which is the first byte of name?
        // No, param_1[0] is the first byte of name. So it sets name[0] = 0x01 as an error flag.
        name[0] = '\x01';
        // Clean up extraData again
        if (extraData != nullptr) {
            if (*(int*)(extraData + 0x14) != 0) {
                cleanupObject(1);
            }
            freeMemory(extraData);
        }
        extraData = nullptr;
        return;
    }

private:
    // Helper: parse one hex digit from string, advance pointer
    int parseHexNibbleFromString(const char** strPtr) {
        const char* s = *strPtr;
        char c = *s;
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else {
            return -1;
        }
        (*strPtr)++;
        return value;
    }
};