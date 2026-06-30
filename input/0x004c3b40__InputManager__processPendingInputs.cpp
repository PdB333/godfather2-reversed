// FUNC_NAME: InputManager::processPendingInputs
// Reconstructed from address 0x004c3b40 in The Godfather 2 (x86, EARS engine)
// This function iterates over a buffer of input event identifiers and dispatches
// them to either keyboard or controller action handlers based on the current input mode.

// Forward declarations of called functions (addresses in comments)
int __cdecl decodeInputEvent(int* pEvent);                          // 0x004986e0 – returns action ID
int __cdecl keyboardGetActionForCode(char keyCode);                  // 0x00497110 – returns action index
void __cdecl keyboardExecuteAction(int actionIndex);                // 0x004970b0 – performs the action
int __cdecl padGetAction();                                          // 0x004971f0 – returns action index for current pad state
void __cdecl padSetState(byte buttonMask, int actionIndex);         // 0x00496640 – sets button state (0xff = all buttons)

class InputManager {
public:
    // +0x00: vtable (implicit)
    // +0x20: int inputMode;           // 1 = keyboard, 2 = controller
    // +0x24: byte keyboardKeyCode;    // key code for keyboard mode
    // +0x3c: int* pEventBuffer;       // pointer to array of input event DWORDs
    // +0x40: int eventCount;          // number of events in buffer
    // ...

    void processPendingInputs() __thiscall {
        int* pEvent = *(int**)(this + 0x3c);
        int count = *(int*)(this + 0x20);

        // Iterate over all pending input events
        for (int i = 0; i < count; i++) {
            int event = pEvent[i];
            int actionId = decodeInputEvent(&event);  // decode event to action ID

            // Valid action IDs are non-zero and not the sentinel -8
            if (actionId != 0 && actionId != -8) {
                if (*(int*)(this + 0x20) == 1) {
                    // Keyboard mode: get action index from key code, then execute
                    int keyAction = keyboardGetActionForCode(*(byte*)(this + 0x24));
                    if (keyAction != -1) {
                        keyboardExecuteAction(0); // 0 param indicates execute immediate
                    }
                }
                else if (*(int*)(this + 0x20) == 2) {
                    // Controller mode: get action from pad, then set button state
                    int padAction = padGetAction();
                    if (padAction != -1) {
                        padSetState(0xff, padAction); // 0xff = all buttons pressed
                    }
                }
            }
        }
    }
};