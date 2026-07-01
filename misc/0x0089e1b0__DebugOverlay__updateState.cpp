// FUNC_NAME: DebugOverlay::updateState
// Function address: 0x0089e1b0
// Role: Applies debug overlay state (color data and other rendering parameters) to an internal structure, then triggers render preparation.
// Reads from global debug color/data constants and copies them into the overlay's draw data block.
// Checks if the overlay has a valid resource (pointer at +0x10) before proceeding.

// Forward declarations for called functions (likely rendering/state management)
void __cdecl prepareDebugRender(uint32_t param);                // FUN_004ec1c0
void __cdecl submitDrawCall(void *drawData);                    // FUN_004df830
void __cdecl finalizeDebugOverlay(void);                        // FUN_0089bb60

// Global constants (from overlapping symbols at 0x00d786c0..0x00d786cc)
extern const uint32_t g_debugColor0;        // _DAT_00d786c0
extern const uint32_t g_debugColor1;        // _UNK_00d786c4
extern const uint32_t g_debugColor2;        // _UNK_00d786c8
extern const uint32_t g_debugColor3;        // _UNK_00d786cc

class DebugOverlay {
public:
    void updateState(uint32_t param);

private:
    // Offset 0x00: (assumed vtable or other base)
    // Offset 0x04: ... (unknown)
    // Offset 0x08: ...
    // Offset 0x0C: ...
    void* m_resource;   // +0x10 – Must be non‑null to proceed (e.g., texture, font, or shader)
    // Offset 0x14: unknown
    // Offset 0x18: unknown
    // Offset 0x1C: unknown
    DebugDrawData* m_drawData;  // +0x20 – Pointer to internal draw state (contains color fields)
    // ... other members
};

// Structure for draw data (residing at the pointer at +0x20)
struct DebugDrawData {
    /* +0x00 */ uint32_t field_0;      // unknown
    /* +0x04 */ uint32_t field_4;
    /* +0x08 */ uint32_t field_8;
    /* +0x0C */ uint32_t field_C;
    /* +0x10 */ uint32_t colorRgba0;   // written from g_debugColor0
    /* +0x14 */ uint32_t colorRgba1;   // written from g_debugColor1
    /* +0x18 */ uint32_t colorRgba2;   // written from g_debugColor2
    /* +0x1C */ uint32_t colorRgba3;   // written from g_debugColor3
};

void __thiscall DebugOverlay::updateState(uint32_t param)
{
    // Check if the overlay resource is valid
    if (this->m_resource != 0) {
        DebugDrawData* drawData = this->m_drawData;

        // Copy global debug color constants into the draw data block
        drawData->colorRgba0 = g_debugColor0;
        drawData->colorRgba1 = g_debugColor1;
        drawData->colorRgba2 = g_debugColor2;
        drawData->colorRgba3 = g_debugColor3;

        // Prepare rendering using the passed parameter (e.g., an index or state)
        prepareDebugRender(param);

        // Submit the draw data for rendering
        submitDrawCall(drawData);

        // Finalize the debug overlay (e.g., flush commands)
        finalizeDebugOverlay();
    }
}