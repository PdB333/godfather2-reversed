// FUNC_NAME: TokenStream::readFloatToken
// Function at 0x00630de0: Reads a float token from the input stream and writes a float token to the output stream.
// Handles token types 3 (direct float) and 4 (reference to external float).
// If the float equals a sentinel value (DAT_00e2b05c), it attempts to skip tokens until a valid one is found.

#include <cstdint>

// External functions (callees)
extern int readExternalFloat(float* outFloat); // FUN_00636850
extern void logError(const char* message);     // FUN_00627ac0 (prints "number")
extern void writeFloatToBuffer();              // FUN_00b99e20 (unknown, possibly debug)

// Global constants
extern const float FLOAT_SENTINEL; // DAT_00e2b05c
extern const char* ERROR_STRING;   // PTR_s_number_00e2a8a8

// Token types
enum TokenType : int32_t {
    TOKEN_FLOAT = 3,
    TOKEN_FLOAT_REF = 4
};

// Stream structure (offsets relative to this)
// +0x08: writePtr (int32_t*) - current write position in output buffer
// +0x0C: readPtr (int32_t*) - current read position in input buffer
struct TokenStream {
    int32_t* writePtr;  // +0x08
    int32_t* readPtr;   // +0x0C
};

int32_t TokenStream::readFloatToken() {
    int32_t* currentRead = this->readPtr;
    int32_t* currentWrite = this->writePtr;

    // Check if there is data to read (read pointer should be less than write pointer)
    if (currentWrite <= currentRead || currentRead == nullptr) {
        goto error;
    }

    int32_t tokenType = *currentRead;
    float floatValue;

    if (tokenType == TOKEN_FLOAT) {
        // Direct float: value is at currentRead[1]
        floatValue = reinterpret_cast<float*>(currentRead)[1];
    } else if (tokenType == TOKEN_FLOAT_REF) {
        // Reference to external float: read it via helper
        float tempFloat;
        if (readExternalFloat(&tempFloat) == 0) {
            goto error;
        }
        // Create a temporary token of type FLOAT with the resolved value
        int32_t fakeToken[2] = { TOKEN_FLOAT, *reinterpret_cast<int32_t*>(&tempFloat) };
        currentRead = fakeToken; // point to fake token
        floatValue = reinterpret_cast<float*>(currentRead)[1];
    } else {
        goto error;
    }

    // Check for sentinel value; if equal, skip tokens until a valid one is found
    if (floatValue == FLOAT_SENTINEL) {
        while (true) {
            // Advance read pointer? Actually the loop condition checks the same pointers again
            // but the code jumps to error which sets floatValue=0.0 and then writes that.
            // This loop seems to call logError and then fall through to write 0.0.
            logError(ERROR_STRING);
            // The original code jumps to LAB_00630e9b which sets floatValue=0.0 and then continues.
            // We simulate that by breaking out and setting floatValue=0.0.
            break;
        }
        floatValue = 0.0f;
    }

    // Write the output token (type FLOAT, value)
    *currentWrite = TOKEN_FLOAT;
    double doubleVal = static_cast<double>(floatValue);
    writeFloatToBuffer();
    reinterpret_cast<float*>(currentWrite)[1] = static_cast<float>(doubleVal);

    // Advance write pointer by 8 bytes (one token)
    this->writePtr = currentWrite + 2; // 2 int32_t = 8 bytes

    return 1;

error:
    floatValue = 0.0f;
    // Fall through to write 0.0 token? The original code jumps to LAB_00630e9b which sets local_14=0.0 and then continues to write.
    // But the error path also sets local_14=0.0 and then writes. So we replicate that.
    // Write a token with value 0.0
    *currentWrite = TOKEN_FLOAT;
    writeFloatToBuffer();
    reinterpret_cast<float*>(currentWrite)[1] = 0.0f;
    this->writePtr = currentWrite + 2;
    return 1; // Always returns 1
}