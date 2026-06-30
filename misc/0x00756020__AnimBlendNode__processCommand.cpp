// FUNC_NAME: AnimBlendNode::processCommand
// Address: 0x00756020
// Role: Dispatches blend animation commands (0x12-0x1A) to appropriate handlers.
// Fields: +0x58 mFlags, +0x5c mSpeedMultiplier, +0x64 mState, +0x6c mBaseNode

enum AnimCommand {
    kAnimCmdSetBlendWeight    = 0x12, // case 0
    kAnimCmdLerpBlend        = 0x13, // case 1
    kAnimCmdScaleAndLerp     = 0x14, // case 2
    kAnimCmdDirectScaledLerp = 0x15, // case 3
    kAnimCmdResetBlend       = 0x16, // case 4
    kAnimCmdUnused           = 0x17, // case 5 (no-op)
    kAnimCmdEnable           = 0x18, // case 6
    kAnimCmdDisable          = 0x19, // case 7
    kAnimCmdSetFlagBit2      = 0x1A, // case 8
};

class AnimBlendNode {
public:
    uint8_t mFlags;         // +0x58
    float   mSpeedMultiplier; // +0x5c
    int32_t mState;         // +0x64 (0 = idle, 0x48 = blending?)
    void*   mBaseNode;      // +0x6c (default blend node)

    // Internal helpers (functions called by this method)
    void* getInputNode(float weight);            // FUN_00755fa0
    void  setBlendWeight(void* node, float w);   // FUN_007558c0
    void  lerpTo(void* node, float target, int zero); // FUN_00470130
    void  resetToDefault(void* node, int zero);   // FUN_0046ffe0
    void  setActive(void* node, bool active);     // FUN_007557b0
    bool  defaultHandler(void* arg1, float arg2, void* arg3, int cmd, void* arg4); // FUN_0080e8e0
};

bool __thiscall AnimBlendNode::processCommand(void* arg1, float blendWeight, void* arg3, int cmd, void* arg4) {
    bool result = true;

    switch (cmd - 0x12) {
    case 0: // kAnimCmdSetBlendWeight (0x12)
        if (mState != 0 && mState != 0x48) {
            void* node = getInputNode(blendWeight);
            setBlendWeight(node, blendWeight);
            return true;
        }
        break;

    case 1: // kAnimCmdLerpBlend (0x13)
        lerpTo(mBaseNode, blendWeight);
        return true;

    case 2: // kAnimCmdScaleAndLerp (0x14)
        if (mState != 0 && mState != 0x48) {
            float scaledWeight = mSpeedMultiplier * blendWeight;
            void* node = getInputNode(scaledWeight);
            lerpTo(node, scaledWeight, 0);
            return true;
        }
        break;

    case 3: // kAnimCmdDirectScaledLerp (0x15)
        lerpTo(mBaseNode, mSpeedMultiplier * blendWeight, 0);
        return true;

    case 4: // kAnimCmdResetBlend (0x16)
        if (mState != 0 && mState != 0x48) {
            void* node = getInputNode(0.0f);
            resetToDefault(node, 0);
            return true;
        }
        break;

    case 5: // kAnimCmdUnused (0x17)
        break; // no-op

    case 6: // kAnimCmdEnable (0x18)
        {
            void* node = getInputNode(1.0f);
            setActive(node, true);
            return true;
        }

    case 7: // kAnimCmdDisable (0x19)
        {
            void* node = getInputNode(0.0f);
            setActive(node, false);
            return true;
        }

    case 8: // kAnimCmdSetFlagBit2 (0x1A)
        mFlags |= 4;
        return true;

    default:
        result = defaultHandler(arg1, blendWeight, arg3, cmd, arg4);
    }

    return result;
}