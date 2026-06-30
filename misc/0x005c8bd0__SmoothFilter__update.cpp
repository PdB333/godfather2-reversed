// FUNC_NAME: SmoothFilter::update
void __thiscall SmoothFilter::update(float *this, int param_2, int param_3, int param_4)
{
    // Smoothing factors loaded from global addresses
    float posFactor = _DAT_00e3eb50;          // damping factor for position component
    float velFactorX = _UNK_00e3eb54;         // damping factor for X velocity
    float velFactorY = _UNK_00e3eb58;         // damping factor for Y velocity
    float velFactorZ = _UNK_00e3eb5c;         // damping factor for Z velocity

    // Current smoothed values (4 floats) at offsets: +0x10 = posX, +0x14 = velX, +0x18 = velY, +0x1c = velZ
    float currentPosX  = this[0x10 / 4];      // +0x10
    float currentVelX  = this[0x14 / 4];      // +0x14
    float currentVelY  = this[0x18 / 4];      // +0x18
    float currentVelZ  = this[0x1c / 4];      // +0x1c

    // Target values (4 floats) at offsets: +0x20 = targetPosX, +0x24 = targetVelX, +0x28 = targetVelY, +0x2c = targetVelZ
    float targetPosX  = this[0x20 / 4];       // +0x20
    float targetVelX  = this[0x24 / 4];       // +0x24
    float targetVelY  = this[0x28 / 4];       // +0x28
    float targetVelZ  = this[0x2c / 4];       // +0x2c

    // Lerp position towards target
    this[0x10 / 4] = (targetPosX - currentPosX) * posFactor + currentPosX;

    // Spring-damper update for velocity components
    this[0x14 / 4] = (targetVelX - currentVelX) * velFactorX + currentVelX;
    this[0x18 / 4] = (targetVelY - currentVelY) * velFactorY + currentVelY;
    this[0x1c / 4] = (targetVelZ - currentVelZ) * velFactorZ + currentVelZ;

    // Apply the smoothed value (e.g., update camera position)
    FUN_005c8690(param_2, param_4, &this[0x10 / 4]);
}