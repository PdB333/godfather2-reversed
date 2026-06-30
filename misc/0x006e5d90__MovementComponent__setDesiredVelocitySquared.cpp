// FUNC_NAME: MovementComponent::setDesiredVelocitySquared
void __thiscall MovementComponent::setDesiredVelocitySquared(float x, float y)
{
    *(float *)(this + 0x58) = x * x; // +0x58: desired velocity X squared
    *(float *)(this + 0x5c) = y * y; // +0x5c: desired velocity Y squared
}