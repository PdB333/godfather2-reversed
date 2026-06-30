// FUNC_NAME: PhysicsComponent::getScaledVectors
// Function address: 0x00514890
// Takes two output float* (param_1, param_2) and scales two internal vectors based on thresholded energy values.
// The object layout:
//   +0x00: m_vector1[4] (first vector, indices 0-3)
//   +0x10: m_vector2[4] (second vector, indices 4-7)
//   +0x40: m_energy1 (index 16)
//   +0x4C: m_energy2 (index 19)
// Global constants:
//   gEnergyThreshold  (DAT_00e44634)
//   gEnergyScale      (DAT_00e445f0)
//   gDefaultEnergy    (DAT_00e2b1a4)

void __thiscall PhysicsComponent::getScaledVectors(float* outVector1, float* outVector2)
{
    float fVar5 = gEnergyThreshold;
    float fVar4 = gEnergyScale;
    float fVar7 = gDefaultEnergy;
    float fVar6 = gDefaultEnergy;

    // First vector scaling
    if (m_energy1 < gEnergyThreshold) {
        fVar6 = m_energy1 * gEnergyScale;
    }

    float v1_x = m_vector1[0];
    float v1_y = m_vector1[1];
    float v1_z = m_vector1[2];
    float v1_w = m_vector1[3]; // likely w component or unused

    outVector1[0] = fVar6 * v1_x;
    outVector1[1] = fVar6 * v1_y;
    outVector1[2] = fVar6 * v1_z;
    outVector1[3] = fVar6 * v1_w;

    // Second vector scaling
    if (m_energy2 < gEnergyThreshold) {
        fVar7 = m_energy2 * gEnergyScale;
    }

    float v2_x = m_vector2[0];
    float v2_y = m_vector2[1];
    float v2_z = m_vector2[2];
    float v2_w = m_vector2[3];

    outVector2[0] = fVar7 * v2_x;
    outVector2[1] = fVar7 * v2_y;
    outVector2[2] = fVar7 * v2_z;
    outVector2[3] = fVar7 * v2_w;

    return;
}