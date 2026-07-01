// FUNC_NAME: Attachment::updateAttachedTransform
// Address: 0x008ffd80
// Role: Syncs position/rotation of an attached object (at this+0x184) with the current player's transform, scaled by a global factor.
// Note: uses __fastcall with this in ECX (first param). Global DAT_00d5c458 = world scale factor. DAT_00d5780c = probably 1.0f (unused).

void __fastcall Attachment::updateAttachedTransform(int this) // this is param_1
{
    void* pAttachedObj; // from this+0x184
    int playerObj; // returned by FUN_00471610 (likely Player*)
    Vector3 localPos; // scaled player position (local_3c,38,34)
    Vector3 localRot; // rotation from player (local_30,2c,28)
    float unused1; // local_14 = _DAT_00d5780c (maybe 1.0)
    float unused2; // local_24 = _DAT_00d5780c (unused)
    
    // Check if the attached object pointer is valid
    pAttachedObj = *(void**)(this + 0x184);
    if (pAttachedObj != 0) {
        // Get current player object
        playerObj = FUN_00471610(); // e.g., getActivePlayer()
        
        // Retrieve player's world position (fills localPos with three floats)
        FUN_004bffa0(&localPos, playerObj); // e.g., getPosition()
        
        // Apply global world scale to position components
        localPos.x *= _DAT_00d5c458; // g_worldScale
        localPos.y *= _DAT_00d5c458;
        localPos.z *= _DAT_00d5c458;
        
        // Copy rotation from player object (offsets +0x30, +0x34, +0x38)
        // These three floats might represent a quaternion or euler angles
        localRot.x = *(float*)(playerObj + 0x30);
        localRot.y = *(float*)(playerObj + 0x34);
        localRot.z = *(float*)(playerObj + 0x38);
        
        // Unused constants (likely 1.0f for homogeneous transform)
        unused1 = _DAT_00d5780c; // maybe 1.0f
        unused2 = _DAT_00d5780c; // maybe 1.0f
        
        // Replicate scaled position into a new Vector3 for the call
        // (could be due to stack layout)
        Vector3 posForTransform;
        posForTransform.x = localPos.x;
        posForTransform.y = localPos.y;
        posForTransform.z = localPos.z;
        
        // Call to set transform of attached object
        // Third parameter may be another player object (possibly the same)
        FUN_00850f90(this + 0x184, &posForTransform, &localRot, FUN_00471610());
    }
}