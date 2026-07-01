// FUNC_NAME: IsPlayerWithinAimCone
bool IsPlayerWithinAimCone(void) {
    Vector3 aimPosition;   // from local_38, local_34, local_30
    Vector3 aimDirection;  // from local_2c, local_28, local_24

    // Retrieve aim origin (position) and aim direction (forward vector)
    // The three zero parameters are likely unused flags or indices.
    getAimVectors(&aimPosition, &aimDirection, 0, 0, 0);

    int playerTransformPtr = getPlayerTransform();
    Vector3 playerPosition;
    playerPosition.x = *(float *)(playerTransformPtr + 0x30);  // +0x30: world x
    playerPosition.y = *(float *)(playerTransformPtr + 0x34);  // +0x34: world y
    playerPosition.z = *(float *)(playerTransformPtr + 0x38);  // +0x38: world z

    Vector3 directionToPlayer;
    directionToPlayer.x = playerPosition.x - aimPosition.x;
    directionToPlayer.y = playerPosition.y - aimPosition.y;
    directionToPlayer.z = playerPosition.z - aimPosition.z;

    // Normalize the direction vector in-place.
    vectorNormalize(&directionToPlayer, &directionToPlayer);

    // Dot product: directionToPlayer · aimDirection
    float dot = directionToPlayer.x * aimDirection.x +
                directionToPlayer.y * aimDirection.y +
                directionToPlayer.z * aimDirection.z;

    // Global threshold (likely cosine of half-angle of aim cone)
    return _DAT_00d65ffc < dot;  // Returns true if dot > threshold (player is within cone)
}