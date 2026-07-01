// FUNC_NAME: Node::setTransform
// Address: 0x00827860
// Role: Sets a 6-field transform (position + rotation) and notifies registered listeners

#include <cstdint>

struct TransformData {
    float field_0x00; // +0x34
    float field_0x04; // +0x38
    float field_0x08; // +0x3C
    float field_0x0C; // +0x40
    float field_0x10; // +0x44
    float field_0x14; // +0x48
};

class ListenerBase {
public:
    virtual void onTransformChanged(const TransformData* newData); // vtable+4
    // offset +0x20 (32) is a byte flag (bool)
    // This is a placeholder; actual class layout assumed from code
};

// This class represents an entity that owns a transform and notifies children
class Node {
public:
    void setTransform(const TransformData* newData); // __thiscall

private:
    // +0x00 : vtable (implied from __thiscall)
    // +0x04 : pointer to array of 8-byte entries (listeners)
    uint8_t* m_listenerArray; // actually struct { ListenerBase* ptr; uint32_t extra; }[N]
    // +0x08 : count of listeners
    uint32_t m_listenerCount;
    // padding (0x0C-0x33 unknown)
    // +0x34 : transform data (6 floats)
    TransformData m_transform;
    // (size at least 0x4C)
};

void __thiscall Node::setTransform(const TransformData* newData) {
    // Avoid self-assignment: compare address of internal field with input pointer
    if (&m_transform != newData) {
        m_transform = *newData; // copy 6 floats
    }

    if (m_listenerCount != 0) {
        for (uint32_t i = 0; i < m_listenerCount; ++i) {
            // Each listener entry is 8 bytes; first 4 bytes are pointer to ListenerBase
            ListenerBase* listener = *reinterpret_cast<ListenerBase**>(
                m_listenerArray + i * 8
            );

            // Check active flag at offset 0x20 (byte)
            if (*reinterpret_cast<const uint8_t*>(listener) + 0x20 != 0) {
                // Call virtual function at vtable+4
                listener->onTransformChanged(newData);
            }
        }
    }
}