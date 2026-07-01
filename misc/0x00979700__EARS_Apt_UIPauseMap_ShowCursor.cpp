// Xbox PDB: EARS_Apt_UIPauseMap_ShowCursor
// FUNC_NAME: DebugCursorManager::updateCursor
void __thiscall DebugCursorManager::updateCursor(int this, int pSourceObject)
{
    int *pCursorHandle; // pointer to member storing cursor handle
    int cursorHandle;   // local for new cursor handle
    char nameBuffer[16]; // used for something? Actually local_a0 is 16 bytes, but it's passed to FUN_004df420
    // The struct at local_90 is 16 floats? Actually 16 * 4 = 64 bytes, but we only have 16 undefined4, so naming as a rectangle struct:
    struct ViewportRect { // +0x00..0x3F (64 bytes)
        float x, y, w, h;
        // ... likely more fields
    } viewport;
    char formattedName[64]; // output buffer for cursor name

    pCursorHandle = (int *)(this + 0xf8); // pointer to cursor handle (0 if none, else handle)

    // If cursor handle is not yet created, copy the viewport from this object:
    if (*pCursorHandle == 0) {
        // Copy 64 bytes from this+0x170 into local viewport struct
        viewport = *(ViewportRect *)(this + 0x170);
    } else {
        // Otherwise, reset the viewport via some function (maybe clear or copy from cached?)
        FUN_004df780(&viewport);
    }

    // Initialize/debug state
    FUN_004df600();

    // Only create cursor if global debug cursor flag is set
    if (DAT_0110acca != '\0') {
        // If pSourceObject is provided, create a named cursor
        if (pSourceObject != 0) {
            // Get the name string from pSourceObject (offset +0x40)
            char **ppName = (char **)FUN_008c7550(*(int *)(pSourceObject + 0x40));
            char *pName = *ppName;
            if (pName == (char *)0x0) {
                pName = &DAT_0120546e; // fallback string (e.g., "default")
            }
            // Format: "dv_cursor_<name>"
            FUN_005c4630(formattedName, 0x40, "dv_cursor_%s", pName);
            // Load/retrieve the cursor resource by name
            FUN_004eacb0(formattedName);
            // Create a new cursor object (returns handle)
            cursorHandle = FUN_004df420(&cursorHandle, nameBuffer, &viewport, 0x2ff, 4, 0, 0xffffffff, 0);
            // Replace existing cursor handle if any
            if (*pCursorHandle != 0) {
                *(int *)(*pCursorHandle + 8) = 0; // clear back pointer
                *pCursorHandle = 0;
            }
            *pCursorHandle = cursorHandle;
            if (cursorHandle != 0) {
                *(int **)(cursorHandle + 8) = pCursorHandle; // set back pointer to this
            }
        }

        // Ensure there's at least a default cursor named "dv_cursor"
        if (*pCursorHandle == 0) {
            FUN_004eacb0("dv_cursor");
            cursorHandle = FUN_004df420(&cursorHandle, nameBuffer, &viewport, 0x2ff, 4, 0, 0xffffffff, 0);
            if (*pCursorHandle != 0) {
                *(int *)(*pCursorHandle + 8) = 0;
                *pCursorHandle = 0;
            }
            *pCursorHandle = cursorHandle;
            if (cursorHandle != 0) {
                *(int **)(cursorHandle + 8) = pCursorHandle;
            }
        }
    }
    return;
}