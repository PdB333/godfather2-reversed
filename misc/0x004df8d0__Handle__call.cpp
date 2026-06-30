// FUNC_NAME: Handle::call
// Function address: 0x004df8d0
// Role: Forwarding function that dereferences a handle (pointer to pointer) and calls a method on the target if non-null.
// The class has a pointer member at offset +0x00 (int* m_pTarget).
// This pattern is common for smart handles or proxy objects in the EARS engine.

void __thiscall Handle::call(int* thisPtr, int arg0, int arg1)
{
    // Dereference the handle to get the actual object pointer
    int* pTarget = reinterpret_cast<int*>(*thisPtr);
    if (pTarget != nullptr)
    {
        // Forward the call to the target object's method at 0x0051cbc0
        FUN_0051cbc0(pTarget, arg0, arg1);
    }
    // Return void (implicit)
}