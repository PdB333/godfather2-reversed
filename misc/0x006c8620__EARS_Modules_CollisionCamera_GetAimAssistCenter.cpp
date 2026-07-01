// Xbox PDB: EARS::Modules::CollisionCamera::GetAimAssistCenter
// FUNC_NAME: BoneController::calcBoneAimTarget
bool BoneController::calcBoneAimTarget(Vector3D& outTarget, int boneId)
{
    // boneId: 0 = player position, 1 = thoracic, 2 = lumbar, 3 = neck1, 4 = shoulder with pelvis interpolation, other = lumbar with neck1 interpolation
    if (!this)
        return false;

    switch (boneId)
    {
    case 0:
    {
        // Get player position from global
        int playerObj = FUN_00471610(); // returns pointer to player object?
        outTarget.x = *(float*)(playerObj + 0x30);
        outTarget.y = *(float*)(playerObj + 0x34);
        outTarget.z = *(float*)(playerObj + 0x38);
        return true;
    }
    case 1:
        if (!getBoneIndex("m_thoracic"))
            return false;
        getBoneWorldPosition(); // fill internal data
        return true;
    case 2:
        if (!getBoneIndex("m_lumbar"))
            return false;
        getBoneWorldPosition();
        return true;
    case 3:
        if (!getBoneIndex("m_neck1"))
            return false;
        getBoneWorldPosition();
        return true;
    case 4:
    {
        // Get shoulder and pelvis positions and average with chest
        if (!getBoneIndex("l_shoulder"))
            return false;
        Vector3D shoulderPos;
        getBoneWorldPosition(&shoulderPos); // assume stores in internal buffer
        
        if (!getBoneIndex("m_pelvis"))
            return false;
        Vector3D pelvisPos;
        getBoneWorldPosition(&pelvisPos);
        
        // Also get third bone? Actually it appears to also get m_thoracic? The decompiled code is messy.
        // Based on code: seems to compute weighted average of three points (shoulder, shoulder?, pelvis?) 
        // The original code had some odd stack calculations. Likely it takes shoulder, chest (from case1?), and pelvis.
        // But we don't have chest position stored. Actually it calls getBoneIndex for m_thoracic?
        // Let's reconstruct from the pattern:
        // It first gets l_shoulder, then later calls getBoneIndex for m_pelvis. The third point might come from earlier case1? Or from a previous call? The stack manipulations suggest it's using previously stored data.
        // Simpler: it uses the positions of l_shoulder, m_pelvis, and something else (maybe the result of case1?).
        // Since the decompiled is ambiguous, I'll assume it gets three bones: l_shoulder, m_pelvis, and m_thoracic.
        if (!getBoneIndex("m_thoracic"))
            return false;
        Vector3D chestPos;
        getBoneWorldPosition(&chestPos);
        
        // Weighted average: (sh+sh+chest)/3 ? Actually code: (float)(pcVar8 + pcVar8 + pcStack_38) * DAT_00d5c454
        // Where pcVar8 = "m_pelvis", pcStack_38 = something. This is too mangled.
        // Likely it computes (shoulder + pelvis + chest) / 3.0f
        outTarget.x = (shoulderPos.x + pelvisPos.x + chestPos.x) * 0.333333f; // DAT_00d5c454 = ~0.3333?
        outTarget.y = (shoulderPos.y + pelvisPos.y + chestPos.y) * 0.333333f;
        outTarget.z = (shoulderPos.z + pelvisPos.z + chestPos.z) * 0.333333f;
        return true;
    }
    default:
    {
        // Default: interpolate between lumbar and neck1 positions
        if (!getBoneIndex("m_lumbar"))
            return false;
        Vector3D lumbarPos;
        getBoneWorldPosition(&lumbarPos);
        
        if (!getBoneIndex("m_neck1"))
            return false;
        Vector3D neckPos;
        getBoneWorldPosition(&neckPos);
        
        // Lerp: out = lumbar + (neck - lumbar) * DAT_00d5f040
        float t = DAT_00d5f040; // likely 0.5f or similar
        outTarget.x = lumbarPos.x + (neckPos.x - lumbarPos.x) * t;
        outTarget.y = lumbarPos.y + (neckPos.y - lumbarPos.y) * t;
        outTarget.z = lumbarPos.z + (neckPos.z - lumbarPos.z) * t;
        return true;
    }
    }
}