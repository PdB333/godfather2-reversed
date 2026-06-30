// FUNC_NAME: EARSObject::setVectorWithParams
// Address: 0x00424720
// Role: Wrapper that reorders a 3D vector's components (y, x, z) and passes them along with an extra parameter and 'this' to the actual function at 0x0056b8a0.
void __thiscall EARSObject::setVectorWithParams(void *this, undefined4 extraParam, undefined4 *vectorArg) // vectorArg[0]=x, vectorArg[1]=y, vectorArg[2]=z
{
    FUN_0056b8a0(vectorArg[1], // y
                 *vectorArg,   // x
                 vectorArg[2], // z
                 extraParam,
                 this);
    return;
}