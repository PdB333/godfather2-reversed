// FUNC_NAME: Entity::isWithinRadiusSq
// Address: 0x0075a220
// Role: Checks if the squared distance to a target (obtained via call to getTargetDistanceSq) is within a given squared radius.
// This is a member function of an Entity-derived class.

bool __thiscall Entity::isWithinRadiusSq(float radiusSq)
{
    // Call method that computes squared distance from this entity to some target (e.g., another entity or point).
    // The called function returns a float (via x87 ST0).
    float distanceSq = computeSquaredDistanceToTarget();  // placeholder for FUN_004702b0(this)
    return (distanceSq <= radiusSq) ? true : false;
}