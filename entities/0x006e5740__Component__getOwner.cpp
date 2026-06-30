// FUNC_NAME: Component::getOwner
int __fastcall Component::getOwner(int thisPtr)
{
    // At offset +0x30C0, store a back-pointer to the owning object minus 0x48.
    // If non-null, adjust to get the actual owner base address.
    int *pBackPtr = *(int **)(thisPtr + 0x30C0);
    if (pBackPtr != nullptr)
    {
        return (int)(pBackPtr - 0x48); // Convert to owner pointer
    }
    return 0;
}