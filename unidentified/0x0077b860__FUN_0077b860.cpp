// FUNC_NAME: SomeClass::updateSomething
void SomeClass::updateSomething(int param_1, int param_2)
{
    // Read two 8-byte values from offsets +0x253c and +0x2544 in the object
    // These likely represent a 16-byte structure (e.g., a vector or quaternion)
    __int64 local_10 = *(__int64 *)(param_2 + 0x253c);
    __int64 local_8 = *(__int64 *)(param_2 + 0x2544);
    
    // Call function with the 16-byte data, the object pointer, and 1.0f as a scalar
    FUN_0077eaa0(&local_10, param_2, 0x3f800000); // 1.0f
    return;
}