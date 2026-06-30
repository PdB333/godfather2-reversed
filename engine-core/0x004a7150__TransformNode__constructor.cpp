// FUNC_NAME: TransformNode::constructor
// Function address: 0x004a7150
// Role: Initializes a TransformNode by copying a 4x4 rotation/scaling matrix from another node
// and resetting translation to zero and homogeneous coordinate to 1.
// Links this node into a parent's child list if parent exists.

#include <cstdint>

class TransformNode {
public:
    // VTable pointer located at +0x00
    // Data members inferred from offsets:
    // +0x04: start of this struct for linked list (child pointer?)
    // +0x50: 4x4 matrix (16 floats) stored as row-major, offset 0x50 to 0x8C
    // +0x90: parent pointer (offset 0x90)
    // +0x98: next child pointer in parent's list (offset 0x98)
    // +0x9C: previous child pointer? (set to 0)
    // Offsets relative to this pointer.

    void constructor(TransformNode* this, TransformNode* source) {
        // Set vtable
        *reinterpret_cast<void**>(this) = &PTR_FUN_00e35468;

        // Call some initialization function (allocator? parent retriever?)
        int parent = FUN_0060ffd0();
        if (parent != 0) {
            // Link this node into parent's child list
            this->field_98 = *reinterpret_cast<int*>(parent + 0x84);   // previous head
            this->field_9C = 0;
            if (this->field_98 != 0) {
                *reinterpret_cast<void**>(this->field_98 + 0x8C) = &this[1]; // set previous head's prev to this+4
            }
            *reinterpret_cast<void**>(parent + 0x84) = &this[1];      // update head to this+4
            this->field_90 = parent;                                   // store parent pointer
            FUN_006101b0();                                            // post-link callback
        }

        // Copy 4x4 matrix from source (first four rows of 4 floats each)
        const float* src = reinterpret_cast<float*>(source);
        float* dst = reinterpret_cast<float*>(this) + 0x50 / 4; // offset 0x50
        for (int i = 0; i < 16; ++i) {
            dst[i] = src[i];
        }

        // Zero translation column (elements [0][3], [1][3], [2][3])
        dst[3]  = 0.0f;   // element [0][3] at offset 0x5C
        dst[7]  = 0.0f;   // element [1][3] at offset 0x6C
        dst[11] = 0.0f;   // element [2][3] at offset 0x7C
        // Set homogeneous w to identity (usually 1.0)
        dst[15] = DAT_00e2b1a4; // element [3][3] at offset 0x8C

        // Second call to post-link (maybe redundant)
        FUN_006101b0();
    }

private:
    // Expected field layout (based on code offsets, 4-byte alignment):
    // +0x00: void* vtable;
    // +0x04 to +0x4F: unknown (12 fields? or padding)
    // +0x50 to +0x8F: float matrix[4][4]; // stored row-major, 16 floats
    // +0x90: void* parent;   // pointer to parent node
    // +0x94: ??? (maybe field_94, not used here)
    // +0x98: void* nextChild; // linked list next
    // +0x9C: void* prevChild; // linked list prev (set to 0)
    char _pad[0x90 - 4]; // fake to illustrate offsets
    void* parent;        // +0x90
    int field_94;        // +0x94 (unused in this function)
    int field_98;        // +0x98
    int field_9C;        // +0x9C
};

// External functions (defined elsewhere)
extern void FUN_0060ffd0();
extern void FUN_006101b0();
extern float DAT_00e2b1a4;
extern void* PTR_FUN_00e35468;