// FUNC_NAME: Entity::isVisible
// Address: 0x008773c0
// Role: Checks visibility of an entity against a frustum/plane and possibly a flag override.
uint __thiscall Entity::isVisible( int* visibilityContext )
{
    int entityPtr;
    uint result;
    uint tempLocal[2]; // maybe a stack variable for FUN_004af8c0

    // Check if "always visible" flag is set (bit 1 of m_flags at +0xC88)
    if ( ( ( this->m_highFlags >> 2 ) & 1 ) != 0 ) {
        // Return shifted value from another flag (bit 10) as a combined result
        return ( ( this->m_highFlags >> 10 ) << 8 );
    }

    entityPtr = visibilityContext[0];
    result = 0;
    if ( ( entityPtr != 0 ) && ( *(char*)(entityPtr + 0x10) + entityPtr != 0 ) ) {
        // Call some initialization/hash function (e.g., to get a pointer)
        FUN_004af8c0( tempLocal, 0x2001 );
        result = 0;
        if ( tempLocal[0] != 0 ) {
            result = tempLocal[0];
        }
    }

    if ( result == this ) {
        // If result equals this, call another function to retrieve something
        result = FUN_004afca0( visibilityContext[1] );
    }

    if ( ( result != 0 ) && ( *(char*)(result + 0x15E) < 0 ) ) {
        // Initialize global camera/frustum data if first time
        if ( ( DAT_globalCameraFlags & 1 ) == 0 ) {
            DAT_globalCameraFlags = DAT_globalCameraFlags | 1;
            DAT_globalCameraPositionX = 0.0f;
            DAT_globalCameraPositionY = DAT_globalCameraFacing;
            DAT_globalCameraPositionZ = 0.0f;
            DAT_globalCameraPadding = 0;
        }

        // Use visibilityContext[3] as a pointer to a bounding sphere (or similar)
        uint boundingSpherePtr = visibilityContext[3];
        if ( ( boundingSpherePtr != 0 ) &&
            ( DAT_globalFrustumThreshold <=
                *(float*)(boundingSpherePtr + 0x18) * DAT_globalCameraDirectionZ +
                *(float*)(boundingSpherePtr + 0x14) * DAT_globalCameraDirectionY +
                DAT_globalCameraDirectionX * *(float*)(boundingSpherePtr + 0x10) ) ) {
            // Return special value indicating visible (bit 8 set)
            return CONCAT31( (int3)(boundingSpherePtr >> 8), 1 );
        }
    }

    return result & 0xFFFFFF00;
}