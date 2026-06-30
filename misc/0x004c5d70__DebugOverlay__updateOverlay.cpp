// FUNC_NAME: DebugOverlay::updateOverlay
void __fastcall DebugOverlay::updateOverlay(int thisPtr, int overlayPtr)
{
    bool debugEnabled = checkDebugEnabled();                 // FUN_004166b0
    if (debugEnabled && (g_currentOverlay == overlayPtr))   // DAT_012058e8 = global overlay pointer
    {
        drawOverlay(*(int*)(overlayPtr + 0x10),              // +0x10: text/data pointer
                    *(int*)(overlayPtr + 0xb8),              // +0xb8: color/format
                    (int*)(overlayPtr + 0xf0));              // +0xf0: position/dimensions
    }
}