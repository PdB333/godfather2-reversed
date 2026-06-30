// FUNC_NAME: Math::addVector3PreserveW
// Address: 0x0051e2c0
// Role: Adds two 4-component vectors (x,y,z) component-wise, preserving the destination's w component.
// Note: Uses custom calling convention: dest in EAX, src1 in EDX, src2 on stack, ECX unused.
void __fastcall addVector3PreserveW(void* unusedEdxReserved, float* src1, float* src2)
{
    // The destination pointer is passed via EAX register (denoted as "dest" here)
    // For clarity we use a local variable representing the register artifact.
    // In the actual binary, the destination is placed in EAX before the call.
    float* dest; // in_EAX
    // The following operations are performed on the register pointer:
    // Store original w component of dest
    float wOrig = dest[3];
    // Add x, y, z components
    *dest = src1[0] + src2[0];
    dest[1] = src1[1] + src2[1];
    dest[2] = src1[2] + src2[2];
    // Restore the original w component (unchanged)
    dest[3] = wOrig;
}
```