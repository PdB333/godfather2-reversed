// FUNC_NAME: MovementComponent::getMovementVector
void __thiscall MovementComponent::getMovementVector(float *outVector) const
{
    float speed = *(float *)(this + 0xa4);       // +0xa4: movement speed scalar
    float dirX = *(float *)(this + 0x80);        // +0x80: direction X
    float dirY = *(float *)(this + 0x84);        // +0x84: direction Y
    float dirZ = *(float *)(this + 0x88);        // +0x88: direction Z
    float dirW = *(float *)(this + 0x8c);        // +0x8c: direction W (e.g., quaternion w or homogeneous component)

    outVector[0] = speed * dirX;
    outVector[1] = speed * dirY;
    outVector[2] = speed * dirZ;
    outVector[3] = speed * dirW;
}