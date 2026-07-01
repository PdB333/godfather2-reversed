// FUNC_NAME: HUDTextElement::setTextFromSource
/* 0x00936da0 - HUDTextElement::setTextFromSource
   Called to update the text of a HUD element from an internal data source.
   Retrieves a localized/processed string via FUN_009313f0, sets it on the element,
   then triggers a UI update if the global manager exists.
*/

#include <cstdint>

// Forward declarations for called functions
extern void FUN_004d3d90(const char* message); // debug log?
extern void FUN_009313f0(int32_t* handleBuf, const char** outStrPtr, void (*destructor)(void*), void (*handleDestructor)(int32_t));
extern void FUN_00936890(void* widget, const char* text); // set widget text

// Global pointers (inferred)
extern void* gTextManager;       // DAT_01129928
extern void* gUIManager;         // DAT_01129890  (vtable-based)

void __thiscall HUDTextElement::setTextFromSource(void* this) {
    // Stack cleanup handles (initialized null)
    int32_t handleBuf[3] = {0, 0, 0};   // local_10
    void (*handleDestructor)(int32_t) = nullptr; // local_4
    const char* textStr = nullptr;               // local_20
    int32_t dummy1 = 0;                         // local_1c
    int32_t dummy2 = 0;                         // local_18
    void (*strDestructor)(const char*) = nullptr; // local_14

    // Get source pointer from this->mSource (+0x70)
    void* source = *static_cast<void**>(*static_cast<uintptr_t*>(this) + 0x70);
    if (source == nullptr) {
        source = reinterpret_cast<void*>(&DAT_0120546e); // empty string
    }

    // Debug output of source
    FUN_004d3d90(static_cast<const char*>(source));

    // Retrieve the actual text string from the source handle + set destructors
    FUN_009313f0(handleBuf, &textStr, strDestructor, handleDestructor);
    // Note: FUN_009313f0 likely sets strDestructor and handleDestructor as
    //       static function pointers for cleanup later. In this function
    //       they are retrieved via registers/stack but not captured here.

    // Fallback to empty string if retrieval failed
    const char* resolvedText = textStr ? textStr : reinterpret_cast<const char*>(&DAT_0120546e);

    // Get the current UI widget from the global text manager (+0x98)
    void* widget = *static_cast<void**>(*static_cast<uintptr_t*>(gTextManager) + 0x98);
    if (widget == nullptr) {
        widget = reinterpret_cast<void*>(&DAT_0120546e);
    }

    // Set the text on that widget
    FUN_00936890(widget, resolvedText);

    // Call update/refresh on the UI manager if present
    if (gUIManager != nullptr) {
        // vtable offset 0x2c = update()
        void (__thiscall* update)(void*) = *static_cast<void (__thiscall**)(void*)>(*static_cast<uintptr_t*>(gUIManager) + 0x2c);
        update(gUIManager);
    }

    // Clean up retrieved string and handle if they were allocated
    if (textStr != nullptr && strDestructor != nullptr) {
        strDestructor(textStr);
    }
    if (handleBuf[0] != 0 && handleDestructor != nullptr) {
        handleDestructor(handleBuf[0]);
    }
}