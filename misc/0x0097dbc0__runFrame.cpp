// FUNC_NAME: runFrame
// Function address: 0x0097dbc0
// Identified role: Main frame update dispatcher that orchestrates four subsystems in sequence.

// Forward declarations for the four sub-update phases
void preUpdate();   // Phase 0: Pre-update (input, state transitions)
void update();      // Phase 1: Main simulation (physics, AI, animations)
void postUpdate();  // Phase 2: Post-update (collision resolution, cleanup)
void render();      // Phase 3: Rendering (draw calls, UI)

void runFrame() {
    preUpdate();   // Pre-frame processing
    update();      // Core simulation
    postUpdate();  // Post-simulation adjustments
    render();      // Output frame
}