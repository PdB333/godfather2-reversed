// FUNC_NAME: Timer::update

void Timer::update(void)
{
    int iVar2 = 0;
    TimerData* data = *(TimerData**)(this + 0x10); // +0x10: pointer to timer data (value at +4, count at +8)
    if (0 < data->count) {
        do {
            int delta = getDeltaTime(); // FUN_00626f80: returns engine delta time
            data->value -= delta;
            iVar2 = iVar2 + 1;
        } while (iVar2 < data->count);
    }
}