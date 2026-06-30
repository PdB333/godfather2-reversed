// FUNC_NAME: MaterialEffect::loadFromStream
// Function address: 0x006f3280
// This function deserializes a material effect definition from a binary stream.
// It reads a sequence of tokens (key-value pairs) that define up to 8 color layers
// with corresponding multipliers. After reading all tokens, it computes a final
// accumulated color/lighting value at offset 0x114.

#include <cstdint>

// Known EARS parser function stubs (defined elsewhere)
extern void __thiscall initializeParser(Stream* stream);
extern void __thiscall beginParsing(Stream* stream, uint32_t magic);
extern bool __thiscall moreData(Stream* stream);
extern uint32_t __thiscall nextTokenType(Stream* stream);
extern Stream* __thiscall nextToken(Stream* stream);
extern const char* __thiscall getTokenString(Stream* stream);
extern void __thiscall readColorArray(Stream* stream, int32_t* color);
extern void __thiscall advanceParser(Stream* stream);
extern void __thiscall copyString(char* dst, const char* src);

// Sentinel values for uninitialized color channels (0xBADBABBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911)
const int SENTINEL_R = static_cast<int32_t>(0xBADBABBA);
const int SENTINEL_G = static_cast<int32_t>(0xBEEFBEEF);
const int SENTINEL_B = static_cast<int32_t>(0xEAC15A55);
const int SENTINEL_A = static_cast<int32_t>(0x91100911);

// Offset constants for the class layout
const int OFFSET_HAS_DATA = 0x50;          // byte flag
const int OFFSET_FLAGS = 0x54;             // byte flags (bit0: needs rebuild)
const int OFFSET_STRING1 = 0x58;           // char* (string)
const int OFFSET_STRING2 = 0x60;           // char* (string)
const int OFFSET_INT1 = 0x68;              // int
const int OFFSET_INT2 = 0x6C;              // int
const int OFFSET_INT3 = 0x70;              // int
const int OFFSET_COLOR0 = 0x74;            // 4 x int32 (r,g,b,a)
const int OFFSET_COLOR1 = 0x84;
const int OFFSET_COLOR2 = 0x94;
const int OFFSET_COLOR3 = 0xA4;
const int OFFSET_COLOR4 = 0xB4;
const int OFFSET_COLOR5 = 0xC4;
const int OFFSET_COLOR6 = 0xD4;
const int OFFSET_COLOR7 = 0xE4;
const int OFFSET_MULT0 = 0xF4;            // float
const int OFFSET_MULT1 = 0xF8;
const int OFFSET_MULT2 = 0xFC;
const int OFFSET_MULT3 = 0x100;
const int OFFSET_MULT4 = 0x104;
const int OFFSET_MULT5 = 0x108;
const int OFFSET_MULT6 = 0x10C;
const int OFFSET_MULT7 = 0x110;
const int OFFSET_ACCUMULATOR = 0x114;      // final float result

