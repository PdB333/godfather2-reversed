// FUNC_NAME: Entity::checkProximityTrigger
undefined4 __fastcall Entity::checkProximityTrigger(Entity* this)
{
    int iVar1;
    Vector3 localPos;  // local_c, local_8, local_4 originally
    float timeDelta;
    float diffX, diffY, diffZ;
    float sqDist;

    iVar1 = FUN_00542d70();
    if (iVar1 != 0 && *(int*)(iVar1 + 0xc4) == 1 &&
        (g_currentTime - *(float*)(this + 0xf80) < g_timeThreshold))
    {
        if (*(float*)(this + 0xfc8) == *(float*)(this + 0xfc4))
        {
            FUN_00875190(&localPos, 0);
            diffX = *(float*)(this + 0xf84) - localPos.x;
            diffY = *(float*)(this + 0xf88) - localPos.y;
            diffZ = *(float*)(this + 0xf8c) - localPos.z;
            sqDist = diffX*diffX + diffY*diffY + diffZ*diffZ;
            if (g_squaredDistanceThreshold < sqDist)
            {
                return 1;
            }
        }
    }
    return 0;
}