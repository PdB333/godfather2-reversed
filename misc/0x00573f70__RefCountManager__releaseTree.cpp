// FUNC_NAME: RefCountManager::releaseTree

// This function recursively traverses a binary tree of Node objects,
// releasing each node via a virtual function from an interface,
// and decrementing a reference counter in the manager.

// Node structure:
// +0x0: unknown (possibly data or vtable)
// +0x4: unknown
// +0x8: left child pointer
// +0xc: right child pointer

// RefCountManager structure:
// +0x0: vtable pointer
// +0x4: refCount (int)
// +0xc: pointer to interface object with its own vtable

class Node;

// Interface with a vtable that contains a release method at offset 4
class NodeReleaser {
public:
    virtual void release(Node* node, int param) = 0; // offset 4 (index 1)
};

class RefCountManager {
public:
    int refCount;                  // +0x4
    NodeReleaser* nodeReleaser;    // +0xc (points to an object implementing NodeReleaser)

    void __thiscall releaseTree(Node* node);
};

void __thiscall RefCountManager::releaseTree(Node* node) {
    // Recurse into children first (post-order traversal)
    if (node->leftChild != nullptr) {       // +0x8
        releaseTree(node->leftChild);
    }
    if (node->rightChild != nullptr) {      // +0xc
        releaseTree(node->rightChild);
    }

    // Call the release method on the node via the interface's vtable
    // The vtable's second entry (offset 4) is the release function
    void** vtable = *(void***)nodeReleaser; // get vtable pointer from interface object
    typedef void (__thiscall* ReleaseFunc)(Node*, int);
    ReleaseFunc func = (ReleaseFunc)vtable[1]; // index 1 (offset 4 / sizeof(void*))
    func(node, 0); // second argument is 0 (likely flags or context)

    // Decrement the global reference count
    refCount--;
}