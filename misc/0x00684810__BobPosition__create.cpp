// FUNC_NAME: BobPosition::create
// Function at 0x00684810: Allocates a BobPosition object (size 0x70) with type flags and initializes it.
// param_1: likely some context or parent object
// param_2: possibly a memory pool or allocator handle
int __cdecl BobPosition::create(int param_1, int param_2)
{
    // Local structure representing allocation parameters (type ID and flags).
    struct BobPositionCreateParams {
        int type;   // +0x00: type identifier (e.g., 2)
        int flags;  // +0x04: flags (e.g., 0x10)
        int pad;    // +0x08: padding/reserved (0)
    } createParams = {2, 0x10, 0};

    // Allocate BobPosition object (size 0x70 = 112 bytes) via engine allocator.
    // FUN_0043b980 is likely a memory allocator or object factory.
    int allocatedObj = FUN_0043b980(0x70, &createParams, param_2);
    if (allocatedObj != 0)
    {
        // If allocation succeeded, run constructor/initialization on the object.
        // FUN_00906930 takes param_1 (probably the parent/owner) and returns the initialized object.
        return FUN_00906930(param_1);
    }
    return 0; // allocation failed
}