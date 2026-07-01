// FUNC_NAME: NPC::evaluateCoverForTarget
bool __thiscall NPC::evaluateCoverForTarget(int thisPtr, int targetObj, int coverIndex, int targetData)
{
    float maxDistance;
    float dx, dy, dz;
    float distSq;
    bool result;
    int iVar2;
    int iVar4;
    byte* coverFlags;
    int* collisionMgr;
    byte rayResult;
    
    // Cover data per node: each entry is 0x24 bytes.
    // At +0x140 in the array base: initial byte flags? Actually base is from this+0x2c88.
    // So coverFlags points to the start of the cover entry's data? But offset 0x140 is added.
    // Apparently each cover node has a data block of 0x24 bytes, stored in a contiguous array.
    // coverFlags = base + 0x140 + coverIndex * 0x24 -> points to byte flags at offset 0 of that entry.
    coverFlags = (byte*)(*(int*)(thisPtr + 0x2c88) + 0x140 + coverIndex * 0x24);
    
    // iVar2 likely an identifier for the target (e.g., entity ID or pointer)
    iVar2 = *(int*)(targetObj + 0x28);
    
    // The float at the same entry +0x20 (which is coverFlags+0x20) is a max distance threshold.
    // If it's not equal to a sentinel value (typically -1.0f indicating "unset"),
    // and if the target does NOT have a certain bit set (bit 1 of a flags word at targetObj+0x74),
    // and the squared distance from the player to the target position exceeds the threshold,
    // then return 0 (cover not usable).
    maxDistance = *(float*)(*(int*)(thisPtr + 0x2c88) + 0x160 + coverIndex * 0x24);
    if ((maxDistance != DAT_00d5ccf8) &&
        ((*(uint*)(targetObj + 0x74) >> 1 & 1) == 0))
    {
        // Get the player/camera position from some global system
        int playerPos = FUN_00471610();  // likely returns pointer to position struct
        dx = *(float*)(playerPos + 0x30) - *(float*)(targetData + 0xc);
        dy = *(float*)(playerPos + 0x34) - *(float*)(targetData + 0x10);
        dz = *(float*)(playerPos + 0x38) - *(float*)(targetData + 0x14);
        distSq = dz*dz + dy*dy + dx*dx;
        if (maxDistance < distSq)
        {
            return false;  // target too far
        }
    }
    
    // Check if the cover node's flags indicate it's usable (bit 1 not set? Actually bit 2? We'll call it kCoverFlagOccupied or something)
    if ((*coverFlags & 2) == 0)
    {
        return true;  // cover is free
    }
    
    // Cover node is "occupied" (bit 1 set). Do additional checks.
    // targetData+0x18 likely holds an entity pointer or ID.
    iVar4 = *(int*)(targetData + 0x18);
    if (iVar4 == 0)
    {
        // No entity in targetData; try line-of-sight check via collision manager
        collisionMgr = (int*)FUN_00716430();
        rayResult = (**(code**)(*collisionMgr + 0x14))(targetData + 0xc, 0, 0);
        if (rayResult != 0)
        {
            return true;
        }
    }
    else
    {
        // Subtract 0x48 from the entity pointer? Possibly to get a base object pointer.
        iVar4 = iVar4 - 0x48;
        if (iVar4 != iVar2)
        {
            // Check if the entity can be seen through cover
            rayResult = FUN_00715cd0(iVar4, 0, 0);
            if (rayResult != 0)
            {
                return true;
            }
        }
    }
    
    return false;
}