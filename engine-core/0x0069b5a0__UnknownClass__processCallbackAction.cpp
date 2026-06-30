// FUNC_NAME: UnknownClass::processCallbackAction
void __thiscall UnknownClass::processCallbackAction(int param_1, int param_2)
{
    // Stack-allocated callback data (3 ints: [handle, functionPointer, maybe refcount])
    int callbackData[3];
    // Note: Ghidra decompiler may have split the function pointer; it is actually callbackData[1].
    // We reinterpret the array to include the function pointer.
    struct CallbackData {
        int handle;           // +0x00
        void (*callback)(int); // +0x04
        int unk;              // +0x08
    };
    CallbackData* cb = reinterpret_cast<CallbackData*>(callbackData);
    
    // Step 1: Allocate and fill callback data from param_2
    // FUN_006985a0 likely creates a callback context and stores it in the stack array
    int result = FUN_006985a0(callbackData, param_2); // returns some handle
    
    // Step 2: Perform some action using param_1 (probably 'this' or an ID)
    FUN_0069b380(param_1);
    
    // Step 3: Clean up the allocated handle (result)
    FUN_004d3e20(result);
    
    // Step 4: If callback data handle is non-zero, invoke the stored callback
    if (cb->handle != 0) {
        cb->callback(cb->handle);
    }
    return;
}