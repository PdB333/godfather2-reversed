// FUNC_NAME: GameNode::findBestObject
// Address: 0x00460b00
// Role: Recursively traverses a node hierarchy (children at +0x34, count at +0x58) to find the best child object
//       (type 0x1961bed) based on the smallest value at offset +0x38. If outObject is null, selects the first found.
//       Container nodes (type -0xc0deffc) cause recursion into their sub-hierarchy. Also checks a flag at +0xc (bit 2)
//       and calls an update function if not set.

// Forward declarations
class GameNode;

// Child node structure – each element is 0x20 bytes
struct ChildNode {
    char pad[0x8];          // +0x0 – unknown
    int  type;              // +0x8 – node type identifier (0x1961bed = object, -0xc0deffc = container)
    char pad2[0x14 - 0x8 - 0x4]; // +0xc to +0x13 – unknown
    void* subObjectPtr;     // +0x1c – pointer to a sub-object; when dereferenced at +0x14 yields the actual GameNode
};

class GameNode {
public:
    // +0x0: vtable pointer (inferred)
    // +0x4: unknown
    // +0x8: unknown
    // +0xc: uint32 flags – bit 2 (0x4) indicates whether update is needed
    // +0x34: ChildNode* children – pointer to array of child nodes
    // +0x58: int16 childCount – number of children in the array (stored as short)
    // +0x38: (on child sub-objects) uint32 someValue – used for comparison (e.g., distance, priority)

    // Update function (FUN_00442bd0) – called if the flag at +0xc bit 2 is not set
    void ensureUpdated();

    // Recursive search for best object
    // param_2 (outObject): output – pointer to best found GameNode
    // param_3 (outValue): output – associated value from the best node
    // param_4: unused context parameter (passed through recursion)
    void findBestObject(GameNode*& outObject, uint32& outValue, void* param_4) /* __thiscall */ {
        uint32 flags = *(uint32*)((char*)this + 0xc);
        if (!(flags & 0x4)) {
            ensureUpdated();
        }

        int16 count = *(int16*)((char*)this + 0x58);
        ChildNode* children = *(ChildNode**)((char*)this + 0x34);

        for (int i = 0; i < count; i++) {
            ChildNode& child = children[i];
            if (child.type == 0x1961bed) {
                // Object-type child: check its sub-object
                if (child.subObjectPtr != nullptr) {
                    GameNode* subNode = *(GameNode**)((char*)child.subObjectPtr + 0x14);
                    uint32 nodeValue = *(uint32*)((char*)subNode + 0x38);
                    if (outObject == nullptr || outValue < nodeValue) {
                        outObject = subNode;
                        outValue = nodeValue;
                    }
                }
            } else if (child.type == -0xc0deffc) {
                // Container-type child: recurse into the sub-hierarchy
                GameNode* subContainer = *(GameNode**)((char*)child.subObjectPtr + 0x14);
                subContainer->findBestObject(outObject, outValue, param_4);
            }
        }
    }
};