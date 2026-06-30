// FUNC_NAME: InputManager::getInputVector
// Address: 0x00714b80
// Purpose: Retrieves the current analog input vector (e.g., for movement or camera). 
// Handles special conditions like keyboard backspace triggering random input, and 
// mouse override of the Y axis.

#include <cstdlib>

// Represents a 12-byte input vector (two floats, one int/pointer)
struct AnalogInputVector {
    float x;   // +0x00
    float y;   // +0x04
    float z;   // +0x08
};

// Forward declarations of called functions (from the same module)
AnalogInputVector* getRandomInput(int selection);   // FUN_006e5dd0
AnalogInputVector* getDefaultInput();               // FUN_006e5dc0
void* getGlobalInputState();                        // FUN_00471610

// Global constant for random threshold
extern float g_randomThreshold;  // _DAT_00d5c458

// Virtual function table offset for filling default input
// 0x48 is assumed to be a virtual function in the manager class pointed by this->manager

class InputManager {
public:
    // +0x10: Pointer to a higher-level manager object (e.g., PlayerManager or GameManager)
    // This manager contains device states and flags.
    // Offsets relative to manager:
    //   +0x21dc: iVar1 – pointer to the currently active input device (keyboard/controller)
    //   +0x8e4:  bit 0xe flag – enable special random mode? Likely internal debug flag.
    //   +0x8e0:  bit 0xa flag – enable mouse override on Y axis.
    //   +0x74c:  pointer to mouse device object (or null if not present)
    //   +0x48:   virtual function (#12?) for filling a default input vector.
    void* manager;

    // Device object structure (the one pointed by iVar1 from manager->+0x21dc)
    // +0x88: character key code (e.g., '\b' = backspace)
    // This device might be a keyboard/controller state.

    AnalogInputVector* getInputVector(AnalogInputVector* outputVector) {
        int inputDevicePtr = *(int*)( *(int*)((char*)this + 0x10) + 0x21dc );
        uint flags1 = *(uint*)( *(int*)((char*)this + 0x10) + 0x8e4 );
        uint flags2 = *(uint*)( *(int*)((char*)this + 0x10) + 0x8e0 );
        AnalogInputVector* resultPtr;

        if ( ((flags1 >> 0xe) & 1) != 0 && inputDevicePtr != 0 ) {
            // Special mode: random input based on device key
            if ( *(char*)(inputDevicePtr + 0x88) == '\b' ) {
                // Backspace key triggers random direction selection
                int randVal = rand();
                int randomChoice = 1;
                if ( (float)randVal <= g_randomThreshold ) {
                    randomChoice = 2;
                }
                resultPtr = getRandomInput(randomChoice);
                *outputVector = *resultPtr;  // copy 12 bytes from resultPtr
                return resultPtr;
            }
            // Otherwise use default input
            resultPtr = getDefaultInput();
            outputVector->x = resultPtr->x;
            outputVector->y = resultPtr->y;
            // Note: outputVector->z is not set here? It's set later or left uninitialized.
            // Actually original: *(undefined8 **)(param_2 + 1) = puVar3; 
            // This sets the pointer at offset 8 to the pointer stored in resultPtr+0x08? 
            // Adjusted: outputVector->z = *(int*)&resultPtr[1]; but careful.
            // We'll replicate as pointer copy:
            outputVector->z = resultPtr->z;  // Since z is same type as pointer? Assuming same size.
            return resultPtr;
        }

        // Normal path: call virtual function of manager to fill output
        void* managerPtr = *(void**)((char*)this + 0x10);
        (*(void (**)(void*, AnalogInputVector*))(*(int*)managerPtr + 0x48))(managerPtr, outputVector);

        // Mouse override for Y axis if applicable
        void* mouseDevice = *(void**)(*(int*)((char*)this + 0x10) + 0x74c);
        if ( mouseDevice != nullptr &&
             mouseDevice != (void*)0x00000048 &&   // null check pattern
             ((flags2 >> 0xa) & 1) != 0 ) {
            void* globalInput = getGlobalInputState();
            // Update Y component (offset 4) with global input's second float
            outputVector->y = *(float*)((int)globalInput + 0x34);
            resultPtr = (AnalogInputVector*)((int)globalInput + 0x30);
        } else {
            resultPtr = (AnalogInputVector*)mouseDevice; // actually last assignment in original
        }
        return resultPtr;
    }
};
```

**Note on reconstructing the final pointer assignment:**  
The original last lines are:
```
iVar1 = FUN_00471610();
puVar3 = (undefined8 *)(iVar1 + 0x30);
*(undefined4 *)((int)param_2 + 4) = *(undefined4 *)(iVar1 + 0x34);
```
This updates param_2's Y component and sets puVar3 to point to iVar1+0x30. Then the function returns puVar3. If the condition fails, puVar3 is the earlier mouseDevice pointer. In our reconstruction, `resultPtr` is assigned appropriately. The return value is the "source" of the input vector (the pointer that was used as data source).