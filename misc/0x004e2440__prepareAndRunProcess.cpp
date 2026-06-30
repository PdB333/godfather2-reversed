// FUNC_NAME: prepareAndRunProcess
void prepareAndRunProcess(uint32 arg) { // addr 0x004e2440: Wrapper that initializes a local context and then runs the main process
    uint32 context = 0; // local context variable, initialized to 0
    FUN_004e1d80(&context, arg); // initializes context based on arg (likely a handle or ID)
    FUN_004e2250(); // runs the main processing step
}