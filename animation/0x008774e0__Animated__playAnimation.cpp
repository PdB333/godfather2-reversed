// FUNC_NAME: Animated::playAnimation
// Address: 0x008774e0
// Role: Plays an animation resource stored in object fields. Attempts to load from path/size, falls back to default handle.

void __fastcall Animated::playAnimation(int *this)
{
    // Offsets: +0xA3C (0x28f*4) -> animation path string pointer
    // Offsets: +0xA40 (0x290*4) -> animation size or flags (non-zero indicates valid path)
    // Default handle constant (0x46f5c7b4) likely represents "none" or invalid resource
    int resourceHandle = 0x46f5c7b4; // default invalid handle

    if (this[0x290] != 0) {
        char *animPath = (char *)this[0x28f];
        if (animPath == NULL) {
            animPath = (char *)0x0120546e; // fallback default path string (e.g., "default")
        }
        resourceHandle = FUN_004db3f0(0x46f5c7b4, animPath, this[0x290]); // load animation resource
        if (FUN_0045f1b0(resourceHandle) == 0) {
            // Resource load failed, reset to default
            resourceHandle = 0x46f5c7b4;
        }
    }

    // Virtual function at vtable+0x14c: plays the animation resource
    // Signature: void __thiscall play(int handle, bool loop = 1, int param3 = 0)
    (*(void (__thiscall **)(int, int, int))(*this + 0x14c))(resourceHandle, 1, 0);
}