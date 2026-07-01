// FUNC_NAME: AptValue::getShapeInstance
// 0x005a8340
// Returns the shape instance pointer stored at offset 0x58 in the AptValue object.
// If the shape instance is not valid (isShapeInstanceValid returns false), a debug assertion is triggered.

class AptValue {
public:
    // Retrieves the shape instance pointer from this object.
    void* getShapeInstance() __thiscall {
        // Check if the shape instance is ready
        if (!isShapeInstanceValid()) {
            // Debug assertion: shape instance must be valid
            // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h, line 0x2a5
            // Expression: "isShapeInst()"
            // In the original code, this triggers an EA-style assertion and potentially a debug break.
            // For reconstructed code, we simulate a breakpoint.
            __debugbreak();
        }
        // Return the shape instance pointer at offset 0x58 from this.
        return *(void**)((char*)this + 0x58);
    }

private:
    // Checks whether the shape instance is valid.
    bool isShapeInstanceValid() {
        // Calls internal function FUN_005a83e0
        // Implementation details unknown.
        // Returns true if the shape instance is ready.
        return false; // placeholder
    }
};