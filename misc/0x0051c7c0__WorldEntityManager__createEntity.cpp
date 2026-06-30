// FUNC_NAME: WorldEntityManager::createEntity

int WorldEntityManager::createEntity(uint entityType, uint flags, uint unknown, int parentId1, int parentId2, void* pData /* passed in EAX */)
{
    // Check if this manager is active and the entity type is allowed
    if (*(byte*)(this + 0x1c) != 0)
    {
        uint allowedTypes = (*(uint (__stdcall **)())PTR_FUN_0110ac0c)(*(byte*)(this + 0x1d));
        if ((entityType & allowedTypes) != 0)
        {
            Entity* pHead = s_entityListHead;
            // If the manager has "persistent" flag or the entity is marked as "portal" (0x400)
            if ((*(byte*)(this + 0x14) & 8) != 0 || (flags & 0x400) != 0)
            {
                // Search existing entities for a match
                while (pHead != nullptr)
                {
                    if (pHead->parent == this && pHead->field_70 == parentId1 && pHead->field_74 == parentId2)
                    {
                        if (pHead->pReserved == nullptr)
                            return (int)pHead;
                        *pHead->pReserved = 0;
                        pHead->pReserved = nullptr;
                        return (int)pHead;
                    }
                    pHead = pHead->pNext;
                }
                // If flagged as portal, return 0 if not found
                if ((flags & 0x400) != 0)
                    return 0;
            }

            // Allocate new entity
            Entity* pEntity = (Entity*)FUN_0051a1a0();
            if (pEntity != nullptr)
            {
                // Initialize ID fields
                pEntity->field_74 = parentId2;
                pEntity->field_70 = parentId1;

                // Copy 16 dwords from pData into entity body offsets
                uint* pSrc = (uint*)pData;
                pEntity->dataBlock[0] = pSrc[0];
                pEntity->dataBlock[1] = pSrc[1];
                pEntity->dataBlock[2] = pSrc[2];
                pEntity->dataBlock[3] = pSrc[3];
                pEntity->dataBlock[4] = pSrc[4];
                pEntity->dataBlock[5] = pSrc[5];
                pEntity->dataBlock[6] = pSrc[6];
                pEntity->dataBlock[7] = pSrc[7];
                pEntity->dataBlock[8] = pSrc[8];
                pEntity->dataBlock[9] = pSrc[9];
                pEntity->dataBlock[10] = pSrc[10];
                pEntity->dataBlock[11] = pSrc[11];
                pEntity->dataBlock[12] = pSrc[12];
                pEntity->dataBlock[13] = pSrc[13];
                pEntity->dataBlock[14] = pSrc[14];
                pEntity->dataBlock[15] = pSrc[15];

                // Store entity type
                pEntity->entityType = entityType;

                // Call some initialization
                FUN_0051d020();

                // Call virtual function at +0x78
                (*(void (__thiscall **)(Entity*))(pEntity->vtable + 0x78))(pEntity);

                // If flag has bit 2 (0x4), set bit 0x400000 in entity flags
                if ((flags & 4) != 0)
                    pEntity->flags |= 0x400000;

                // If parent has flag 0x20000000, add bit 0 to flags
                if ((*(uint*)(this + 0x14) & 0x20000000) != 0)
                    flags |= 1;

                bool bAddToActiveList = false;
                bool bCallTrigger = false;
                // Determine mode based on flags (bits 1 and 0)
                if ((flags & 2) == 0)
                {
                    if ((flags & 1) == 0)
                    {
                        // Normal create, check if entity validation succeeds
                        if ((*(uint*)(this + 0x14) & 4) == 0)
                        {
                            if (FUN_0051c200((int)pEntity) == 0)
                            {
                                FUN_0051a330();
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        pEntity->flags |= 1;
                        if ((*(byte*)(this + 0x14) & 4) == 0)
                        {
                            bAddToActiveList = true;
                            bCallTrigger = true;
                        }
                    }
                }
                else
                {
                    pEntity->flags |= 1;
                    bAddToActiveList = true;
                    bCallTrigger = false;
                }

                FUN_0051a710(); // Possibly some post-process

                // Append new entity to end of linked list
                int* ppNext = &s_entityListHead;
                int next = s_entityListHead;
                while (next != 0)
                {
                    ppNext = (int*)(next + 0x14);
                    next = *ppNext;
                }
                pEntity->pNext = 0;
                *ppNext = (int)pEntity;

                // If we need to add to active list and not already active
                if (bCallTrigger && (pEntity->flags & 0x40000) == 0)
                {
                    pEntity->flags |= 0x40000;
                    FUN_0051b120(); // Trigger some event
                }
                if (bAddToActiveList)
                {
                    FUN_0051b120(); // Trigger event
                }

                // If entity has flag 1 and parent has flag 0x20000000, set high bit
                if ((pEntity->flags & 1) != 0 && (*(uint*)(*(int*)(pEntity + 0x10) + 0x14) & 0x20000000) != 0)
                {
                    pEntity->flags |= 0x80000000;
                }

                // If entity is in active list and has flag 1, and validation passes
                if ((pEntity->flags & 0x40000) != 0 && (pEntity->flags & 1) != 0)
                {
                    if (FUN_0051c200((int)pEntity) != 0)
                    {
                        FUN_0051b210(); // Finalize activation
                    }
                }

                // Clear flag 0 if sign bit not set
                if ((int)pEntity->flags >= 0)
                    pEntity->flags &= 0xfffffffe;

                // If global flag is set, call some debug/logging
                if (s_globalDebugFlag != 0)
                    FUN_0051abd0((int)pEntity, s_debugData);

                return (int)pEntity;
            }
        }
    }
    return 0;
}