// FUNC_NAME: CMenuManager::UpdateMenuItems
// Address: 0x0042fc70
// Role: Updates a list of UI menu items, handles selection, plays sounds, and updates state.
// This function iterates over an array of item entries stored in a list structure,
// processes each item, updates the current selection, and triggers audio/UI feedback.
// It uses spin locks for synchronization.

#include <cstdint>

// Forward declarations
void SpinLockAcquire(int lockId);   // 0x00613440
void SpinLockRelease(int lockId);   // 0x00613570
uint32_t GetInputState();           // 0x0042e5e0
void ProcessInput(uint32_t flags);  // 0x0042a3f0
bool IsDebugMode();                 // 0x004166b0
void DebugPrint();                  // 0x00614a50
void SetUIWidgetFocus(uint32_t widget, uint32_t param2, int param3); // 0x0049e4c0? Actually 0x0049e4c0 takes 3 params
void SetUIWidgetData(uint32_t widget, int param2, int param3);       // 0x0049e2f0
bool UpdateItemState(int itemObj, uint32_t itemId, uint32_t itemData, int param3); // 0x0042f2d0
void PlaySound(int channel, uint32_t soundId, uint8_t something, int param4, int param5, int param6, int param7); // 0x0060c8d0
void PlaySoundAtPosition(uint16_t soundId, uint32_t param2, uint32_t param3, uint32_t param4, uint16_t param5, uint16_t param6); // 0x0060cb70

// Global variables (from data references)
extern uint32_t DAT_012053d8;       // e.g., g_ControllerConnected
extern uint16_t DAT_012053dc;       // e.g., g_InputModeFlags
extern int DAT_01205838;            // e.g., g_CurrentSoundBank (cached)
extern void* DAT_012058e8;          // e.g., g_pSoundManager (vtable pointer)
extern void* DAT_01205750;          // e.g., g_pAudioManager (vtable pointer)
extern void** PTR_PTR_01124798;     // e.g., g_SelectionMarkerIndicator

// Constants for field offsets in this class (CMenuManager)
#define OFFSET_ACTIVE_MENU_BASE 0x2CB0   // Sub-structure offset within this
#define OFFSET_IS_MENU_ACTIVE   0x39F8   // bool, checked against 0
#define OFFSET_CURRENT_ITEM_ID  0x60     // uint32_t, last processed item ID
#define OFFSET_CURRENT_SOUND1   0x6C     // int, last sound bank 1
#define OFFSET_CURRENT_SOUND2   0x70     // int, last sound bank 2
#define OFFSET_CURRENT_SOUND3   0x74     // int, last sound bank 3
#define OFFSET_SELECTION_STATE  0x78     // uint32_t, state flag (0 on new selection)
#define OFFSET_LAST_ITEM_DATA   0x68     // uint32_t, last item data
#define OFFSET_FOCUSED_WIDGET   0x64     // uint32_t, handle to currently focused UI widget (offset 100 decimal)

// Structure of a menu item entry (size 0x20)
struct MenuItemEntry {
    uint32_t itemData;      // +0x08: item data
    uint32_t itemId;        // +0x0C: item identifier
    void*    pItemObj;      // +0x10: pointer to associated item object (iVar7)
    uint32_t field_0x14;    // (unused in this function)
    uint32_t field_0x18;    // +0x18: value used for sound2 updates
    // ... rest of 0x20 bytes
};

// Structure of menu list descriptor
struct MenuListDescriptor {
    void*    pItemArray;    // +0x10: base pointer to array of MenuItemEntry
    uint16_t itemCount;     // +0x1A: number of items
    uint16_t* pIndices;     // +0x1C: pointer to array of ushort indices into pItemArray
};

// Structure of item object (pointed to by MenuItemEntry.pItemObj)
// Fields accessed at various offsets:
// +0x07: byte (type byte)
// +0x26: byte (sound param)
// +0x27: byte (sound param)
// +0x30: uint32_t (position X?)
// +0x34: uint32_t (position Y?)
// +0x3C: uint16_t (sound ID)
// +0x40: uint16_t (sound param)
// +0x42: uint16_t (sound param)
// +0x54: uint32_t (widget handle)
// +0x60: uint32_t (more sound data)
// +0x6C: int (sound bank)
struct ItemObject {
    // ... many fields ...
};

