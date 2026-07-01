// FUNC_NAME: PlayerCCTVariables::setWalkingSpeed
void __thiscall PlayerCCTVariables::setWalkingSpeed(float value)
{
    // +0x20: m_fWalkingSpeed (float walking speed)
    // +0x64 (100): m_bDirty (byte flag indicating change)
    if (value != this->m_fWalkingSpeed)
    {
        this->m_bDirty = 1;
        this->m_fWalkingSpeed = value;
    }
}