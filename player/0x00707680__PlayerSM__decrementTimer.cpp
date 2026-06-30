// FUNC_NAME: PlayerSM::decrementTimer
void __thiscall PlayerSM::decrementTimer(float deltaTime)
{
    float *timer = (float *)((int)this + 0x2a8); // state timer offset
    if (*timer > 0.0f)
    {
        *timer -= deltaTime;
        if (*timer < 0.0f)
        {
            *timer = 0.0f;
        }
    }
}