// FUNC_NAME: Interpolator::sinEase
// Address: 0x006c89d0
// Role: Computes a sin-based ease interpolation using object's frequency factor (offset +0x60).
// The function calculates sin(end - start), then uses that to modulate a second sin.
float __thiscall Interpolator::sinEase(int this, float start, float end, float t)
{
    // delta = end - start
    float delta = end - start;

    // First sine: sin(delta)
    float sinDelta = sinf(delta);

    // +0x60: frequency/amplitude scaling factor specific to this interpolator
    float frequencyFactor = *(float *)(this + 0x60);

    // Second sine: sin(sinDelta * frequencyFactor * t + start)
    // This creates a wavy easing curve that depends on the start and frequency.
    float result = sinf(sinDelta * frequencyFactor * t + start);

    // Result is left in ST0 for the caller.
    return result;
}