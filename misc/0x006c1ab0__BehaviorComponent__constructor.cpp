// FUNC_NAME: BehaviorComponent::constructor
// Function address: 0x006c1ab0
// Role: Initializes a BehaviorComponent with a time offset and default state.
// Called from FUN_006c7e60 (likely another constructor).

void __thiscall BehaviorComponent::constructor(BehaviorComponent *this, float *initialTimePtr)
{
    // Compute time difference from a global constant (might be current game time)
    double delta = (double)(DAT_00e44564 - *initialTimePtr);
    FUN_00b9a9fa(); // unknown global function (likely debug or logging)
    FUN_006daa50(); // unknown global function

    // +0x10: initial time difference stored as float
    *(float *)((unsigned char*)this + 0x10) = (float)delta;
    // +0x14, 0x18, 0x1c: zero out a Vector3 (velocity or position)
    *(int *)((unsigned char*)this + 0x14) = 0;
    *(int *)((unsigned char*)this + 0x18) = 0;
    *(int *)((unsigned char*)this + 0x1c) = 0;

    // +0x30: byte flag set to 1 (e.g., enabled)
    *(unsigned char*)((unsigned char*)this + 0x30) = 1;
    // +0x38: byte flag set to 1 (e.g., active)
    *(unsigned char*)((unsigned char*)this + 0x38) = 1;
    // +0x34: int set to 0 (some counter or ID)
    *(int *)((unsigned char*)this + 0x34) = 0;
    // +0x39..0x3c: four bytes zeroed (likely padding or additional flags)
    *(unsigned char*)((unsigned char*)this + 0x39) = 0;
    *(unsigned char*)((unsigned char*)this + 0x3a) = 0;
    *(unsigned char*)((unsigned char*)this + 0x3b) = 0;
    *(unsigned char*)((unsigned char*)this + 0x3c) = 0;

    // Call a sub-initializer using the original float pointer
    FUN_006c0810(initialTimePtr);

    // Store a global value (DAT_00d5eea0) into +0x64
    int globalVal = DAT_00d5eea0;
    // +0x4c..0x60: six ints/floats zeroed
    *(int *)((unsigned char*)this + 0x4c) = 0;
    *(int *)((unsigned char*)this + 0x50) = 0;
    *(int *)((unsigned char*)this + 0x54) = 0;
    *(int *)((unsigned char*)this + 0x58) = 0;
    *(int *)((unsigned char*)this + 0x5c) = 0;
    *(int *)((unsigned char*)this + 0x60) = 0;
    // +0x64: store the global value (possibly a resource handle or ID)
    *(int *)((unsigned char*)this + 0x64) = globalVal;
    // +0x68..0x70: zero three more ints/floats
    *(int *)((unsigned char*)this + 0x68) = 0;
    *(int *)((unsigned char*)this + 0x6c) = 0;
    *(int *)((unsigned char*)this + 0x70) = 0;
}