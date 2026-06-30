// FUNC_NAME: CharacterSteeringController::computeSteeringVelocity
// Address: 0x006c0dd0
// Role: Calculates a new velocity vector by clamping and interpolating towards a desired direction.
// The function takes the current velocity (param_1), an output pointer (hidden via return address), and a this pointer (param_3) for a character/vehicle controller.
// The controller provides a desired direction via a virtual method at vtable+0x4c.

void CharacterSteeringController::computeSteeringVelocity(float *currentVelocity, void *unused, void *hiddenOutput) // hiddenOutput is the return struct pointer
{
    float desiredDirX, desiredDirY;
    float currentX = currentVelocity[0];
    float currentY = currentVelocity[1];
    float currentZ = currentVelocity[2];

    // Call virtual method to get desired direction vector (x,y)
    (*(void (**)(void *, float *, float *))(this->vtable + 0x4c))(this, &desiredDirX, &desiredDirY);

    // Compute length of desired direction vector
    float desiredLength = sqrt(desiredDirY * desiredDirY + desiredDirX * desiredDirX);

    // If desired direction is negligible, just copy current velocity
    if (desiredLength <= kEpsilon) // DAT_00e50de4
    {
        *(float2 *)hiddenOutput = *(float2 *)currentVelocity;
        hiddenOutput[2] = currentZ;
        return;
    }

    // Determine the maximum allowed speed for this step
    float maxSpeed = kDefaultMaxSpeed; // _DAT_00d5c458
    if (desiredLength <= kSpeedThreshold) // DAT_00e445ac
    {
        maxSpeed = desiredLength * kSpeedScale; // DAT_00e445f0
    }

    // Scale direction to max speed
    float scale = maxSpeed / desiredLength;
    float deltaX = scale * desiredDirX;
    float deltaY = scale * desiredDirY;

    // Get smoothing factor from external function (likely clamped 0..1)
    float smoothingFactor = (float)FUN_006c9b00(currentVelocity, &stack_variable, 0, 0); // returns interpolation weight

    // If smoothing factor >= 1, apply full delta
    if (smoothingFactor >= 1.0f)
    {
        *(float2 *)hiddenOutput = CONCAT44(currentY, currentX + deltaX);
        hiddenOutput[2] = currentZ + deltaY;
    }
    else
    {
        // Interpolate between current velocity and target velocity
        hiddenOutput[0] = currentX + smoothingFactor * deltaX;
        hiddenOutput[1] = currentY + smoothingFactor * kConstantFactor; // _DAT_00d577a0 (likely a constant like 0.0? Actually it's used with currentY? Wait code says: unaff_retaddr[1] = fVar2 * _DAT_00d577a0 + param_1[1]; That seems off: param_1[1] is currentY, _DAT_00d577a0 might be a vertical component? Could be another scaling. We'll keep as is.)
        hiddenOutput[2] = currentZ + smoothingFactor * deltaY;
    }
}