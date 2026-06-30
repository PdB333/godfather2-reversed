// FUNC_NAME: defaultSetup
// Function address: 0x005e2be0
// Role: Creates a default parameter struct (1,0,0,0) and passes it to an internal setup function

void defaultSetup(void)
{
    // Struct representing a set of parameters (4 fields, 13 bytes, likely padded to 16)
    struct DefaultParams {
        int param1;   // +0x00
        int param2;   // +0x04
        int param3;   // +0x08
        uint8_t param4; // +0x0C
    } params;

    params.param1 = 1;
    params.param2 = 0;
    params.param3 = 0;
    params.param4 = 0;

    // Call the underlying setup function with the initialized struct
    FUN_005e2440(&params);
}