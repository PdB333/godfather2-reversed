// FUN_004f80d0: CameraShakeController::update

void __thiscall CameraShakeController::update(CameraShakeController* this, float deltaTime)
{
    // FS:[0x2c] -> game global context pointer
    int* globalContext = *(int**)__readfsdword(0x2c); // e.g., GameContext*
    int* contextPtr = globalContext;

    // Check if secondary object (e.g., shake source) exists and has data
    if ((*(int*)(this + 0x34) != 0) && (*(int*)(*(int*)(this + 0x34) + 0x10) != 0))
    {
        // Call some setup/reset function with the base object and a flag
        FUN_004ebc00(*(void**)(this + 4), 0);

        // Fetch a value from data at +0x24 offset 0x50
        int dataVal = *(int*)(*(int*)(this + 0x24) + 0x50);

        // Compute target write address: global context base + 8 + (source+8)
        int* target = (int*)(*(int*)(*contextPtr + 8) + *(int*)(*(int*)(this + 0x34) + 8));

        // Write two values: one from XMM0 (probably a third parameter), one from dataVal
        // in_XMM0_Da is likely a float passed in XMM0 register (undocumented third param)
        *(float*)(target + 0x2c / 4) = *(float*)&in_XMM0_Da; // +0x2c: strength/scalar?
        *(int*)(target + 0x28 / 4) = dataVal; // +0x28: some ID or flags
    }

    // Timer countdown at +0x30
    if (0.0f < *(float*)(this + 0x30))
    {
        float timer = *(float*)(this + 0x30) - deltaTime;
        *(float*)(this + 0x30) = timer;
        if (timer <= 0.0f)
        {
            // Timer expired
            *(float*)(this + 0x30) = 0.0f;

            // Set flag bit 0 on a per-instance flag word
            int flagAddr = *(int*)(*contextPtr + 8) + *(int*)(this + 0x10);
            *(uint*)(flagAddr) |= 1;

            // Check and update another state object at +0x2c
            int* stateObj = *(int**)(this + 0x2c);
            if (stateObj != 0)
            {
                if ((*(uint*)(stateObj + 0xc / 4) & 0x20000) == 0)
                {
                    *(uint*)(stateObj + 0xc / 4) |= 0x20000;
                    FUN_0051b120(); // Notify some system
                }
                *(uint*)(stateObj + 0xc / 4) &= 0xfffbffff; // Clear bit 0x40000
            }
        }
    }

    // Update transform matrix if state object exists and condition (e.g., not frozen)
    if ((*(int*)(this + 0x2c) != 0) && (*(int*)(*(int*)(this + 0x2c) + 0xb0) == 0))
    {
        // Check additional flags before copying
        if (((*(uint*)(*(int*)(*(int*)(this + 4) + 0x10) + 0x14) & 0x8000) == 0) ||
            ((*(uint*)(*(int*)(*contextPtr + 8) + *(int*)(this + 0x10)) & 0x40000000) == 0))
        {
            // Retrieve 16-float matrix from some source
            float* sourceMatrix = (float*)FUN_004f7c10(); // returns pointer to 16 floats (4x4 matrix)
            float* destMatrix = (float*)(*(int*)(this + 0x2c) + 0x30); // offset 0x30
            for (int i = 0; i < 16; i++)
                destMatrix[i] = sourceMatrix[i];
        }

        // Copy a single value from base object's +0x84 to state object's +0x84
        *(int*)(*(int*)(this + 0x2c) + 0x84) = *(int*)(*(int*)(this + 4) + 0x84);
    }
}