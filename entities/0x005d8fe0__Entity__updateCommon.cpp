// FUNC_NAME: Entity::updateCommon
void __fastcall Entity::updateCommon(int* thisPtr)
{
    // Pre-update processing (e.g., input, animation)
    FUN_005d8d50();

    // Call virtual functions sequentially: likely updateTransform, updateAnimation, getAnimProgress
    (*(code**)(*thisPtr + 0x54))(); // vtable offset 0x54: updateTransform
    (*(code**)(*thisPtr + 0x44))(); // vtable offset 0x44: updateAnimation
    int animProgress = (*(code**)(*thisPtr + 0x40))(); // vtable offset 0x40: getAnimProgress

    // Notify some manager (e.g., AudioManager) of animation state
    FUN_005d87b0(&PTR_DAT_00f1752c, animProgress);

    // Invoke a function pointer stored at offset 0x120 (thisPtr[0x48]) with a vtable offset of +4
    // Likely a callback or state handler (e.g., onPost Update)
    (*(code**)(thisPtr[0x48] + 4))();
}