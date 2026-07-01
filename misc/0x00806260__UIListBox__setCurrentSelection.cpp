// FUNC_NAME: UIListBox::setCurrentSelection

#include <cstdint>

// Forward declarations of external functions with guessed names
int* __thiscall getInputManager(int* globalPtr); // FUN_0043b870 - returns input manager singleton
bool __thiscall isMenuInputAllowed(); // FUN_008a4380 - checks if menu input is active
void __thiscall playSelectionSound(bool isSelectable); // FUN_007f3f00 - plays UI sound based on selection state

// Internal helper: given a wrapper pointer (which may be 0 or 0x48 sentinel), returns the underlying object pointer.
// Wrapper structure: at +0x00 maybe next? +0x04 prev? The actual object starts at wrapper - 0x48.
inline int* getObjectFromWrapper(int* wrapper) {
    if (wrapper == nullptr || wrapper == (int*)0x48) {
        return nullptr;
    }
    return (int*)((uint8_t*)wrapper - 0x48);
}

// Functions for highlight management (order deduced from usage)
void __thiscall removeSelectionHighlight(int* thisPtr, int highlightData); // FUN_0043c5b0
void __thiscall applySelectionHighlight(int* thisPtr, int highlightData); // FUN_0043c490

// Functions for transition/animation
void __thiscall startScrollAnimation(int* thisPtr); // FUN_008c3bc0
void __thiscall updateScrollAnimation(int* thisPtr); // FUN_008c3c80

// Retrieve a visual field (e.g., highlight color or icon) from an object at given offset
int __thiscall getSelectionVisual(int* object, int offset); // FUN_008c6d20 - here used with offset 0x50

// Get the wrapper structure associated with an ID/handle
int* __thiscall getWrapperFromHandle(int handle); // FUN_008c74d0 - returns pointer to base, then +0x48 is wrapper

// Remove a node from doubly linked list (updates head pointer at given address)
void __thiscall unlinkWrapper(int** headPointer); // FUN_004daf90

void __thiscall UIListBox::setCurrentSelection(int newSelection) {
    // Current selection ID stored at +0x1ed4
    int* currentSelectionId = (int*)((uint8_t*)this + 0x1ed4);
    // Current wrapper pointer stored at +0x1ed8
    int** wrapperPtrField = (int**)((uint8_t*)this + 0x1ed8);
    // Previous node pointer for linked list at +0x1edc
    int* prevWrapperPtr = (int*)((uint8_t*)this + 0x1edc);
    // Transition state field at +0x1b94 (negative = animating)
    int* transitionState = (int*)((uint8_t*)this + 0x1b94);

    int* currentWrapper = *wrapperPtrField;

    // If selection unchanged and wrapper exists and not special sentinel, skip
    if (*currentSelectionId == newSelection && currentWrapper != nullptr && currentWrapper != (int*)0x48) {
        return;
    }

    // ---- Step 1: Remove highlight from previous selection if it was valid ----
    if (currentWrapper != nullptr && currentWrapper != (int*)0x48) {
        int* oldObject = getObjectFromWrapper(currentWrapper);
        // Get visual data from old object at offsets +0x50 (via function) and +0x88
        int visualFrom50 = getSelectionVisual(oldObject, 0x50);
        removeSelectionHighlight(this, visualFrom50);
        removeSelectionHighlight(this, *(oldObject + 0x88)); // direct field
    }

    // ---- Step 2: Update current selection ID ----
    *currentSelectionId = newSelection;

    // ---- Step 3: Update wrapper pointer and manage linked list ----
    int* newWrapperBase = getWrapperFromHandle(newSelection);
    int* newWrapper = (newWrapperBase != nullptr) ? (int*)((uint8_t*)newWrapperBase + 0x48) : nullptr;

    if (*wrapperPtrField != newWrapper) {
        if (*wrapperPtrField != nullptr) {
            unlinkWrapper(wrapperPtrField); // Remove old wrapper from list
        }
        *wrapperPtrField = newWrapper;
        if (newWrapper != nullptr) {
            // Store old previous pointer of new node (likely next in list)
            *prevWrapperPtr = *(newWrapper + 1); // offset 0x04 = prev pointer
            // Update new node's prev to point to the container field
            *(newWrapper + 1) = (int)wrapperPtrField;
        }
    }

    // ---- Step 4: Apply highlight to new selection ----
    if (newWrapper != nullptr && newWrapper != (int*)0x48) {
        int* newObject = getObjectFromWrapper(newWrapper);

        // Check if transition is active (negative field)
        if (*transitionState < 0) {
            if (oldObject != nullptr) {
                startScrollAnimation(this);
            }
            updateScrollAnimation(this);
        }

        int* newObjectSafe = getObjectFromWrapper(newWrapper); // re-get (safe)
        // Get visual data from new object
        int visualFrom50_new = getSelectionVisual(newObjectSafe, 0x50);
        int visualFrom88_new = *(newObjectSafe + 0x88);

        // Determine if item is selectable (field at +0xec)
        bool isSelectable = (*(newObjectSafe + 0xec) != 0);

        // Check global condition: if input manager exists and menu input allowed
        int* inputMgr = getInputManager((int*)0x01130950); // DAT_01130950 is likely a global pointer
        if (inputMgr != nullptr && !isMenuInputAllowed()) {
            playSelectionSound(isSelectable);
        }

        // Apply highlight to new selection
        applySelectionHighlight(this, visualFrom88_new);
        applySelectionHighlight(this, visualFrom50_new);
    }
}