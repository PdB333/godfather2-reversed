// FUNC_NAME: UnknownClass::getOwnerFromComponent
int __fastcall getOwnerFromComponent(int componentPtr)
{
    // +0xB4: pointer to an inner member of the owner (e.g., component slot)
    int* ownerInnerPtr = *(int**)(componentPtr + 0xB4);
    if (ownerInnerPtr != 0) {
        // Subtract the offset of that inner member within the owner to get the owner object base
        return (int)(ownerInnerPtr - 0x48);
    }
    return 0;
}