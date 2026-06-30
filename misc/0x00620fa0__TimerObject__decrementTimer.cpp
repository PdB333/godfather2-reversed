// FUNC_NAME: TimerObject::decrementTimer
class TimerObject {
public:
    // vtable layout:
    // +0x00: virtual destructor
    // +0x04: some virtual
    // ...
    // +0x10: virtual void onTimerExpired(int)   // vtable[4]

    int timerCounter; // offset +0x18

    // Decrements the timer count. Returns remaining time.
    // If count < 1 after decrement, calls onTimerExpired(1).
    int __thiscall decrementTimer() {
        this->timerCounter--;
        int result = this->timerCounter;
        if (result < 1) {
            // vtable+0x10 => function pointer at index 4
            (*(void (__thiscall **)(TimerObject*, int))(*(int*)this + 0x10))(this, 1);
        }
        return result;
    }
};