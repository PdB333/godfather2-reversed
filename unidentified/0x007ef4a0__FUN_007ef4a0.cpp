// FUNC_NAME: SomeClass::getComponentFloat
// Function address: 0x007ef4a0
// Returns a float stored at offset 0x40 in a component pointed to by this+0x4.
// The original implementation promotes the 32-bit float to x87 extended precision (float10).

float __fastcall SomeClass::getComponentFloat(void* thisPtr)
{
    // thisPtr points to a game object
    // +0x4: pointer to a sub-component (e.g., a transform or physics state)
    void* component = *(void**)((char*)thisPtr + 4);
    // +0x40: a float value, likely a speed, scale, or other scalar
    float value = *(float*)((char*)component + 0x40);
    return value; // implicit promotion to float10 on x87
}