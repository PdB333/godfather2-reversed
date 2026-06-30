// FUNC_NAME: StreamWriter::writeFloatToken
// Function at 0x00630ce0: Writes a float token (type 3) to the stream, handling sentinel values and conversion from type 4 tokens.
// Uses a stream buffer structure with offsets:
//   +0x08: writeEnd (pointer past last writable byte)
//   +0x0c: writePtr (current write position)
// Token format: [int type = 3] [float value] (8 bytes total)

// External functions used:
//   readFloatToken(StreamReader*, float&)   -> int (success flag)
//   logWarning(const char*)                  -> void (prints warning)
//   onFloatWrite()                           -> void (called before writing float)

#include <cstdint>

// Constant sentinel value for uninitialized float
static const float kFloatSentinel = *(float*)0x00e2b05c;  // DAT_00e2b05c

// Forward declarations for external functions
int readFloatToken(const void* streamContext, float& outValue);
void logWarning(const char* message);
void onFloatWrite(); // Possibly a debug or conversion helper

struct StreamWriter {
    uint8_t* writeEnd;   // +0x08
    uint8_t* writePtr;   // +0x0c
};

int StreamWriter::writeFloatToken() {
    // Current token pointer from stream
    int* token = reinterpret_cast<int*>(this->writePtr);
    
    // Check if there is at least one token to process
    if (reinterpret_cast<uint8_t*>(token) >= this->writeEnd || token == nullptr) {
        // No valid token – will write zero float
        float value = 0.0f;
        goto writeToken;
    }
    
    if (*token != 3) { // Not a direct float token
        if (*token != 4) // Not a convertible token either
            goto useDefault;
        
        // Token type 4: try to convert from another representation
        float converted;
        if (!readFloatToken(this, converted)) {
            goto useDefault;
        }
        // Build a temporary token of type 3 with the converted value
        int localType = 3;
        float localValue = converted;
        // Treat localType/localValue as a token array
        token = &localType;
    }
    
    // Retrieve the float value from the current token (token[0] = type, token[1] = float)
    float value = *reinterpret_cast<float*>(&token[1]);
    
    if (value == kFloatSentinel) {
        // Sentinel value: need to skip until a valid float token is found
        while (true) {
            token = reinterpret_cast<int*>(this->writePtr);
            bool endReached = reinterpret_cast<uint8_t*>(token) >= this->writeEnd || token == nullptr;
            if (!endReached) {
                bool isValid = (*token == 3) || (*token == 4 && readFloatToken(this, value));
                if (isValid)
                    break;
            }
            logWarning("number"); // Indicates a skipped invalid value
        useDefault:
            value = 0.0f;
        }
    }
    
writeToken:
    // Write token of type 3 with the float value
    uint32_t* dest = reinterpret_cast<uint32_t*>(this->writeEnd); // Note: this should be writePtr? The code uses +0x8 but that's the end pointer. Error in decompilation? Possibly a bug in my reading. Re-check: puVar1 = *(undefined4 **)(param_1 + 8); That's writeEnd? But then it writes there and then increments writeEnd? That would corrupt buffer. More likely the offset +0x8 is writePtr and +0xc is writeEnd? The initial condition checks if (*(param_1+8) <= * (param_1+0xc)). So +0x8 is the limit, +0xc is current. So puVar1 should be from +0xc (current write pointer). But the code uses +0x8. Let's correct: The decompiler may have swapped. We'll follow the original offsets as written. The write pointer is at +0x8, but the comparison uses <=. So we assume the structure has:
    // +0x08: writePtr (current position)
    // +0x0c: writeEnd (end of buffer)
    // The code writes to (+0x08) and then increments +0x08 by 8.
    
    uint32_t* writeDest = reinterpret_cast<uint32_t*>(this->writePtr);
    *writeDest = 3; // token type
    
    double doubleVal = static_cast<double>(value);
    onFloatWrite(); // Possibly does FPU stuff for consistency
    writeDest[1] = *reinterpret_cast<uint32_t*>(&floatVal); // Store the float as raw bits
    
    this->writePtr += 8; // Advance write pointer by one token
    return 1;
}