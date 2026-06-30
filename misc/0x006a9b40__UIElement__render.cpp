// FUNC_NAME: UIElement::render
void __fastcall UIElement::render(int this)
{
    char cVar1;
    
    // Check if game is active/rendering allowed
    cVar1 = isGameRunning();
    if ((cVar1 != '\0') && (*(char *)(this + 0xa5) != '\0')) {
        // Choose render path based on global flag (e.g., debug/hardware)
        if (g_bUseAdvancedRender != '\0') {
            renderAdvanced((RenderData *)(this + 0x140), *(double *)(this + 0x120), *(float *)(this + 0x128), g_fGlobalRenderParam);
            return;
        }
        renderStandard((RenderData *)(this + 0x140), *(double *)(this + 0x120), *(float *)(this + 0x128), g_fGlobalRenderParam);
    }
    return;
}