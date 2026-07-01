// FUNC_NAME: InputDeviceManager::getSelectedController
void __fastcall InputDeviceManager::getSelectedController(int this)
{
    int gameManager;
    int controllerObj;
    int selectedControllerPtr;
    undefined4 stack_local_30_array[6]; // Actually stack structure, size not fully known
    undefined4 *stack_ptr;
    undefined4 unknownHash;
    undefined1 someFlag;
    undefined4 **ppStack;
    undefined4 stackData0;
    undefined4 stackData1;
    undefined8 stackData2;
    undefined4 stackData3;
    undefined4 stackData4;
    undefined1 stackData5;
    undefined4 stackData6;

    gameManager = getGameManager(); // 0x00471610
    // Dereference: this+0x210 points to a controller manager object.
    // Its vtable at +0x34 gives a function that returns a pointer to an input device/controller.
    controllerObj = (*(code **)(*(int **)(this + 0x210) + 0x34))();

    // Adjust pointer based on object at controllerObj+0xc
    if (*(int *)(controllerObj + 0xc) == 0) {
        selectedControllerPtr = 0;
    } else {
        selectedControllerPtr = *(int *)(controllerObj + 0xc) - 0x48; // +0x48 offset (likely element size)
    }

    // Re-add offset if non-zero (seems to revert the earlier subtraction)
    if (selectedControllerPtr != 0) {
        selectedControllerPtr = selectedControllerPtr + 0x48;
    }

    // Stack-only operation: if selectedControllerPtr is non-zero, save its field at +4 and replace it with address of local variable (linked list manipulation)
    stackData1 = 0;
    if (selectedControllerPtr != 0) {
        stackData1 = *(undefined4 *)(selectedControllerPtr + 4);
        *(int **)(selectedControllerPtr + 4) = &selectedControllerPtr;
    }

    // Build a stack structure for logging/debug
    stackData6 = DAT_01205228; // Global flag/state
    stackData5 = 1;
    stackData2 = *(undefined8 *)(gameManager + 0x30);
    stackData3 = *(undefined4 *)(gameManager + 0x38);
    ppStack = &stackData0;
    unknownHash = DAT_0112ad8c; // Global hash value
    someFlag = 0;

    // Likely a debug/log output function with hash and arguments
    FUN_00408a00(&unknownHash, 0);

    // Cleanup: if selectedControllerPtr was non-null, restore the overwritten pointer (linked list element removal?)
    if (selectedControllerPtr != 0) {
        FUN_004daf90(&selectedControllerPtr);
    }

    return;
}