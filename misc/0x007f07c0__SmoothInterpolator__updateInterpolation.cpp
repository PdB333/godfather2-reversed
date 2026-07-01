// FUNC_NAME: SmoothInterpolator::updateInterpolation
// Address: 0x007f07c0
// This function updates a smooth interpolation between two float values, possibly for a follower camera or physics constraint.
// It reads floats at offset 0x124 from two child objects (target and current), and uses a stored time at +0xf4 with a global simulation time to compute a custom smoothing factor.

extern float g_simTime; // Global simulation time, likely _DAT_00d5780c

class SmoothInterpolator
{
public:
    // +0x00: vtable (not shown)
    // +0x04: Pointer to target object (has a float at +0x124)
    // +0x08: Pointer to current object (has a float at +0x124)
    // +0xf4: Last update time (float)

    void updateInterpolation(); // __fastcall with this in ECX
};

void __fastcall SmoothInterpolator::updateInterpolation()
{
    float fVar1;
    
    // Compute time since last update
    fVar1 = g_simTime - *(float *)((char *)this + 0xf4);
    
    // Call the interpolation function with:
    //   - Float value from current object at +0x08 -> +0x124
    //   - Float value from target object at +0x04 -> +0x124
    //   - A computed smoothing parameter: g_simTime - fVar1*fVar1
    //   (This non-linear factor may be part of a custom easing or spring formula)
    lerpFloat(*(float *)(*(int *)((char *)this + 8) + 0x124),
              *(float *)(*(int *)((char *)this + 4) + 0x124),
              g_simTime - fVar1 * fVar1);
    
    return;
}