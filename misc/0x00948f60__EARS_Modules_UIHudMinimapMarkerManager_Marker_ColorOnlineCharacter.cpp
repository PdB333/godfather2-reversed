// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_ColorOnlineCharacter
// FUNC_NAME: MinimapMarker::applyMarkerColor
void __thiscall MinimapMarker::applyMarkerColor() {
    char pathBuffer[256];

    // Check if the base path (e.g., "ui/minimap") is set (offset 0x18)
    if (this->basePath != nullptr) {
        // Construct path to marker icon color asset
        __snprintf(pathBuffer, sizeof(pathBuffer), "%s/marker/icon/color/", this->basePath);

        // Call render function with color from byte components at +0x150..0x152
        FUN_0059ef40(pathBuffer,
                     static_cast<float>(this->colorRed),   // +0x150
                     static_cast<float>(this->colorGreen), // +0x151
                     static_cast<float>(this->colorBlue)); // +0x152
    }
}