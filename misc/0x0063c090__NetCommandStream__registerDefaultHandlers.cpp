// FUNC_NAME: NetCommandStream::registerDefaultHandlers
void __thiscall NetCommandStream::registerDefaultHandlers(void) {
    // Internal stream buffer descriptor at this+0x10
    // +0x20: capacity, +0x24: count
    int *bufferDesc = *(int **)(this + 0x10);
    
    // Stream stack pointer at this+0x8
    int * &stackPtr = *(int **)(this + 0x8);
    
    // Helper to write a command entry: type (6) + pointer to handler
    auto writeCommand = [&](void *handlerFunc) {
        // Check space in the stream buffer
        checkStreamSpace(); // FUN_00625ca0
        if ((uint)bufferDesc[0x20] <= (uint)bufferDesc[0x24]) {
            flushStream(); // FUN_00627360
        }
        
        // Allocate a new command node (0x10 bytes)
        int *commandNode = allocateCommandNode(0); // FUN_00638110(0)
        commandNode[3] = (int)handlerFunc; // offset 0xc = handler pointer
        
        // Push (type=6, node) onto the stack
        stackPtr[1] = (int)commandNode;
        stackPtr[0] = 6;
        stackPtr += 2; // advance stack by 8 bytes (two 4-byte slots)
        
        // Finalize the command: pop the last entry and copy back? 
        // This pattern adjusts the stack by -0x10 (16 bytes) after a finalization call.
        int *top = stackPtr;
        int *finalizeResult = (int *)finalizeCommandNode(); // FUN_00638020()
        finalizeResult[0] = top[-2]; // copy first dword from previous entry
        finalizeResult[1] = top[-1]; // copy second dword
        stackPtr -= 4; // pop 16 bytes (back to before the push)
    };
    
    // Register 10 command handlers
    writeCommand((void*)FUN_0063b1b0);  // Handler #1
    writeCommand((void*)FUN_0063b740);  // Handler #2
    writeCommand((void*)&LAB_0063bcb0); // Handler #3
    writeCommand((void*)&LAB_0063bcd0); // Handler #4
    writeCommand((void*)&LAB_0063bcf0); // Handler #5
    writeCommand((void*)&LAB_0063bd10); // Handler #6
    writeCommand((void*)&LAB_0063bd30); // Handler #7
    writeCommand((void*)&LAB_0063bd50); // Handler #8
    writeCommand((void*)&LAB_0063bd70); // Handler #9
    writeCommand((void*)FUN_0063bd90);  // Handler #10
}