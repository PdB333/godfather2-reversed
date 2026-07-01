// FUNC_NAME: EntityManager::updateAllEntities
// Function address: 0x0090c610
// Role: Iterates over all managed entities and calls an update function for each.
// The count of entities is stored at offset +0x18 in the manager object.

void __fastcall EntityManager::updateAllEntities(EntityManager* thisPtr)
{
    uint entityCount = *(uint*)((int)thisPtr + 0x18); // +0x18: m_entityCount
    for (uint i = 0; i < entityCount; i++)
    {
        // Calls a per-entity update function (likely advances an internal index)
        updateEntity(); // FUN_004df6e0
    }
}