// Xbox PDB: EARS_Apt_UIBooksExecStyles_SetStyle
// FUNC_NAME: DebugExecStyleMenu::addExecStyleItem

// Function at 0x00914820: Adds an execution style item to the debug menu.
// Parameters:
//   this - pointer to DebugExecStyleMenu instance (m_itemCount at +0x04)
//   styleId1, styleId2, styleId3 - three ID/hash values for the style
//   baseName - base name string (e.g., "strangle")
//   index - some index parameter (e.g., 0x21fb6201 in call)
void __thiscall DebugExecStyleMenu::addExecStyleItem(int this,
                                                     undefined4 styleId1,
                                                     undefined4 styleId2,
                                                     undefined4 styleId3,
                                                     char* baseName,
                                                     undefined4 index)
{
    float f1, f2, f3;
    String formattedString;
    String checkedName;

    // Initialize local floats
    f1 = 0.0f;
    f3 = 0.0f;
    f2 = 0.0f;

    // Convert the three style IDs to floats (likely reinterpretation of bits, e.g., uint32 to float)
    hashToFloat(styleId1, &f1);
    hashToFloat(styleId2, &f2);
    hashToFloat(styleId3, &f3);

    // Format: "{#%u}\n{#%u} %d, {#%u} %d, {#%u} %d" with index, f1, f2, f3 cast to int
    // The format uses #%u for the index, then %d for the float values cast to int
    formatString(&formattedString, "{#%u}\n{#%u} %d, {#%u} %d, {#%u} %d",
                 index, 0x21fb6201, (int)f1, 0x54ffb17a, (int)f2, 0xfc0d9129, (int)f3);

    // Create the checked version of the base name (appends "_checked")
    formatString(&checkedName, "%s_checked", baseName);

    // Determine the final string to pass to the menu item adder
    char* finalString;
    char* finalName;

    if (f1 == globalDefaultStyleFloat) // 0x00d577a0 - default style threshold?
    {
        finalString = (formattedString.m_data != nullptr) ? formattedString.m_data : emptyString;
        // In the false branch, for the "else" part, the original code would use checkedName
        // But note: in the else branch, the code sets param_5 = checkedName and uses that.
    }
    else
    {
        finalString = (formattedString.m_data != nullptr) ? formattedString.m_data : emptyString;
        finalName = (checkedName.m_data != nullptr) ? checkedName.m_data : emptyString;
    }

    // Add the item to the execution styles menu
    addExecStyleItemToMenu("ExecStylesAddItem", 0, &globalExecStylesMenu, 2, finalName, finalString);

    // Increment item count at this+0x04
    *(int*)(this + 4) = *(int*)(this + 4) + 1;

    // Clean up the temporary strings (custom string class deallocation via function pointer)
    if (checkedName.m_data != nullptr)
        checkedName.m_deallocFunc(checkedName.m_data);
    if (formattedString.m_data != nullptr)
        formattedString.m_deallocFunc(formattedString.m_data);
}

// Helper functions (callees)
void hashToFloat(undefined4 hash, float* outFloat); // 0x008934e0: Converts hash to float
void formatString(String* out, const char* fmt, ...); // 0x004d4ad0: Custom vsprintf-like
void addExecStyleItemToMenu(const char* command, int param2, void* menuPtr, int param4, const char* name, const char* display); // 0x005a04a0

// Global variables
extern float globalDefaultStyleFloat; // 0x00d577a0
extern char* emptyString; // 0x0120546e (empty string)
extern char globalExecStylesMenu[]; // 0x00d84448 (menu object)