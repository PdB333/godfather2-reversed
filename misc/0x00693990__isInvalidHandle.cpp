// FUNC_NAME: isInvalidHandle
bool isInvalidHandle(void* param_1, int handle)
{
    // This function checks if a given handle is invalid (negative index).
    // param_1 appears unused; likely a leftover this pointer from a member function call.
    int result = FUN_004d4b20(handle); // Function that validates or converts handle to internal index
    return result < 0; // Return true if handle is invalid (negative index)
}