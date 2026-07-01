// FUNC_NAME: Debug::render
void __thiscall Debug::render(int *this)
{
    // Check if debug draw mode is in range 1..3 (e.g., OSD, wireframe, etc.)
    if (this[0x3a] - 1U < 3) {
        drawOverlay(0xff000000, gDebugTextureHandle, 0, 1);
        beginDebugDraw();
        renderDebugInfo();
        // Call virtual render method at vtable offset 0x2c (per-class debug drawing)
        ((void (__thiscall *)(int*))(*(int*)(*(int*)this + 0x2c)))(this);
    }
    // Global debug manager pointer; check if extra overlay is enabled (+0x40 flag)
    if (*(int *)(gDebugManager + 0x40) != 0) {
        drawExtraOverlay();
    }
}