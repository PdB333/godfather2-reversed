// FUNC_NAME: SimObject::integratePositionFromForces
int __thiscall SimObject::integratePositionFromForces(SimObject* this, float* outPosition, void* param_3, float* forces)
{
    // forces likely a struct: +0x38 = thrust, +0x3c = drag, +0x40 = lift (or similar)
    // global constants
    extern float gWindDragFactor; // DAT_00e445c8
    extern float gWindDamping;    // DAT_00e44564

    // Get global world state (wind? environment velocity?)
    WorldState* world = getWorldState(); // FUN_00471610

    // Copy world position into output (initial guess)
    // world +0x30 = position
    outPosition[0] = world->position.x;
    outPosition[1] = world->position.y;
    outPosition[2] = world->position.z;

    // Add world velocity * thrust scaling
    // world +0x10 = velocity, thrust = forces +0x38
    outPosition[0] += world->velocity.x * forces[0x38 / 4];
    outPosition[1] += world->velocity.y * forces[0x38 / 4];
    outPosition[2] += world->velocity.z * forces[0x38 / 4];

    // Compute local force from object's orientation matrix (at this+0x200)
    // and world velocity, scaled by drag coefficient and gWindDragFactor
    float localForce[3];
    getLocalForce(localForce, this + 0x200, &world->velocity, *(float*)(this + 0x234) * gWindDragFactor);
    // forces +0x40 is lift factor
    outPosition[0] += forces[0x40 / 4] * localForce[0];
    outPosition[1] += forces[0x40 / 4] * localForce[1];
    outPosition[2] += forces[0x40 / 4] * localForce[2];

    // Compute cross product and additional force
    // (world velocity crossed with local force components)
    float crossX, crossY, crossZ;
    world = getWorldState();
    float* worldVel = &world->velocity;
    // crossX = worldVel.y * localForce.z - worldVel.z * localForce.y
    crossX = worldVel[1] * localForce[2] - worldVel[2] * localForce[1];
    world = getWorldState();
    worldVel = &world->velocity;
    crossY = worldVel[2] * localForce[0] - worldVel[0] * localForce[2];
    world = getWorldState();
    worldVel = &world->velocity;
    crossZ = worldVel[0] * localForce[1] - worldVel[1] * localForce[0];

    // Apply damping: gWindDamping - forces +0x3c
    float damping = gWindDamping - forces[0x3c / 4];
    outPosition[0] += damping * crossX;
    outPosition[1] += damping * crossY;
    outPosition[2] += damping * crossZ;

    // Return pointer to world velocity (convenience)
    return (int)(&world->velocity);
}