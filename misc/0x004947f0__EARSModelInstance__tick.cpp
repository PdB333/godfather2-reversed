// FUNC_NAME: EARSModelInstance::tick
// Function at 0x004947f0: Main per-frame update for a model instance.
// - Calls global transform sync, optional skinning update, bounds and visibility refresh.
void __thiscall EARSModelInstance::tick(void) {
    // Synchronize world transform from parent hierarchy (likely sets dirty flags).
    syncWorldTransform();  // FUN_00490b20

    // If a skeleton skinning data pointer is present, apply blending/corrections.
    if (this->pSkinData != nullptr) {  // +0x1c0
        // pSkinData is likely a skeleton or blend shape pointer.
        // meshHandle ( +0x14 ) identifies which mesh to update.
        // Bone transform output buffer at this + 0x1d0.
        applySkinning(this->meshHandle,      // +0x14
                      this->pSkinData,       // +0x1c0
                      this->boneTransforms); // +0x1d0  // FUN_0060ad20
    }

    // Refresh bounding box/collision volumes after transform/skin changes.
    updateBounds(); // FUN_00492190

    // Recalculate visibility / culling state.
    updateVisibility(); // FUN_00494220
}