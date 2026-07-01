// FUNC_NAME: TimeSynchronizer::updateFrameValue
// Address: 0x008ded90 (thunk to 0x008db540)
// Role: Updates a float at offset +0x1AC based on base value, context scaling, and global frame time.

// Known globals (from decompilation):
extern float g_frameTime;         // DAT_01205224
extern float g_frameTimeOffset;   // DAT_00e44578 (added if g_frameTime negative)
extern float g_scalingFactor;     // DAT_00d60d04

// Internal update function (FUN_004df600)
void internalUpdate();

void __fastcall updateTimeSynchronizer(int obj) {
    // +0x58: pointer to an interface with a method at +0x28
    // Call that method with argument 0x10 (likely a step/update command)
    void (*interfaceMethod)(int) = reinterpret_cast<void (*)(int)>(
        *reinterpret_cast<int*>(
            *reinterpret_cast<int*>(obj + 0x58) + 0x28
        )
    );
    interfaceMethod(0x10);

    // Note: The original stores the return address (unaff_retaddr) into obj+0x190.
    // This is likely a hook/debug mechanism; omitted for reconstruction.

    // Two calls to internal update (FUN_004df600)
    internalUpdate();
    internalUpdate();

    // +0x1C8: base float value
    float base = *reinterpret_cast<float*>(obj + 0x1C8);

    // +0x190: optional context object pointer
    int context = *reinterpret_cast<int*>(obj + 0x190);
    if (context != 0) {
        // Scale base by a factor from context at +0x1DB8
        float factor = *reinterpret_cast<float*>(context + 0x1DB8);
        base *= factor;
    }

    // Apply global frame time with possible offset for negative values
    float frameDelta = g_frameTime;
    if (frameDelta < 0.0f) {
        frameDelta += g_frameTimeOffset;
    }

    // Final value: frameDelta + base * scalingFactor
    *reinterpret_cast<float*>(obj + 0x1AC) = frameDelta + base * g_scalingFactor;
}