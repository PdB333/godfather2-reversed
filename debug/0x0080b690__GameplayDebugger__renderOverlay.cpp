// FUNC_NAME: GameplayDebugger::renderOverlay
void GameplayDebugger::renderOverlay() {
    char debugString[68]; // buffer for formatted debug text (e.g., FPS, memory, state)
    if (isDebugModeEnabled()) {
        beginDebugOverlay();          // push overlay state / clear screen area
        drawDebugInfo(this);          // render class-specific debug data
        formatDebugString(debugString); // build text string from internal counters
        endDebugOverlay();            // pop overlay state / commit to screen
    }
}