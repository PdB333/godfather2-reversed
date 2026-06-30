// FUNC_NAME: BaseEntity::process

void BaseEntity::process() {
    // Increment recursion guard / process depth counter
    ++g_processDepth;

    // Network byte order conversion of 0 (likely a no-op used for syncing or debug)
    htonl(0);

    // Call virtual update method at vtable index 3 (offset 0xC)
    this->vtable->onUpdate();

    // Attempt to obtain a target entity from two sources
    BaseEntity* pTarget = getLocalPlayer();           // FUN_00655250
    if (pTarget == nullptr) {
        pTarget = getLocalAI();                       // FUN_00655130
    }

    // If a target exists, process action using data at offset 0x1A4
    if (pTarget != nullptr) {
        uint32_t actionParam = *(uint32_t*)(reinterpret_cast<uint8_t*>(pTarget) + 0x1A4); // some field
        processTargetAction(actionParam, pTarget);     // FUN_006576b0
    }

    --g_processDepth;
}