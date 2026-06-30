// FUNC_NAME: CTryCallHandler::invoke
undefined4 __thiscall CTryCallHandler::invoke(void *this, code *callback, undefined4 param_3)
{
    undefined4 savedStackPtr;      // saved stack pointer from this+0x50
    undefined1 jmpbuf[64];         // buffer for setjmp/longjmp
    undefined4 retVal = 0;         // return value (always 0)

    // Save the current "stack pointer" stored at offset 0x50 of the object
    savedStackPtr = *(undefined4 *)((int)this + 0x50);

    // Replace it with the address of our local variable (effectively pushing a new frame)
    *(undefined4 **)((int)this + 0x50) = &savedStackPtr;

    // Try to execute the callback; if an exception occurs (longjmp), 
    // setjmp returns non-zero and we skip the callback.
    if (__setjmp3(jmpbuf, 0) == 0) {
        // Normal execution: call the function pointer with 'this' and param_3
        callback(this, param_3);

        // Restore the saved stack pointer
        *(undefined4 *)((int)this + 0x50) = savedStackPtr;
    } else {
        // Exception path: restore stack pointer and return 0
        *(undefined4 *)((int)this + 0x50) = savedStackPtr;
    }

    return retVal;
}