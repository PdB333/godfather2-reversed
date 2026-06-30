// Reconstructed function at 0x0040caf0
// This helper walks two intrusive linked lists stored on a manager-like object,
// clears any cached tail pointer when the removed node is the current tail, and
// then invokes the node's virtual cleanup method with flag `1`.
//
// The exact gameplay meaning of the lists is not visible from this function
// alone, but the pattern is consistent with tear-down of owned engine objects,
// listeners, or queued tasks.

#include <cstdint>

using NodeCleanupFn = void(__thiscall*)(void*, int);

struct IntrusiveNode
{
    void** vtable;                // +0x00
    std::uint8_t unknown_04[0x18];
    IntrusiveNode* next;          // +0x1c
};

class DualListOwner
{
public:
    IntrusiveNode*& primaryHead()
    {
        return *reinterpret_cast<IntrusiveNode**>(reinterpret_cast<std::uint8_t*>(this) + 0x00);
    }

    IntrusiveNode*& primaryTail()
    {
        return *reinterpret_cast<IntrusiveNode**>(reinterpret_cast<std::uint8_t*>(this) + 0x04);
    }

    IntrusiveNode*& secondaryHead()
    {
        return *reinterpret_cast<IntrusiveNode**>(reinterpret_cast<std::uint8_t*>(this) + 0x08);
    }

    IntrusiveNode*& secondaryTail()
    {
        return *reinterpret_cast<IntrusiveNode**>(reinterpret_cast<std::uint8_t*>(this) + 0x0C);
    }

    void __thiscall clearAllNodes();
};

static void ReleaseNode(IntrusiveNode* node)
{
    auto** const vtable = node->vtable;
    auto const cleanup = reinterpret_cast<NodeCleanupFn>(vtable[0]);
    cleanup(node, 1);
}

void __thiscall DualListOwner::clearAllNodes()
{
    // Drain the first intrusive list from the head. If the node being removed
    // is also the cached tail, clear the tail pointer before releasing it.
    while (IntrusiveNode* node = primaryHead())
    {
        if (primaryTail() == node)
        {
            primaryTail() = nullptr;
        }

        primaryHead() = node->next;
        ReleaseNode(node);
    }

    // Drain the second intrusive list using the same lifetime rules.
    while (IntrusiveNode* node = secondaryHead())
    {
        if (secondaryTail() == node)
        {
            secondaryTail() = nullptr;
        }

        secondaryHead() = node->next;
        ReleaseNode(node);
    }
}
