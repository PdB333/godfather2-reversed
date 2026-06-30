// FUNC_NAME: EARSObject::submitWorldMatrix

class EARSObject {
public:
    // +0x00: vtable pointer
    // +0x04: some flags or ID
    // +0x10: 4x4 world matrix (16 floats, stored row-major)
    // (actual layout may vary)
};

// External globals
extern int DAT_012058e8; // expected vtable for renderable objects
extern void computeWorldMatrix(int matrix[16]); // FUN_00417560
extern void submitMatrixToRenderer(void* arg, int flags, int matrix[16]); // FUN_0060b020
extern void postUpdate(); // FUN_00494310

void __thiscall EARSObject::submitWorldMatrix() {
    int localMatrix[16];

    // Fill local matrix (likely from parent transforms, etc.)
    computeWorldMatrix(localMatrix);

    // Copy computed matrix into object's member storage
    // +0x10: matrix[0..15]
    for (int i = 0; i < 16; i++) {
        this->matrix[i] = localMatrix[i]; // offsets +0x10..+0x4C
    }

    // Check if this object is of the renderable type (vtable check)
    if (*(void**)this == (void*)DAT_012058e8) {
        // Retrieve something from the vtable (+0x14)
        // Typically a function pointer or a renderer context
        void* vtableEntry = *(void**)(*(void**)this + 0x14);
        // Submit the matrix to the rendering system
        submitMatrixToRenderer(vtableEntry, this->field4, &this->matrix[0]);
    }

    // Perform any post‑update tasks
    postUpdate();
}