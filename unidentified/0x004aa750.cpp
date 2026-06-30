// FUNC_004aa750: Countdown::tick
// This function is called each frame to decrement the remaining tick count for this Countdown object.
// When it reaches zero, it notifies the global CountdownManager via OnCountdownComplete with reason 0.
// Offset +0x14 holds the remaining tick count.

class Countdown {
public:
    int32_t mRemainingTicks; // +0x14

    __thiscall void tick() {
        if (--mRemainingTicks == 0) {
            extern void* gCountdownManager; // DAT_012233a4
            extern void __fastcall OnCountdownComplete(void* manager, int32_t reason); // FUN_0044f130
            OnCountdownComplete(gCountdownManager, 0);
        }
    }
};