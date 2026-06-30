// FUNC_NAME: Transform::applyScaleTranslate
void __thiscall Transform::applyScaleTranslate(const float* input, const float* translation, float* output) const
{
    // This function applies a non-uniform scale (stored in this object) and then a translation.
    // output = scale * input + translation   (component-wise for each of the 4 components)
    // The transform stores scale factors as a 4-float array (e.g., sx, sy, sz, sw).
    
    float sx = this->scale[0];  // +0x00
    float sy = this->scale[1];  // +0x04
    float sz = this->scale[2];  // +0x08
    float sw = this->scale[3];  // +0x0C

    float ix = input[0];
    float iy = input[1];
    float iz = input[2];
    float iw = input[3];

    float tx = translation[0];
    float ty = translation[1];
    float tz = translation[2];
    float tw = translation[3];

    output[0] = sx * ix + tx;
    output[1] = sy * iy + ty;
    output[2] = sz * iz + tz;
    output[3] = sw * iw + tw;
}