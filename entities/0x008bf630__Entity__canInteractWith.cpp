// FUNC_NAME: Entity::canInteractWith
// Address: 0x008bf630
// Role: Determines if the player/entity can interact with a given object based on distance and state.
// Returns 1 if interaction is allowed, 0 otherwise.

int Entity::canInteractWith(float* outDistance, Entity* target) {
    Entity* savedTarget;
    bool valid;
    int player;
    int transform1, transform2;
    float dx, dy, dz, distSq;

    savedTarget = target;
    if (this != target) {
        *outDistance = 0.0f;
        valid = target->getInteractionParams(0x369ac561, outDistance); // Probably a hash for "use" action
        if (valid && (player = getLocalPlayer(), player != 0) &&
            (player = FUN_007351e0(), player != 0) &&
            ((*(uint*)(player + 0x5C) >> 0x1D) & 1) == 0) {
            return 0;
        }
        if (*outDistance != g_maxInteractionDistance) {
            transform1 = FUN_00471610(); // Get position of 'this'? Or player?
            transform2 = FUN_00471610(); // Get position of target?
            dx = *(float*)(transform2 + 0x30) - *(float*)(transform1 + 0x30);
            dy = *(float*)(transform2 + 0x34) - *(float*)(transform1 + 0x34);
            dz = *(float*)(transform2 + 0x38) - *(float*)(transform1 + 0x38);
            distSq = dx * dx + dy * dy + dz * dz;
            if (*outDistance < distSq) {
                return 0;
            }
        }
        if (target != (Entity*)g_interactionFlag) {
            return FUN_007f80e0(target, target); // Perform interaction logic
        }
    }
    return 1;
}