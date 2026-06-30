// FUNC_NAME: readMultiLineInput
// Address: 0x004d78b0
// This function reads multiple lines from an input source (likely a file or console), concatenates them with spaces,
// and returns a dynamically allocated buffer containing the concatenated string, terminated with a newline and null.
// It stops reading when an empty line is encountered. The initial string pointer (in EAX) is used to determine the initial buffer size.
// The function uses a global temporary buffer of 0x800 bytes (DAT_01225e30) for line accumulation.

#include <cstddef>
#include <cstdlib>
#include <cstring>

// External functions from the game's I/O subsystem
extern char* readLineSource(int mode, int param);        // FUN_004d5e10
extern char* getLineEnd(char* start, int mode, void* sep); // FUN_004d5fd0
extern void* allocateMemory(size_t size);                 // FUN_009c8e80 (likely malloc wrapper)

// Global scratch buffer (0x800 bytes)
static char g_lineBuffer[2048]; // DAT_01225e30

char* readMultiLineInput(void* inputString) {
    // Compute length of the initial string (used for allocation)
    char* str = (char*)inputString;
    char* strEnd = str + 1;
    while (*str != '\0') {
        str++;
    }
    size_t initialLen = (size_t)str - (size_t)strEnd; // likely (strlen - 1) but safe to use strlen

    // Allocate output buffer: size = 2 * initialLen + 1 (based on decompiled allocation)
    char* outputBuffer = (char*)allocateMemory(initialLen * 2 + 1);
    char* writePtr = outputBuffer;

    do {
        // Read first line of a group (mode 0)
        char* lineStart = readLineSource(0, 0);
        char* lineEnd = getLineEnd(lineStart, 0, nullptr);
        size_t lineLen = (size_t)lineEnd - (size_t)lineStart;

        // Limit line length to buffer size (0x7ff = max copy length)
        if (lineLen >= 0x800) {
            lineLen = 0x7ff;
        } else if (lineLen == 0) {
            // Empty line terminates input
            g_lineBuffer[0] = '\0';
            *writePtr = '\0';
            return outputBuffer;
        }

        // Copy line to temp buffer
        strncpy(g_lineBuffer, lineStart, lineLen);
        g_lineBuffer[lineLen] = '\0';

        // Append first line to output
        char* src = g_lineBuffer;
        while (*src) {
            *writePtr++ = *src++;
        }

        // Read subsequent lines of the group (mode 1)
        while (true) {
            lineStart = readLineSource(1, 0);
            lineEnd = getLineEnd(lineStart, 1, nullptr);
            lineLen = (size_t)lineEnd - (size_t)lineStart;

            if (lineLen >= 0x800) {
                lineLen = 0x7ff;
            } else if (lineLen == 0) {
                break;  // empty line ends the group
            }

            strncpy(g_lineBuffer, lineStart, lineLen);
            g_lineBuffer[lineLen] = '\0';

            // Insert space before the next line
            *writePtr++ = ' ';
            src = g_lineBuffer;
            while (*src) {
                *writePtr++ = *src++;
            }
        }

        // After the group, add a newline
        *writePtr++ = '\n';
        g_lineBuffer[0] = '\0';
    } while (true);

    return outputBuffer; // unreachable, but required by original code
}