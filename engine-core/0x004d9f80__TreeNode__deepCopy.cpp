// FUNC_NAME: TreeNode::deepCopy

extern void* __cdecl AllocateMemory(size_t size);

class TreeNode {
public:
    uint64_t field_0;        // +0x00
    uint64_t field_8;        // +0x08
    uint64_t field_10;       // +0x10
    int32_t field_18;        // +0x18
    int16_t field_1C;        // +0x1C
    // +0x1E padding (2 bytes)
    TreeNode* child;         // +0x20

    __thiscall TreeNode* deepCopy(TreeNode* source) {
        child = nullptr;
        field_0 = source->field_0;
        field_8 = source->field_8;
        field_10 = source->field_10;
        field_18 = source->field_18;
        field_1C = source->field_1C;

        if (source->child != nullptr) {
            TreeNode* newChild = (TreeNode*)AllocateMemory(0x24);
            if (newChild != nullptr) {
                newChild->deepCopy(source->child);
                child = newChild;
            } else {
                child = nullptr;
            }
        }
        return this;
    }
};