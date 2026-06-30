// FUNC_NAME: scaleVector4
void scaleVector4(float scale)
{
    // Scale all four components of a 4D vector (likely a quaternion or 4D vector)
    // The vector is stored in global memory at addresses 0x01125260-0x0112526c
    // These globals are likely static members of a math class or module-level variables
    _DAT_01125260 = scale * _DAT_01125260; // x or w component
    _DAT_01125264 = scale * _DAT_01125264; // y or x component
    _DAT_01125268 = scale * _DAT_01125268; // z or y component
    _DAT_0112526c = scale * _DAT_0112526c; // w or z component
}