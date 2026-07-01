// FUNC_NAME: getParentFromEmbeddedComponent
int __fastcall getParentFromEmbeddedComponent(int thisPtr)
{
    // Check if the component pointer at offset +0x84 is non-null.
    // The component is embedded within a parent object, and the parent
    // can be obtained by subtracting 0x48 from the component pointer.
    int* componentPtr = *(int**)(thisPtr + 0x84);
    if (componentPtr != nullptr)
    {
        return (int)componentPtr - 0x48; // Return pointer to owning parent object
    }
    return 0; // Null if no component
}