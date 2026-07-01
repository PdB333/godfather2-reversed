// FUNC_NAME: FlashEffect::update

void __thiscall FlashEffect::update(float deltaTime)
{
    // Accumulate elapsed time
    elapsedTime += deltaTime; // +0x10

    // Check if fade duration has been reached and global duration is less than this fade duration
    if ((fadeDuration <= elapsedTime) && (g_globalFadeDuration < fadeDuration)) // +0x14, global DAT_00e44598
    {
        // Trigger on-fade-complete callback
        onFadeComplete(); // FUN_008d7670

        // Set up target color from global constant
        ColorARGB targetColor = g_targetColor; // DAT_0112f9dc (ARGB)
        targetColor.a = 0;   // local_8 (alpha? or second word)
        targetColor.b = 0;   // local_4 (unused? maybe channel)

        // Apply the fade color to screen
        setFadeColor(&targetColor, 0); // FUN_00408a00

        // Reset internal fade state
        resetFadeState(); // FUN_008d7410

        // Reset elapsed timer
        elapsedTime = 0.0f; // +0x10
    }
}