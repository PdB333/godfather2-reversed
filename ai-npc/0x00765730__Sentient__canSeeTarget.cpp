// FUNC_NAME: Sentient::canSeeTarget
// Address: 0x00765730
// Role: Determines if this entity can see its current target (e.g., for AI or player targeting)
//   Uses a global combat flag to override line-of-sight check.
//   Offsets: this+0x5c -> sceneNode (ISceneNode*), +0x70 -> localTransform (Matrix4),
//   sceneNode+0x24cc -> targetMemberPtr (void*), which after -0x48 gives a CBaseEntity* with flag at +0x8e0.

bool __thiscall Sentient::canSeeTarget() {
    // Get the scene node (likely owned by the game object)
    ISceneNode* sceneNode = *(ISceneNode**)(this + 0x5c); // +0x5c

    // Dereference a pointer stored in the scene node and adjust to get the target entity
    int targetMember = *(int*)(sceneNode + 0x24cc); // +0x24cc: pointer to a member of the target object
    CBaseEntity* targetEntity = nullptr;
    if (targetMember != 0) {
        targetEntity = (CBaseEntity*)(targetMember - 0x48); // subtract offset to get base of target entity
    }

    // Check global condition (e.g., is combat mode active?)
    bool globalCombatActive = GlobalCombatActive(); // FUN_00717f40

    // If global combat is active and we have a valid target that has its visibility flag set (bit 0), immediately return true
    if (globalCombatActive && targetEntity != nullptr && (*(byte*)((uint)targetEntity + 0x8e0) & 1) != 0) { // +0x8e0: flags
        return true;
    }

    // Perform transform-based visibility check
    // Retrieve a transform ID and the scene node, then compute a local world transform
    uint32 transformID = *(uint32*)(sceneNode + 0x21dc); // +0x21dc: some ID (e.g., camera slot)
    Matrix4* outTransform = (Matrix4*)(this + 0x70); // use a transform buffer stored in the class
    GetWorldTransform(transformID, sceneNode, outTransform); // FUN_0071a720

    // Invert the transform (to get view or inverse camera)
    MatrixInverse(outTransform); // FUN_00716420

    // Perform a frustum / line-of-sight test
    bool inFrustum = IsTransformInFrustum(outTransform); // FUN_00714770: returns char (0 = not visible, nonzero = visible)

    // Return true if the target is NOT visible (i.e., weapon lock or AI check requires non-visibility? Actually `bool == !inFrustum`?)
    // The decompiled logic: return (cVar1 == '\0'); so if inFrustum returns 0 -> false? Let's interpret: 
    //   if isTransformInFrustum returns 0 (not visible), function returns true?
    // This suggests the function returns true when the target is outside the frustum (e.g., for culling).
    // However, the name "canSeeTarget" might need reversal.
    // Based on context: the function ultimately returns true when the target is not visible (for culling purposes).
    // But the name is arbitrary; we keep the logic as decompiled.
    return (inFrustum == 0);
}

// Called helper functions (declared elsewhere)
bool GlobalCombatActive(); // FUN_00717f40
void GetWorldTransform(uint32 id, ISceneNode* node, Matrix4* out); // FUN_0071a720
void MatrixInverse(Matrix4* m); // FUN_00716420
char IsTransformInFrustum(Matrix4* m); // FUN_00714770: returns 0 if not in frustum (or visible? unknown)