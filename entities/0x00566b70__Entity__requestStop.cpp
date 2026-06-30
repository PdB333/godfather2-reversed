// FUNC_NAME: Entity::requestStop
// Address: 0x00566b70
// Role: Handles stop request for an entity, updates state and calls debug logging.

// Assumes global pointer to debug handler with vtable at +0x0c (print) and +0x60 (log)
extern DebugHandler* gDebugHandler;

// This function processes a stop request, updates internal state, and returns success.
// Structure offsets (relative to this):
// +0x0c: Pointer to debug output object (used if state == 2)
// +0x10: State integer (preserved if 9, else reset to 0)
// +0x14: State byte (updated)
// +0x2c: Flags (bits 5 and 6 cleared)
int __fastcall Entity::requestStop(Entity* this)
{
    // If global debug handler exists, call its print method (vtable +0x0c)
    if (gDebugHandler != nullptr) {
        (*(void(__thiscall**)(DebugHandler*))(*(uint*)gDebugHandler + 0x0c))(gDebugHandler);
    }

    // Check if there is a debug output object AND current state byte is 2 (maybe "playing")
    if (*(int**)(this + 0x0c) != nullptr && *(char*)(this + 0x14) == 0x02) {
        // Call debug log method (vtable +0x60) with severity 5 and message
        (*(void(__thiscall**)(void*, int, const char*))(**(int**)(this + 0x0c) + 0x60))(
            *(void**)(this + 0x0c), 5, "We Want To Stop Plasma");
    }

    // Extract lower bits from flags, clear bits for new state
    uint flags = *(uint*)(this + 0x2c);
    uint tempFlags = (flags >> 6) & 0xffffff01;
    // Combine sign extension and add 4 to compute new state byte
    int newState = (int)((tempFlags >> 8) | ( (char)(tempFlags & 0xff) != 0 ? 0xff000000 : 0 )) + 4;
    *(char*)(this + 0x14) = (char)newState;

    // Clear bits 5 and 6 in flags (reset state-related bits)
    *(uint*)(this + 0x2c) = flags & 0xffffff9f;

    // Keep state integer unless it is 9 (special persistent state)
    if (*(int*)(this + 0x10) != 9) {
        *(int*)(this + 0x10) = 0;
    }

    // Return success (low byte = 1, high bytes = newState>>8)
    return (uint)(newState >> 8) | 1;
}