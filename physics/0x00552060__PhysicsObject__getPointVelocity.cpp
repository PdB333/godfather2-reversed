// FUNC_NAME: PhysicsObject::getPointVelocity
// Function at 0x00552060
// Computes the world-space velocity of a point attached to this rigid body.
// Given a point in world space, returns the velocity at that point assuming it moves with the body.
// The body has position (0x130), linear velocity (0x1a0), angular velocity (0x1b0), and an extra float at 0x1ac (maybe mass or damping).
void __thiscall PhysicsObject::getPointVelocity(float *in_point, float *out_velocity)
{
    // Body position (origin) - offset +0x130
    float posX = *(float *)(this + 0x130);
    float posY = *(float *)(this + 0x134);
    float posZ = *(float *)(this + 0x138);

    // Linear velocity - offset +0x1a0
    float linVelX = *(float *)(this + 0x1a0);
    float linVelY = *(float *)(this + 0x1a4);
    float linVelZ = *(float *)(this + 0x1a8);

    // Angular velocity - offset +0x1b0
    float angVelX = *(float *)(this + 0x1b0);
    float angVelY = *(float *)(this + 0x1b4);
    float angVelZ = *(float *)(this + 0x1b8);

    // Relative position from body center
    float relX = in_point[0] - posX;
    float relY = in_point[1] - posY;
    float relZ = in_point[2] - posZ;

    // Cross product: angular_velocity × relative_position
    // crossX = angVelY * relZ - angVelZ * relY
    // crossY = angVelZ * relX - angVelX * relZ
    // crossZ = angVelX * relY - angVelY * relX
    float crossX = angVelY * relZ - angVelZ * relY;
    float crossY = angVelZ * relX - angVelX * relZ;
    float crossZ = angVelX * relY - angVelY * relX;

    // Output velocity = linear velocity + cross product
    out_velocity[0] = linVelX + crossX;
    out_velocity[1] = linVelY + crossY;
    out_velocity[2] = linVelZ + crossZ;
    // The 4th component is set from an extra field at +0x1ac (maybe scaling or weight)
    out_velocity[3] = *(float *)(this + 0x1ac);
}