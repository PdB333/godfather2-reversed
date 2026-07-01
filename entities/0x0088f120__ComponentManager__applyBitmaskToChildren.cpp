// FUNC_NAME: ComponentManager::applyBitmaskToChildren
void __thiscall ComponentManager::applyBitmaskToChildren(uint bitMask)
{
    // Iterate over linked list of children.
    // List is circular with sentinel at this+0x64 (offset 0x64).
    // First real node is at this+0x68 (sentinel->next).
    for (int node = *(int *)(this + 0x68); node != (int)(this + 0x64); node = FUN_00ab3c50(node))
    {
        // Each node points to a child object at offset +0x10.
        int child = *(int *)(node + 0x10);

        // Check if the specific bit is set in the mask stored at this+0x5C.
        if ((*(uint *)(this + 0x5C) & bitMask) == 0)
        {
            // Bit not set -> set byte at child+0x280 to 1 (enable).
            *(byte *)(child + 0x280) = 1;
        }
        else
        {
            // Bit set -> set byte at child+0x280 to 0 (disable).
            *(byte *)(child + 0x280) = 0;
        }
    }
}