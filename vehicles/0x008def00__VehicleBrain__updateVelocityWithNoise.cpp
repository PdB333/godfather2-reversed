// FUNC_NAME: VehicleBrain::updateVelocityWithNoise
void __fastcall VehicleBrain::updateVelocityWithNoise(int thisPtr)
{
    float currentSpeed = *(float *)(thisPtr + 0x1ac); // +0x1ac: m_currentSpeed
    int gameTime = DAT_01205224; // global game time or frame counter
    float deltaTime = DAT_00d60d04; // global delta time (e.g., 1/60)
    float epsilon = DAT_00e44578; // small constant for sign adjustment

    // Compute random perturbations (likely from a noise generator)
    float random1 = (float)FUN_008dab60(); // returns float in [0,1]
    float random2 = (float)FUN_008dab60();

    // Adjust gameTime if negative (wrap-around handling)
    float adjustedTime = (float)gameTime;
    if (gameTime < 0) {
        adjustedTime += epsilon;
    }

    // Compute new velocity components
    float velX = random1 * deltaTime - (currentSpeed - adjustedTime);
    float velY = random2 * deltaTime;

    // Apply the computed velocity (likely to a physics object)
    FUN_009265c0(velX, velY); // e.g., setTargetVelocity or applyImpulse
}