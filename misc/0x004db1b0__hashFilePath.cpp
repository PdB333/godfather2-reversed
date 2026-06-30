//FUNC_NAME: hashFilePath
// Function at 0x004db1b0: Computes a hash of a file path string with normalization flags.
// Flags: bit0=caseSensitive (if 0, convert uppercase to lowercase; if 1, keep case)
//        bit1=stripPath (advance to filename after last slash/backslash)
//        bit2=stopAtDot (return early if dot encountered)
//        bit3=forceUpper (convert lowercase to uppercase)
//        bit4=initialNeg (start hash with -1 instead of 0)
//        bit5=normalizeSlashes (convert backslash to forward slash)
// Hash algorithm: iVar2 = iVar2 * 0x1003f + charValue (djb2 variant)

#include <cstdint>

static const uint32_t kFlagCaseSensitive   = 0x01;
static const uint32_t kFlagStripPath       = 0x02;
static const uint32_t kFlagStopAtDot       = 0x04;
static const uint32_t kFlagForceUpper      = 0x08;
static const uint32_t kFlagInitialNeg      = 0x10;
static const uint32_t kFlagNormalizeSlashes = 0x20;

int32_t hashFilePath(const char* path, uint32_t flags)
{
    int32_t hash = (flags & kFlagInitialNeg) ? -1 : 0;

    if (path != nullptr)
    {
        // Strip path if requested: advance to last slash/backslash
        if (flags & kFlagStripPath)
        {
            const char* p = path;
            while (*p != '\0')
            {
                if (*p == '\\' || *p == '/')
                {
                    path = p + 1;
                }
                p++;
            }
        }

        // Process each character
        char ch = *path;
        while (ch != '\0')
        {
            path++;
            if (ch == '.')
            {
                if (flags & kFlagStopAtDot)
                {
                    return hash;
                }
            }
            else if (ch == '\\' && (flags & kFlagNormalizeSlashes))
            {
                ch = '/';
            }

            uint32_t charVal = (uint32_t)ch;

            // Case conversion (unless caseSensitive flag is set)
            if (!(flags & kFlagCaseSensitive))
            {
                if (!(flags & kFlagForceUpper))
                {
                    // Convert uppercase to lowercase
                    if (charVal >= 'A' && charVal <= 'Z')
                    {
                        charVal += 0x20;
                    }
                }
                else
                {
                    // Convert lowercase to uppercase
                    if (charVal >= 'a' && charVal <= 'z')
                    {
                        charVal -= 0x20;
                    }
                }
            }

            hash = hash * 0x1003f + charVal;
            ch = *path;
        }
    }

    return hash;
}