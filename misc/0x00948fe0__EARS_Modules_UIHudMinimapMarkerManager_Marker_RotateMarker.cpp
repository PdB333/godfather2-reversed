// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_RotateMarker
// FUNC_NAME: MarkerIcon::setRotation
void __thiscall MarkerIcon::setRotation(float rotation)
{
    char buffer[256];
    if (*(char*)(this + 0x18) != '\0')  // +0x18: path string (e.g., marker icon name)
    {
        __snprintf(buffer, 0x100, "%s/marker.icon._rotation", (char*)(this + 0x18));
        FUN_0059ecb0(buffer, rotation);  // Set property: likely a float property setter
    }
}