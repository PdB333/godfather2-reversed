// FUNC_NAME: Sentient::setSpeed
void __thiscall Sentient::setSpeed(Sentient* this, float speed)
{
    double dVar1;

    // Multiply speed by global scale constants (game->internal unit conversion)
    dVar1 = (double)(speed * g_speedScaleFactor * g_velocityConversion); // DAT_00e445c8 and _DAT_00d5c458
    validateSpeed(); // FUN_00b99e20 – likely checks debug or clamps
    *(float*)((uintptr_t)this + 0x50) = (float)dVar1; // +0x50: m_speed
    return;
}