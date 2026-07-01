// FUNC_NAME: compareRenderObjects
int __cdecl compareRenderObjects(int* const* renderablePtrA, int* const* renderablePtrB)
{
    // Guard: if the first pointer is null, return 0 (equal)
    if (renderablePtrA == nullptr) {
        return 0;
    }

    // Only proceed if second pointer is valid and global render context exists
    if ((renderablePtrB != nullptr) && (g_renderContext != 0)) {
        int renderMode = *(int*)(g_renderContext + 0xb8); // +0xb8: current render mode/scene type

        // Opaque depth sorting modes? (10, 11, 12 are typical opaque/alpha-test sort keys)
        if ((renderMode != 10) && (renderMode != 11) && (renderMode != 12)) {
            // For other modes (e.g., deferred or shadow), check if distance sort is needed
            if ((renderMode != 25) &&
                (isDistanceSortDisabled() == false)) {
                if (isAlternativeSortEnabled() == false) {
                    // Fallback: return the leftover EDX (likely from a prior subtraction)
                    return extraout_EDX;
                }
                // Sort by distance squared (offset +0x18 from renderable data)
                return *(int*)(*renderablePtrA + 0x18) - *(int*)(*renderablePtrB + 0x18);
            }
            // Sort by material/sorting key (offset +0x2c)
            return *(int*)(*renderablePtrA + 0x2c) - *(int*)(*renderablePtrB + 0x2c);
        }
        // Sort by material/sorting key (offset +0x28) for opaque-like modes
        return *(int*)(*renderablePtrA + 0x28) - *(int*)(*renderablePtrB + 0x28);
    }
    return 0;
}