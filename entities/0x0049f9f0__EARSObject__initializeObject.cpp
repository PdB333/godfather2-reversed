// FUNC_NAME: EARSObject::initializeObject
// Address: 0x0049f9f0
// Role: Initializes an EARS object by calling a sub-function with static data and an output buffer.
//       The two integer parameters are stored locally but appear unused in this wrapper.
//       The unused first parameter (param_1) likely corresponds to the implicit 'this' pointer.

void EARSObject::initializeObject(int param2, int param3)
{
    int unusedCounter = 0;                   // local_4, likely a debug counter or sentinel
    int savedParam3 = param3;                // local_8, stored but not directly used
    int savedParam2 = param2;                // local_c, stored but not directly used
    char outputBuffer[8];                    // local_14, buffer to hold result from sub-function

    // Call sub-function with static data pointer and output buffer
    // FUN_0049f960 is responsible for populating outputBuffer based on the static configuration at LAB_0049ec30
    FUN_0049f960(&LAB_0049ec30, outputBuffer);

    return;
}