// FUNC_NAME: EntityUpdate::Tick
// Function address: 0x0046ec60
// Role: Main per-frame update tick for an EA EARS entity. Handles state changes, per-frame logic, and custom callbacks.

void __fastcall EntityUpdate::Tick(EntityUpdate* this)
{
    uint uVar1;

    // Check if entity state is non-zero and not 0x48 (likely a specific state like "spawning" or "transition")
    if ((this->state != 0) && (this->state != 0x48)) {
        // Virtual call to handle state change (vtable+0x88)
        (*(this->vtable + 0x88))();
    }

    uVar1 = FUN_0043b490();
    // XOR with global DAT_01205250, masked to 7 bits; if zero, trigger some event
    if (((uVar1 ^ DAT_01205250) & 0x7f) == 0) {
        FUN_0046e8d0();
    }

    // Virtual call to per-frame update (vtable+0x104), passes stack buffer (maybe delta time or input data)
    (*(this->vtable + 0x104))(stackBuffer);

    // Compare a float field at +0x154 with global DAT_00e2b05c; if different, call some handler
    if (this->someFloat != DAT_00e2b05c) {
        FUN_004705e0();
    }

    // Check bit 0 at offset +0x15f (flag byte)
    if ((this->flagsByte & 1) != 0) {
        // Virtual call to visibility/handler (vtable+0x134) with argument 0
        (*(this->vtable + 0x134))(0);
    }

    // Check custom callback pointer at +0x158 (function pointer) and bit 9 of ushort at +0x15e
    if ((this->customCallback != nullptr) && ((this->flagsUshort >> 9 & 1) == 0)) {
        // Call custom callback with this pointer as argument
        this->customCallback(this);
    }
}