// FUNC_NAME: EffectBase::tick | Address: 0x0043be00 | Decrements lifetime counter; on expiry calls vtable[4] (offset 0x10) with argument 1.

// this: pointer to EffectBase object
// param_1 likely is 'this' via __fastcall (ecx)
int __fastcall EffectBase::tick(int *this) {
    // Offset +0x24 (9*4) stores the remaining lifetime/timer.
    this[9] = this[9] - 1;          // decrement life counter
    int remaining = this[9];
    if (remaining < 1) {
        // Call virtual function at vtable index 4 (offset 0x10).
        // Typically this is an onExpired or onComplete handler.
        (**(code **)(*this + 0x10))(1);
    }
    return remaining;
}