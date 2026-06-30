// FUNC_NAME: PresentationManager::setupRendering
void __thiscall PresentationManager::setupRendering(int param_1) {
    // +0x18: pointer to render context (contains vtable at +0xD0)
    int* renderContext = *(int**)(this + 0x18);
    
    // Initialization step (e.g., reset states)
    FUN_00560ef0();
    
    // Begin render command group
    FUN_009f2000();
    // Virtual call at vtable offset 0x40 – likely SetRenderTarget(g_renderTarget)
    (*(void (__stdcall **)(void*))(*(int*)renderContext + 0x40))(&DAT_01139820);
    
    // End render command group or transition to next pass
    FUN_009f2000();
    // Virtual call at vtable offset 0x44 – likely ClearRenderTarget() or BeginScene()
    (*(void (__stdcall **)(void*))(*(int*)renderContext + 0x44))(&DAT_01139820);
    
    // Apply additional rendering options from param_1
    FUN_0053f390(param_1);
    
    // Extract a value from the parameter (e.g., a rectangle or layer index)
    int someValue = *(int*)(param_1 + 8); // +0x08: e.g., width/height or texture ID
    
    // Re-fetch render context (may have been modified)
    renderContext = *(int**)(this + 0x18);
    
    // Begin another render pass
    FUN_009f2000();
    // Virtual call at vtable offset 0x58 – likely DrawQuad(someValue, &localRect)
    (*(void (__stdcall **)(int, void*))(*(int*)renderContext + 0x58))(someValue, &stack0xffffffd8);
    
    // If a specific flag is set, perform cleanup or finalization
    if (*(int*)(this + 0x10c) == 1) { // +0x10c: e.g., bFinalPass
        FUN_00560620();
    }
}