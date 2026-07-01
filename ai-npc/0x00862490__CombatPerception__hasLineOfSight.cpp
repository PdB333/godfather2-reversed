// FUNC_NAME: CombatPerception::hasLineOfSight

// This function checks if this entity (perception component) has line of sight to a target entity,
// with support for recursive multi-hop visibility (e.g., through reflections or chain of entities).
// param_2: recursion depth (number of hops allowed)
// returns: 1 if visible, 0 otherwise

bool CombatPerception::hasLineOfSight(int depth)
{
    // Get player data from global state (likely player transform/camera)
    // FUN_00471610 is a getter for player data (maybe getPlayerData())
    TNL::NetObject* playerData = FUN_00471610(); // iVar1

    // Check if entity is hidden/untargetable (bitmask at +0xf28)
    if ((*this->m_flags & 0x0E000000) != 0) {
        return true; // always visible if hidden flag set? actually early out for "temporarily visible"
    }

    // Get maximum detection range from component data
    float outerRadius = this->m_outerRadius; // +0xff8

    // Compare with global max detection limit
    if (g_MaxDetectionRange < outerRadius) {
        // Use larger of inner and outer detection radii
        float effectiveRadius = (this->m_detectionRadius > this->m_alertRadius) ? this->m_detectionRadius : this->m_alertRadius; // +0xfa0 and +0xfa4
        effectiveRadius += outerRadius;

        // Get player position (from playerData)
        Vector3 playerPos = playerData->position; // +0x30,0x34,0x38

        // Compute squared distance from this entity's position to player
        Vector3 selfPos = this->m_position; // +0xffc,0x1000,0x1004
        float dx = playerPos.x - selfPos.x;
        float dy = playerPos.y - selfPos.y;
        float dz = playerPos.z - selfPos.z;
        float distSq = dx*dx + dy*dy + dz*dz;

        if (distSq < effectiveRadius * effectiveRadius) {
            return true; // player is within simple distance check
        }
    }

    // Check if a target is assigned and recursion depth allows further checks
    int targetId = this->m_targetID; // +0x1194
    if (targetId == 0 || targetId == 0x48 || depth < 1) {
        return false;
    }

    // Resolve target entity by its hash (0x10e5319e is some hash function seed/constant)
    // FUN_006c12a0 likely finds entity by ID/hash
    Entity* targetEntity = FUN_006c12a0(targetId - 0x48, 0x10e5319e);
    if (targetEntity == nullptr) {
        return false;
    }

    // Get multiple player/entity data for direction vectors
    // The function is called six times, likely returning pointers to different entities' transform data
    // Pairing: (iVar1,iVar2) give x components, (iVar3,iVar4) y, (iVar5,iVar6) z
    Entity* data1 = FUN_00471610(); // iVar1
    Entity* data2 = FUN_00471610(); // iVar2
    Entity* data3 = FUN_00471610(); // iVar3
    Entity* data4 = FUN_00471610(); // iVar4
    Entity* data5 = FUN_00471610(); // iVar5
    Entity* data6 = FUN_00471610(); // iVar6

    // Construct two direction vectors from these components
    // Vector A = (data1->dirX, data3->dirY, data5->dirZ)
    // Vector B = (data2->dirX, data4->dirY, data6->dirZ)
    // This is used for line-of-sight cone check
    float dot1 = data4->dirY * data3->dirY + data2->dirX * data1->dirX + data6->dirZ * data5->dirZ; // +0x24 +0x20 +0x28

    // Compare dot product to global cosine threshold (likely field of view)
    if (g_VisibilityCosineThreshold <= dot1) {
        // Now compute direction from this entity to target (player?)
        Entity* data7 = FUN_00471610(); // iVar1 again? Actually fresh calls
        Entity* data8 = FUN_00471610(); // iVar2

        Vector3 dirToTarget;
        dirToTarget.x = data8->position.x - data7->position.x; // +0x30
        dirToTarget.y = data8->position.y - data7->position.y; // +0x34
        dirToTarget.z = data8->position.z - data7->position.z; // +0x38

        // Normalize the direction vector
        FUN_0043a210(&dirToTarget, &dirToTarget); // VectorNormalize (assumed)

        // Get two more transform data for the second cone check
        Entity* data9 = FUN_00471610();  // iVar1
        Entity* data10 = FUN_00471610(); // iVar2
        Entity* data11 = FUN_00471610(); // iVar3

        // Dot product with normalized direction to target
        float dot2 = data10->dirY * dirToTarget.y + data9->dirX * dirToTarget.x + data11->dirZ * dirToTarget.z;
        if (g_VisibilityCosineThreshold <= dot2) {
            // Recursively check visibility with decreased depth
            return this->hasLineOfSight(depth - 1);
        }
    }

    return false;
}