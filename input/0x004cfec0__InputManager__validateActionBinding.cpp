// FUNC_NAME: InputManager::validateActionBinding
// Address: 0x004cfec0
// Role: Checks whether the actionID is present in the binding entry associated with a key code.
// The InputManager holds a two-level mapping: key code high byte selects an ActionGroup pointer table (at +0x44),
// low byte selects a BindingInfo pointer within that group. The BindingInfo (+0x14: count, +0x16: dataIndex)
// points into a global binding data array (at +0x450) of 3-byte records, where the first two bytes are the actionID.
// This function iterates over those records to confirm the action is bound; if not, it returns silently.

void __thiscall InputManager::validateActionBinding(uint actionID, ushort keyCode) {
    // +0x448: enabled flag (short). If not set, early out.
    if (*(short *)(this + 0x448) == 0) return;
    if (actionID == 0) return;

    // High byte of keyCode selects group of bindings.
    int pGroup = *(int *)(this + 0x44 + ((uint)(keyCode >> 8) * 4));
    if (pGroup == 0) return;

    // Low byte selects a specific binding entry within the group.
    int pEntry = *(int *)(pGroup + ((keyCode & 0xff) * 4));
    if (pEntry == 0) return;

    ushort count = *(ushort *)(pEntry + 0x14);   // number of 3-byte entries
    ushort dataIndex = *(ushort *)(pEntry + 0x16); // index into main binding data array
    if (count == 0) return;

    // Base of this binding's entries in the global binding data.
    byte *pbIter = (byte *)((uint)dataIndex * 3 + *(int *)(this + 0x450));

    for (int i = 0; i < count; i++) {
        // Each entry is 3 bytes: byte0 = low byte of actionID, byte1 = high byte of actionID, byte2 = unknown.
        if (*pbIter == (actionID & 0xff) && *(pbIter + 1) == (byte)(actionID >> 8)) {
            // Action found – no further action (validation passes).
            return;
        }
        pbIter += 3;
    }
    // Action not found – silently return.
    return;
}