// FUNC_NAME: EntityPrototype::createInstance
int __fastcall EntityPrototype::createInstance(EntityPrototype* thisPtr)
{
    MemoryManager* memMgr = MemoryManager::getInstance(); // FUN_009c8f80
    AllocatorParams allocParams;
    allocParams.size = 0x170;
    allocParams.alignment = 0x10;
    allocParams.flags = 0;
    
    NewEntity* newEntity = (NewEntity*)memMgr->allocate(0x170, &allocParams);
    if (newEntity == nullptr)
        return 0;
    
    int result = Entity::initFromTemplate(newEntity, thisPtr); // FUN_006cd2b0
    if (result == 0)
        return 0;
    
    // Check if entity on slot 0x78 is invalid or in a specific state (0x48)
    if (thisPtr->entitySlot0x78 == 0 || thisPtr->entitySlot0x78 == 0x48)
    {
        ResourceManager* resMgr = getResourceManager(thisPtr + 0x68, 0); // FUN_00445ff0
        insertResourceByHash(resMgr, 0x55859efa, &allocParams); // FUN_004480d0
    }
    
    // Check if entity on slot 0x80 is invalid or in a specific state (0x48)
    if (thisPtr->entitySlot0x80 == 0 || thisPtr->entitySlot0x80 == 0x48)
    {
        ResourceManager* resMgr = getResourceManager(thisPtr + 0x58, 0); // FUN_00445ff0
        insertResourceByHash(resMgr, 0x55859efa, &allocParams); // FUN_004480d0
    }
    
    Entity::setupSubEntity(thisPtr + 0x78); // FUN_006cd230
    newEntity->flags |= 0x80000; // Set some flag (e.g., kFlagActive)
    return (int)newEntity;
}