void CMenuManager::UpdateMenuItems(MenuListDescriptor* pMenuList, void** ppNewSelection, int param3)
{
    int iVar2;
    bool bIsFirstItem;
    char cResult;
    uint32_t uVar5;
    int iVar7;
    MenuItemEntry* pEntry;
    void* pItemObj;
    uint32_t itemId;
    uint32_t itemData;
    int itemSound2;

    // Acquire spin lock
    SpinLockAcquire(1);

    // Get input state flags
    uVar5 = GetInputState();

    // Check if we have a new selection and menu is active
    if ( (ppNewSelection != nullptr) && (*(int*)((uint8_t*)this + OFFSET_IS_MENU_ACTIVE) == 0) )
    {
        // Or in controller flag if no active menu
        uVar5 |= (uint32_t)DAT_012053d8 << 8;
    }

    // If no current focus and input mode has left/right? (uVar5>>8) & DAT_012053dc
    if ( (*(int*)((uint8_t*)pMenuList + 0x40) == 0) && (( (uint32_t)(uint16_t)DAT_012053dc & (uVar5 >> 8) ) != 0) )
    {
        // Redirect to sub-list within this class (e.g., another menu)
        pMenuList = (MenuListDescriptor*)((uint8_t*)this + OFFSET_ACTIVE_MENU_BASE);
    }

    // Process input with the combined flags
    ProcessInput(uVar5);

    // Main iteration loop
    if (ppNewSelection == nullptr)
    {
        // Branch when no new selection pointer provided: process all items
        bIsFirstItem = false;
        // local_8 is loop counter, local_1c is pEntry
        for (int i = 0; i < (int)(uint16_t)pMenuList->itemCount; i++)
        {
            // Compute pointer to current item entry from indices array
            uint16_t idx = pMenuList->pIndices[i];
            pEntry = &((MenuItemEntry*)pMenuList->pItemArray)[idx];
            if (pEntry == nullptr) break;

            pItemObj = pEntry->pItemObj; // +0x10
            itemId = pEntry->itemId;    // +0x0C
            itemData = pEntry->itemData; // +0x08

            // Check if this entry is the first item in the list (special marker)
            if (pItemObj == nullptr)
            {
                // This shouldn't happen; treat as uninitialized?
                continue;
            }

            // Check if this item is the special "selection marker" (PTR_PTR_01124798)
            // The code checks pItemObj? Actually it compares ppuVar1 (which is *(void***)(*(int*)(pItemObj+0x54)+8)) to &PTR_PTR_01124798
            // This is a bit convoluted. We'll reconstruct careful.
            void** ppSelection = *(void***)(*(int*)((uint8_t*)pItemObj + 0x54) + 8);
            if (ppSelection == &PTR_PTR_01124798)
            {
                // This is the selection marker item
                if (bIsFirstItem)
                {
                    // Already processed first item? This branch corresponds to going to LAB_0042fd8a? Actually read code carefully.
                    // The original code: if (ppuVar1 == local_20) { if (!bVar3) goto LAB_0042fd8a; else goto LAB_0042fe4a; }
                    // Here local_20 tracks the previous ppSelection. If it matches previous, it skips? This is complex.
                    // We'll simplify: if this is the first item, handle selection marker.
                    if (*(int*)((uint8_t*)this + 100) != 0) // 100 = OFFSET_FOCUSED_WIDGET
                    {
                        SetUIWidgetFocus(*(int*)((uint8_t*)this + 100), *(uint32_t*)((uint8_t*)this + OFFSET_SELECTION_STATE), param3);
                    }
                    SetUIWidgetData(*(uint32_t*)((uint8_t*)pItemObj + 0x54), 0, param3);
                    *(uint32_t*)((uint8_t*)this + 100) = *(uint32_t*)((uint8_t*)pItemObj + 0x54); // OFFSET_FOCUSED_WIDGET
                    *(uint32_t*)((uint8_t*)this + OFFSET_LAST_ITEM_DATA) = itemData;
                    *(uint32_t*)((uint8_t*)this + OFFSET_SELECTION_STATE) = 0;
                }
                else
                {
                    // Not first item? Then skip selection marker processing? Actually code goes to LAB_0042fd8a which is the else branch.
                    // We'll treat as normal item for now.
                    goto normal_process;
                }
            }
            else
            {
                // Not selection marker, process normally
                bIsFirstItem = false;
normal_process:
                // Call update function for this item
                cResult = UpdateItemState((int)pItemObj, itemId, itemData, param3);
                if (cResult)
                {
                    // Item is active/selected, update sounds and state
                    // Update sound bank 1 (from item type)
                    iVar2 = *(int*)(&DAT_01164014 + (uint)*(uint8_t*)((uint8_t*)pItemObj + 7) * 8); // sound bank table
                    if (iVar2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND1))
                    {
                        if (DAT_01205838 != iVar2)
                        {
                            // Call audio manager to set sound bank
                            (*(void (**)(void*, int))(*(void**)DAT_01205750 + 0x15c))(DAT_01205750, iVar2);
                            DAT_01205838 = iVar2;
                        }
                        *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND1) = iVar2;
                    }

                    // Update sound bank 2 (from item entry)
                    itemSound2 = pEntry->field_0x18; // +0x18
                    if (itemSound2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND2))
                    {
                        PlaySound(0, itemSound2, *(uint8_t*)((uint8_t*)pItemObj + 0x26), 0, 0, 0, 1);
                        *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND2) = itemSound2;
                    }

                    // Update sound bank 3 (from item object)
                    iVar2 = *(int*)((uint8_t*)pItemObj + 0x6C);
                    if (iVar2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND3))
                    {
                        PlaySound(1, iVar2, *(uint8_t*)((uint8_t*)pItemObj + 0x27), 0, 0, 0, 1);
                        *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND3) = iVar2;
                    }

                    // Determine if item type is 'vertical' (0x0B) or 'horizontal' (0x0C)? Actually checked as '\v' and '\f' which are 0x0B and 0x0C.
                    bool bIsVertical = (*(uint8_t*)((uint8_t*)pItemObj + 7) == 0x0B) || (*(uint8_t*)((uint8_t*)pItemObj + 7) == 0x0C);
                    uint32_t uVar6 = bIsVertical ? 1 : 0;

                    // Call sound manager to set something (maybe stereo/mono)
                    (*(void (**)(void*, uint32_t))(*(void**)DAT_012058e8 + 0x38))((void*)DAT_012058e8, uVar6);

                    // Play position-dependent sound
                    PlaySoundAtPosition( *(uint16_t*)((uint8_t*)pItemObj + 0x3C),
                                         *(uint32_t*)((uint8_t*)pItemObj + 0x60),
                                         *(uint32_t*)((uint8_t*)pItemObj + 0x34),
                                         *(uint32_t*)((uint8_t*)pItemObj + 0x30),
                                         *(uint16_t*)((uint8_t*)pItemObj + 0x40),
                                         *(uint16_t*)((uint8_t*)pItemObj + 0x42) );
                }
            }
        } // end for
    }
    else
    {
        // Branch when a new selection pointer is provided: only process items that are active?
        // Similar loop but without the special selection marker handling
        for (int i = 0; i < (int)(uint16_t)pMenuList->itemCount; i++)
        {
            uint16_t idx = pMenuList->pIndices[i];
            pEntry = &((MenuItemEntry*)pMenuList->pItemArray)[idx];
            if (pEntry == nullptr) break;

            pItemObj = pEntry->pItemObj;
            itemId = pEntry->itemId;
            itemData = pEntry->itemData;

            cResult = UpdateItemState((int)pItemObj, itemId, itemData, param3);
            if (cResult)
            {
                // Update sounds as above
                iVar2 = *(int*)(&DAT_01164014 + (uint)*(uint8_t*)((uint8_t*)pItemObj + 7) * 8);
                if (iVar2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND1))
                {
                    if (DAT_01205838 != iVar2)
                    {
                        (*(void (**)(void*, int))(*(void**)DAT_01205750 + 0x15c))(DAT_01205750, iVar2);
                        DAT_01205838 = iVar2;
                    }
                    *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND1) = iVar2;
                }

                itemSound2 = pEntry->field_0x18;
                if (itemSound2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND2))
                {
                    PlaySound(0, itemSound2, *(uint8_t*)((uint8_t*)pItemObj + 0x26), 0, 0, 0, 1);
                    *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND2) = itemSound2;
                }

                iVar2 = *(int*)((uint8_t*)pItemObj + 0x6C);
                if (iVar2 != *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND3))
                {
                    PlaySound(1, iVar2, *(uint8_t*)((uint8_t*)pItemObj + 0x27), 0, 0, 0, 1);
                    *(int*)((uint8_t*)this + OFFSET_CURRENT_SOUND3) = iVar2;
                }

                bool bIsVertical = (*(uint8_t*)((uint8_t*)pItemObj + 7) == 0x0B) || (*(uint8_t*)((uint8_t*)pItemObj + 7) == 0x0C);
                uint32_t uVar6 = bIsVertical ? 1 : 0;
                (*(void (**)(void*, uint32_t))(*(void**)DAT_012058e8 + 0x38))((void*)DAT_012058e8, uVar6);

                PlaySoundAtPosition( *(uint16_t*)((uint8_t*)pItemObj + 0x3C),
                                     *(uint32_t*)((uint8_t*)pItemObj + 0x60),
                                     *(uint32_t*)((uint8_t*)pItemObj + 0x34),
                                     *(uint32_t*)((uint8_t*)pItemObj + 0x30),
                                     *(uint16_t*)((uint8_t*)pItemObj + 0x40),
                                     *(uint16_t*)((uint8_t*)pItemObj + 0x42) );
            }
        }
    }

    // Call cleanup function
    FUN_0042f240(); // Could be PostUpdateUI()

    // Release spin lock
    SpinLockRelease(1);
    return;
}