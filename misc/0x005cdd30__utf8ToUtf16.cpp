// FUNC_NAME: utf8ToUtf16
// Function address: 0x005cdd30
// Converts a null-terminated UTF-8 string to UTF-16 (UCS-2) and stores result in a global buffer.
// Input pointer is passed in EAX (custom calling convention). Special handling for 0x85 (ellipsis) -> three periods.
// Global buffer at 0x0119dac0 (g_utf16Buffer).

#include <cstdint>

// Global buffer for UTF-16 output (size unknown, assume sufficient)
static uint16_t g_utf16Buffer[1024]; // +0x0119dac0

void utf8ToUtf16(const char* utf8Str)
{
    const uint8_t* src = reinterpret_cast<const uint8_t*>(utf8Str);
    uint16_t* dst = g_utf16Buffer;

    // Find end of input string
    const uint8_t* srcEnd = src;
    while (*srcEnd != 0) {
        srcEnd++;
    }
    // srcEnd now points to the null terminator

    if (src >= srcEnd) {
        *dst = 0;
        return;
    }

    do {
        uint8_t ch = *src;
        if (ch < 0x80) {
            // Single byte (ASCII)
            *dst = (uint16_t)ch;
            dst++;
            src++;
        }
        else if ((ch & 0xE0) == 0xC0) {
            // Two-byte UTF-8 sequence
            if ((src[1] & 0xC0) != 0x80) {
                // Invalid continuation byte, abort
                *dst = 0;
                return;
            }
            *dst = ((uint16_t)(ch & 0x1F) << 6) | (uint16_t)(src[1] & 0x3F);
            dst++;
            src += 2;
        }
        else if ((ch & 0xF0) == 0xE0) {
            // Three-byte UTF-8 sequence
            if (((src[1] & 0xC0) != 0x80) || ((src[2] & 0xC0) != 0x80)) {
                // Invalid continuation bytes, abort
                *dst = 0;
                return;
            }
            *dst = ((uint16_t)(ch & 0x0F) << 12) | ((uint16_t)(src[1] & 0x3F) << 6) | (uint16_t)(src[2] & 0x3F);
            dst++;
            src += 3;
        }
        else {
            // Special case: 0x85 (horizontal ellipsis in some encodings) -> three periods
            if (ch == 0x85) {
                *dst = 0x2E; // '.'
                dst[1] = 0x2E;
                dst[2] = 0x2E;
                dst += 3;
                // Note: original code increments src by 1 and then jumps to the increment at the end of the loop
                // So we set dst and then fall through to the increment
                // But we need to handle the increment properly: the original code does:
                // *puVar3 = 0x2e; puVar3[1]=0x2e; puVar3=puVar3+2; *puVar3=0x2e; then goto LAB_005cde0e which does puVar3++ and src++
                // So effectively: write three periods, then increment dst by 3? Actually it writes first, then increments dst by 2, then writes third, then increments dst by 1 (total +3) and src by 1.
                // So we do: dst[0]=0x2E, dst[1]=0x2E, dst[2]=0x2E; dst+=3; src+=1;
                // But the original code writes the third period after incrementing dst by 2, so it's dst[2] after the first two.
                // We'll just do the same.
                src++; // consume the 0x85 byte
                // Continue to the end-of-loop check
            }
            else {
                // Unknown byte, replace with '?'
                *dst = 0x3F; // '?'
                dst++;
                // Abort further processing (original code jumps to LAB_005cde2f which sets *dst=0 and returns)
                *dst = 0;
                return;
            }
        }

        // Check if we've reached the end of input
        if (src >= srcEnd) {
            *dst = 0;
            return;
        }
    } while (true);
}