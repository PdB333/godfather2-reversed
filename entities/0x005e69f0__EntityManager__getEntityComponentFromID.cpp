// FUNC_NAME: EntityManager::getEntityComponentFromID
static void* __fastcall EntityManager_getEntityComponentFromID(void* entityManager, int componentHandle)
{
    // Call internal lookup function that searches for a component entry by handle.
    // It returns a pointer to a structure that contains the actual component pointer at offset 0x18.
    int lookupResult = internalComponentLookup(componentHandle, nullptr, nullptr);
    if (lookupResult != 0)
    {
        // The looked-up structure has a pointer to the component at offset +0x18.
        return *(void**)(lookupResult + 0x18);
    }
    return 0;
}