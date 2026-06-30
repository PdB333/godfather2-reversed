// FUNC_NAME: setZ (stores float at offset +0x8, likely z component of a vector)
float __thiscall setZ(int thisPtr, float value)
{
    *(float*)(thisPtr + 8) = value; // +0x8: z-coordinate of position or similar field
    return value;
}