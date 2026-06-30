// FUNC_NAME: GameObjectState::getStatusString
class GameObjectState {
public:
    int state;                  // +0x00 discriminator: 0, 1, 2, else unknown
    char inlineBuffer[76];      // +0x04 used when state == 0 (actual size unknown)
    char* externalStringPtr;    // +0x50 used when state == 2 (offset = 0x14 * 4 = 0x50)
    // Note: other fields may exist between inlineBuffer and externalStringPtr

    // __thiscall
    char* getStatusString() {
        if (state == 0) {
            // Return pointer to inline buffer at offset +0x04
            return (char*)(&state + 1);
        }
        if (state == 1) {
            return getSomeString();   // external function at 0x004da080
        }
        if (state == 2) {
            return externalStringPtr; // pointer stored at +0x50
        }
        return "(unknown)";
    }
};

extern char* getSomeString(); // 0x004da080