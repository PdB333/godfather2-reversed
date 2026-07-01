// FUNC_NAME: AptValue::getAnimFloat

// Function at 0x0059c8b0: Getter for a float member at offset 0x58 with precondition that an animation instance exists.
// This is a debug-build assertion: if isAnimationInst() fails, it triggers an assert log and breakpoint.

class AptValue {
public:
    // Checks if animation instance exists (likely virtual or external)
    bool isAnimationInst();

    // Returns the animation-related float at +0x58
    float getAnimFloat() {
        if (!isAnimationInst()) {
            // Assertion: "isAnimationInst()" at line 0x2a0 in apt/_AptValue.h
            const char* expression = "isAnimationInst()";
            const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
            int line = 0x2a0;
            int assertType = 2; // unknown assert severity
            // Global debug flag (DAT_01128f14) – if set, may break
            if (DAT_01128f14 != 0) {
                // Attempt to trigger a debug break via exception handler
                // piVar1 = TlsGetValue(...) etc. – simplified as a break
                __debugbreak(); // or asm int 3
            }
        }
        // Return value at offset 0x58 from this pointer
        return *(float*)((char*)this + 0x58);
    }
};

// NOTE: In the original binary, the assertion code reads from FS_OFFSET (thread-local-storage) 
// and uses a software interrupt (swi(3)) to break. This reconstruction simplifies that logic 
// to a debug break for readability.