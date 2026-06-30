// FUNC_NAME: EARSAnimController::notifyObservers

int __thiscall EARSAnimController::notifyObservers(void* this) {
    // Call global synchronization function (likely entering a critical section or updating global state)
    globalUpdateTick();

    float duration;
    int currentTime;
    
    // Check if we have a valid animation state object at offset +0x98
    if (*(int*)((int)this + 0x98) == 0) {
        duration = 0.0f;
        currentTime = -1;
    }
    else {
        // Read duration/scale from the animation state (+0x98 -> +0x1c8)
        duration = *(float*)(*(int*)((int)this + 0x98) + 0x1c8);
        // Get current time from external function (returns ticks or milliseconds)
        currentTime = getCurrentTime();
    }

    float timeFloat = (float)currentTime;
    if (currentTime < 0) {
        timeFloat += FLOAT_BIAS_CONSTANT;  // DAT_00e44578 – bias for negative values
    }

    // Compute tick count from time ratio: round((timeFloat / duration) * TICK_SCALE)
    float ratio = (timeFloat / duration) * TICK_SCALE_CONSTANT; // DAT_00e2e230
    int tickCount = static_cast<int>(ratio + 0.5f); // round-to-nearest

    // Notify all registered callbacks (linked list at +0xb4)
    int* pNode = *(int**)((int)this + 0xb4);
    while (pNode != nullptr) {
        // Each node has a function pointer at offset +4, called with tickCount
        (*(void(__thiscall*)(void*, int))(*pNode + 4))(this, tickCount);
        pNode = *(int**)pNode; // advance to next node (next pointer at node start)
    }

    return 1;
}