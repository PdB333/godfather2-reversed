// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_ColorMonopoly
// FUNC_NAME: MarkerIcon::SetBackgroundColor
// Function address: 0x00948ee0
// Role: Sets the background color for a marker icon by constructing a path and calling a shader/color function.

void __fastcall MarkerIcon::SetBackgroundColor(void* thisPtr)
{
    char pathBuffer[256]; // stack buffer for constructing path

    // Check if there is a base path at offset +0x18
    if (*(char*)((uintptr_t)thisPtr + 0x18) != '\0')
    {
        // Build path: <basePath>/marker/icon/bg/
        __snprintf(pathBuffer, sizeof(pathBuffer), "%s/marker/icon/bg/",
                   (const char*)((uintptr_t)thisPtr + 0x18));

        // Apply color from bytes at offsets +0x150 (R), +0x151 (G), +0x152 (B) as floats
        FUN_0059ef40(pathBuffer,
                     (float)*(unsigned char*)((uintptr_t)thisPtr + 0x150),
                     (float)*(unsigned char*)((uintptr_t)thisPtr + 0x151),
                     (float)*(unsigned char*)((uintptr_t)thisPtr + 0x152));
    }
}