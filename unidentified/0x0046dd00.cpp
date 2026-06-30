// FUN_0046dd00: ActionManager::createAction
// Role: Creates an action component node attached to a parent node, using a resource identifier.
// param_1: pointer to parent node (e.g., ActionNodeManager)
// param_2: some value (e.g., action type or resource ID)
// returns: pointer to inner action structure at offset 0x58 of the created component, or 0 on failure

#include <cstdint>

// Forward declarations for called functions (assumed globals)
extern Node* __cdecl findNode(void* param);
extern ResourceHandle __cdecl resolveResource(Node* node, uint32_t nameOrPtr);
extern ActionComponent* __cdecl createComponent(ResourceHandle handle, Node* node);
extern void __cdecl initComponent(ActionComponent* component, int32_t zero);

// Structures (offsets in comments)
struct Node {
    char pad0[0x1C];
    uint8_t flags;          // +0x1C
};

struct ActionComponent {
    char pad0[0x18];
    uint32_t field_0x18;    // +0x18 (set to param_2)
    char pad1[0x3C];
    uint8_t actionData[0x58 - 0x1C]; // placeholder for the returned substructure
};

// Note: The structure sizes are approximate from offsets used.

int32_t FUN_0046dd00(void* param_1, uint32_t param_2)
{
    Node* node = findNode(param_1);
    if (node != nullptr) {
        ResourceHandle resource;
        if ((node->flags & 1) == 0) {
            // If flag 1 is clear, resolve resource by name (string pointer)
            resource = resolveResource(node, *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(node) + 0x28));
        } else {
            // Otherwise use direct value at offset 0x28
            resource = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(node) + 0x28);
        }

        ActionComponent* component = createComponent(resource, node);
        if (component != nullptr) {
            component->field_0x18 = param_2;
            initComponent(component, 0);
            return reinterpret_cast<int32_t>(reinterpret_cast<char*>(component) + 0x58); // return pointer to sub-struct
        }
    }
    return 0;
}