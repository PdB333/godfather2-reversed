// FUNC_NAME: TreeNode::operator=
// Function address: 0x004d9f80
// Deep-copy assignment operator for a tree node (36-byte struct with child pointer at +0x04)
// Uses custom EA EARS allocator (FUN_009c8e50) for child nodes

#include <cstdint>

// Forward declaration of the custom allocator used by this engine
extern void* __cdecl earsAlloc(uint32_t size); // FUN_009c8e50

class TreeNode {
public:
    // Layout (total 36 bytes, aligned to 4):
    // +0x00: uint32_t   m_data0      (unknown purpose)
    // +0x04: TreeNode*  m_child      (pointer to first child, can be null)
    // +0x08: uint64_t   m_data8      (8-byte field)
    // +0x10: uint64_t   m_data16     (8-byte field)
    // +0x18: uint32_t   m_data24     (4-byte field)
    // +0x1c: uint16_t   m_data28     (2-byte field)
    // +0x1e: padding (6 bytes to reach size 0x24)

    TreeNode& __thiscall operator=(const TreeNode& src);

    // other methods omitted
};

TreeNode& TreeNode::operator=(const TreeNode& src) {
    // Initialize child pointer to null before copying (defensive)
    // Will be overwritten by the block copy below
    m_child = nullptr;

    // Copy the first 8 bytes (m_data0 + m_child)
    *reinterpret_cast<uint64_t*>(this) = *reinterpret_cast<const uint64_t*>(&src);

    // Copy the next two 8-byte blocks
    *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(this) + 8) =
        *reinterpret_cast<const uint64_t*>(reinterpret_cast<const char*>(&src) + 8);
    *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(this) + 16) =
        *reinterpret_cast<const uint64_t*>(reinterpret_cast<const char*>(&src) + 16);

    // Copy the 4-byte field at offset 24
    *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 24) =
        *reinterpret_cast<const uint32_t*>(reinterpret_cast<const char*>(&src) + 24);

    // Copy the 2-byte field at offset 28
    *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(this) + 28) =
        *reinterpret_cast<const uint16_t*>(reinterpret_cast<const char*>(&src) + 28);

    // Deep-copy the child subtree if it exists
    if (src.m_child != nullptr) {
        TreeNode* newChild = static_cast<TreeNode*>(earsAlloc(0x24)); // allocate 36 bytes
        if (newChild != nullptr) {
            // Recursively copy the child
            newChild->operator=(*src.m_child);
            m_child = newChild;
        } else {
            // Allocation failed: set child to null (avoid dangling pointer)
            m_child = nullptr;
        }
    }
    // Note: if src.m_child is null, m_child remains null (from earlier copy)
    // The initial setting to null before block copy is redundant but present in disassembly

    return *this;
}