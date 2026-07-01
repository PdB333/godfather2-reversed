// FUNC_NAME: DialogTreeManager::updateActiveDialogNode
// Address: 0x008e4020
// Updates the currently active dialog node, handling animation, sound, and UI state.

typedef unsigned int uint;
typedef int int32;
typedef unsigned char byte;

const int32 kMagicDialogId1 = 0xBADBDBBA; // -0x45245246
const int32 kMagicDialogId2 = 0xBEEFBEEF; // -0x41104111
const int32 kMagicDialogId3 = 0xEAC15A55; // -0x153ea5ab
const int32 kMagicDialogId4 = 0x91100911; // -0x6eeff6ef

// Component hash constants (likely)
const uint32 kComponentAnimHash = 0x254cce9;
const uint32 kComponentTalkHash = 0x43c8ec5b;

// External functions (declared elsewhere)
extern int* __fastcall getComponentFromId(void* obj, int index);
extern int __fastcall getComponent(void* obj, uint hash);
extern void __fastcall updateAnimComponent(int hAnim);
extern void __fastcall applyAnimEffect(int hAnim);
extern int* __fastcall getAnimController(int* component, uint hash);
extern int* __fastcall getTalkController(int* component, uint hash);
extern void __fastcall playSoundAttachedToObject(uint soundId, uint target);
extern void __fastcall playSoundDirect(uint soundId, uint target);
extern void __fastcall updateObjectState(void* obj);
extern int __fastcall getMainMenuActive();
extern int __fastcall isCutscenePlaying();
extern void __fastcall setAnimState(int state, int val);
extern void __fastcall setComponentState(int* comp, int val);
extern void __fastcall resetComponentState(uint state);
extern void __fastcall finishAnimUpdate(int hAnim, int extra);
extern void* __fastcall registerCallbackForSound(uint soundId);
extern int __fastcall checkUIFlipState(uint transform);
extern bool __fastcall isTransformFlipped(uint transform);
extern int __fastcall spawnEffect(uint effectType, int hAnim, int a, int b, int c, int d, int e, int priority, int* outHandle, int zero1, int zero2, int zero3);
extern void __fastcall playSoundWithEffect(int effectHandle, int type, uint soundId, uint global1);
extern void __fastcall destroyObject(int handle);

