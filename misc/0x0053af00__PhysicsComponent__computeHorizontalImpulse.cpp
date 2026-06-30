// FUNC_NAME: PhysicsComponent::computeHorizontalImpulse
// Address: 0x0053af00
// Computes a horizontal impulse vector (x, 0, z) from a direction and scale, multiplied by a stored factor and global time constant.
int __thiscall PhysicsComponent::computeHorizontalImpulse(float* outVector, float scale, float* direction)
{
    float factor = *(this + 0x34); // +0x34: mass or inertia multiplier
    float scaledTime = scale * DAT_00e2a848; // global time step or damping constant
    double dVar2 = (double)scaledTime;
    FUN_00b99fcb(); // possible sine/cosine or clamping function
    outVector[0] = (float)dVar2 * direction[0] * factor;
    outVector[1] = 0.0f; // always horizontal (no Y component)
    dVar2 = (double)scaledTime;
    FUN_00b99e20(); // complementary math function
    outVector[2] = (float)dVar2 * direction[2] * factor;
    FUN_00414aa0(); // unknown post-process call
    return 1;
}