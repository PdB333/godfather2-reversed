// FUNC_NAME: updateTargetReference
void __fastcall updateTargetReference(int thisPtr)
{
    // Offset +0x9c: pointer to another object (e.g., target entity)
    // Offset +0x84: byte flag (bit 0 indicates if target reference is valid)
    // Offset +0x98: current target reference (int)
    // The pointed object's offset +0xac contains the target reference value

    if (*(int*)(thisPtr + 0x9c) != 0 && (*(byte*)(thisPtr + 0x84) & 1) != 0)
    {
        *(int*)(thisPtr + 0x98) = *(int*)(*(int*)(thisPtr + 0x9c) + 0xac);
    }
    else
    {
        *(int*)(thisPtr + 0x98) = 0;
    }
}