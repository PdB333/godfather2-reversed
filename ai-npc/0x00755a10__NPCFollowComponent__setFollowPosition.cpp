// FUNC_NAME: NPCFollowComponent::setFollowPosition
void __thiscall NPCFollowComponent::setFollowPosition(float *inputPosition)
{
    // Copy input 3D position to target position at +0x6c (x,y,z)
    *(Vector3 *)(this + 0x6c) = *(Vector3 *)inputPosition;

    // Check flag at +0x58 bit 0x20 – if set, clamp target to follow radius from player
    if ((*(byte *)(this + 0x58) & 0x20) != 0)
    {
        // Get player (or camera) position from global singleton
        float *playerPos = (float *)getPlayerPosition(); // returns pointer to struct with position at +0x30
        Vector3 delta;

        delta.x = *(float *)(playerPos + 0x30 / sizeof(float)) - inputPosition[0];  // playerX - targetX
        delta.y = *(float *)(playerPos + 0x34 / sizeof(float)) - inputPosition[1];  // playerY - targetY
        delta.z = *(float *)(playerPos + 0x38 / sizeof(float)) - inputPosition[2];  // playerZ - targetZ

        normalizeVector3(&delta); // unit vector from target towards player

        // Clamp target to within constant radius of player
        float followDistance = g_followClampRadius; // global float at 0x00d5d7b8
        *(float *)(this + 0x6c) = delta.x * followDistance + playerPos[0x30 / 4];
        *(float *)(this + 0x70) = delta.y * followDistance + playerPos[0x34 / 4];
        *(float *)(this + 0x74) = delta.z * followDistance + playerPos[0x38 / 4];
    }
}