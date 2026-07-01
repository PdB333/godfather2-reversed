// FUNC_NAME: initializeMaterialParameters
// Function address: 0x0049d2e0
// Role: Initializes material shader parameters (e.g., "color") by allocating handles and binding them to string IDs.
// The function processes an array of 6 MaterialParameter structures (starting at 0x0110a450) containing
// parameter names (e.g., "color"). For each, it allocates a GPU resource (handle), creates a string ID,
// and binds them together.

#include <cstddef> // for size_t, nullptr

// Forward declarations of called functions with plausible names.
extern void materialBegin(const char* type, int id); // 0x0049c6e0: Begin material definition
extern int createStringId(int base, const char* str, int len); // 0x00ab8560: Create or hash string to ID
extern int allocateShaderHandle(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6); // 0x00606c80: Allocate GPU shader handle
extern int bindShaderParameter(int handle, int slot); // 0x00606ac0: Bind parameter to slot (returns -1 on failure)
extern void releaseShaderHandle(int handle); // 0x006065a0: Release allocated handle
extern void setShaderParameterBinding(int stringId, int handle, int bindFlags); // 0x00610e20: Bind string ID to handle

// Structure for a material parameter (16 bytes)
// Offsets: +0x00 name pointer, +0x04 unknown (unused?), +0x08 stringId, +0x0C handle
struct MaterialParameter {
    const char* name;       // +0x00: pointer to parameter name string
    int unknown;            // +0x04: unknown (maybe padding or hash, not used here)
    int stringId;           // +0x08: string ID created by createStringId
    int handle;             // +0x0C: GPU resource handle (or -1 if invalid)
};

// Global array of 6 material parameters starting at address 0x0110a450
// Note: The actual pointer to the first name ("color") is stored at the base of this array.
extern MaterialParameter materialParameters[6]; // physically at 0x0110a450

void initializeMaterialParameters()
{
    // Start material definition with type "Material" and ID 3
    materialBegin("Material", 3);

    // Create a base string ID for "placeholder" (length 0xB = 11 characters)
    int baseId = createStringId(0, "placeholder", 0xB);

    // Iterate over the 6 material parameter structures
    MaterialParameter* param = &materialParameters[0];
    MaterialParameter* end = &materialParameters[6]; // 0x0110a4b0

    while (param < end)
    {
        // Allocate a GPU shader handle with specific parameters:
        // (3, 0x210080, 1, 1, 1, 0xffffffff)
        int handle = allocateShaderHandle(3, 0x210080, 1, 1, 1, 0xffffffff);

        // Attempt to bind the handle to slot 4 (binding slot index)
        int bindResult = bindShaderParameter(handle, 4);

        // If binding failed (returns -1), release the handle and set to invalid (-1)
        if (bindResult == -1)
        {
            releaseShaderHandle(handle);
            handle = -1; // treat as invalid handle
        }

        // Store the handle in the structure at offset +0x0C
        param->handle = handle;

        // Compute length of the parameter name (null-terminated string)
        const char* name = param->name;
        size_t nameLen = 0;
        while (name[nameLen] != '\0')
            nameLen++;

        // Create a string ID for this name using the baseId as context
        int paramStringId = createStringId(baseId, name, nameLen);

        // Store the string ID at offset +0x08
        param->stringId = paramStringId;

        // Bind the string ID to the handle (third argument = 1, likely a flag)
        setShaderParameterBinding(paramStringId, param->handle, 1);

        // Move to next parameter structure (each is 16 bytes)
        param++;
    }
}