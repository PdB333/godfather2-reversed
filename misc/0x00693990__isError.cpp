// FUNC_NAME: isError
// Address: 0x00693990
// Role: Checks if the result from an internal engine function is negative, indicating an error or invalid state.
// Parameters: param_1 is unused (likely this pointer or padding), param_2 is the value to check.
// Callee: FUN_004d4b20 (likely returns a status/index; negative means failure).

bool isError(void* unused, int32_t value) {
    int32_t result = getStatusOrIndex(value); // TODO: rename FUN_004d4b20 to actual function name
    return result < 0;
}