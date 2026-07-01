// FUNC_NAME: Player::clearState
// Function address: 0x007ff990
// Role: Clears various state flags and releases resources. Called during player state transitions (e.g., death, respawn, action end).

void __fastcall Player::clearState()
{
    // Special check: if this is not the invalid pointer (-0x3C0) and there's an active action/mode at +0x3D4, clear it
    if ((this != reinterpret_cast<Player*>(-0x3C0)) && (*(int*)((char*)this + 0x3D4) != 0)) {
        this->clearActionState(0);  // FUN_005512c0 – disables current action
    }

    // Check bit 4 of flags at +0x8E0 (m_flags0). If set, call a virtual function through vtable[0x28] with argument 0x20
    // Likely handling a special state (e.g., entering/exiting vehicle or cover)
    if (((*(uint*)((char*)this + 0x8E0) >> 4) & 1) != 0) {
        (**(void (__fastcall**)(int))(*(int*)((char*)this + 0x58) + 0x28))(0x20); // virtual call
    }

    // Clear bit 4 in m_flags0
    *(uint*)((char*)this + 0x8E0) &= 0xFFFFFFEF;

    // Clear bit 27 in another flags field at +0x1B94 (m_flags1)
    *(uint*)((char*)this + 0x1B94) &= 0xF7FFFFFF;

    // Check bit 5 of flags at +0x970 (m_timerFlags). If set, check a timer via virtual +0xC0
    if (((*(uint*)((char*)this + 0x970) >> 5) & 1) != 0) {
        float timer = (*(float (__fastcall**)())(**(int**)this + 0xC0))(); // virtual call, returns float >0 if active
        if (0.0f < timer) {
            *(uint*)((char*)this + 0x970) &= 0xFFFFFFDF; // Clear bit 5
            this->resetTimer(); // FUN_007f7050 – resets associated timer
        }
    }

    // Same for bit 6 in m_timerFlags
    if (((*(uint*)((char*)this + 0x970) >> 6) & 1) != 0) {
        float timer = (*(float (__fastcall**)())(**(int**)this + 0xC0))();
        if (0.0f < timer) {
            *(uint*)((char*)this + 0x970) &= 0xFFFFFFBF; // Clear bit 6
            this->resetTimer();
        }
    }

    // Pointer to a resource/object at +0x1E40 (e.g., weapon, inventory item)
    void** resourcePtr = (void**)((char*)this + 0x1E40);

    // If resource is non-null and not a special sentinel value 0x48, set state at +0x858 to 4 (e.g., "ready to remove")
    if ((*resourcePtr != nullptr) && (*resourcePtr != (void*)0x48)) {
        *(int*)((char*)this + 0x858) = 4;
    }

    // Release the resource and nullify the pointer
    if (*resourcePtr != nullptr) {
        this->releaseResource(resourcePtr); // FUN_004daf90 – destroys/frees the object
        *resourcePtr = nullptr;
    }
}