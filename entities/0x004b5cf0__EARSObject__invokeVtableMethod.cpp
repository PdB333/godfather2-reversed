// FUNC_NAME: EARSObject::invokeVtableMethod
void __fastcall EARSObject::invokeVtableMethod(int thisPtr)
{
    // Performs a global pre-check or profiling hook (e.g., debug assertions, frame markers)
    FUN_009f2000(); // Likely CheckPreconditions() or BeginProfiling()

    // Calls a virtual method at vtable index 0x10 (offset 0x40) on the object pointed to
    // by the member at offset +0xD0.
    // This pattern is common for delegated function calls in EA's EARS engine.
    int* componentPtr = *(int**)(thisPtr + 0xD0); // +0xD0: pointer to a sub-object (e.g., SimObject or Component)
    int vtablePointer = *componentPtr;            // vtable pointer at offset 0 of component
    int methodOffset = 0x40;                     // index 16 (0x40 / 4 = 0x10)
    int methodPtr = *(int*)(vtablePointer + methodOffset);
    (*(void (__thiscall**)(int))methodPtr)((int)componentPtr); // Call the virtual method on the component
}