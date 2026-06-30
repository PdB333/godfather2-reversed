// FUNC_NAME: TokenStream::readFloatToken
// Address: 0x006311e0
// Reads a float value from an input token stream, converting type 4 tokens (e.g., speech-related).
// Skips tokens with a sentinel value (global constant DAT_00e2b05c), printing "number" for each skipped token.
// Writes a float (type 3) token to the output stream and advances the output pointer by 8 bytes.

#include <cstdint>

// Token types
const int TOKEN_TYPE_FLOAT = 3;       // Direct float value
const int TOKEN_TYPE_CONVERTIBLE = 4; // Requires conversion via FUN_00636850

// External functions
extern int __cdecl convertTokenToFloat(float* outValue); // FUN_00636850
extern void __cdecl logSkippedNumber();                  // FUN_00627ac0 prints "number"
extern void __cdecl finalizeFloatWrite();                // FUN_00b9d99d (e.g., clamp or NaN handling)

// Structure offsets (assumed):
// +0x08: output write pointer (points to current slot in output array)
// +0x0c: input read pointer (points to current slot in input array)
// Each slot: 8 bytes: [int type] [float value] for input; output writes type=3 then float.

typedef int TokenType;

struct TokenSlot {
    TokenType type;  // offset 0
    float value;     // offset 4
};

class TokenStream {
public:
    TokenSlot* outputWritePtr;  // +0x08
    TokenSlot* inputReadPtr;    // +0x0c

    // Reconstructed method
    int __thiscall readFloatToken();
};

int __thiscall TokenStream::readFloatToken() {
    TokenSlot* slot;
    int convResult;
    TokenSlot* currentSlot;
    double tempDouble;
    float parsedFloat;
    int localType;
    float localFloat;

    // Start with the input read pointer (may point to end)
    currentSlot = this->inputReadPtr;

    // If output write pointer has already reached or passed input read pointer (should be end?),
    // or input read pointer is null, jump to end with zero float.
    if (this->outputWritePtr <= currentSlot || currentSlot == nullptr) {
        goto skipAndZero;
    }

    // Check the type of the current input token
    if (currentSlot->type != TOKEN_TYPE_FLOAT) {
        if (currentSlot->type != TOKEN_TYPE_CONVERTIBLE) {
            goto skipAndZero; // Unsupported type, skip
        }
        // Type 4: try to convert to float
        convResult = convertTokenToFloat(&parsedFloat);
        if (convResult == 0) {
            goto skipAndZero; // Conversion failed
        }
        // Simulate a local float token for the value
        localType = TOKEN_TYPE_FLOAT;
        localFloat = parsedFloat;
        currentSlot = reinterpret_cast<TokenSlot*>(&localType); // Point to fake slot
    }

    // Extract the float value from the current token (real or fake)
    parsedFloat = currentSlot->value;

    // Check if the float value equals the global sentinel (e.g., NaN or special constant)
    if (parsedFloat == *reinterpret_cast<const float*>(0x00e2b05c)) { // DAT_00e2b05c
        // Skip tokens until we find a valid one (type 3 or convertible type 4)
        while (true) {
            currentSlot = this->inputReadPtr;

            bool atEndOrNull = (this->outputWritePtr <= currentSlot || currentSlot == nullptr);
            bool invalidType = (currentSlot->type != TOKEN_TYPE_FLOAT &&
                               (currentSlot->type != TOKEN_TYPE_CONVERTIBLE ||
                                (convResult = convertTokenToFloat(&localType), convResult == 0)));

            if (!atEndOrNull && !invalidType) {
                break; // Found a valid token
            }

            // Log skipped token and set float to zero
            logSkippedNumber(); // FUN_00627ac0(PTR_s_number_00e2a8a8)
        skipAndZero:
            parsedFloat = 0.0f;
        }
    }

    // Write output token: type = TOKEN_TYPE_FLOAT (3), value = parsedFloat
    TokenSlot* outSlot = this->outputWritePtr;
    outSlot->type = TOKEN_TYPE_FLOAT;
    tempDouble = static_cast<double>(parsedFloat);
    finalizeFloatWrite(); // Possibly clamp or handle special values
    outSlot->value = static_cast<float>(tempDouble);
    this->outputWritePtr++; // Advance output pointer by 8 bytes (sizeof(TokenSlot))

    return 1; // Success
}