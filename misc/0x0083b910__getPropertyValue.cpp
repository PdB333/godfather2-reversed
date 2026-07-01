// FUNC_NAME: getPropertyValue
// Function address: 0x0083b910
// Wrapper that calls an internal lookup function (FUN_004480d0) to retrieve a property value.
// Returns 1 (true) if found, 0 (false) otherwise. Output value written via outValue pointer.

int getPropertyValue(uint param1, uint param2, uint* outValue)
{
    uint localValue = 0;                         // Storage for fetched value
    char success = FUN_004480d0(param1, param2, &localValue); // Internal lookup call

    if (success != '\0') {                       // Non-zero = success
        *outValue = localValue;                  // Set output to fetched value
        return 1;
    }
    *outValue = 0;                               // Default to zero on failure
    return 0;
}