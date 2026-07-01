// FUNC_NAME: Entity::preRenderUpdate
void __fastcall Entity::preRenderUpdate(Entity* this)
{
    // g_entityManager is a global singleton at 0x01130950
    if (this != nullptr)
    {
        // Get some manager object (e.g., SceneManager or RenderManager)
        int* manager = reinterpret_cast<int*>(FUN_0043b870(g_entityManager));
        // Check if the manager's active flag (offset +0x20) is set
        if (manager != nullptr && *reinterpret_cast<int*>(manager + 0x20) != 0)
        {
            // Update debug display or debug UI
            FUN_00998270();
        }
    }

    // Mark the entity as needing update (1 = true)
    FUN_007a4250(1);

    // Call virtual function at vtable offset 0xfc (e.g., updateLogic)
    (**(code**)(*this + 0xfc))();

    // Build a world transform from a global matrix (e.g., camera or parent)
    Transform worldTransform;
    FUN_004a9000(&worldTransform);
    // Run identity or clear function
    FUN_00472120();

    // Initialize local transform fields (offset +0x84, +0x74, +0x64 are zeroed)
    worldTransform.field_84 = 0;
    worldTransform.field_74 = 0;
    worldTransform.field_64 = 0;
    // Set field_54 from a global constant (_DAT_00d5780c)
    worldTransform.field_54 = _DAT_00d5780c;

    // Propagate the transform data to a separate stack area (uStack_90 etc.)
    Transform renderTransform = worldTransform;

    // Call virtual function at vtable offset 0x28 (setTransform)
    (**(code**)(*this + 0x28))(&renderTransform);

    // Call virtual function at vtable offset 0x304 (postUpdate or finalizeRender)
    (**(code**)(*this + 0x304))();
}