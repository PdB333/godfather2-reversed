// FUNC_NAME: initializerWrapper
// Function address: 0x00559af0
// Role: Wrapper function that calls two initialization/loading functions in sequence.
// Called from 0x00559ba0.

void initializerWrapper(void* param1, void* param2, void* param3, void* param4, void* param5)
{
    // Call first initialization step (no arguments)
    firstInitStep();
    // Call second initialization step with all parameters
    secondInitStep(param1, param2, param3, param4, param5);
}