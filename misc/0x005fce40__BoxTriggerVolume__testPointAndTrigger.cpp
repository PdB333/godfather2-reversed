// FUNC_NAME: BoxTriggerVolume::testPointAndTrigger
// Address: 0x005fce40
// This function tests if a point is within a given distance of an axis-aligned bounding box.
// If so, it triggers a callback (FUN_005fcce0). The object has a vtable, an enabled flag at +0x3e,
// and an AABB pointer at +0x48 (min[3], max[3]).

void BoxTriggerVolume::testPointAndTrigger(const float* point, float threshold) const
{
    // Vtable entries (offsets in bytes):
    // +0x00: first virtual (unknown)
    // +0x04: isEnabled() -> bool
    // +0x08: beginTest()
    // +0x0C: endTest()
    typedef void (__thiscall *VoidFunc)(const BoxTriggerVolume*);
    typedef char (__thiscall *BoolFunc)(const BoxTriggerVolume*);
    VoidFunc beginTest = (VoidFunc)(*(int*)this + 8);
    VoidFunc endTest   = (VoidFunc)(*(int*)this + 12);
    BoolFunc isEnabled = (BoolFunc)(*(int*)this + 4);

    beginTest(this);

    // enabled flag at +0x3e (short, non-zero = active)
    if (*(short*)((uintptr_t)this + 0x3e) != 0 && isEnabled(this))
    {
        float* box = *(float**)((uintptr_t)this + 0x48); // min[3] at box[0..2], max[3] at box[3..5]

        float sqDist = 0.0f;

        // X distance
        float dx = point[0];
        if (dx < box[0])
        {
            dx = dx - box[0];
            sqDist += dx * dx;
        }
        else if (dx > box[3])
        {
            dx = dx - box[3];
            sqDist += dx * dx;
        }

        // Y distance
        float dy = point[1];
        if (dy < box[1])
        {
            dy = dy - box[1];
            sqDist += dy * dy;
        }
        else if (dy > box[4])
        {
            dy = dy - box[4];
            sqDist += dy * dy;
        }

        // Z distance
        float dz = point[2];
        if (dz < box[2])
        {
            dz = dz - box[2];
            sqDist += dz * dz;
        }
        else if (dz > box[5])
        {
            dz = dz - box[5];
            sqDist += dz * dz;
        }

        if (sqDist <= threshold * threshold)
        {
            // Trigger callback (likely an event or action)
            FUN_005fcce0();
        }
    }

    endTest(this);

    // Release point? Possibly frees a temporary vector.
    FUN_006021f0(point);
}