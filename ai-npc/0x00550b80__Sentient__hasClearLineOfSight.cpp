// FUNC_NAME: Sentient::hasClearLineOfSight
bool Sentient::hasClearLineOfSight(void) {
    // +0x40 = mForward.x, +0x44 = mForward.y, +0x48 = mForward.z
    // +0x90 = mToTarget.x, +0x94 = mToTarget.y, +0x98 = mToTarget.z
    // +0xac = mConeCosineThreshold (dot product threshold for field-of-view)
    
    float dot = mForward.x * mToTarget.x + mForward.y * mToTarget.y + mForward.z * mToTarget.z;
    
    // If target is within the forward cone (dot >= threshold), skip expensive raycast
    // If outside cone, perform line-of-sight raycast (can still see if no obstruction)
    if (dot < mConeCosineThreshold) {
        byte raycastResultBuffer[16];           // local_70 – output from raycast
        int raycastMin = -1;                    // local_5c – invalid / init value
        int raycastMax = -1;                    // local_50 – invalid / init value
        int collisionMask = DAT_00e2b1a4;       // local_60 – global collision filter
        int hitCount = 0;                       // local_30 – number of hits
        int hitResult = 0;                      // local_20 – set to non‑zero if hit
        performRaycast(raycastResultBuffer);    // FUN_00550c50
        return hitResult == 0;                  // no hit → line of sight clear
    }
    return false;                               // target behind cone, no raycast
}