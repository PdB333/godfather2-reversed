// FUNC_NAME: EntityManager::findEntityByPredicate
// Reconstructed from function at 0x008e62c0
// This function iterates through an internal array of entity pointers (this+0x20, count at this+0x24)
// and returns the first entity for which a predicate (FUN_008e2d50) succeeds.
// The predicate appears to take two arguments: a reference entity (param_2) and the current list entity
// (the decompiler may have omitted the first argument due to calling convention confusion).
int __thiscall EntityManager::findEntityByPredicate(EntityManager* this, Entity* referenceEntity)
{
    // Check bit 19 of referenceEntity's flags (offset 0x5c). If clear, fail fast.
    if (!(referenceEntity->flags & (1 << 19)))
    {
        return 0;
    }

    // No entities in list -> return 0
    if (this->count == 0)
    {
        return 0;
    }

    // Iterate over all stored entities (pointers at this+0x20)
    // Note: The original decompiled code called FUN_008e2d50 only with param_2,
    // but it is likely intended to compare referenceEntity with each list entity.
    // We assume FUN_008e2d50 takes (referenceEntity, listEntity)
    for (unsigned int i = 0; i < this->count; i++)
    {
        Entity* listEntity = this->entityArray[i];
        if (entityMatchesPredicate(referenceEntity, listEntity)) // original: FUN_008e2d50(referenceEntity)
        {
            return listEntity;
        }
    }

    return 0;
}