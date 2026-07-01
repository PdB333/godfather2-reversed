// FUNC_NAME: SomeClass::addDeltaTime
void __thiscall SomeClass::addDeltaTime(float deltaTime)
{
    // Check if flags at +0x118 have bits 0x18000 (pause/disable flags?) cleared
    if ((*(uint *)(this + 0x118) & 0x18000) == 0)
    {
        // Accumulate time at +0x148
        *(float *)(this + 0x148) += deltaTime;
    }
}