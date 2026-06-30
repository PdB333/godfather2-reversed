// FUNC_NAME: GlobalTransitionManager::updateTransition
// Address: 0x0041df10
// Role: Handles state transitions between three preset states used for visual effects (e.g., color or position interpolation).
// Called from main update loop at 0x0042e7e0.

// Global data layout (offsets approximate):
// +0x01206a88: int g_bAllowTransitions (0=no, 1=yes)
// +0x01206aec: int g_currentTransitionIndex (index into the transition array, modulo 3)
// +0x01206af0: int g_transitionStates[3] (array of target values)
// +0x011f38f0: int g_transitionCurrentValue  (X/primary component)
// +0x011f38f4: int g_transitionCurrentValue2 (Y/secondary component, often 0)
// +0x01206b00: int g_transitionTargetValue   (final target state after transition completes)

// Forward declarations of called functions (their addresses):
bool isTransitionAllowed();         // 0x0041ddf0 – checks conditions (e.g., not paused, not already transitioning)
void updateTransitionEffect(int effectId, int oldVal, int newVal);  // 0x00609340 – apply visual/effect change
void completeTransition(int param); // 0x00609890 – finalize transition (e.g., set flag, trigger anim)
void interpolateTransition(int current, int target); // 0x0060df60 – smooth interpolation between states

void GlobalTransitionManager::updateTransition()
{
    if (!isTransitionAllowed())
        return;
    if (g_bAllowTransitions != 1)
        return;

    int oldValue1 = g_transitionCurrentValue;  // uVar1
    int oldValue2 = g_transitionCurrentValue2; // uVar3

    // Advance to the next state in the circular 3‑slot array
    int nextIndex = (g_currentTransitionIndex + 1) % 3;
    g_transitionCurrentValue  = g_transitionStates[nextIndex];
    g_transitionCurrentValue2 = 0;

    // Deactivate the previous effect (pass old values)
    updateTransitionEffect(0, oldValue1, oldValue2);

    // Check if we reached the final target state
    if (g_transitionCurrentValue == g_transitionTargetValue && g_transitionCurrentValue2 == 0)
    {
        completeTransition(1); // Transition fully complete
    }
    else
    {
        // Continue interpolation toward the target
        interpolateTransition(g_transitionCurrentValue, g_transitionTargetValue);
    }

    // Save the new (just computed) values temporarily
    int newValue1 = g_transitionCurrentValue;  // iVar2
    int newValue2 = g_transitionCurrentValue2; // iVar4 (always 0 here)

    // Restore the original values before the state advancement
    g_transitionCurrentValue2 = 0; // already 0
    g_transitionCurrentValue  = oldValue1;

    // Activate the effect again, but this time with the *new* state?
    // This seems to update the effect using the pre‑transition old values and the new secondary (0)
    updateTransitionEffect(0, newValue1, newValue2);
}