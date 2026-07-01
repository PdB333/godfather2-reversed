// FUNC_NAME: Player::initComponent
void __fastcall Player::initComponent(Player* thisPtr)
{
    // Set a flag at offset 0x18c indicating component initialization is underway
    thisPtr->flags |= 0x1000; // +0x18c: bitfield of flags

    // Attempt to allocate memory for a component (size 0xC = 12 bytes)
    void* allocatedMemory = FUN_009c8e50(0xC); // allocation function

    if (allocatedMemory != nullptr)
    {
        // Construct the component, passing 'this' as the parent
        Component* newComponent = (Component*)FUN_0084e6f0(thisPtr); // component constructor

        // Store pointer to the component at offset 0x1b0
        thisPtr->m_pComponent = newComponent; // +0x1b0: pointer to component
    }
    else
    {
        // Allocation failed; set component pointer to null
        thisPtr->m_pComponent = nullptr;
    }
}