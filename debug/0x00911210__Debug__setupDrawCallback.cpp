// FUNC_NAME: Debug::setupDrawCallback
// Function address: 0x00911210
// Role: Registers a debug draw callback (either from object or global) and enables debug drawing.

void __fastcall Debug::setupDrawCallback(int param_1) // param_1: pointer to a Debug object (or null)
{
    // Enable debug drawing system
    Debug::enableDebugDrawing(1);

    if (param_1 != 0) {
        // Use the callback stored at offset +0x10 in the object
        Debug::setDrawFunction(param_1 + 0x10, &Debug::debugDrawHandler, 1);
    } else {
        // Use null context (global draw handler)
        Debug::setDrawFunction(0, &Debug::debugDrawHandler, 1);
    }
}