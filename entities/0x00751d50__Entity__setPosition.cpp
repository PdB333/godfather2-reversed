// FUNC_NAME: Entity::setPosition
void __thiscall Entity::setPosition(int thisPtr, double x, double y, double z)
{
    // Store the three double values at offsets +0x78, +0x80, +0x88
    *(double*)(thisPtr + 0x78) = x; // +0x78: m_positionX
    *(double*)(thisPtr + 0x80) = y; // +0x80: m_positionY
    *(double*)(thisPtr + 0x88) = z; // +0x88: m_positionZ
}