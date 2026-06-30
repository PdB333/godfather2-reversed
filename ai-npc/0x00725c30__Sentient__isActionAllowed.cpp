// FUNC_NAME: Sentient::isActionAllowed
bool __fastcall Sentient::isActionAllowed(void) {
    // this +0x12C (300): likely object state/enum (e.g., mState)
    // this +0x128: pointer to a behavior interface (e.g., mBehavior)
    //    The vtable of that interface has a function at offset 0x10 (4th entry)
    //    that returns whether the action is currently prohibited.
    
    int state = *(int*)((char*)this + 300);
    if (state != 0 && state != 0x48) {
        // Not in the special "always allowed" states (0 or 0x48).
        // Call the virtual method to check if action is disallowed.
        void* behavior = *(void**)((char*)this + 0x128);
        auto checkFunc = *(bool (__thiscall**)(void*))((char*)behavior + 0x10);
        bool prohibited = checkFunc(this);
        if (prohibited) {
            return false;
        }
    }
    return true;
}