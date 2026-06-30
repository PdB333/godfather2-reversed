// FUNC_NAME: ScriptRuntime::readNumericValue
// Reconstructed C++ for function at 0x0062d740
// This function reads a numeric literal from the bytecode stream.
// It supports both pre-compiled float tokens (type 10) and string-converted integers.

#include <cstdlib>
#include <cctype>

// Forward declarations of helper functions
void readFloatToken(ScriptRuntime* runtime);  // FUN_00628080
void error(ScriptRuntime* runtime, const char* msg);  // FUN_00627a20
bool isStringToken(ScriptRuntime* runtime);  // FUN_00636850
float readPrecompiledFloat(ScriptRuntime* runtime);  // FUN_006259b0
char* readStringFromBytecode(ScriptRuntime* runtime);  // FUN_00633990 (approximate)
void expandStringBuffer(ScriptRuntime* runtime);  // FUN_00627360
void stringError(const char* msg);  // FUN_00627ac0

// Global constants (symbolic names)
extern const float kFloat_Ten;  // DAT_00e39f98 = 10.0f
extern const float kTwoToThe32;  // DAT_00e44578 = 4294967296.0f

// Offsets into the ScriptRuntime structure
// +0x00: vtable
// +0x04: unknown
#define OFFSET_BYTECODE_END 0x08
#define OFFSET_BYTECODE_PTR 0x0c
#define OFFSET_STRING_BUFFER 0x10

// Token types (approximate)
enum TokenType {
    TOKEN_NONE = 0,
    TOKEN_NUMBER = 3,
    TOKEN_STRING = 4,
    TOKEN_FLOAT_LITERAL = 10  // precompiled float
};

// Structure representing the script runtime
struct ScriptRuntime {
    // make offsets explicit
    // +0x00: vtbl
    // +0x04: pad/unknown
    uint8_t* bytecodeEnd;       // +0x08
    uint8_t* bytecodePtr;       // +0x0c
    void* stringBuffer;         // +0x10 (complex structure for string operations)
};

// Bytecode instruction token layout
struct Token {
    int type;       // 4 bytes (e.g., 3, 4, 10)
    float value;    // 4 bytes (payload)
}; // total 8 bytes

// Main function
int ScriptRuntime::readNumericValue() {
    Token* outputPtr = reinterpret_cast<Token*>(this->bytecodeEnd);
    Token* current = reinterpret_cast<Token*>(this->bytecodePtr);

    float floatVal = kFloat_Ten;  // default base for conversion (10)

    // If there is a precompiled float token ahead, read it
    if (current < outputPtr && current != nullptr && current->type > 0) {
        readFloatToken();  // might update floatVal or read next token
        floatVal = in_XMM0_Da;  // from the XMM0 register in assembly, corresponds to reading a float?
        // Actually this is complex; we keep the logic simplified.
        // In reality, FUN_00628080 likely reads a float from the bytecode.
    }

    int base = static_cast<int>(floatVal);
    if (base == static_cast<int>(kFloat_Ten)) {
        // Token type 10: read precompiled float directly
        current = reinterpret_cast<Token*>(this->bytecodePtr);
        outputPtr = reinterpret_cast<Token*>(this->bytecodeEnd);
        if (current >= outputPtr || current == nullptr || current->type == -1) {
            error("value expected");
            current = reinterpret_cast<Token*>(this->bytecodePtr);  // updated
        }
        // Handle string token before float? This part is messy.
        // Actually the original code:
        // if token is 3, or (token is 4 and isStringToken(runtime) != 0)
        if (current < outputPtr && current != nullptr &&
            (current->type == TOKEN_NUMBER || 
            (current->type == TOKEN_STRING && isStringToken()))) {
            float floatResult = readPrecompiledFloat();  // FUN_006259b0
            Token* dest = reinterpret_cast<Token*>(this->bytecodeEnd);
            dest->type = TOKEN_NUMBER;
            dest->value = floatResult;
            // advance bytecodePtr by 8 bytes
            this->bytecodeEnd = reinterpret_cast<uint8_t*>(dest + 1);
            return 1;
        }
        return 1; // fall through to error
    }
    else {
        // Token is not precompiled float -> parse string
        uint8_t* strPtr = reinterpret_cast<uint8_t*>(this->bytecodePtr);
        if (strPtr >= this->bytecodeEnd || strPtr == nullptr) {
            stringError("string");
            base = 1;  // set base to 1? Actually they set iVar8 = 1 after error.
        }
        else {
            if (*(int*)strPtr == TOKEN_STRING) {
                strPtr = reinterpret_cast<uint8_t*>(*(int*)(strPtr + 4) + 0x10);
            }
            else {
                int result = readStringFromBytecode(); // get string from bytecode
                if (result == 0) {
                    strPtr = nullptr;
                }
                else {
                    strPtr = reinterpret_cast<uint8_t*>(*(int*)(strPtr + 4) + 0x10);
                }
                // Check if string buffer has space
                if (*(unsigned int*)(*(int*)(this->stringBuffer) + 0x20) <= *(unsigned int*)(*(int*)(this->stringBuffer) + 0x24)) {
                    expandStringBuffer();
                }
            }
            if (strPtr == nullptr) {
                stringError("string");
                base = 1;
            }
        }

        // Validate base (must be between 2 and 34, else error)
        if (static_cast<unsigned int>(base - 2) > 0x22) {
            error("base out of range");
            // debug break
            __debugbreak();  // original: swi(3)
        }

        // Convert string to unsigned long with given base
        char* endPtr = nullptr;
        unsigned long value = strtoul(reinterpret_cast<const char*>(strPtr), &endPtr, base);

        if (strPtr != reinterpret_cast<uint8_t*>(endPtr)) {
            // Skip trailing whitespace
            while (isspace(static_cast<unsigned char>(*endPtr))) {
                endPtr++;
            }
            if (*endPtr == '\0') {
                // Successful conversion
                Token* dest = reinterpret_cast<Token*>(this->bytecodeEnd);
                dest->type = TOKEN_NUMBER;
                float floatVal = static_cast<float>(static_cast<int>(value));
                if (static_cast<int>(value) < 0) {
                    // Handle unsigned range (value > 0x7FFFFFFF)
                    floatVal = floatVal + kTwoToThe32;
                }
                dest->value = floatVal;
                this->bytecodeEnd = reinterpret_cast<uint8_t*>(dest + 1);
                return 1;
            }
        }

        // Conversion failed
        Token* dest = reinterpret_cast<Token*>(this->bytecodeEnd);
        dest->type = TOKEN_NONE;
        this->bytecodeEnd = reinterpret_cast<uint8_t*>(dest + 1);
        return 1;
    }
}