// FUNC_NAME: Animated::playAnimation
// Function at 0x008b8f10: plays an animation on this object, checks flag to ensure not already playing.
void __thiscall Animated::playAnimation(int this, int animId, float blendTime)
{
    if ((*(uint *)(this + 0x18c) & 8) == 0) {
        // Not currently animating, proceed
        uint8_t priority = 0; // default priority
        if (animId == 0) {
            animId = 1;
            blendTime = DAT_00d5ef70; // default blend time constant
            priority = 2; // higher priority
        }

        // Reset any current animation state
        stopAnimation(this); // FUN_0072de20

        // Build animation request structure on stack (16-byte buffer at local_24)
        // Structure layout (conjectured, based on assignments):
        // offset 0: priority (byte)
        // offset 1: animId (byte)
        // offset 2: loop flag or extra (byte) - set to priority again? maybe unused
        // offset 4: vtable pointer (pointer to animation table)
        // offset 8: blendSpeed (float) - square if below threshold
        // The structure is passed to setAnimationRequest.

        // We fill the struct members via direct stack layout.
        // The decompiler separated them, but they are part of the 16-byte buffer.
        // We'll use a hypothetical struct for clarity.
        struct /* packed */ {
            uint8_t priority;
            uint8_t animId;
            uint8_t extra; // set to priority again (loop?)
            uint8_t pad;
            void **vtable;
            float blendSpeed;
        } request; // actually this is local_24 area, but we declare separately.

        request.priority = priority;           // local_25 = 0 or 2
        request.animId = (uint8_t)animId;      // local_14
        request.extra = priority;              // local_11 = local_25
        request.vtable = &PTR_LAB_00e5445c;    // animation virtual table
        if (_DAT_00d577a0 <= blendTime) {
            request.blendSpeed = blendTime * blendTime; // square blend speed if above threshold
        } else {
            request.blendSpeed = blendTime; // or unmodified? original code only sets if condition true, else uninitialized. We may need to initialize.
            // In the original, local_10 is only set inside the if, so it might be uninitialized otherwise.
            // We'll assume it's left as the previous value (or default). Safer to set it to blendTime.
            // Actually the condition is: if (_DAT_00d577a0 <= param_3) local_10 = param_3*param_3; So if false, local_10 remains whatever was on stack. That might be a bug, but we replicate.
        }

        // Issue the animation request
        setAnimationRequest(&request); // FUN_0081dab0, takes the 16-byte struct

        // Set animation flag (bit 3) to indicate animation is now playing
        *(uint *)(this + 0x18c) |= 8;

        // Finalize animation change
        finalizeAnimationChange(); // FUN_0072c130
    }
}