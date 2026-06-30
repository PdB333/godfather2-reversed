// FUNC_NAME: createConditionalEffect
// Function address: 0x004df420
// This function checks a condition (4 ints array) and, if satisfied, retrieves a manager object and calls
// an internal function to create an effect/event. It returns an output pointer (param_1) which is set to 0 on failure.

// Global constant referenced
#define SOME_GLOBAL_CONSTANT 0.0f // DAT_00e2b1a4 - likely a float constant

// Forward declarations
int* __cdecl getManager(); // FUN_004e0f60 - returns pointer to manager or some object
void __cdecl callEffectFunc(int manager, int arg1, int arg2, int arg3); // FUN_004df210

// The main function
undefined4* createConditionalEffect(
    undefined4* outResult,    // param_1 - pointer to output result (set to 0 on failure)
    int* conditionFlags,      // param_2 - array of 4 ints (must be non-zero to proceed)
    undefined4 param3,        // param_3 - first parameter for internal function
    undefined4 param4,        // param_4 - second parameter for internal function
    undefined4 param5,        // param_5 - third parameter for internal function
    undefined4 param6,        // param_6 - additional data (likely index or identifier)
    undefined4 param7,        // param_7 - additional data
    undefined4* optionalVector // param_8 - optional pointer to a 3-float vector + something
)
{
    // Local variables that appear to be set but not explicitly used in the call to callEffectFunc
    // They might be part of a larger structure passed implicitly, or used for debugging.
    undefined4 local_30; // First component from optionalVector[0]
    undefined4 local_2c; // Second component from optionalVector[1]
    undefined4 local_28; // Third component from optionalVector[2]
    undefined4 local_24; // Set to global constant
    undefined4 local_20; // Set to 2 (maybe type or count)
    undefined4 local_1c; // Copied from param6
    undefined4 local_18; // Copied from param7
    uint local_14; // If optionalVector != null, address of local_30; else 0

    // Check condition: all 4 ints must be non-zero? Actually if any non-zero, proceed.
    // (Original: if (*param_2 != 0 || param_2[1] != 0) || (param_2[2] != 0 || param_2[3] != 0))
    if (conditionFlags[0] != 0 || conditionFlags[1] != 0 || conditionFlags[2] != 0 || conditionFlags[3] != 0)
    {
        int* manager = getManager(); // FUN_004e0f60
        if (manager != nullptr && *manager != 0)
        {
            // If optional vector provided, copy its first three ints (probably floats) and use global constant
            if (optionalVector != nullptr)
            {
                local_30 = optionalVector[0];
                local_2c = optionalVector[1];
                local_28 = optionalVector[2];
                local_24 = *(undefined4*)&SOME_GLOBAL_CONSTANT; // DAT_00e2b1a4
            }
            // These are always set regardless of optionalVector
            local_1c = param6;
            local_18 = param7;
            // If optionalVector not null, local_14 = address of local_30; else 0
            local_14 = (optionalVector != nullptr) ? (uint)&local_30 : 0;
            local_20 = 2; // Constant indicator

            // Call the actual effect function with first int from manager and param3, param4, param5
            callEffectFunc(*manager, param3, param4, param5);
            return outResult;
        }
    }
    // Condition failed or manager invalid, set output to 0
    *outResult = 0;
    return outResult;
}