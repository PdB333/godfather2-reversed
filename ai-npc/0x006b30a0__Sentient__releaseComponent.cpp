// FUNC_NAME: Sentient::releaseComponent
// Reconstructed C++ for function at 0x006b30a0
// This function is a destructor helper that releases a component held at offset +0x174.
// It checks if the component pointer is non-null and calls the release function FUN_008c7d50.

void __fastcall Sentient::releaseComponent(Sentient* thisPtr)
{
    // Offset +0x174: Pointer to a component object (e.g., RagdollComponent, or similar owned object)
    void* component = thisPtr->field_0x174;
    if (component != NULL) {
        // FUN_008c7d50 is likely a destructor or release function that takes the component and the owning object.
        FUN_008c7d50(component, thisPtr);
    }
}