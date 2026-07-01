// FUNC_NAME: Animated::playAnimation
// Address: 0x007cbf50
// Role: Plays an animation on an entity if not already playing. Retrieves animation handle from resource ID and starts playback at normal speed and full blend weight.

void __thiscall Animated::playAnimation(int* thisObj, int animResourceId)
{
    // Check if animResourceId is valid and bit 6 of mAnimationFlags is clear (not already playing)
    if ((animResourceId != 0) && (((uint)thisObj[0x74] >> 6 & 1) == 0))
    {
        // Get animation handle from the resource ID
        int animHandle = getAnimationHandle(animResourceId);  // FUN_004dafd0
        // Store handle at offset 0x1CC (thisObj[0x73])
        thisObj[0x73] = animHandle;
        // Call virtual function at vtable slot 0x2c (playAnimation) with:
        // animHandle, loop=1, startNow=1, unknown=0, speed=1.0f, blendWeight=1.0f
        (**(code**)(*thisObj + 0x2c))(animHandle, 1, 1, 0, 0x3f800000, 0x3f800000);
        // Call post-animation-setup routine (e.g., notify observers)
        postAnimationSetup();  // FUN_007cb020
    }
    return;
}