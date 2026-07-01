// FUNC_NAME: SteeringTarget::setFromTransform

struct SteeringTarget {
    float quaternion[4]; // +0x00: 4-component quaternion
    float steeringAngle; // +0x10: computed steering angle derived from velocity
};

// 0x00949110: Fills SteeringTarget from an entity's transform (velocity @ entity+0x20, quaternion @ entity+0x30)
// Velocity is used to compute a steering angle (if moving), and the entity's quaternion is copied.
SteeringTarget* __thiscall SteeringTarget::setFromTransform(SteeringTarget* this, void* entity)
{
    float* velocity;
    float* entityQuat;

    this->steeringAngle = 0.0f;
    if (entity != NULL) {
        velocity = (float*)((char*)entity + 0x20);
        // Check if velocity vector has non-zero magnitude
        if (velocity[0]*velocity[0] + velocity[1]*velocity[1] + velocity[2]*velocity[2] != 0.0f) {
            // Compute heading angle using global constants (likely sin/cos of some reference)
            double dVar4 = (double)(DAT_00e56a68 * velocity[0] - DAT_00e56a60 * velocity[2]);
            FUN_00b9a9fa(); // Possibly a randomizer or noise function (side-effect only)
            // Scale and offset the angle to produce final steering value
            this->steeringAngle = (DAT_00e44564 - (float)dVar4) * DAT_00e44748;
        }
        // Copy quaternion from entity (+0x30..0x3c)
        entityQuat = (float*)((char*)entity + 0x30);
        this->quaternion[0] = entityQuat[0];
        this->quaternion[1] = entityQuat[1];
        this->quaternion[2] = entityQuat[2];
        this->quaternion[3] = entityQuat[3];
    } else {
        // Null entity: zero out quaternion (steering remains 0)
        this->quaternion[0] = 0.0f;
        this->quaternion[1] = 0.0f;
        this->quaternion[2] = 0.0f;
        this->quaternion[3] = 0.0f;
    }
    return this;
}