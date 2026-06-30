// FUNC_NAME: Value::operator<(Value const&)
// Function at 0x00634150: Less-than comparison for generic Values (EARS engine variant type)
// Uses type dispatch via PTR_DAT_00e2a89c (string table of type names)
// Type 3 = float, type 4 = custom compare via FUN_006340e0, others via generic compare FUN_00634030

#include <cstdint>

// Forward declarations of helper functions
extern uint __stdcall genericCompare(Value* this, int* other);         // FUN_00634030
extern uint __stdcall fallbackCompare();                                 // FUN_006337e0
extern int  __stdcall type4Compare();                                    // FUN_006340e0
extern void __stdcall printTypeError(const char* format, ...);           // FUN_00633920

// External type name table (array of C strings indexed by type code)
// Address 0x00e2a89c
extern const char* typeNameTable[];

struct Value {
    int type;         // +0x00 type identifier
    float floatVal;   // +0x04 only valid when type == 3
    // Other fields follow for non‑float types
};

uint __thiscall Value::operator<(const Value& other) const {
    if (this->type == other.type) {
        if (this->type == 3) {
            // Strict inequality: this->floatVal < other->floatVal
            if (this->floatVal <= other.floatVal && other.floatVal != this->floatVal) {
                return 1;
            }
        } else if (this->type == 4) {
            int cmpResult = type4Compare();
            return (uint)(cmpResult < 0);
        } else {
            uint result = genericCompare(const_cast<Value*>(this), const_cast<int*>(&other.type));
            if (result == 0xffffffff) {
                result = fallbackCompare();
            }
            return result;
        }
    } else {
        // Type mismatch – print diagnostic
        const char* thisTypeName = typeNameTable[this->type];
        const char* otherTypeName = typeNameTable[other.type];
        // Check if the third character of the type names matches
        if (thisTypeName[2] == otherTypeName[2]) {
            printTypeError("attempt to compare two %s values", thisTypeName);
        } else {
            printTypeError("attempt to compare %s with %s", thisTypeName, otherTypeName);
        }
    }
    return 0;
}