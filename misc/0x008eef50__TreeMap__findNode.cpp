// FUNC_NAME: TreeMap::findNode

#include <cstdint>
#include <cassert>

// Forward declarations of helper functions (likely defined elsewhere)
void copyData(void* dst, bool flag, void* src, uint32_t* key);
void assertCondition(bool condition);
void splayTree(void* node, uint32_t* key);
void rotateTree(void* context);
char compareKeys(void* context, uint32_t* key);
void* lookupInTree(void* context, uint32_t* key);

// Structure representing a tree node (size 0x10+)
struct TreeNode {
    TreeNode* left;      // +0x00
    TreeNode* right;     // +0x04
    TreeNode* parent;    // +0x08
    uint32_t key;        // +0x0c
    // Data follows at +0x10
};

// Structure representing the tree container
struct TreeMap {
    TreeNode* root;       // +0x00
    TreeNode* current;    // +0x04
    void* something;      // +0x08 (maybe count or auxiliary)
};

// __thiscall, returns pointer to output buffer
void* __thiscall TreeMap::findNode(void* output, TreeMap* self, TreeNode* parent, uint32_t* key) {
    // Check if the tree is empty (root is null)
    if (self->something == nullptr) {
        copyData(output, 1, self->current, key);
        return output;
    }

    TreeNode* firstNode = *reinterpret_cast<TreeNode**>(&self->current);
    // Debug check: parent must be null or equal to this tree map
    assert((parent == nullptr) || (parent == reinterpret_cast<TreeNode*>(self)));

    if (parent == firstNode) {
        // If the key is less than the current node's key, copy data from this node
        if (*key < parent->key) {
            copyData(output, 1, parent, key);
            return output;
        }
    } else {
        TreeNode* curNode = self->current;
        assert((parent == nullptr) || (parent == reinterpret_cast<TreeNode*>(self)));

        if (parent == curNode) {
            // Compare with the root node?
            TreeNode* rootNode = *reinterpret_cast<TreeNode**>(&self->current->right);  // +8 offset?
            if (*(uint32_t*)(reinterpret_cast<char*>(rootNode) + 0xc) < *key) {
                copyData(output, 0, rootNode, key);
                return output;
            }
        } else {
            // General case: compare keys and decide
            bool keyLessThanParent = *key < parent->key;
            if (*key < parent->key) {
                splayTree(nullptr);  // splay the parent node
                if (*key < parent->key) {
                    // Check a flag (offset 0x15 in parent's right child)
                    if (*reinterpret_cast<char*>(*reinterpret_cast<int*>(parent->right + 0x8) + 0x15) != '\0') {
                        copyData(output, 0, parent, key);
                        return output;
                    }
                    copyData(output, 1, parent, key);
                    return output;
                }
                keyLessThanParent = *key < parent->key;
            }
            if (keyLessThanParent) {
                // Prepare a context capture: pair (tree, something)
                struct Context {
                    TreeMap* tree;
                    void* somePtr;
                } ctx;
                ctx.tree = self;
                ctx.somePtr = self->current;  // or maybe self->current? Actually local_8 = *(param_1+4)
                rotateTree(&ctx);
                char compResult = compareKeys(&ctx, key);
                if (compResult != 0 || *key < parent->key) {
                    // Check same flag as above
                    if (*reinterpret_cast<char*>(*reinterpret_cast<int*>(parent->right + 0x8) + 0x15) != '\0') {
                        copyData(output, 0, parent, key);
                        return output;
                    }
                    copyData(output, 1, parent, key);
                    return output;
                }
            }
        }
    }

    // Fallback: lookup in the tree using context and key
    Context ctx;
    ctx.tree = self;
    ctx.somePtr = self->current;
    void* resultNode = lookupInTree(&ctx, key);
    // Copy the result node's data to output (assumes resultNode points to a 8-byte data block)
    *reinterpret_cast<uint64_t*>(output) = *reinterpret_cast<uint64_t*>(resultNode);
    return output;
}