// FUNC_NAME: getOwnerFromComponentNode
int __thiscall getOwnerFromComponentNode(int componentNode)
{
    int ownerPtr;
    int basePtr;

    ownerPtr = 0;
    if ((*(int *)(componentNode + 4) != 0) &&
        (basePtr = *(int *)(*(int *)(componentNode + 4) + 4), basePtr != 0))
    {
        // Subtract the offset of the component node within its owner structure
        // +0x48 is likely the size of the component node or the base class offset
        ownerPtr = basePtr - 0x48;
        if (ownerPtr != 0)
        {
            return ownerPtr;
        }
    }
    return 0;
}