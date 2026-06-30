// FUNC_NAME: ChaseCamera::constrainToTarget
// Approximate structure offsets:
//   this+0x10: m_pos.x (float)
//   this+0x14: m_pos.y (float)
//   this+0x18: m_pos.z (float)
//   this+0x1c: m_extra (float) – possibly rotation or offset scalar
// target is a 4-float array: [tx, ty, tz, tExtra]
void __thiscall ChaseCamera::constrainToTarget(const float* target)
{
    float tx = target[0];
    float ty = target[1];
    float tz = target[2];
    float tExtra = target[3];

    float dx = m_pos.x - tx;
    float dy = m_pos.y - ty;
    float dz = m_pos.z - tz;
    float dist = sqrtf(dx*dx + dy*dy + dz*dz);

    // Global constants used to define a maximum allowed distance
    // DAT_00e51178 and DAT_00e5117c are likely derived from a squared threshold
    float maxDist = s_maxDistScale * s_maxDistBase; 
    if (maxDist < dist) {
        float factor = maxDist / dist;
        m_pos.x = factor * dx + tx;
        m_pos.y = factor * dy + ty;
        m_pos.z = factor * dz + tz;
        m_extra = factor * (m_extra - tExtra) + tExtra;
    }
}