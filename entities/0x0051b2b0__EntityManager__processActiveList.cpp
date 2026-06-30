// FUNC_NAME: EntityManager::processActiveList
void __thiscall EntityManager::processActiveList(void)
{
    short activeCount;
    int i;
    Entity** entryPtr;
    Entity* entity;
    uint32_t* memoryHeader;
    MemoryManager* memoryMgr;
    
    // TLS: get memory manager pointer (from FS:[0x2c])
    memoryMgr = (MemoryManager*)__readfsdword(0x2c);
    
    activeCount = *(short*)(this + 0x80);
    if (0 < activeCount) {
        entryPtr = (Entity**)(this + 0xF4);
        i = 0;
        do {
            entity = *entryPtr;
            if ((*(int*)(this + 0x10) != 0) && (entity != 0)) {
                // Mark memory block used by this entity (bit 30 = 0x40000000)
                memoryHeader = (uint32_t*)(*(int*)(entity->field_0x10) + *(int*)(memoryMgr->field_0x8));
                *memoryHeader |= 0x40000000;
                // Call entity's virtual function at vtable+0x24 (likely an update method)
                (*(void (**)(void))(entity->vtable + 0x24))();
            }
            i++;
            entryPtr += 5; // 5 int32 stride (20 bytes per entry)
        } while (i < activeCount);
    }
}