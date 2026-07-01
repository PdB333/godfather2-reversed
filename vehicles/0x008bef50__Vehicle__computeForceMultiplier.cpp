// FUNC_NAME: Vehicle::computeForceMultiplier
double Vehicle::computeForceMultiplier() {
    // +0x19c: pointer to some sub-object (e.g., physics component)
    int* physicsComponent = *(int**)(this + 0x19c);
    // +0x40: offset within that sub-object (e.g., force type or index)
    int forceType = *(int*)(physicsComponent + 0x40);
    // Call to get base force value (likely from a table or formula)
    double baseForce = FUN_008be7f0(forceType);
    // +0x1d0: pointer to another component (e.g., damage modifier)
    int* damageComponent = *(int**)(this + 0x1d0);
    // +0x34: float multiplier (e.g., damage scaling factor)
    float damageScale = *(float*)(damageComponent + 0x34);
    // +0x94: global multiplier from a singleton (e.g., difficulty or game settings)
    float globalMultiplier = *(float*)(DAT_0112f938 + 0x94);
    return baseForce * damageScale * globalMultiplier;
}