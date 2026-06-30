// FUNC_NAME: ThrowableItem::computeAimPosition
// 0075bd60 - Computes an aim target position for a throwable/projectile, returning success status.
// Offsets: +0x80 flags (bit1: use camera pos, bit2: enable offset), +0x88 relative pos, +0x8c-94 offset, +0x98 pointer (height source), +0x9c pointer (vtable base)

#include <cstdint>

// External functions (likely from engine)
float* getCameraPosition();                     // FUN_00471610
float normalizeVector(float* vec);              // FUN_0043a210 (normalizes 3D vector, returns length)

// Global constant for projectile height adjustment
extern float g_projectileHeightOffset;          // _DAT_00d65140

bool __thiscall ThrowableItem::computeAimPosition(float* outPos, int bAdjustForHeight)
{
    outPos[0] = 0.0f;
    outPos[1] = 0.0f;
    outPos[2] = 0.0f;

    bool bSuccess = false;

    // Check if the parent object pointer is valid
    if (*(int*)(this + 0x9c) == 0)
        return false;

    // Get vtable of the base class (offset -0x48 from the parent)
    int* vtableBase = (int*)(*(int*)(this + 0x9c) - 0x48);
    if (vtableBase == nullptr || *(int*)(this + 0x98) == 0)
        return false;

    // Bit 1 of flags: 0 = use camera position, 1 = use relative position
    bool bUseCameraPos = ((*(uint32_t*)(this + 0x80) >> 1) & 1) == 0;

    if (bUseCameraPos)
    {
        // Use camera position as base
        float* camPos = getCameraPosition();
        outPos[0] = camPos[0];
        outPos[1] = camPos[1];
        outPos[2] = camPos[2];
    }
    else
    {
        // Call virtual method (offset 0xa4) to compute world position from relative offset
        typedef void (__thiscall *GetPosFunc)(float*, int);
        GetPosFunc getPos = (GetPosFunc)(vtableBase[0xa4 / 4]);
        getPos(outPos, (int)(this + 0x88));
    }

    // Bit 2 of flags: 1 = apply offset from +0x8c/+0x90/+0x94
    bool bUseOffset = ((*(uint32_t*)(this + 0x80) >> 2) & 1) != 0;
    if (bUseOffset)
    {
        outPos[0] += *(float*)(this + 0x8c);
        outPos[1] += *(float*)(this + 0x90);
        outPos[2] += *(float*)(this + 0x94);
    }

    // Success if using camera and no offset? (both bits cleared)
    bSuccess = (bUseCameraPos && !bUseOffset);

    if (bAdjustForHeight != 0)
    {
        bSuccess = false;

        // Compute vector from current outPos to camera
        float* camPos2 = getCameraPosition();
        float diffX = camPos2[0] - outPos[0];
        float diffY = camPos2[1] - outPos[1];
        float diffZ = camPos2[2] - outPos[2];

        // Normalize the direction
        float dir[3] = { diffX, diffY, diffZ };
        normalizeVector(dir); // dir becomes unit vector

        // Query interface on vtable (GUID 0x55859efa)
        typedef char (__thiscall *QueryInterfaceFunc)(uint32_t, int*);
        QueryInterfaceFunc query = (QueryInterfaceFunc)(vtableBase[0x10 / 4]);
        int tempParam = 0;
        char bResult = query(0x55859efa, &tempParam);

        // The following code uses a register-aliased variable 'unaff_retaddr' (likely a pointer from the interface)
        // In the original asm, this might be a return value or saved ebp. We'll represent it as a local.
        int* unaff_retaddr; // conceptual; originally from ECX/stack
        // Assume unaff_retaddr is set by query or by previous context - this is an approximation.
        // Ghidra shows it used after the query; we treat it as a pointer obtained from the interface.
        // For reconstruction, we note that the decompiler shows a check on unaff_retaddr.
        if (bResult && unaff_retaddr != 0 && *(int*)(unaff_retaddr + 0x1e88) != 0)
        {
            // Get height from interface result chain
            diffZ = *(float*)(*(int*)(unaff_retaddr + 0x1e88) + 0x18);
        }
        else
        {
            diffZ = 0.0f;
        }

        // Also get height from this+0x98 chain
        int* ptr = *(int**)(this + 0x98);
        int* chain = *(int**)((int)ptr + 0x1e88);
        if (chain != 0)
        {
            diffZ += *(float*)(chain + 0x18); // offset 0x18 is height?
        }

        // Add global height offset
        diffZ += g_projectileHeightOffset;

        // Apply the height-adjusted direction to the aim point
        outPos[0] += dir[0] * diffZ;
        outPos[1] += dir[1] * diffZ;
        outPos[2] += dir[2] * diffZ; // Note: dir[2] is from normalized vector, but diffZ is reused
    }

    return bSuccess;
}