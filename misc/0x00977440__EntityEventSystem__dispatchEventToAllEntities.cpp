// FUNC_NAME: EntityEventSystem::dispatchEventToAllEntities
void __fastcall EntityEventSystem::dispatchEventToAllEntities(EventData* eventData)
{
    EntityManager* entityMgr = g_pEntityManager; // DAT_0112a66c
    int compareValue = *(int*)((uint)eventData + 0x144); // +0x144
    int* entityList = *(int**)((uint)entityMgr + 0x10); // +0x10: pointer to array of entity pointers
    uint count = *(uint*)((uint)entityMgr + 0x14); // +0x14: number of entities

    if (count != 0) {
        for (uint i = 0; i < count; ++i) {
            int entityEntryPtr = entityList[i]; // each entry is a pointer to an EntityEntry structure
            Entity* entity = (Entity*)getEntityByID(*(int*)(entityEntryPtr + 0x84)); // +0x84: ID field
            if (entity != 0) {
                switch (*(int*)((uint)eventData + 0x14c)) { // +0x14c: event type
                case 3:
                    *(bool*)((uint)entity + 0xad) = false; // +0xad: flag1
                    *(int*)((uint)eventData + 0x13c) = 0; // +0x13c: result
                    break;
                case 4:
                    *(bool*)((uint)entity + 0xad) = (compareValue == *(int*)(entityEntryPtr + 0x50)); // +0x50: some ID
                    break;
                }
                *(bool*)((uint)entity + 0x280) = false; // +0x280: flag2
            }
        }
    }
}