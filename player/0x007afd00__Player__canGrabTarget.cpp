// FUNC_NAME: Player::canGrabTarget
// Address: 0x007afd00
// Returns true if the player is within range and facing the grabber target

bool __fastcall Player::canGrabTarget(Player *this)
{
    Component *grabberComponent;
    Player *player;
    // Stack locals for transforms/vectors from virtual calls
    Vector3 localPos;      // +0x94 offset from local_94
    Vector3 localForward;  // +0x88 from fStack_88
    Vector3 targetPos;     // +0x38 from fStack_38
    Vector3 targetForward; // +0x48 from fStack_48
    float dotProduct;
    float distSq;
    float unused;

    // +0x58: pointer to a component (probably a GrabberComponent)
    grabberComponent = *(Component **)(this + 0x58);
    // Get singleton player (e.g., local player controller)
    player = (Player *)FUN_007ab710(); // likely PlayerManager::getLocalPlayer()

    if (grabberComponent && player) {
        // Call virtual at vtable+0x94: getComponent("m_grabber") -> returns component data or sets up
        (**(code **)(*(unsigned int *)grabberComponent + 0x94))(&localPos, "m_grabber");
        // Call virtual at vtable+0x90: getWorldTransform(&localPos, &localForward, 1) -> returns position and forward vector
        (**(code **)(*(unsigned int *)grabberComponent + 0x90))(&localPos, &localForward, 1);
        // Call virtual at vtable+0x90 on player: getWorldTransform(targetPos, targetForward, 1) using target from player+0x402
        (**(code **)(*(unsigned int *)player + 0x90))(targetPos, player + 0x402, 1);
        
        // Compute squared distance between grabber and player positions
        distSq = (localPos.z - targetPos.z) * (localPos.z - targetPos.z) +
                 (localPos.y - targetPos.y) * (localPos.y - targetPos.y) +
                 (localPos.x - targetPos.x) * (localPos.x - targetPos.x);
        
        // Compute dot product of the forward vectors
        dotProduct = localForward.x * targetForward.x +
                     localForward.y * targetForward.y +
                     localForward.z * targetForward.z;
        
        // Check distance threshold (DAT_00d5ef90) and facing threshold (DAT_00d5f6e8)
        if (distSq <= DAT_00d5ef90 && dotProduct >= DAT_00d5f6e8) {
            return true;
        }
    }
    return false;
}