// FUNC_NAME: Sentient::isThreatDetected
// Function address: 0x007eb750
// Purpose: Check if any hostile entity is within detection range, based on the current target's entity list.

bool Sentient::isThreatDetected()
{
    // Field at +0x1ed8 (0x7b6 * 4) likely m_pCurrentTarget (Entity*)
    Entity* pTarget = *(Entity**)((char*)this + 0x1ed8);

    // If no target, target is invalid (0x48), or target's state field (+0xa4) < 2, skip
    if (!pTarget || (uintptr_t)pTarget == 0x48 || *(uint32_t*)((char*)pTarget + 0xa4) < 2)
        return false;

    // Get list from target's entity ID/pointer stored at +0x40
    void* list = EntityManager::getList(*(void**)((char*)pTarget + 0x40));
    EntityListNode* node = *(EntityListNode**)list; // Head of linked list

    if (!node)
        return false;

    do {
        Entity* pEntity = node->pEntity; // First element of node
        if (pEntity && pEntity != this) {
            // Retrieve global gameplay state (likely GameManager)
            GameManager* gameMgr = GameManager::getInstance(DAT_01131040);
            if (gameMgr && (*(uint8_t*)((char*)gameMgr + 0x44) & 0x40) != 0) {
                // Call virtual function at offset 0xc0 (e.g., getThreatLevel())
                float threat = pEntity->vtable->getThreatLevel(pEntity);
                if (threat > 0.0f) {
                    // Additional check: maybe isAlive or isVisible
                    if (isEntityActive(pEntity))
                        return true;
                }
                // Get position vectors from two entities (likely this and pEntity)
                Vector3* pos1 = (Vector3*)getPositionVector(); // FUN_00471610
                Vector3* pos2 = (Vector3*)getPositionVector(); // FUN_00471610 (second call returns same pointer? Actually different)
                // Compute squared distance between them
                float distSq = Vector3::distSquared(pos1 + 0x30, pos2 + 0x30); // Offset 0x30 for position inside struct
                if (distSq < g_fDetectionRangeSq) // _DAT_00d6ff0c
                    return true;
            }
        }
        node = node->pNext; // node[1] is next pointer
    } while (node);

    return false;
}