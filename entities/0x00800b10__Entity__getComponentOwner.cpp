// FUNC_NAME: Entity::getComponentOwner
int __fastcall Entity::getComponentOwner(int thisPtr)
{
    // thisPtr is a pointer to an Entity (or similar)
    // Offset +0x74c: pointer to a component or child object
    int componentPtr = *(int *)(thisPtr + 0x74c);
    
    // Check if the component pointer is valid (not null and not a sentinel value 0x48)
    if (componentPtr != 0 && componentPtr != 0x48)
    {
        // The component is embedded inside a larger object; subtract header size (0x48) to get the owner object
        int ownerPtr = componentPtr - 0x48; // +0x48 is the offset from owner to component
        // Check bit 2 at +0x1d0 of the owner (likely a flag indicating validity/activity)
        // Bit 2 (value 4) tested via (value >> 2) & 1
        if ((*(unsigned int *)(ownerPtr + 0x1d0) >> 2 & 1) != 0 && componentPtr != 0)
        {
            return ownerPtr;
        }
    }
    return 0; // No valid owner found
}