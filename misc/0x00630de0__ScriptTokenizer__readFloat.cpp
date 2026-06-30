// FUNC_NAME: ScriptTokenizer::readFloat
// Function address: 0x00630de0
// Reads a float value from the input token stream (offset +0x0c) and writes it to the output stream (offset +0x08).
// Token types: 3 = float constant, 4 = string variable needing conversion.
// Sentinal value (DAT_00e2b05c) triggers re-read of next token.

#pragma once
#include <cstdint>

// Token structure: [type (int32), value (float or int32)]
struct Token {
    int32_t type;
    union {
        float floatVal;
        int32_t intVal;
    };
};

// External functions
extern int convertStringToFloat(float* outValue); // FUN_00636850
extern void logError(const char* msg);            // FUN_00627ac0
extern void crcUpdate();                          // FUN_00b99e20

extern float SENTINEL_VALUE;                      // DAT_00e2b05c

class ScriptTokenizer {
public:
    // +0x08: pointer to current output token
    // +0x0c: pointer to current input token
    int readFloat();
};

int ScriptTokenizer::readFloat() {
    Token* inputToken = *reinterpret_cast<Token**>(reinterpret_cast<uintptr_t>(this) + 0x0C);
    Token* outputToken = *reinterpret_cast<Token**>(reinterpret_cast<uintptr_t>(this) + 0x08);

    // Validate pointers
    if (outputToken <= inputToken || inputToken == nullptr) {
        logError("number");
        inputToken = nullptr; // force error path
        goto write_default;
    }

    // Check token type
    if (inputToken->type != 3 && inputToken->type != 4) {
        logError("number");
        goto write_default;
    }

    float value;
    if (inputToken->type == 3) {
        value = inputToken->floatVal;
    } else { // type == 4 (string reference)
        if (convertStringToFloat(&value) == 0) {
            logError("number");
            goto write_default;
        }
        // Simulate creation of temporary float token
        // (original code repointed piVar3 to a local token)
    }

    // Sentinel value forces a loop to read next token until a valid float is obtained
    if (value == SENTINEL_VALUE) {
        while (true) {
            inputToken = *reinterpret_cast<Token**>(reinterpret_cast<uintptr_t>(this) + 0x0C);
            if (outputToken <= inputToken || inputToken == nullptr) {
                logError("number");
                value = 0.0f;
                break;
            }
            if (inputToken->type == 3) {
                value = inputToken->floatVal;
                break;
            } else if (inputToken->type == 4) {
                if (convertStringToFloat(&value) != 0) {
                    break;
                }
            }
            logError("number");
        }
    }

    // Write the float to the output stream
    outputToken = *reinterpret_cast<Token**>(reinterpret_cast<uintptr_t>(this) + 0x08);
    outputToken->type = 3;
    crcUpdate();
    outputToken->floatVal = static_cast<float>(static_cast<double>(value));
    *reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(this) + 0x08) += 8;
    return 1;

write_default:
    // Default: write zero float
    outputToken = *reinterpret_cast<Token**>(reinterpret_cast<uintptr_t>(this) + 0x08);
    outputToken->type = 3;
    crcUpdate();
    outputToken->floatVal = 0.0f;
    *reinterpret_cast<int32_t*>(reinterpret_cast<uintptr_t>(this) + 0x08) += 8;
    return 1;
}