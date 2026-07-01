// FUNC_NAME: DebugOverlay::updateLineDisplay
// Function at 0x008084d0: Updates a single debug line with time info and draws it
// This is a member function of a debug overlay class (likely from EA EARS engine)
// The class has a vtable with virtual functions at offsets 0x19c and 0xa4
// It uses a global time manager (FUN_00471610) to get frame time and delta time

class DebugOverlay {
public:
    // vtable index: 0x19c / 4 = 103 -> Returns number of lines or an indicator
    virtual int getLineIndex();

    // vtable index: 0xa4 / 4 = 41 -> Sets time info and possibly formats output buffer
    virtual void setTimeInfo(const double* currentTime, char* lineBuffer);

    // Embedded buffer at this+0x1b9 (size probably 441 bytes for line text)
    char lineBuffer[441]; // +0x1b9
};

// Forward declarations for external functions
void* __fastcall getTimeManager(); // FUN_00471610: returns pointer to a TimeManager singleton
void __cdecl drawDebugLine(float deltaTime, int lineIndex, const char* formattedBuffer, int flags); // FUN_00805a10

void __thiscall DebugOverlay::updateLineDisplay() {
    int lineIndex = this->getLineIndex(); // virtual call, returns line to update

    if (lineIndex > 0) {
        void* timeMgr = getTimeManager();

        // TimeManager structure fields (offsets):
        // +0x30: double currentTime (8 bytes)
        // +0x38: float deltaTime (4 bytes)
        double currentTime = *(double*)((char*)timeMgr + 0x30);
        float deltaTime = *(float*)((char*)timeMgr + 0x38);

        // Call virtual function to set time info into the line buffer
        // Passes pointer to currentTime and the embedded buffer at this+0x1b9
        this->setTimeInfo(&currentTime, this->lineBuffer);

        // Draw the line: uses deltaTime, lineIndex, and the buffer (now containing formatted text)
        // The third argument is likely a pointer to the formatted time info (reusing stack variable)
        // The fourth argument is 0 (unknown flag)
        drawDebugLine(deltaTime, lineIndex, (const char*)&currentTime, 0);
    }
}