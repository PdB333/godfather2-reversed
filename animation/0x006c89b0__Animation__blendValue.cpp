// FUNC_NAME: Animation::blendValue
// Function address: 0x006c89b0
// Interpolates a value using a member blend factor (stored at +0x60) and an additional weight.
// Used for blending animation/camera parameters over time.
float Animation::blendValue(float from, float to, float weight) {
    // Standard linear interpolation: from + (to - from) * blendFactor * weight
    // Where blendFactor is a member variable controlling how much of the transition is applied.
    return (to - from) * this->blendFactor * weight + from;
}