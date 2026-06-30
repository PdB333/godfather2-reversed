// FUNC_NAME: someClass::someCullingOrScalingFunction

void __thiscall someCullingOrScalingFunction(int this, void* param_2, int* param_3, void* param_4, void* param_5)
{
    float local_4 = 0.0f;
    // The global _DAT_00e44670 is likely a scaling factor (e.g. screen height, map size, or a flag)
    // Call to compute a normalized value or distance; local_4 receives result
    FUN_005ec6d0(this, &local_4, param_4, param_5);
    // Scale the float value by the global and store as an int (e.g. pixel coordinate or game unit)
    *param_3 = (int)(local_4 * _DAT_00e44670);
}