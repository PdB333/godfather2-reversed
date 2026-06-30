// FUNC_NAME: initializeObject
// Function address: 0x00604030
// Role: Wrapper function that calls base initialization and then additional setup on the third parameter.
void __cdecl initializeObject(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    // Call base initialization with all parameters
    FUN_00603da0(param_1, param_2, param_3, param_4);
    // Call additional setup on the third parameter (likely an object pointer)
    FUN_00604060(param_3);
}