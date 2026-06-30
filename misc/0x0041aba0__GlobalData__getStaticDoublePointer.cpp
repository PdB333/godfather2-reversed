// FUNC_NAME: GlobalData::getStaticDoublePointer
// Function at 0x0041aba0: Returns the address of a global double pointer (PTR_PTR_0110b384).
// This is a getter for a static pointer that can be reassigned by the caller.
// Used in computed call at 0x00432480 (likely a dispatch table or singleton initialization).

void* getStaticDoublePointer()
{
    // Return address of the static double-pointer variable in data segment
    // The actual value at this address is a pointer to another pointer.
    return &PTR_PTR_0110b384; // +0x0: address of global double pointer
}