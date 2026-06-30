// FUNC_NAME: GhostRecord::clear
class GhostRecord {
public:
    // Offsets: +0x00 = mGhostId (int32), initialized to -1 (0xFFFFFFFF)
    // +0x04 = mState (int32), initialized to 0
    // +0x18 = mLastUpdateTime (int32), initialized to 0
    // +0x1C = mLastDirtyFlags (int32), initialized to 0
    // +0x30 = mLastSendTime (int32), initialized to 0
    // +0x34 = mAckState (int32), initialized to 0
    // +0x48 = mSequenceCount (int32), initialized to 0
    // +0x4C = mPriority (int8), initialized to 0
    void __thiscall clear() {
        mGhostId = -1;           // *param_1 = 0xFFFFFFFF
        mState = 0;              // param_1[1] = 0
        mLastUpdateTime = 0;     // param_1[6] = 0
        mLastDirtyFlags = 0;     // param_1[7] = 0
        mLastSendTime = 0;       // param_1[0xC] = 0
        mAckState = 0;           // param_1[0xD] = 0
        mSequenceCount = 0;      // param_1[0x12] = 0
        mPriority = 0;           // *(byte*)(this + 0x19) = 0
    }

private:
    int32 mGhostId;           // +0x00
    int32 mState;             // +0x04
    // Padding or additional fields up to +0x18
    int32 mLastUpdateTime;    // +0x18
    int32 mLastDirtyFlags;    // +0x1C
    // Padding or additional fields up to +0x30
    int32 mLastSendTime;      // +0x30
    int32 mAckState;          // +0x34
    // Padding or additional fields up to +0x48
    int32 mSequenceCount;     // +0x48
    int8  mPriority;          // +0x4C
};