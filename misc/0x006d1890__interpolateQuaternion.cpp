// FUNC_NAME: interpolateQuaternion

// Address: 0x006d1890
// Role: Performs a quaternion (or 4-component vector) interpolation (lerp) between two vectors.
// If FUN_006d0ee0 returns non-zero, no interpolation is performed and 0 is returned.
// Otherwise, param_1 is updated as: param_1[i] = param_2[i] + gBlendFactor * (param_1[i] - param_2[i]) for i=0..3.
// This is equivalent to a blend from param_2 towards param_1 with factor gBlendFactor.
// gBlendFactor at 0x00d5780c is likely a globally defined smoothing/delta factor.

extern float gBlendFactor; // _DAT_00d5780c
extern char FUN_006d0ee0(float* target, float* source, float* blendFactor); // Returns 0 to indicate interpolation should proceed

int interpolateQuaternion(float* param_1, float* param_2)
{
    float blend[1]; // local_14, used to hold the global blend factor
    blend[0] = gBlendFactor;
    char skip = FUN_006d0ee0(param_2, param_1, blend);
    if (skip == 0) {
        float yTarget = param_2[1];
        float zTarget = param_2[2];
        float wTarget = param_2[3];
        param_1[0] = (param_1[0] - param_2[0]) * blend[0] + param_2[0];
        param_1[1] = (param_1[1] - yTarget) * blend[0] + yTarget;
        param_1[2] = (param_1[2] - zTarget) * blend[0] + zTarget;
        param_1[3] = (param_1[3] - wTarget) * blend[0] + wTarget;
        return 1;
    }
    return 0;
}