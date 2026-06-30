// FUNC_NAME: processDebugCommandString (static helper)
// Address: 0x0068fb10
// Role: Parses a command string (from a pointer pointer), checks if it matches one of two hardcoded hashes (likely debug commands), and if so, sets up a callback handler via FUN_0068f7a0.

struct DebugCommandContext {
    int32_t result;         // +0x00 (local_38)
    uint32_t unused1;       // +0x04 (local_34)
    uint32_t unused2;       // +0x08 (local_30)
    void (*callback)(int);  // +0x0C (local_2c) - function pointer
};

// Check if debug mode is enabled or global flag indicates special mode
bool isDebugMode(int32_t mode); // FUN_0068e8f0

// Token iterator: returns non-zero if more tokens remain
char hasMoreTokens(); // FUN_0068e210

// Process token: computes hash or processes part of string
void processToken(const char* str, int32_t offset, int32_t length); // FUN_004d43f0

// Hash comparison: returns a constant hash (e.g., 0x12496f4c or 0x3fdf44d2) for exact string match
uint32_t compareStringSegment(const char* start, const char* end); // FUN_004db060

// Register a command handler: sets the context struct with result and callback pointer
void registerCommandHandler(uint32_t commandId, int32_t zero, DebugCommandContext* ctx); // FUN_0068f7a0

// Execute the registered handler if context is valid
void executeCommandHandler(DebugCommandContext* ctx); // FUN_004d3e20

void processDebugCommandString(uint32_t* param_1) // param_1 points to a pointer to the command string (or NULL for default)
{
    // Check if global flag at +0x568 equals 0x12 (some special state) or debug mode is active
    if (*(char*)(DAT_012233b4 + 0x568) == '\x12' || isDebugMode(4) == '\0') // Note: isDebugMode returns 0 on failure?
    {
        return; // Not active, exit
    }

    const char* commandStr = (const char*)*param_1;
    if (commandStr == nullptr)
    {
        commandStr = &DAT_0120546e; // Default command string
    }

    // Compute length of command string (twice, stored separately)
    int32_t length1 = 0;
    const char* scan = commandStr;
    while (*scan++ != '\0');
    length1 = (int)(scan - commandStr - 1);

    int32_t length2 = 0;
    scan = commandStr;
    while (*scan++ != '\0');
    length2 = (int)(scan - commandStr - 1);

    // Initialize context structure
    DebugCommandContext ctx;
    ctx.result = 0;
    ctx.unused1 = 0;
    ctx.unused2 = 0;
    ctx.callback = nullptr;

    // Prepare for parsing loop (though the loop seems to process the same entire string each time)
    const char* strStart = commandStr;
    int32_t offset = 0;
    int32_t currentLength = length2; // actually length2 again

    while (hasMoreTokens() != '\0')
    {
        processToken(strStart, offset, currentLength); // Probably no effect if length doesn't change
        uint32_t hash = compareStringSegment(strStart + offset, strStart + length1 + offset); // Compare full string
        if (hash == 0x12496f4c)
        {
            registerCommandHandler(0x3ddc7637, 0, &ctx);
        }
        else if (hash == 0x3fdf44d2)
        {
            registerCommandHandler(0x2938c6cc, 0, &ctx);
        }
        // No else: other hashes ignored
    }

    executeCommandHandler(&ctx);
    if (ctx.result != 0 && ctx.callback != nullptr)
    {
        ctx.callback(ctx.result);
    }
}