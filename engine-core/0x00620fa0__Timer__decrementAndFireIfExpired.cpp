// FUNC_NAME: Timer::decrementAndFireIfExpired
int __thiscall Timer::decrementAndFireIfExpired(int *this) {
    // Decrement timer counter at offset +0x18 (this[6])
    this[6] = this[6] - 1;
    int remaining = this[6];
    if (remaining < 1) {
        // Fire virtual function at vtable index 4 (offset +0x10) – likely onTimerExpired(1)
        (*(void (__thiscall **)(int *))(*(int *)this + 0x10))(1);
    }
    return remaining;
}