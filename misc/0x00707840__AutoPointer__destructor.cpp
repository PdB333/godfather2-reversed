// FUNC_NAME: AutoPointer::destructor
void __fastcall AutoPointer::destructor(int *thisPtr)
{
    // +0x00: pointer to managed resource (int)
    if (*thisPtr != 0) {
        // Release the resource (likely an operator delete or custom deallocation)
        operatorDelete(thisPtr);
        *thisPtr = 0; // Nullify to avoid dangling
    }
}