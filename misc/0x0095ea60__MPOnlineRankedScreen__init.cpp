// FUNC_NAME: MPOnlineRankedScreen::init

// Structure for a UI element: 3 ints (likely x, y, width/height?) and a callback function pointer
struct UIElement {
    int data[3]; // +0x00: unknown purpose (maybe rect or state)
    void (*callback)(int); // +0x0C: function pointer (invoked with data[0] as argument)
};

// External functions (from EARS UI framework)
void subInitCommon();                      // FUN_0095e9f0
void registerLocalizedString(const char* key); // FUN_004d3bc0
void getUIElement(UIElement* out);        // FUN_004d3e20
void setupScreenState(int count);         // FUN_0095e090
void showUIElement(UIElement* elem);      // FUN_004d3b50

// Global variables for screen state
static int currentStepIndex;   // DAT_01130838
static int totalSteps;         // DAT_0113083c
static int unknownOffset;      // DAT_01130834 (possibly offset for UI elements)
static int previousStepIndex;  // DAT_011307ec

void MPOnlineRankedScreen::init()
{
    UIElement elemA, elemB, elemC, elemD;

    subInitCommon();

    // Register localized strings for the help screen title and top-level menu
    registerLocalizedString("$mp_online_ranked_help");
    registerLocalizedString("$mp_online_ranked");

    // Initialize UI element structs (clear to zero)
    elemC.data[0] = 0;
    elemC.data[1] = 0;
    elemC.data[2] = 0;
    elemC.callback = nullptr;

    elemD.data[0] = 0;
    elemD.data[1] = 0;
    elemD.data[2] = 0;
    elemD.callback = nullptr;

    // Fetch UI elements from the engine (likely two main elements: help text and continue button)
    getUIElement(elemA);
    getUIElement(elemB);

    // Determine the number of steps/pages for the help screen
    if (currentStepIndex == totalSteps) {
        int stepCount;
        if (totalSteps == 0) {
            stepCount = 1;
        } else {
            stepCount = totalSteps * 2;
        }
        setupScreenState(stepCount);
    }

    // Update step index
    int currentStepOffset = currentStepIndex * 0x20; // presumably size of UI element block?
    currentStepIndex++;

    // If the offset plus unknown offset is non-zero, show the two conditional UI elements
    if (currentStepOffset + unknownOffset != 0) {
        showUIElement(elemC);
        showUIElement(elemD);
    }

    // Invoke callbacks for all UI elements (if they have been set)
    if (elemD.data[0] != 0) {
        elemD.callback(elemD.data[0]);
    }
    if (elemC.data[0] != 0) {
        elemC.callback(elemC.data[0]);
    }
    if (elemA.data[0] != 0) {
        elemA.callback(elemA.data[0]);
    }
    if (elemB.data[0] != 0) {
        elemB.callback(elemB.data[0]);
        previousStepIndex = currentStepIndex;
        return;
    }
    previousStepIndex = currentStepIndex;
}