void __thiscall MaterialEffect::loadFromStream(int thisPtr, int stream)
{
    char cVar1;
    uint32_t tokenType;
    int srcVal;

    // Initialize parser
    initializeParser(reinterpret_cast<Stream*>(stream));
    beginParsing(reinterpret_cast<Stream*>(stream), 0xe4223e3f);  // magic constant

    cVar1 = moreData(reinterpret_cast<Stream*>(stream));
    do {
        if (cVar1 != '\0') {
            // End of tokens: compute final accumulated value
            reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] = 0.0f;

            // Check each color layer and add/multiply
            int32_t* color0 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR0);
            if (color0[0] != SENTINEL_R || color0[1] != SENTINEL_G ||
                color0[2] != SENTINEL_B || color0[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] =
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT0)[0];
            }

            int32_t* color1 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR1);
            if (color1[0] != SENTINEL_R || color1[1] != SENTINEL_G ||
                color1[2] != SENTINEL_B || color1[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT1)[0];
            }

            int32_t* color2 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR2);
            if (color2[0] != SENTINEL_R || color2[1] != SENTINEL_G ||
                color2[2] != SENTINEL_B || color2[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT2)[0];
            }

            int32_t* color3 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR3);
            if (color3[0] != SENTINEL_R || color3[1] != SENTINEL_G ||
                color3[2] != SENTINEL_B || color3[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT3)[0];
            }

            int32_t* color4 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR4);
            if (color4[0] != SENTINEL_R || color4[1] != SENTINEL_G ||
                color4[2] != SENTINEL_B || color4[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT4)[0];
            }

            int32_t* color5 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR5);
            if (color5[0] != SENTINEL_R || color5[1] != SENTINEL_G ||
                color5[2] != SENTINEL_B || color5[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT5)[0];
            }

            int32_t* color6 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR6);
            if (color6[0] != SENTINEL_R || color6[1] != SENTINEL_G ||
                color6[2] != SENTINEL_B || color6[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT6)[0];
            }

            int32_t* color7 = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR7);
            if (color7[0] != SENTINEL_R || color7[1] != SENTINEL_G ||
                color7[2] != SENTINEL_B || color7[3] != SENTINEL_A) {
                reinterpret_cast<float*>(thisPtr + OFFSET_ACCUMULATOR)[0] +=
                    reinterpret_cast<float*>(thisPtr + OFFSET_MULT7)[0];
            }

            // If rebuild flag is set, trigger finalization
            if (*reinterpret_cast<char*>(thisPtr + OFFSET_HAS_DATA) != '\0') {
                if ((*reinterpret_cast<uint8_t*>(thisPtr + OFFSET_FLAGS) & 1) != 0) {
                    // Call finalization functions (likely build and apply material)
                    reinterpret_cast<void (__thiscall*)(int)>(0x006f2ea0)(thisPtr);
                    reinterpret_cast<void (__thiscall*)(int)>(0x006f2bf0)(thisPtr);
                }
                *reinterpret_cast<char*>(thisPtr + OFFSET_HAS_DATA) = '\0';
            }
            return;
        }

        // Process next token from the stream
        advanceParser(reinterpret_cast<Stream*>(stream));
        tokenType = nextTokenType(reinterpret_cast<Stream*>(stream));

        switch (tokenType) {
        case 0:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<int32_t*>(thisPtr + OFFSET_FLAGS) = srcVal;
            break;
        case 1:
            nextToken(reinterpret_cast<Stream*>(stream));
            copyString(
                reinterpret_cast<char*>(thisPtr + OFFSET_STRING1),
                getTokenString(reinterpret_cast<Stream*>(stream))
            );
            break;
        case 2:
            nextToken(reinterpret_cast<Stream*>(stream));
            copyString(
                reinterpret_cast<char*>(thisPtr + OFFSET_STRING2),
                getTokenString(reinterpret_cast<Stream*>(stream))
            );
            break;
        case 3:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<int32_t*>(thisPtr + OFFSET_INT1) = srcVal;
            break;
        case 4:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<int32_t*>(thisPtr + OFFSET_INT2) = srcVal;
            break;
        case 5:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<int32_t*>(thisPtr + OFFSET_INT3) = srcVal;
            break;
        case 6:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR0);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 7:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT0) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 8:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR1);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 9:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT1) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 10:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR2);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0xB:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT2) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 0xC:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR3);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0xD:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT3) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 0xE:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR4);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0xF:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT4) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 0x10:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR5);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0x11:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT5) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 0x12:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR6);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0x13:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT6) = *reinterpret_cast<float*>(&srcVal);
            break;
        case 0x14:
        {
            int32_t* colorPtr = reinterpret_cast<int32_t*>(thisPtr + OFFSET_COLOR7);
            nextToken(reinterpret_cast<Stream*>(stream));
            readColorArray(reinterpret_cast<Stream*>(stream), colorPtr);
            break;
        }
        case 0x15:
            srcVal = *reinterpret_cast<int32_t*>(nextToken(reinterpret_cast<Stream*>(stream)) + 8);
            *reinterpret_cast<float*>(thisPtr + OFFSET_MULT7) = *reinterpret_cast<float*>(&srcVal);
            break;
        }

        advanceParser(reinterpret_cast<Stream*>(stream));
        cVar1 = moreData(reinterpret_cast<Stream*>(stream));
    } while (true);
}