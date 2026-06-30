// FUNC_NAME: ComparisonCondition::evaluate
// Address: 0x006ed300
// Role: Evaluates a stored comparison condition against an external value.
// The condition has a type (byte, int, float) and stores three fields:
// field0 (int type), field1 (int), field2 (int), field3 (threshold value).
// The helper functions (FUN_006ebff0, FUN_006eb7b0, FUN_006eb7c0) perform
// the actual comparison and return a result. This function then checks if
// the stored threshold is less than that result.

class ComparisonCondition {
public:
    // Offset 0x00: comparison type (0=byte, 1=int, 2=float)
    int type;
    // Offset 0x04: first parameter for comparison function
    int field1;
    // Offset 0x08: second parameter for comparison function
    int field2;
    // Offset 0x0C: threshold value (interpreted as byte, int, or float based on type)
    union {
        byte byteThreshold;
        int intThreshold;
        float floatThreshold;
    } threshold;

    // External helper functions (declared elsewhere)
    static byte byteCompare(int param1, int param2, int externalValue);
    static int intCompare(int param1, int param2, int externalValue);
    static float floatCompare(int param1, int param2, int externalValue);

    // __thiscall: evaluates condition with given external value
    bool __thiscall evaluate(int externalValue) {
        bool result = false;
        if (type == 0) {
            // Byte comparison
            byte compareResult = byteCompare(field1, field2, externalValue);
            // Return true if stored threshold < compareResult
            result = (threshold.byteThreshold < compareResult);
        } else if (type == 1) {
            // Integer comparison
            int compareResult = intCompare(field1, field2, externalValue);
            // Return true if stored threshold < compareResult
            result = (threshold.intThreshold < compareResult);
        } else if (type == 2) {
            // Float comparison
            float compareResult = floatCompare(field1, field2, externalValue);
            // Return true if stored threshold < compareResult
            result = (threshold.floatThreshold < compareResult);
        }
        return result;
    }
};