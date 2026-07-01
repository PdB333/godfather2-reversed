// FUNC_NAME: AnimationBlendController::updateBlendProgress
void __fastcall AnimationBlendController::updateBlendProgress(int *this)
{
    int iVar1;
    float fVar2;
    // Stack structure used to pass data to FUN_004bdae0
    struct {
        undefined4 field_0;
        undefined4 field_4;
        undefined4 field_8;
        float field_C;
    } stackData;
    undefined4 local_20;
    undefined4 uStack_24;
    undefined4 uStack_1c;

    // Check if the animation/motion object pointer is valid (offset +0x00)
    if ((int *)*this != (int *)0x0) {
        // Call virtual function at vtable+4 (likely returns a vector/quaternion)
        (**(code **)(*(int *)*this + 4))(&local_20);
        // Call virtual function at vtable+8 (returns a float, e.g., blend weight)
        fVar2 = (float10)(**(code **)(*(int *)*this + 8))();
        // Reset some state (e.g., timer or flag)
        FUN_004262f0(0);
        // Prepare stack data from the virtual call results
        stackData.field_0 = uStack_24;
        stackData.field_4 = local_20;
        stackData.field_8 = uStack_1c;
        stackData.field_C = (float)fVar2;
        // Check transition condition (returns 2 if transition should advance)
        iVar1 = FUN_004bdae0(&stackData);
        if (iVar1 == 2) {
            // Increment transition counter at offset +0x08
            this[2] = this[2] + 1;
            return;
        }
    }
    // Reset counter if condition fails or no animation object
    this[2] = 0;
    return;
}