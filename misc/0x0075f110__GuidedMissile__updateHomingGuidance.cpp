// FUNC_NAME: GuidedMissile::updateHomingGuidance
// Function at 0x0075f110: Computes a homing force toward a target and plays a guidance sound.
// Reconstructed from Ghidra decompilation.

// Known classes: not directly, but matches a guided projectile/missile pattern.
// Fields:
// this+0x58 : pointer to a physics body object (vtable at +0x1c0 returns linear speed)
// this+0x60 : position x (relative to target? actually world pos of missile)
// this+0x68 : position z (world)
// this+0x78 : function pointer for default sound id retrieval (returns undefined4)
// this+0x8c : optional override function pointer (takes address of +0x78 as argument)
// this+0x110 : computed force vector x
// this+0x114 : computed force vector y (always 0)
// this+0x118 : computed force vector z
// this+0x11c : byte flag (set to 0 at end)
// this+0x120 : scalar magnitude (used for sound volume?)

// External functions:
// FUN_00471610 : returns a pointer to a target object (with position at +0x30 and +0x38)
// FUN_0056afa0 : computes length (or squared length?) of a 3D vector
// FUN_0045f020 : plays a sound (soundID, bool?, float volume, bool loop?, bool something)

void GuidedMissile::updateHomingGuidance()
{
    // Get current linear speed from physics body
    float speed = (**(float (__thiscall **)(int))(**(int **)(this + 0x58) + 0x1c0))();
    
    // Get target object pointer
    int *targetPtr = FUN_00471610();
    
    // Compute 2D displacement (horizontal only, y=0)
    float dx = *(float *)(this + 0x60) - *(float *)(targetPtr + 0x30);
    float dz = *(float *)(this + 0x68) - *(float *)(targetPtr + 0x38);
    float dy = 0.0f;  // y component unused
    int dummy = 0;     // unused (uStack_14)
    
    // Compute distance (using a helper function that may compute magnitude)
    float distance = FUN_0056afa0(&dx, &dx);  // note: both args point to dx, may return 2D length
    
    // Homing acceleration: v^2 / (distance * tuningFactor)
    float accelScale = (speed * speed) / (distance * DAT_00e44750);
    
    // Store force vector (normalized direction * acceleration)
    *(float *)(this + 0x110) = dx * accelScale;
    *(float *)(this + 0x114) = dy * accelScale;
    *(float *)(this + 0x118) = dz * accelScale;
    
    // Compute force magnitude for sound scaling
    float forceMag = *(float *)(this + 0x110) * *(float *)(this + 0x110) +
                     *(float *)(this + 0x114) * *(float *)(this + 0x114) +
                     *(float *)(this + 0x118) * *(float *)(this + 0x118);
    float soundScale = speed / sqrt(forceMag);
    *(float *)(this + 0x120) = soundScale;
    soundScale *= _DAT_011260b0;  // global volume multiplier
    
    // Get sound ID via function pointer(s)
    int soundId;
    if (*(int (__thiscall **)(int))(this + 0x8c) == nullptr) {
        soundId = (*(int (__thiscall **)())(this + 0x78))();
    } else {
        soundId = (*(int (__thiscall **)(int *))(this + 0x8c))((int *)(this + 0x78));
    }
    
    // Play the guidance sound
    FUN_0045f020(soundId, 0, soundScale, 1, 1);
    
    // Clear flag
    *(unsigned char *)(this + 0x11c) = 0;
}