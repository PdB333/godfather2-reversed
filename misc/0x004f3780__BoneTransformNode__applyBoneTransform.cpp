// FUNC_NAME: BoneTransformNode::applyBoneTransform
// Function address: 0x004f3780
// Updates a bone transform (either absolute or additive) and links the node into a global list.

// Assume this class is defined elsewhere.
class BoneTransformNode {
public:
    // +0x00: vtable? (not used)
    // +0x04: flags? (not used directly)
    // +0x10: pointer to the bone transform buffer (array of float3/quat)
    void* m_pBoneArray;
    // +0x24: pointer to the bone info structure passed in
    void* m_pBoneInfo;
    // +0x2c: next node in global list
    BoneTransformNode* m_pNext;
    // +0x30: previous node in global list
    BoneTransformNode* m_pPrev;
};

// Structure for bone info (passed in ESI)
struct BoneInfo {
    // +0x04: flags (bit0: additive, bit1: set if replacing?)
    unsigned int flags;
    // +0x10: translation or scale vector (x,y,z)
    float translateX;
    float translateY;
    float translateZ;
    // +0x1c: quaternion or rotation part (w?)
    int rotationPart;
    // +0x20: more rotation data?
    int rotationPart2;
    // Note: actual size likely larger.
};

// Global list head (DAT_012234c8)
struct BoneTransformListHead {
    // +0x00: unknown
    // +0x04: pointer to first node in list
    BoneTransformNode* pHead;
};

extern BoneTransformListHead g_BoneTransformHead; // 0x12234c8

// External functions (not shown)
void ConvertBoneTransform(int param1, int param2, int param3, void* dest); // FUN_0056b8a0
void NotifyBoneTransformChanged(); // FUN_00533fb0

void __thiscall BoneTransformNode::applyBoneTransform(BoneInfo* pBoneInfo)
{
    // FS:[0x2c] points to thread-local storage, get global context pointer
    int* pGlobalContext = *(int**)(__readfsdword(0x2c));
    int someIndex = *(int*)(pGlobalContext + 2); // pGlobalContext[2] -> offset index

    // Get destination transform pointer: this->m_pBoneArray + 0x10 + index
    void* destTransform = (void*)(*(int*)((char*)this->m_pBoneArray + 0x10) + someIndex);
    // Or more literally: dest = (char*)this->m_pBoneArray + 0x10 + someIndex

    // Convert bone info into destination transform (e.g., quaternion to matrix)
    ConvertBoneTransform(pBoneInfo->rotationPart, pBoneInfo->rotationPart2, 0, destTransform);

    // Check flags
    if ((pBoneInfo->flags & 1) == 0) {
        // Not additive
        if ((pBoneInfo->flags & 2) != 0) {
            // Absolute replace: copy translation from bone info to destination
            float* dest = (float*)((char*)this->m_pBoneArray + 0x40 + someIndex);
            dest[0] = pBoneInfo->translateX;
            dest[1] = pBoneInfo->translateY;
            dest[2] = pBoneInfo->translateZ;
        }
    } else {
        // Additive: add translation to existing values
        float* dest = (float*)((char*)this->m_pBoneArray + 0x40 + someIndex);
        dest[0] += pBoneInfo->translateX;
        dest[1] += pBoneInfo->translateY;
        dest[2] += pBoneInfo->translateZ;
    }

    // Notify system that a bone transform changed
    NotifyBoneTransformChanged();

    // Store pointer to bone info in this node
    this->m_pBoneInfo = pBoneInfo;

    // Insert this node into global linked list
    BoneTransformNode* prevHead = g_BoneTransformHead.pHead;
    this->m_pNext = prevHead;
    this->m_pPrev = nullptr;
    if (prevHead != nullptr) {
        prevHead->m_pPrev = this;
    }
    g_BoneTransformHead.pHead = this;
}