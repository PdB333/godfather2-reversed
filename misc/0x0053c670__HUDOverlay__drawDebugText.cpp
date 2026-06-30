// FUNC_NAME: HUDOverlay::drawDebugText

// Function at 0x0053c670: draws debug text overlay on HUD elements
// Compares overlay type ID at +0x10 with two global constants,
// then calls renderDebugString with appropriate text source
void __fastcall HUDOverlay::drawDebugText(HUDOverlay* this) {
    // Begin overlay rendering context (e.g., push scissor rect, enable alpha)
    pushRenderContext();

    int overlayType = *(int*)((uint8_t*)this + 0x10); // +0x10: overlay type ID
    // First condition: overlay type matches a specific debug overlay and a global debug string exists
    if (overlayType == g_debugOverlayTypeA && g_debugString != nullptr) {
        renderDebugString(overlayType, g_debugString, g_debugTextBuffer);
        return;
    }

    // Second condition: overlay type matches a different debug overlay and internal text buffer is present
    if (overlayType == g_debugOverlayTypeB && *(int*)((uint8_t*)this + 0x270) != 0) { // +0x270: per‑instance text buffer pointer
        renderDebugString(overlayType, *(int*)((uint8_t*)this + 0x270), g_debugTextBuffer);
    }
}