// FUNC_NAME: Network::advanceStreamIndex
// Address: 0x00579aa0
// Role: Advances a pointer in a compressed stream of tokens (packets) with hierarchical index.
// Uses a custom encoding: first byte low nibble is token type (5 = envelope with sub-tokens).
// Main use: skip to a specific index within an envelope, returning base of envelope if found.

#include <cstdint>

// Forward declaration of external helper (presumably decompress or copy)
void FUN_00579a20();

// Tables for skipping variable-length sub-tokens, index by sub-token type (0-15)
extern const int32_t gSubTokenSkipBase[16];   // DAT_00e2c720
extern const int32_t gSubTokenSkipMul[16];    // DAT_00e2c758

// __fastcall: first param in ECX? Actually this function uses in_EAX as implicit second param.
// But Ghidra's decompiler shows only one param; in_EAX is passed in EAX.
// We'll model it as explicit second parameter.
void __fastcall advanceStreamIndex(int** streamPtr, int32_t targetIndex)
{
    uint8_t* currentPos = reinterpret_cast<uint8_t*>(*streamPtr);
    uint8_t headerByte = *currentPos;
    uint8_t tag = headerByte & 0x0F;

    if (tag == 5)
    {
        // Envelope token: contains sub-tokens
        uint32_t numSubTokens = (static_cast<uint32_t>(currentPos[1]) << 4) | (headerByte >> 4);
        // 16-bit relative offset to envelope data (from start of this token)
        uint8_t* envelopeBase = currentPos + *reinterpret_cast<uint16_t*>(currentPos + 2);
        currentPos += 4; // skip header (1 tag+length, 1 more, 2 offset)

        for (uint32_t i = 0; i < numSubTokens; i++)
        {
            uint32_t subTokenSize = (static_cast<uint32_t>(currentPos[1]) << 4) | (currentPos[0] >> 4);
            uint32_t subTokenType = currentPos[0] & 0x0F;

            // subTokenSize - 1 is the last index of this sub-token (0-based)
            int32_t subTokenLimit = static_cast<int32_t>(subTokenSize) - 1;

            if (targetIndex < subTokenLimit)
            {
                // Target index falls inside this sub-token → return envelope base
                switch (subTokenType)
                {
                case 4:
                    FUN_00579a20();
                    FUN_00579a20();
                    // fall through
                default:
                    *streamPtr = reinterpret_cast<int*>(envelopeBase);
                    return;
                }
            }
            else
            {
                targetIndex -= subTokenLimit;
                // Advance past the sub-token data using table
                currentPos += gSubTokenSkipMul[subTokenType] * subTokenSize + gSubTokenSkipBase[subTokenType];
            }
        }
        // All sub-tokens processed; continue after envelope
        *streamPtr = reinterpret_cast<int*>(currentPos);
    }
    else
    {
        // Non-envelope token: simple fixed or variable length
        switch (tag)
        {
        case 0:
            *streamPtr = reinterpret_cast<int*>(currentPos + 5);
            return;
        case 1:
            *streamPtr = reinterpret_cast<int*>(currentPos + 8);
            return;
        case 2:
            *streamPtr = reinterpret_cast<int*>(currentPos + 11);
            return;
        case 3:
            *streamPtr = reinterpret_cast<int*>(currentPos + 14);
            return;
        case 4:
        {
            uint8_t extraByte = currentPos[1];
            uint32_t count = (static_cast<uint32_t>(extraByte) << 4) | (headerByte >> 4);
            FUN_00579a20();
            FUN_00579a20();
            *streamPtr = reinterpret_cast<int*>(currentPos + count * 4 + 2);
            return;
        }
        case 6:
        {
            uint8_t extraByte = currentPos[1];
            uint32_t count = (static_cast<uint32_t>(extraByte) << 4) | (headerByte >> 4);
            *streamPtr = reinterpret_cast<int*>(currentPos + count + 8);
            return;
        }
        case 7:
        {
            uint8_t extraByte = currentPos[1];
            uint32_t count = (static_cast<uint32_t>(extraByte) << 4) | (headerByte >> 4);
            *streamPtr = reinterpret_cast<int*>(currentPos + count * 2 + 8);
            return;
        }
        case 0xC:
            currentPos += 2; // skip 2-byte header
            break;
        case 0xD:
            *streamPtr = reinterpret_cast<int*>(currentPos + 2);
            return;
        default:
            break;
        }
        *streamPtr = reinterpret_cast<int*>(currentPos);
    }
}