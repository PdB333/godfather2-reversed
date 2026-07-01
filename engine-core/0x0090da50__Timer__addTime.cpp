// FUNC_NAME: Timer::addTime

struct Timer {
    uint32_t flags;          // +0x00
    uint32_t currentTime;    // +0x04
    uint32_t duration;       // +0x08
    uint32_t someFlag;       // +0x0C (checked against 0x48)
    // +0x10..0x2C unknown
    uint32_t callbackData;   // +0x30 (0xC*4) - actually offset +0x30? Wait, careful:
    /* The decompiled uses param_1[0xc] at +0x30. But later callback uses puVar1 = param_1 + 0xe (offset 0x38) and param_1[0x13] (offset 0x4C). We need to map correctly. Let's assume:
       +0x30: callbackData (0xC*4)
       +0x38: maybe another callback? puVar1 = param_1+0xe => points to that.
       +0x4C: function pointer (0x13*4)
    Actually in the code:
    - param_1[0xc] is checked (offset 0x30)
    - param_1[0x13] is a function pointer (offset 0x4C)
    - param_1[0xe] is another pointer (offset 0x38) used as data for function pointer if param_1[0x13] is null.
    So likely:
    offset 0x30: some integer flag (maybe linked timer?)
    offset 0x38: data pointer for callback
    offset 0x4C: function pointer (callback)
    But the decompiled: if (param_1[0xc] != 0 && param_1[0xc] != 0x48) -> that's at +0x30.
    Then later: puVar1 = param_1 + 0xe; (offset 0x38)
    if param_1[0x13] != 0 (offset 0x4C) call that with puVar1.
    else call *(uint*)puVar1 i.e., the value at +0x38 as function with 0.
    So structure:
    +0x30: some identifier (perhaps timer type or linked timer id)
    +0x38: either a function pointer (if +0x4C is null) or data pointer for callback at +0x4C.
    +0x4C: callback function pointer (may be null, then +0x38 is the callback directly)
    */
};

void __thiscall Timer::addTime(Timer* this, int delta) {
    // Check if timer is not paused (bit 5 of flags)
    if ((this->flags & 0x20) == 0) {
        this->currentTime += delta;
        uint32_t dur = this->duration;
        if (dur != 0 && this->currentTime >= dur) {
            this->currentTime = dur; // clamp
            // Check if there's a linked timer or special flag (e.g., not a "one-shot"?)
            if (this->someFlag != 0 && this->someFlag != 0x48) {
                // Possibly notify that timer limit reached? Or stop/cleanup?
                // FUN_0090e530 and FUN_0090e540 are likely static helper functions.
                FUN_0090e530();
                FUN_0090e540();
            }
        }
        // Check again after the above possible modifications (flags unchanged)
        if ((this->flags & 0x20) == 0 && this->duration != 0 && this->duration <= this->currentTime) {
            // Need to fire callback
            uint32_t* callbackPtr = &this->callbackData; // actually &this->someData? careful with naming
            // callbackData is at +0x38 (offset 0xE), but we named it incorrectly. Let's use offset notation.
            // For clarity, we'll use pointer arithmetic in reconstruction.
            // We have two potential callbacks:
            // - function pointer at +0x4C
            // - data at +0x38 (either function or data)
            if (*(uint32_t*)((uint8_t*)this + 0x4C) != 0) {
                // Call function with data at +0x38 as argument
                ((void(__thiscall*)(void*))(*(uint32_t*)((uint8_t*)this + 0x4C)))( (void*)((uint8_t*)this + 0x38) );
            } else if (*(uint32_t*)((uint8_t*)this + 0x38) != 0) {
                // Direct function pointer at +0x38, called with 0
                ((void(__cdecl*)(int))*(uint32_t*)((uint8_t*)this + 0x38))(0);
            }
        }
    }
}