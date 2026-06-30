// FUNC_NAME: ResourceManager::collectGarbage

class ResourceManager {
public:
    // +0x28: array of pointers to resources
    SomeResource** m_resourceArray; 
    // +0x2c: number of resources in array
    int m_resourceCount;

    void collectGarbage() {
        int i = 0; // uVar6
        if (m_resourceCount != 0) {
            do {
                SomeResource* pResource = m_resourceArray[i];
                // pResource->refCount at offset 0x14 (5*4 = 20)
                // If reference count is zero, check if any still referenced via dependency tree
                if (pResource->refCount == 0) {
                    // pResource->m_ownerListHead at offset 0x1c (7*4 = 28)
                    OwnerNode* pOwnerNode = pResource->m_ownerListHead;
                    bool bHasReference = false;
                    while (pOwnerNode != nullptr) {
                        // pOwnerNode->ownerRef at +4; if non-null, something else already holds it
                        if (pOwnerNode->ownerRef != nullptr) {
                            bHasReference = true;
                            break;
                        }
                        // pOwnerNode->data at +0x14 points to an object that may have back-references
                        // That object has a list at offset 0x11c
                        BackRefListHead* pBackRefList = *(BackRefListHead**)((char*)pOwnerNode->data + 0x11c);
                        for (BackRefNode* pNode = pBackRefList; pNode != nullptr; pNode = pNode->next) {
                            // pNode->childList at +0x18 is another list
                            for (BackRefChild* pChild = *(BackRefChild**)((char*)pNode + 0x18); pChild != nullptr; pChild = pChild->next) {
                                // pChild->ownerNode at +8 points back to pOwnerNode
                                if (pChild->ownerNode == pOwnerNode) {
                                    bHasReference = true;
                                    goto foundReference;
                                }
                            }
                        }
                        pOwnerNode = pOwnerNode->next;
                    }
foundReference:
                    if (!bHasReference) {
                        // No remaining references; destroy the resource
                        // Virtual function call: pResource->vtable[1](1)
                        (*(code**)(*(int*)pResource + 4))(1);
                        // Remove from array by swapping with last element
                        if (i != m_resourceCount - 1) {
                            m_resourceArray[i] = m_resourceArray[m_resourceCount - 1];
                        }
                        m_resourceCount--;
                    }
                } else {
                    // Resource still has reference count, keep it
                    i++;
                }
            } while (i < m_resourceCount);
        }
    }
};

// Supporting structures (inferred from offsets)
struct SomeResource {
    void** vtable;       // +0
    int refCount;        // +0x14 (5*4)
    OwnerNode* m_ownerListHead; // +0x1c (7*4)
};

struct OwnerNode {
    int* ownerRef;       // +4
    OwnerNode* next;     // +0xc
    void* data;          // +0x14  (points to some external object)
};

struct BackRefListHead {
    // No size known, but at offset 0x11c from data, so data is a larger struct
};

struct BackRefNode {
    BackRefNode* next;   // +0x10
    BackRefChild* childList; // +0x18
};

struct BackRefChild {
    OwnerNode* ownerNode; // +8
    BackRefChild* next;   // +0xc
};