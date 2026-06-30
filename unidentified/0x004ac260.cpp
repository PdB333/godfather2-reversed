// FUNC_004ac260: GameObject::getNodeIdWithVisibilityFlag
uint __fastcall GameObject::getNodeIdWithVisibilityFlag(GameObject* this)
{
    // +0x48: sceneNode pointer (maybe m_pSceneNode)
    uint sceneNodePtr = *(uint*)(this + 0x48);
    // Get the owning object from the scene node. The scene node is embedded at offset 0x48 in the owner struct,
    // so subtracting 0x48 gives the owner base.
    GameObject* pOwner = nullptr;
    if (sceneNodePtr != 0) {
        pOwner = (GameObject*)(sceneNodePtr - 0x48);
    }
    // +0x218 in owner: pointer to a physics/collision component (e.g., m_pPhysicsBody)
    PhysicsBody* pPhysics = nullptr;
    if (pOwner != nullptr) {
        pPhysics = *(PhysicsBody**)((uint)pOwner + 0x218);
    }
    uint result = sceneNodePtr & 0xFFFFFF00; // Keep the scene node identifier (upper 24 bits)
    if (pPhysics != nullptr) {
        // +0x24 in physics: distance to camera or some world-space distance
        if (*(float*)(pPhysics + 0x24) <= g_visibilityDistance) {
            // Within visibility range → set low byte flag to 1
            result = (result & 0xFFFFFF00) | 1;
        }
        // +0x10 in physics: flags, checking bits 0,1,25 (0x2000003)
        if ((*(uint*)(pPhysics + 0x10) & 0x2000003) != 0) {
            // Has active/collision flags → also set low byte flag to 1
            result = (result & 0xFFFFFF00) | 1;
        }
    }
    return result;
}