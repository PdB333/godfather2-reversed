// FUNC_NAME: EntityComponent::getOwner
int __fastcall EntityComponent::getOwner(EntityComponent* thisPtr)
{
    // Check if the component pointer at offset 0x74c is non-null
    if (*(int*)((char*)thisPtr + 0x74c) != 0)
    {
        // Subtract 0x48 to get the owning entity (the component is at offset 0x48 within the owner)
        return *(int*)((char*)thisPtr + 0x74c) - 0x48;
    }
    return 0;
}