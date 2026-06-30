// FUNC_NAME: PlayerActionableTargetSM::setActiveTarget
int __thiscall PlayerActionableTargetSM::setActiveTarget(PlayerActionableTargetSM* this, uint32_t param_1) {
    // Check if the state machine is active (flag at +0x1744)
    if (*(uint8_t*)((uintptr_t)this + 0x1744) != 0) {
        // Get the current target data structure (via internal helper)
        void* targetData = reinterpret_cast<void*(__thiscall*)(PlayerActionableTargetSM*)>(0x005e2150)(this);
        if (targetData != nullptr) {
            // Set the target parameter (e.g., entity ID) at offset +0x24c
            *(uint32_t*)((uintptr_t)targetData + 0x24C) = param_1;
            return 1;
        }
    }
    return 0;
}