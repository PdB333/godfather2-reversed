// FUNC_NAME: Character::updateOrientationFromSource
// Function address: 0x009495d0
// Reconstructed C++ code

// Assumed class offsets:
// +0x11C: m_flags (uint32_t, bitfield)
// +0x120: m_targetYaw (float)
// +0x130: m_rotation[4] (float, quaternion or 4x4 matrix row?)

// External globals (from .data section):
// _DAT_00d577a0 -> g_zeroFloat (likely 0.0f)
// _DAT_00e56a68 -> g_rotCoeffA
// _DAT_00e56a60 -> g_rotCoeffB
// _DAT_00e44564 -> g_angleOffset
// _DAT_00e44748 -> g_angleScale

void __thiscall Character::updateOrientationFromSource(void* pSelf, void* pSource)
{
    // Cast pointers to useful types
    Character* self = (Character*)pSelf;
    struct SourceTransform { // +0x20: direction[3], +0x30: rotation[4]
        char pad[0x20];
        float direction[3];
        float rotation[4];
    }* src = (SourceTransform*)pSource;

    // Copy 16 bytes of rotation from source to self
    self->m_rotation[0] = src->rotation[0];
    self->m_rotation[1] = src->rotation[1];
    self->m_rotation[2] = src->rotation[2];
    self->m_rotation[3] = src->rotation[3];

    // Check bit 2 (0x4) of m_flags
    if ((self->m_flags & 0x4) != 0)
    {
        // Compute squared length of source direction vector
        float sqLen = src->direction[0] * src->direction[0] +
                      src->direction[1] * src->direction[1] +
                      src->direction[2] * src->direction[2];

        // If direction is non-zero (globally zero float check)
        if (sqLen != g_zeroFloat) // g_zeroFloat at 0x00d577a0
        {
            // Linear combination of direction X and Z components
            // dVar5 = g_rotCoeffA * src->direction[0] - g_rotCoeffB * src->direction[2]
            double dVar5 = (double)(g_rotCoeffA * src->direction[0] - g_rotCoeffB * src->direction[2]);

            // Call an unknown helper (possibly a no‑op or debug function)
            FUN_00b9a9fa();

            // Compute new target yaw angle
            float newYaw = (g_angleOffset - (float)dVar5) * g_angleScale;

            if (self->m_targetYaw != newYaw)
            {
                self->m_targetYaw = newYaw;
                self->m_flags |= 0x200000; // Mark as needing update
            }
        }
    }
}