// FUNC_NAME: PlayerTimedActionManager::updateActionCooldown
// Function address: 0x007dc1a0
// Updates an action counter and timer, then calls the underlying action handler
// if the action is enabled. The action is enabled when bit 6 at (pSettings+0x249c) is clear.
// Counter at +0x151 is incremented and wraps at 3; timer at +0x152 increments each tick.

void __thiscall PlayerTimedActionManager::updateActionCooldown(
    void* thisPtr,                  // param_1: this
    void* pSettings,                // param_2: settings object with enable flag at +0x249c
    int arg3,                       // param_3
    int arg4,                       // param_4
    int arg5,                       // param_5
    int arg6                        // param_6
)
{
    // Check if action is enabled (bit 6 of settings[0x249c] is 0)
    if ((*(unsigned int*)((char*)pSettings + 0x249c) >> 6 & 1) == 0)
    {
        // Increment timer byte at +0x152
        *(char*)((char*)thisPtr + 0x152) = *(char*)((char*)thisPtr + 0x152) + 1;

        // Increment counter byte at +0x151 and wrap at 3
        unsigned char counter = *(unsigned char*)((char*)thisPtr + 0x151) + 1;
        *(unsigned char*)((char*)thisPtr + 0x151) = counter;
        if (counter > 2)
        {
            *(unsigned char*)((char*)thisPtr + 0x151) = 0;
        }

        // Call the underlying action handler (arguments reordered: arg3, arg4, arg6, arg5)
        FUN_007dc0c0(arg3, arg4, arg6, arg5);
    }
}