// FUNC_NAME: doSubroutine
// Function at 0x004ad0f0: A simple thunk that delegates to the actual implementation at 0x004ae6f0.
// This wrapper is called from numerous locations across the codebase, suggesting it may be a
// frequently used utility or a virtual function entry point.

// Forward declaration of the actual implementation at 0x004ae6f0
void __cdecl actualImplementation();

void __cdecl doSubroutine()
{
    // Delegate all work to the actual implementation.
    actualImplementation();
}