// FUNC_NAME: UIListManager::updateSelection

struct UIListItem {
    char field_0x00[4];
    char m_activationState; // +0x04: 0=inactive, 1=active, etc.
    char field_0x05[3];
    uint32_t m_flags; // +0x08: flags: bit0=selected, bit1=highlighted, bit2=disabled, etc.
    char field_0x0C[0x1C];
    char m_interactionState; // +0x28: 0=idle, 1=pressed, etc.
    char m_selectability; // +0x29: rank?
    int16_t m_relatedIndex; // +0x2A: index of another item
    char field_0x2C[0x24];
};

struct UIListContainer {
    char m_enabled; // +0x2C: 0=disabled, non-zero=enabled
    char field_0x2D[0x23];
    UIListItem* m_items; // +0x50: array of items (each 0xB0)
};

// Global debug markers (likely part of a memory validation system)
// These are set with low/high bounds to indicate memory regions being used.
static int g_debugMarkerLow;
static int g_debugMarkerHigh;
static int* g_debugWriteAddress; // multiple globals at fixed addresses

void UIListManager::updateSelection(int param_1, UIListContainer* list, int param_3, int startIndex, int param_5, uint32_t flags, bool param_7)
{
    bool hasSelection = false;
    bool isInteractive = false;

    // Check if the list is enabled and if interaction is forced
    if (list->m_enabled != 0 && (flags & 4) == 0) {
        isInteractive = true;
        // Debug markers for memory region access
        if (g_debugMarkerLow < 0x38) g_debugMarkerLow = 0x38;
        if (g_debugMarkerHigh > 0x38) g_debugMarkerHigh = 0x38;
        *g_debugWriteAddress = 8;
        if (g_debugMarkerLow < 0x39) g_debugMarkerLow = 0x39;
        if (g_debugMarkerHigh > 0x39) g_debugMarkerHigh = 0x39;
        *(int*)(g_debugWriteAddress + 1) = list->m_enabled;
        if (g_debugMarkerLow < 0x3a) g_debugMarkerLow = 0x3a;
        if (g_debugMarkerHigh > 0x3a) g_debugMarkerHigh = 0x3a;
        *(int*)(g_debugWriteAddress + 2) = -1;
        if (g_debugMarkerLow < 0x34) g_debugMarkerLow = 0x34;
        if (g_debugMarkerHigh > 0x34) g_debugMarkerHigh = 0x34;
        *(int*)(g_debugWriteAddress - 2) = 1;
        FUN_0041e4d0(3, 1, 1); // Sound effect: cursor move
    }

    // Some global flag that affects item selection logic
    uint8_t selectionMask = *(uint8_t*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x24) + 0xe0);
    hasSelection = false;

    // this->m_itemCount is passed in EAX? Assuming it's derived from something.
    int itemCount = someCount; // from EAX (maybe function return or class member)
    if (startIndex < itemCount) {
        int currentItemOffset = startIndex * 0xB0;
        int remaining = itemCount - startIndex;
        do {
            UIListItem* item = (UIListItem*)((char*)list->m_items + currentItemOffset);
            if ((flags & 0x38) == 0) {
                // Simple selection logic
                if (param_7 != 0 ||
                    ((item->m_flags & 2) != 0 &&
                     (item->m_relatedIndex < 0 ||
                      ((item->m_selectability < 6 && item->m_relatedIndex >= 0) &&
                       ((*(uint8_t*)(item->m_relatedIndex + *(int*)(item->m_selectability * 0x6a0 + 0x1238 + param_1)) & selectionMask) != 0))))) 
                {
                    if ((flags & 0x31) != 0) {
                        if (((item->m_flags & 0xc) == 0) && (item->m_interactionState < 1)) {
                            if (hasSelection) {
                                FUN_00417fe0(0); // Deselect highlight
                                FUN_00412f10(1); // Update visual
                                hasSelection = false;
                                if (isInteractive) {
                                    FUN_0041e490(1); // Play selection sound
                                }
                            }
                        } else if (!hasSelection) {
                            if (g_debugMarkerLow < 0xe) g_debugMarkerLow = 0xe;
                            if (g_debugMarkerHigh > 0xe) g_debugMarkerHigh = 0xe;
                            *g_debugWriteAddress2 = 0; // Some global
                            if (g_debugMarkerLow < 0x1b) g_debugMarkerLow = 0x1b;
                            if (g_debugMarkerHigh > 0x1a) g_debugMarkerHigh = 0x1b;
                            *(int*)(g_debugWriteAddress2 + 0x34) = 1; // Another global
                            hasSelection = true;
                            if (isInteractive) {
                                FUN_0041e490(0); // Play highlight sound
                            }
                        }
                    }
                    FUN_0042f140(param_3, param_5); // Execute item action
                }
            } else {
                uint32_t itemFlags = item->m_flags;
                if ((itemFlags & 0x20) == 0) {
                    if ((itemFlags & 0xc) != 0) {
                        // Case 3: disabled or pressed
                        goto switchCase3;
                    }
                    if (item->m_interactionState > 0) {
                        // Case 2: pressed state
                        goto switchCase2;
                    }
                    if ((item->m_activationState == 1) || ((itemFlags & 0x10) != 0)) {
                        // Case 1: active or special flag
                        goto switchCase1;
                    }
                    if ((itemFlags & 0x18000) == 0) {
                        // Case 0: default
                        goto switchCase0;
                    }
                }
            }
switchCaseEnd:
            currentItemOffset += 0xB0;
            remaining--;
        } while (remaining != 0);
    }

    FUN_0042f240(); // Update cursor animation

    if (hasSelection) {
        // Reset selection state
        if (g_debugMarkerLow < 0x1b) g_debugMarkerLow = 0x1b;
        if (g_debugMarkerHigh > 0x1a) g_debugMarkerHigh = 0x1b;
        *(int*)(g_debugWriteAddress2 + 0x34) = 0;
        if (g_debugMarkerLow < 0xe) g_debugMarkerLow = 0xe;
        if (g_debugMarkerHigh > 0xe) g_debugMarkerHigh = 0xe;
        *g_debugWriteAddress2 = 1;
    }

    if (isInteractive) {
        // Restore debug markers and play sound
        if (g_debugMarkerLow < 0x38) g_debugMarkerLow = 0x38;
        if (g_debugMarkerHigh > 0x38) g_debugMarkerHigh = 0x38;
        *g_debugWriteAddress = 8;
        if (g_debugMarkerLow < 0x39) g_debugMarkerLow = 0x39;
        if (g_debugMarkerHigh > 0x39) g_debugMarkerHigh = 0x39;
        *(int*)(g_debugWriteAddress + 1) = 0;
        if (g_debugMarkerLow < 0x3a) g_debugMarkerLow = 0x3a;
        if (g_debugMarkerHigh > 0x3a) g_debugMarkerHigh = 0x3a;
        *(int*)(g_debugWriteAddress + 2) = -1;
        if (g_debugMarkerLow < 0x34) g_debugMarkerLow = 0x34;
        if (g_debugMarkerHigh > 0x34) g_debugMarkerHigh = 0x34;
        *(int*)(g_debugWriteAddress - 2) = 0;
        FUN_0041e4d0(1, 1, 1); // Sound effect: cursor leave
    }
    return;

    // Jump table targets (addresses 0x0042f84c)
    switchCase0:
        // Default action
        break;
    switchCase1:
        // Active item action
        break;
    switchCase2:
        // Pressed item action
        break;
    switchCase3:
        // Disabled item action
        break;
}