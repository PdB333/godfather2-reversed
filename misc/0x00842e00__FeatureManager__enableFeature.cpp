// FUNC_NAME: FeatureManager::enableFeature
void __fastcall FeatureManager::enableFeature(int thisPtr)
{
    // Check if the 0x1000 flag (likely "initialized" or "enabled") is not set
    if ((*(uint *)(thisPtr + 0x4c) & 0x1000) == 0) {
        // Set the flag to indicate one-time initialization
        *(uint *)(thisPtr + 0x4c) |= 0x1000;
        // Call the first-time setup function
        FUN_0093c210(); // e.g., startSystem()
    }
    // Always call the second function (e.g., setActive(true))
    FUN_0081dd40(1);
}