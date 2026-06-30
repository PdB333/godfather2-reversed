// FUNC_NAME: UIHudMinimapMarkerManager::renderMarker

void __thiscall UIHudMinimapMarkerManager::renderMarker(UIHudMinimapMarkerManager* this, void* markerData) {
    // Convert marker screen position or transform
    UIHudMinimapMarkerManager::convertMarkerPosition(markerData);
    
    int markerFlags = *(int*)((int)this + 0xBA); // +0xBA: marker status/state flags
    bool isActive = (this->vtable->funcAt0x19c)(this); // virtual call: isMarkerActive()
    
    if (!isActive) {
        if (markerFlags != 0) {
            char nameBuffer[60]; // local buffer for marker name
            UIHudMinimapMarkerManager::getMarkerName(markerData, nameBuffer); // e.g., "Hideout", "Safehouse"
            UIMath::hashStringToId(nameBuffer);
            
            // Build color parameters (RGBA) for the marker
            struct MarkerColor {
                float r; // offset +0x30
                float g; // offset +0x34
                float b; // offset +0x38
                float a; // global alpha constant
            } color;
            color.r = *(float*)((int)markerData + 0x30);
            color.g = *(float*)((int)markerData + 0x34);
            color.b = *(float*)((int)markerData + 0x38);
            color.a = DAT_00e2b1a4; // global alpha value
            
            char finalOutput[16];
            UIRenderer::bindColorAndText(&color, finalOutput); // set shader parameters or draw text
        }
    } else {
        // Marker is currently highlighted/active – show expanded tooltip or popup
        UIHudMinimapMarkerManager::showMarkerTooltip();
    }
    
    // Post-render state restore
    (this->vtable->funcAt0x258)(this); // virtual call: finishRendering()
}