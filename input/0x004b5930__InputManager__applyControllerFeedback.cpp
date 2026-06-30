// FUNC_NAME: InputManager::applyControllerFeedback
// Function address: 0x004b5930
// Sends a feedback (rumble/vibration) command to the specified controller object.
// Uses a global function table (retrieved from FUN_009c8f80) to dispatch the command.

struct FeedbackCommand {
    int commandId; // +0x00: command identifier (2 = rumble)
    int param1;    // +0x04: first parameter (e.g., motor speed / intensity = 0x10)
    int param2;    // +0x08: second parameter (e.g., duration / flags = 0)
};

// __thiscall - param_1 is 'this' (controller object)
void __thiscall InputManager::applyControllerFeedback(void* controllerObject) {
    // Retrieve the function table for feedback operations (likely a singleton)
    void** feedbackTable = (void**)FUN_009c8f80(); // FUN_009c8f80 returns global table pointer

    // Build the feedback command structure
    FeedbackCommand cmd;
    cmd.commandId = 2;      // e.g., vibration start command
    cmd.param1 = 0x10;      // 16 – probably intensity or left motor speed
    cmd.param2 = 0;         // flags or duration

    // Call the first virtual function in the table with the controller object and command
    void (*feedbackFunc)(void*, FeedbackCommand*) = (void (*)(void*, FeedbackCommand*))(*feedbackTable);
    feedbackFunc(controllerObject, &cmd);

    return;
}