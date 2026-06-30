// FUNC_NAME: Entity::setFlag
// Function address: 0x0068e9c0
// Role: Sets a flag at offset 0x10 to 1, and calls another function with the parameter.
// The called function (0x004d3d90) likely processes the parameter before the flag is set.

void __thiscall Entity::setFlag(int thisPtr, undefined4 param)
{
    // Call some processing function with the parameter
    FUN_004d3d90(param);
    
    // Set the flag at offset 0x10 to 1 (active/enabled)
    *(byte*)(thisPtr + 0x10) = 1;
}