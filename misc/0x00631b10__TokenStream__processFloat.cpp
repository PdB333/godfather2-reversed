// FUNC_NAME: TokenStream::processFloat
// Address: 0x00631b10
// Function reads a float token from the read stream (possibly skipping sentinel values)
// and writes it to the write stream as a type 3 (float) token.
// Member of a stream class that manages 8-byte tokens (type int + float value).
// Offsets: this +0x08 = write cursor pointer (current write position)
//          this +0x0c = read cursor pointer (current read position)

#include <cstdint>

struct Token {
    int32_t type;   // +0x00
    float   value;  // +0x04
};

class TokenStream {
public:
    Token* mWriteCursor; // +0x08
    Token* mReadCursor;  // +0x0c

    // Internal helper functions (defined elsewhere in the binary)
    int readFloatFromStream(float* outVal);      // FUN_00636850
    void logNumber();                             // FUN_00627ac0 – prints "number"
    void writeFloatToStream();                    // FUN_00d3d41f – post-processing for float write

    int processFloat(); // FUN_00631b10
};

int TokenStream::processFloat() {
    Token* readToken = mReadCursor;
    float floatVal;

    // Initial check: if write cursor has caught up with read cursor or nullptr, skip to writing zero
    if (mWriteCursor <= readToken || readToken == nullptr) {
        goto writeZero;
    }

    // If current token is not type 3 (float), check if it's type 4 (convertible via helper)
    if (readToken->type != 3) {
        if (readToken->type != 4) {
            goto writeZero;
        }
        float temp;
        int result = readFloatFromStream(&temp);
        if (result == 0) {
            goto writeZero;
        }
        // Create a local token of type 3 with the read value
        Token localToken;
        localToken.type = 3;
        localToken.value = temp;
        readToken = &localToken;
    }

    floatVal = readToken->value;

    // If the float equals a sentinel value, skip subsequent tokens until a non‑sentinel is found
    if (floatVal == DAT_00e2b05c) { // replace with actual sentinel constant
        // Loop: re-fetch read token and check validity, type, and sentinel condition
        while (true) {
            readToken = mReadCursor;
            // Check buffer full / null / invalid type
            if (mWriteCursor <= readToken || readToken == nullptr) {
                break;
            }
            if (readToken->type == 3) {
                // Type 3: read directly
                floatVal = readToken->value;
            } else if (readToken->type == 4) {
                float temp;
                int res = readFloatFromStream(&temp);
                if (res == 0) {
                    break;
                }
                floatVal = temp;
            } else {
                break; // invalid type
            }
            // Check if this new value is still the sentinel
            if (floatVal != DAT_00e2b05c) {
                break; // found a non‑sentinel, exit loop
            }
            // Log and retry
            logNumber();
        }
    }

writeZero:
    // At this point, floatVal holds the value to write (may be 0.0f if no valid token)
    Token* writeToken = mWriteCursor;
    writeToken->type = 3;
    double d = static_cast<double>(floatVal);
    writeFloatToStream(); // likely converts double to float and stores with endianness
    writeToken->value = static_cast<float>(d);
    mWriteCursor = reinterpret_cast<Token*>(reinterpret_cast<uint8_t*>(mWriteCursor) + 8);

    return 1;
}