// FUNC_NAME: getResourceForId
// Address: 0x0069d970
// Role: Returns a pointer to a static table entry based on an integer ID.
//       Special case: ID 9 is remapped via another function before lookup.

#include <cstddef>

// Static table of 4 pointers (probably to strings or other resources).
// Data addresses from the original binary (e.g., 0x00d5a340, etc.)
static void* const resourceTable[4] = {
    reinterpret_cast<void*>(0x00d5a340),
    reinterpret_cast<void*>(0x00d5a32c),
    reinterpret_cast<void*>(0x00d5a30c),
    reinterpret_cast<void*>(0x00d5a2f0)
};

// Additional pointers set in the stack frame but never accessed in this path.
// They may belong to a larger table (indices 4-8) or other code paths.
// static void* const local_14 = reinterpret_cast<void*>(0x00d5a2d0);
// static void* const local_10 = reinterpret_cast<void*>(0x00d5a2a4);
// static void* const local_c  = reinterpret_cast<void*>(0x00d5a280);
// static void* const local_8  = reinterpret_cast<void*>(0x00d5a260);
// static void* const local_4  = reinterpret_cast<void*>(0x00d5a23c);

// Function that remaps the ID when it equals 9.
// Placeholder – actual name and purpose unknown.
int FUN_0069d8a0();

void** __cdecl getResourceForId(int id) {
    if (id == 9) {
        id = FUN_0069d8a0();
    }
    // Return pointer to the selected entry.
    // Note: id must be in range 0-3 after remapping.
    return &resourceTable[id];
}