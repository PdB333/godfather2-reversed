// FUNC_NAME: CrewLeaderComponent::setMaxCrewSize
// Function address: 0x0055d7d0
// Sets the maximum crew size, clamped to 15 (0xF). Offset +0x114 holds the value.
void __thiscall CrewLeaderComponent::setMaxCrewSize(void* thisPtr, unsigned int newMax)
{
    if (newMax == 0)
    {
        *(unsigned int*)((unsigned char*)thisPtr + 0x114) = 0; // +0x114: maxCrewSize
        return;
    }
    if (newMax > 0xE)
    {
        newMax = 0xF; // clamp to 15
    }
    *(unsigned int*)((unsigned char*)thisPtr + 0x114) = newMax;
}