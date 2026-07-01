// FUNC_NAME: TrickleTextManager::updateTrickleText
#include <cstddef>

// Result structure for trickle text retrieval functions
struct TrickleTextResult {
    const char* text;         // +0x00: pointer to trickle text string
    int length;               // +0x04: length of the text (0 if empty)
    int unknown;              // +0x08: unused (always 0 in this function)
    void (*destructor)(const char*); // +0x0C: cleanup function for dynamically allocated text
};

// Forward declarations of text retrieval functions (implemented elsewhere)
bool getTrickleText0(TrickleTextResult* out);
bool getTrickleText1(TrickleTextResult* out);
bool getTrickleTextOther(TrickleTextResult* out);

// External symbols (constants from .data)
extern const char* PTR_DAT_00e575fc; // Default trickle text (likely empty string "")
extern const char* DAT_0120546e;      // Placeholder text used when retrieval returns NULL
extern int DAT_00d873d4;             // Format string or data for debug call

// Debug logging function (prints something like "UpdateTrickleText")
void FUN_005a04a0(const char* msg, int code, const int* data, int flag);

class TrickleTextManager {
public:
    // Offset +0x5C: pointer to the currently displayed trickle text
    const char* mCurrentTrickleText;

    // __thiscall method: updates the trickle text based on the given type
    void updateTrickleText(int type);
};

void TrickleTextManager::updateTrickleText(int type) {
    TrickleTextResult result = {nullptr, 0, 0, nullptr};

    // Retrieve text based on the supplied type index
    bool success;
    if (type == 0) {
        success = getTrickleText0(&result);
    } else if (type == 1) {
        success = getTrickleText1(&result);
    } else {
        success = getTrickleTextOther(&result);
    }

    // If retrieval failed or the text is empty, fall back to the default
    if (!success || result.length == 0) {
        mCurrentTrickleText = PTR_DAT_00e575fc;
    } else {
        // Use the retrieved text; if it's NULL, substitute a placeholder
        const char* text = result.text;
        if (text == nullptr) {
            text = DAT_0120546e; // "BLANK" or similar
        }
        mCurrentTrickleText = text;
    }

    // Log/trigger the "UpdateTrickleText" debug message
    FUN_005a04a0("UpdateTrickleText", 0, &DAT_00d873d4, 0);

    // Immediately reset the displayed text to default (debug/cleanup step)
    mCurrentTrickleText = PTR_DAT_00e575fc;

    // Free the retrieved text if it was dynamically allocated
    if (result.text != nullptr && result.destructor != nullptr) {
        result.destructor(result.text);
    }
}