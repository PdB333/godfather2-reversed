// FUNC_NAME: TransformNode::applyTranslationAndLink
class TransformNode {
public:
    // Fields (offsets relative to this):
    // +0x10: mTransformBufferBase - pointer to an array of transform data (affine matrices)
    // +0x24: mSourceNode - pointer to source transform node
    // +0x2c: mPrevNode - previous node in linked list
    // +0x30: mNextNode - next node in linked list

    void __thiscall applyTranslationAndLink(TransformNode* sourceNode) {
        // Thread-local global data pointer (e.g., GameContext)
        int* globalDataPtr = *(int**)(__readfsdword(0x2c));
        int transformIndex = *(int*)(globalDataPtr + 0x8); // +0x8: array index into transform buffer

        // Call a helper that applies a 2D/3D transform offset from sourceNode
        // Parameters: sourceNode->field_0x1c, sourceNode->field_0x20, 0, and destination pointer
        apply2DTransform(
            *(int*)(sourceNode + 0x1c),  // source U or X component
            *(int*)(sourceNode + 0x20),  // source V or Y component
            0,
            mTransformBufferBase + 0x10 + transformIndex // +0x10 offset in transform entry
        );

        // Apply translation component
        float* destTranslation = (float*)(mTransformBufferBase + 0x40 + transformIndex);
        int flags = *(int*)(sourceNode + 0x4);

        if ((flags & 1) == 0) {
            // Bit0 clear: absolute set (only if bit1 set)
            if ((flags & 2) != 0) {
                destTranslation[0] = *(float*)(sourceNode + 0x10);
                destTranslation[1] = *(float*)(sourceNode + 0x14);
                destTranslation[2] = *(float*)(sourceNode + 0x18);
            }
        } else {
            // Bit0 set: additive blend
            destTranslation[0] += *(float*)(sourceNode + 0x10);
            destTranslation[1] += *(float*)(sourceNode + 0x14);
            destTranslation[2] += *(float*)(sourceNode + 0x18);
        }

        // Notify or finalize the transform update
        notifyTransformUpdate();

        // Retrieve the global linked list tail pointer (stored at DAT_012234c8+4)
        // The global structure at DAT_012234c8 is a list head with:
        //   +0x00: head pointer (unused here)
        //   +0x04: tail pointer
        // The list nodes are TransformNodes linked by mPrevNode (+0x2c) and mNextNode (+0x30)
        int* listContainer = (int*)DAT_012234c8;
        int* tailPtr = (int*)(listContainer + 1); // tail pointer

        // Append this node to the linked list
        mSourceNode = sourceNode;             // +0x24
        mPrevNode = *tailPtr;                 // +0x2c
        mNextNode = 0;                        // +0x30 (new tail)

        if (*tailPtr != 0) {
            // Update previous tail's next pointer
            *(int*)(*tailPtr + 0x30) = (int)this;
        }

        // Update global tail to this node
        *tailPtr = (int)this;
    }
};

// External declarations:
void __cdecl apply2DTransform(int param1, int param2, int param3, void* dest);
void __cdecl notifyTransformUpdate(void);
extern int DAT_012234c8; // Global list container (head at +0, tail at +4)