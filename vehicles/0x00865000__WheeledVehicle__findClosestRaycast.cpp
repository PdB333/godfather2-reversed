// FUNC_NAME: WheeledVehicle::findClosestRaycast
bool __thiscall WheeledVehicle::findClosestRaycast(const Vec3& queryPoint, Vec3& outClosestPoint, float& outDistance, int& outIndex)
{
    // Layout of object at this:
    // +0x10B0: Vec3 m_fallbackPoint (default source/target when missing)
    // +0x10C0: int m_sourceValid[3]  (0 = invalid)
    // +0x10C8: Vec3* m_sourcePtr[3] (pointer to source positions)
    // +0x10CC: int m_targetValid[3] (0 = invalid)
    // +0x10D4: Vec3* m_targetPtr[3] (pointer to target positions)
    // Each segment i is defined by source and target points.

    float bestDist = -1.0f;          // initial negative sentinel
    int bestIndex = -1;
    Vec3 bestPoint;                  // will be set if found

    for (int i = 0; i < 3; ++i)
    {
        int sourceValid = *(int*)((char*)this + 0x10C0 + i * 0xC);
        Vec3* source = sourceValid ? *(Vec3**)((char*)this + 0x10C8 + i * 0xC) : nullptr;

        int targetValid = *(int*)((char*)this + 0x10CC + i * 0xC);
        Vec3* target = targetValid ? *(Vec3**)((char*)this + 0x10D4 + i * 0xC) : nullptr;

        // Fallback for missing source (index 1) or missing target (index 0)
        if (!source && i == 1)
        {
            source = (Vec3*)((char*)this + 0x10B0); // m_fallbackPoint
        }
        if (!target && i == 0)
        {
            target = (Vec3*)((char*)this + 0x10B0); // m_fallbackPoint
        }

        if (source && target)
        {
            Vec3 closestOnSegment;
            float squaredDist = calcSquaredDistanceToSegment(queryPoint, *source, *target, closestOnSegment);
            float dist = sqrt(squaredDist);

            if (bestDist < 0.0f || dist < bestDist)
            {
                bestPoint = closestOnSegment;
                bestDist = dist;
                bestIndex = i;
            }
        }
    }

    if (bestDist >= 0.0f)
    {
        outClosestPoint = bestPoint;
        outDistance = bestDist;
        outIndex = bestIndex;
        return true;
    }
    return false;
}