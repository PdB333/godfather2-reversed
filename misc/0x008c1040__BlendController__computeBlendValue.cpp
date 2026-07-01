// FUNC_NAME: BlendController::computeBlendValue
// Function at 0x008c1040: Computes a blended/interpolated value based on current state, time, scale, and external context.
// Used by update functions at 0x008c4a90 and 0x008c4bb0 (likely part of a frame update loop in a physics/animation system).

float __thiscall BlendController::computeBlendValue(float param_2)
{
    // Get global time (likely frame delta time or current game time)
    float gameTime = (float)FUN_008bfda0();          // 0x008bfda0 – getGameTime

    // Read current blend value from this object
    float currentValue = *(float *)(this + 0x160);   // +0x160: current base value

    // Read primary scale from a related struct (likely interpolation parameters)
    float primaryScale = *(float *)(*(int *)(this + 0x1d0) + 0x4c);  // +0x1d0 -> +0x4c

    // Global constant scale (e.g., time scaling factor)
    float globalScale = *(float *)_DAT_00d5c458;     // global constant at address 0x00d5c458

    // Calculate intermediate value: (currentValue + primaryScale) * gameTime * globalScale
    float intermediate = (currentValue + primaryScale) * gameTime * globalScale;

    // Get handle from a secondary data structure
    int handle = *(int *)(*(int *)(this + 0x19c) + 0x40);  // +0x19c -> +0x40

    // Retrieve related blend object via handle (returns pointer)
    int relatedObj = FUN_008c74d0(handle);           // 0x008c74d0 – getRelatedBlendObject

    // Read signed integer that needs to be interpreted as unsigned for float conversion
    int signedInt = *(int *)(*(int *)(this + 0x19c) + 0x68);  // +0x19c -> +0x68
    double unsignedFloat = (double)signedInt;
    if (signedInt < 0) {
        // Convert to unsigned representation by adding 2^32
        unsignedFloat += (double)DAT_00e44578;        // global constant 4294967296.0 at 0x00e44578
    }

    // Read values from the related object
    float relatedPrimaryScale = *(float *)(*(int *)(relatedObj + 0x1d0) + 0x4c); // related -> +0x1d0 -> +0x4c
    float relatedDelta = *(float *)(relatedObj + 0x164);                         // related +0x164

    // Compute subtraction term: unsignedFloat * (relatedPrimaryScale + relatedDelta)
    float subtractTerm = (float)(unsignedFloat * (relatedPrimaryScale + relatedDelta));

    // Read secondary scaling factor from this object
    float secondaryScale = *(float *)(*(int *)(this + 0x1d0) + 0x2c);  // +0x1d0 -> +0x2c

    // Read final offset from a global table
    float globalOffset = *(float *)(DAT_0112f938 + 0x34);               // global base 0x0112f938 + 0x34

    // Final blended value: ((intermediate - subtractTerm + param_2) * secondaryScale) + globalOffset
    return ((intermediate - subtractTerm + param_2) * secondaryScale) + globalOffset;
}