void __fastcall DialogTreeManager::updateActiveDialogNode(void* thisObj)
{
    // +0x1dc: current dialog slot index
    int slotIndex = *(int*)(thisObj + 0x1dc);
    // Array of size 0x20 per slot, base at +0x1f8
    int* slotData = (int*)(thisObj + 0x1f8 + slotIndex * 0x20);
    int animComponentSlot = slotData[0]; // +0x00 (since 0x1f8 + slot*0x20, first int)
    int someOtherSlot = slotData[1]; // +0x04 (0x1fc offset)

    // Check dialog ID at +0x74..0x80 (four ints)
    int id1 = *(int*)(thisObj + 0x74);
    int id2 = *(int*)(thisObj + 0x78);
    int id3 = *(int*)(thisObj + 0x7c);
    int id4 = *(int*)(thisObj + 0x80);
    
    // Early return if dialog is a known magic (already handled) or all zero
    if ((id1 == kMagicDialogId1 && id2 == kMagicDialogId2 && id3 == kMagicDialogId3 && id4 == kMagicDialogId4) ||
        (id1 == 0 && id2 == 0 && id3 == 0 && id4 == 0))
    {
        return;
    }

    // Get the dialog component from the ID block
    int* pDialogComponent = getComponentFromId((int*)(thisObj + 0x74), 0);
    if (pDialogComponent == 0) return;

    // Query current animation state via vtable method at offset 0x10, hash 0xf4636937
    int hAnim = 0;
    bool isValid = (*(bool (__fastcall**)(int*, uint, int*))(*pDialogComponent + 0x10))(pDialogComponent, 0xf4636937, &hAnim);
    if (!isValid || hAnim == 0) return;

    // Process animation (play effect, update)
    updateAnimComponent(hAnim);
    applyAnimEffect(hAnim);

    // Compute component slot for the animation index
    // +0x88: base of animation components, each size 0x5c
    int* animComponentBase = (int*)(thisObj + 0x88 + animComponentSlot * 0x5c);
    int* pComponent = getComponent(animComponentBase, 0);
    int* pAnimCtrl = 0;
    int* pTalkCtrl = 0;
    if (pComponent != 0)
    {
        pAnimCtrl = (int*)getAnimController(pComponent, kComponentAnimHash);
        pTalkCtrl = (int*)getTalkController(pComponent, kComponentTalkHash);
        // Attach sound to the object (+0x1a8 is soundId)
        if (pAnimCtrl != 0)
        {
            uint soundId = *(uint*)(thisObj + 0x1a8);
            uint transform = getComponentFromTransform(pComponent);
            playSoundDirect(transform, soundId);
        }
        else if (pTalkCtrl != 0)
        {
            uint soundId = *(uint*)(thisObj + 0x1a8);
            playSoundAttachedToObject(*(uint*)(pTalkCtrl + 0x180), soundId);
        }
    }

    // Update object state (likely position, visibility)
    updateObjectState(thisObj);

    // Handle dialog state machine for +0x1cc and +0x1c4
    int* dialogStatePtr = (int*)(thisObj + 0x1cc);
    int dialogType = *(int*)(thisObj + 0x1c4);
    bool isMenuActive = getMainMenuActive();
    if (isMenuActive && isCutscenePlaying()) isMenuActive = false; // inverted logic

    if (isMenuActive)
    {
        // Not main menu or cutscene playing – go to default handling
        if (dialogType == 0 || dialogType == 0x48)
        {
            dialogStatePtr = (int*)(thisObj + 0x64); // +0x64? Actually +100 decimal = 0x64
            if (getMainMenuActive() && isCutscenePlaying()) goto LAB_008e4236;
            goto LAB_008e41f8;
        }
        // Compute offset based on dialogType
        int base = (dialogType == 0) ? 0 : (dialogType - 0x48);
        dialogStatePtr = (int*)(thisObj + 0x98 + base);
        int otherBase = (dialogType == 0) ? 0 : (dialogType - 0x48);
        int someField = *(int*)(otherBase + 0x80);
        // ... similar pattern
    }
    else
    {
LAB_008e41f8:
        int* pState = getComponentFromId(dialogStatePtr, 0);
        if (pState == 0) goto LAB_008e4236;
        int someField = *(int*)(pState + 0x80);
        dialogStatePtr = (int*)(pState + 0x98); // +0x98
    }

    // Apply state changes
    uint uVar8 = *(uint*)(dialogStatePtr + 0x15c); // some state field
    if (dialogStatePtr != 0)
    {
        setAnimState((int)dialogStatePtr, 0);
    }
    if (someField != 0)
    {
        setComponentState((int*)someField);
    }

LAB_008e4236:
    // Reset component from other slot
    resetComponentState(*(uint*)(thisObj + 0x1fc + slotIndex * 0x20));
    // Finish animation update
    finishAnimUpdate(hAnim, 0);

    // Register callback for sound completion
    uint soundId = *(uint*)(thisObj + 0x1a8);
    int local_14 = 0;
    int* pCallback = (int*)registerCallbackForSound(&soundId);
    if (pCallback != 0)
    {
        *pCallback = soundId;
    }

    // Determine priority based on UI flip state
    uint priority = 2; // default
    uint transform = getComponentFromTransform(thisObj);
    bool flipped = isTransformFlipped(transform);
    if (flipped)
    {
        priority = 1;
    }

    // Spawn visual/audio effect
    int effectHandle = spawnEffect(uVar8, hAnim, 0, 4, 3, 1, 1, priority, &local_14, 0, 0, 0);
    if (effectHandle != 0)
    {
        // If we have an animation controller or talk controller with active talk flag, play sound
        if (pAnimCtrl != 0 || (pTalkCtrl != 0 && (*(byte*)(hAnim + 0x58) & 1) != 0))
        {
            playSoundWithEffect(effectHandle, 2, kGlobalSoundId1, kGlobalSoundId2);
        }
    }

    // Cleanup
    if (local_14 != 0)
    {
        destroyObject(local_14);
    }
}