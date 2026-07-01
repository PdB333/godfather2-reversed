// FUNC_NAME: Sentient::updateCoverState
void __fastcall Sentient::updateCoverState(int *this)
{
    char cVar1;
    int *componentPtr;
    int someResult;
    int coverTarget;
    float coverTimer;
    int *outComponent;

    outComponent = this;
    // Check if current state is COVER (2) and type is NONE (0) or COVER_HINT (0x48)
    if ((this[0x31] == 2) && ((this[0x1c] == 0) || (this[0x1c] == 0x48))) {
        // Try to get a component by hash (likely CoverHintNodeManager or similar)
        componentPtr = (int *)getComponentByHash(this + 0x16, 0);
        if (componentPtr != (int *)0x0) {
            outComponent = (int *)0x0;
            // Virtual call at +0x10: query for a specific component (hash 0x38523fc3)
            cVar1 = (**(code **)(*componentPtr + 0x10))(0x38523fc3, &outComponent);
            if ((cVar1 != '\0') && (outComponent != (int *)0x0)) {
                applyCoverState(outComponent);
                goto LAB_0086d14a;
            }
        }
        // Fallback: get global cover target
        if (**(int **)(DAT_012233a0 + 4) == 0) {
            coverTarget = 0;
        } else {
            coverTarget = **(int **)(DAT_012233a0 + 4) + -0x1f30;
        }
        someResult = getGlobalCoverTarget();
        if (someResult != 0) {
            coverTarget = getGlobalCoverTarget();
        }
        applyCoverState(coverTarget);
    }
LAB_0086d14a:
    // Check if there is an active cover hint (offset +0x50)
    if ((this[0x14] != 0) && (this[0x14] != 0x48)) {
        if (this[0x14] == 0) {
            componentPtr = (int *)0x0;
        } else {
            componentPtr = (int *)(this[0x14] + -0x48);
        }
        // Virtual call at +0xC0: get cover timer (returns float)
        coverTimer = (float)(**(code **)(*componentPtr + 0xc0))();
        if ((coverTimer <= 0.0f) && (this[0x31] != 0)) {
            this[0x31] = 0; // Reset state to NONE
            exitCover();
        }
    }
    // Get pointer to some state structure via virtual call at +0x30
    coverTarget = (**(code **)(*this + 0x30))();
    // Clear two flags at offsets +0x25 and +0x24 (likely cover flags)
    *(undefined1 *)(coverTarget + 0x25) = 0;
    *(undefined1 *)(coverTarget + 0x24) = 0;
    // Call again (possibly to update after clearing)
    (**(code **)(*this + 0x30))();
    updateAnimation();
    return;
}