// FUNC_NAME: SomeClass::advanceProgress
// Address: 0x00704ab0
// Purpose: Advances a progress counter stored at offset +0x32c, splitting work into two phases.

void SomeClass::advanceProgress(uint desiredProgress)
{
    if (this == nullptr) {
        return;
    }

    uint currentProgress = *(uint *)((uint)this + 0x32c); // mProgress

    if (currentProgress < desiredProgress) {
        // Phase 1: process the existing progress
        FUN_00701290(currentProgress);
        // Phase 2: process the remaining progress
        FUN_00701460(desiredProgress - currentProgress);
    }
    else {
        // Phase 1: process up to desiredProgress
        FUN_00701290(desiredProgress);
        // Phase 2: no remaining work
        FUN_00701460(0);
    }
}