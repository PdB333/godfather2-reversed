// FUNC_NAME: CharacterController::updateMovement
void __thiscall CharacterController::updateMovement(float deltaTime)
{
    // +0x50: m_bActive (bool)
    // +0x58: m_fSpeed (float)
    // +0x68: m_vPosition (Vector3)
    // +0x74: m_vTargetPosition (Vector3)
    // +0x80: m_bFlag1 (bool)
    // +0x90: m_bFlag2 (bool)
    if (m_bActive) {
        if (!m_bFlag1 || !m_bFlag2) {
            updatePosition(&m_vPosition, &m_vTargetPosition, m_fSpeed, deltaTime, true, true);
            if (!m_bFlag2) {
                updateRotation(deltaTime);
            }
        }
        if (!m_bFlag1) {
            updateAnimation(deltaTime);
        }
    }
}