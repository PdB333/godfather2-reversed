// FUNC_NAME: EARSObject::setPosition
// Function address: 0x00490d70
// Reconstructed C++ for EA EARS engine object position update.
// Sets the object's position (stored at offsets +0xB0..+0xB8) from an input vector,
// notifies a global manager (via FUN_0056b480), and if this is the active object
// (global pointer at DAT_012058e8), triggers a subsequent update using fields
// at offsets +0x14 and +0xAC.

struct Vector3 {
    float x, y, z;
};

// External functions referenced
void FUN_0056b480(void* manager, const Vector3* src, const Vector3* dst);
void FUN_0060ad20(void* arg1, void* arg2, void* dummy);

// Global data (symbolic names, addresses from decompilation)
extern void* DAT_011f69f0;    // Some singleton manager (e.g., spatial index)
extern EARSObject* DAT_012058e8; // Pointer to the currently active/camera object

class EARSObject {
public:
    // Fields (offsets relative to this):
    // +0x14: void* unknownField1
    // +0xAC: void* unknownField2
    // +0xB0: Vector3 position

    void setPosition(const Vector3& newPos) {
        // Copy the position into the internal field at +0xB0
        Vector3* internalPos = reinterpret_cast<Vector3*>(reinterpret_cast<char*>(this) + 0xB0);
        *internalPos = newPos;

        // Notify the spatial manager of the change
        // The same pointer is passed as both source and dest (possibly identity)
        FUN_0056b480(&DAT_011f69f0, internalPos, internalPos);

        // If this object is the currently active one (e.g., player, camera),
        // perform an additional update (e.g., camera repositioning)
        if (DAT_012058e8 == this) {
            void* field14  = *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x14);
            void* fieldAC  = *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0xAC);
            // Third argument (extraout_EDX) is a leftover from a previous call;
            // for correctness we pass a dummy (nullptr is assumed)
            FUN_0060ad20(field14, fieldAC, nullptr);
        }
    }
};