// FUNC_NAME: Vector4::setFromScaledInverse
// Address: 0x00582db0
// Purpose: Sets this vector to the component-wise product of scale factors (param_1)
//          and input vector (param_2) with a global constant (DAT_00e2b1a4).
//          Each output component = input_component * (global_constant / scale_component) for x,y,z
//          w component is set to global_constant.
// Note: param_1 is a 3-component scale factor array, param_2 is a 4-component input vector.
void __thiscall Vector4::setFromScaledInverse(Vector4* this, const float* scaleFactors, const float* inputVec)
{
    float globalConstant = DAT_00e2b1a4; // Unknown global constant (likely 1.0f)

    float invScaleX = globalConstant / scaleFactors[0];
    float invScaleY = globalConstant / scaleFactors[1];
    float invScaleZ = globalConstant / scaleFactors[2];

    this->x = inputVec[0] * invScaleX;
    this->y = inputVec[1] * invScaleY;
    this->z = inputVec[2] * invScaleZ;
    this->w = globalConstant;
}