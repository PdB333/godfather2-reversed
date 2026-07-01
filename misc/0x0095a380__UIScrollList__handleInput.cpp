// FUNC_NAME: UIScrollList::handleInput

// Reconstructed C++ for FUN_0095a380 (offset 0x95a380)
// This function handles directional input and selection for a scrollable UI list.
// The object is at param_1 (this pointer), param_2 is the action/input ID.
// Known fields (relative to this):
//   +0x00: vtable pointer
//   +0x60: currentIndex (int)
//   +0x64: maxIndex (int)
//   +0x134: selected (byte/flag)
// Vtable offset +0x2c: function pointer for onSelectionChanged() or onSelect()

#include <cstdint>

// Forward declarations for called functions
extern int getCurrentInputDevice();          // FUN_00466840
extern int getAlternativeInputDevice();      // FUN_00466860
extern void playUISound(const char* soundName, int arg1, int arg2, int arg3); // FUN_005a04a0

class UIScrollList {
public:
    void** vtable;                 // +0x00
    // many other fields...
    int currentIndex;              // +0x60
    int maxIndex;                  // +0x64
    // ... more fields ...
    bool selected;                 // +0x134 (byte, 0/1)

    // Vtable entry at offset 0x2c (index 0x0B) -> onSelectionChanged() or onConfirm()
    typedef void (__thiscall UIScrollList::*SelectionChangedFunc)();
    
    // Constructor, other methods...

    int handleInput(int action);   // __thiscall, param_2 = action
};

int __thiscall UIScrollList::handleInput(int action) {
    int currentDevice = getCurrentInputDevice();
    int alternativeDevice = getAlternativeInputDevice();

    // If action matches current device's "Select" action
    if (action == currentDevice) {
        playUISound("Select", 0, 0, 0);   // (string, param1, param2, param3)
        
        // Check if currentIndex is within valid range
        if (currentIndex <= maxIndex) {
            // Set selected flag
            selected = true;
            
            // Call the vtable function to notify selection changed
            SelectionChangedFunc func = reinterpret_cast<SelectionChangedFunc>(vtable[0x0B]); // offset 0x2c
            (this->*func)();
            
            return 0;
        }
    }
    else {
        // Check for alternative device's "Select" action (e.g., different button)
        if (action == alternativeDevice) {
            // Set deselected
            selected = false;
            
            // Call the vtable function to notify deselection
            SelectionChangedFunc func = reinterpret_cast<SelectionChangedFunc>(vtable[0x0B]);
            (this->*func)();
            
            return 0;
        }
        
        // Handle directional input (cases 6-9)
        switch (action) {
        case 6:
            playUISound("MoveLeft", 0, 0, 0);
            break;
        case 7:
            playUISound("MoveRight", 0, 0, 0);
            break;
        case 8:
            playUISound("MoveUp", 0, 0, 0);
            break;
        case 9:
            playUISound("MoveDown", 0, 0, 0);
            break;
        }
    }
    
    return 0;
}