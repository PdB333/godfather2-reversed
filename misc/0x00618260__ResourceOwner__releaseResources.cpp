// FUNC_NAME: ResourceOwner::releaseResources
// Address: 0x00618260
// Role: Cleanup/destructor helper for a game resource owner. Frees audio resource, and two other resources.

void __fastcall ResourceOwner::releaseResources(int this)
{
    // Call base class cleanup (likely destructor)
    FUN_00612a60();

    // Global state check: if DAT_012058fc is 0 or -1, reset a global flag
    if ((DAT_012058fc == 0) || (DAT_012058fc == -1)) {
        _DAT_00f1592c = 0;
    }

    // Release audio resource at this+0xa4 (e.g., sound stream)
    if (*(int *)(this + 0xa4) != 0) {
        // Parameters: this+0x14 (some identifier), resource pointer at +0xa4,
        // global buffer at DAT_00f15910, and release type 2
        FUN_0060aea0(*(undefined4 *)(this + 0x14), *(int *)(this + 0xa4), &DAT_00f15910, 2);
    }

    // Release secondary resource at this+0xa8 (e.g., dialog tree)
    if (*(int *)(this + 0xa8) != 0) {
        FUN_006063b0();
    }

    // Release tertiary resource at this+0xac (e.g., mission data)
    if (*(int *)(this + 0xac) != 0) {
        FUN_006063b0();
    }
}