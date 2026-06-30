// FUNC_NAME: AnimationManager::triggerActionAnimation
bool AnimationManager::triggerActionAnimation(int actionType) {
    uint animHash = 0;
    int animHandle = 0;

    // Map action type to animation resource hash (likely CRC32 of animation path)
    switch (actionType) {
    case 0: 
        animHash = 0x13d67513; // e.g., "base/walk"
        break;
    case 1: 
        animHash = 0x13d67514; // "base/run"
        break;
    case 2: 
        animHash = 0x13d67515; // "base/sprint"
        break;
    case 3: 
        animHash = 0xba1b8847; // "special/action1"
        break;
    case 4: 
        animHash = 0x60d3064e; // "special/action2"
        break;
    default:
        return false; // Unknown action type, failure
    }

    // Resolve animation via hash and store handle in animHandle (output param)
    // FUN_006039d0 signature: likely resolves resource and returns handle indirectly
    FUN_006039d0(animHash, &animHandle, &actionType);

    // Execute the animation using the resolved handle
    FUN_004d3d90(animHandle);

    return true; // Success
}