// FUNC_NAME: DebugRenderHelper::setTwoVector4s
void __thiscall DebugRenderHelper::setTwoVector4s(int *vec1, int *vec2) // vec1 is this? Actually param1 is this but code uses it as data pointer. Hmm.
{
    // Copy first vector (4 ints) from this object's own data to global debug buffer A
    // Offsets: this+0x0 to this+0xC
    gDebugVector1[0] = vec1[0]; // _DAT_0121b8a0
    gDebugVector1[1] = vec1[1]; // _DAT_0121b8a4
    gDebugVector1[2] = vec1[2]; // _DAT_0121b8a8
    gDebugVector1[3] = vec1[3]; // _DAT_0121b8ac

    // Copy second vector from parameter to global debug buffer B
    // Offsets: vec2+0x0 to vec2+0xC
    gDebugVector2[0] = vec2[0]; // _DAT_0121b8b0
    gDebugVector2[1] = vec2[1]; // uRam0121b8b4
    gDebugVector2[2] = vec2[2]; // uRam0121b8b8
    gDebugVector2[3] = vec2[3]; // uRam0121b8bc

    // Only update the debug system if a certain debug mode is active
    // Checks: gDebugModePointer (DAT_012058e8) points to gDebugSingleton (DAT_0121b740)
    // And current debugState (DAT_0121b754) equals expected active state (DAT_0121bbbc)
    if ( (gDebugModePointer == &gDebugSingleton) && (gDebugCurrentState == gDebugActiveState) )
    {
        // Submit the vector data to the debug drawing system
        // First argument: debug context, second: some identifier, third: pointer to vector data
        debugSubmitVectorData(gDebugActiveState, gDebugIdentifierA, &gDebugVector1);
        debugSubmitVectorData(gDebugActiveState, gDebugIdentifierB, &gDebugVector2);
    }
}