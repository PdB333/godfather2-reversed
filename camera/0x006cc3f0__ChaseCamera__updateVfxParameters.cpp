// FUNC_NAME: ChaseCamera::updateVfxParameters

// Function at 0x006cc3f0 - Updates camera VFX parameters based on flags field.
// Reads bitfield at this+0xdc to select VFX type (row) and sub-type (col).
// Sets VFX parameter fields at this+0xd0, this+0xd4, this+0xd8.
// Manages global VFX instance using static ID at DAT_0112a808.

void __fastcall ChaseCamera::updateVfxParameters(ChaseCamera* this)
{
    int row;
    int col;
    int index;
    int newVfxId;
    int oldVfxId;

    // Extract row from bits 0-2
    if ((*(byte*)((int)this + 0xdc) & 1) == 0) { // bit0 off
        if ((*(uint*)((int)this + 0xdc) >> 1 & 1) == 0) { // bit1 off
            row = (*(uint*)((int)this + 0xdc) >> 2 & 1) * 2; // bit2 => 0 or 2
        } else {
            row = 1;
        }
    } else {
        row = 0;
    }

    // Extract column from bits 5-9
    uint flags = *(uint*)((int)this + 0xdc);
    if ((flags >> 5 & 1) == 0) {
        if ((flags >> 6 & 1) == 0) {
            if ((flags >> 7 & 1) == 0) {
                if ((flags >> 8 & 1) == 0) {
                    col = (flags >> 9 & 1) * 4;
                } else {
                    col = 3;
                }
            } else {
                col = 2;
            }
        } else {
            col = 1;
        }
    } else {
        col = 0;
    }

    // Combined index = col + row * 5 (5 columns per row)
    index = col + row * 5;

    // Set VFX parameters from tables (gVfxParamTable and gVfxIdTable)
    this->m_vfxParam0 = gVfxParamTable[index * 3] * g_vfxGlobalScale; // +0xd8 float
    this->m_vfxParam1 = gVfxParamTable[index * 3 + 1];               // +0xd0
    this->m_vfxParam2 = gVfxParamTable[index * 3 + 2];               // +0xd4

    // Load VFX ID for this configuration
    newVfxId = gVfxIdTable[index];
    oldVfxId = g_currentVfxId; // DAT_0112a808

    if (newVfxId != oldVfxId) {
        // Stop old VFX if it was active
        if (oldVfxId != 0) {
            char buf[16];
            _sprintf(buf, "F2FCamVFX%1d", oldVfxId);
            // Assume FUN_00408a00 is StopVfx, FUN_00408240 is Create/GetVfx
            int vfxHandle = 0;
            FUN_00408240(&vfxHandle, buf); // Create or lookup VFX
            int tempHandle = vfxHandle;
            FUN_00408a00(&tempHandle, 0);  // Stop/disable
            FUN_00408310(&vfxHandle);       // Release handle
            g_currentVfxId = 0;
        }

        // Start new VFX if ID is non-zero
        if (newVfxId != 0) {
            char nameBuf[16];
            _sprintf(nameBuf, "F2FCamVFX%1d", newVfxId);
            int vfxHandle = 0;
            FUN_00408240(&vfxHandle, nameBuf); // Get VFX by name
            int tempHandle = vfxHandle;
            FUN_00408a00(&tempHandle, 0);      // Start/enable
            FUN_00408310(&vfxHandle);           // Release handle
        }
    }

    g_currentVfxId = newVfxId;
}

// Static/global variables (inferred)
// @@ DAT_00e50fe0 - gVfxParamTable (float array, rows 15, stride 3)
// @@ DAT_00e445a4 - g_vfxGlobalScale (float scalar)
// @@ DAT_0112a7c8 - gVfxIdTable (int array, 15 entries)
// @@ DAT_0112a808 - g_currentVfxId (int static)
// @+0xdc - m_vfxFlags (uint bitfield)
// @+0xd0 - m_vfxParam1 (uint/float)
// @+0xd4 - m_vfxParam2 (uint/float)
// @+0xd8 - m_vfxParam0 (float)