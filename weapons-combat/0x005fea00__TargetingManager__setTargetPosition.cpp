// FUNC_NAME: TargetingManager::setTargetPosition
void __thiscall TargetingManager::setTargetPosition(float x, float y)
{
    this->m_targetX = x;   // +0xe4
    this->m_targetY = y;   // +0xe8

    if ((this->m_bTransitioning == 0) && (this->m_pSomeObject != nullptr) && (this->m_pSomeOther != nullptr))
    {
        // Store previous position for interpolation
        this->m_prevX = this->m_newX;   // +0xfc = +0xf8
        this->m_prevY = this->m_newY;   // +0x108 = +0x104
        this->m_prevZ = this->m_newZ;   // +0x10c = +0x110 (note: reversed order)
        this->updateTarget(1);           // forced update flag
    }
}