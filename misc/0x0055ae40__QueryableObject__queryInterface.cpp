// FUNC_NAME: QueryableObject::queryInterface
// Address: 0x0055ae40
// Role: Interface resolution function returning a pointer to the object for two known interface IDs.

int __thiscall QueryableObject::queryInterface(uint interfaceId, uint* outPtr)
{
    // Known interface identifiers (likely hash values)
    const uint INTERFACE_ID_ONE = 0xAF50FBA6;
    const uint INTERFACE_ID_TWO = 0xFFD2E5B1;

    if (interfaceId == INTERFACE_ID_ONE)
    {
        if (outPtr != nullptr)
        {
            *outPtr = reinterpret_cast<uint>(this);
        }
        return 1;
    }
    else
    {
        if (outPtr != nullptr)
        {
            *outPtr = 0;
        }
        if (interfaceId == INTERFACE_ID_TWO)
        {
            if (outPtr != nullptr)
            {
                *outPtr = reinterpret_cast<uint>(this);
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // Unreachable, kept for clarity
    return 1;
}