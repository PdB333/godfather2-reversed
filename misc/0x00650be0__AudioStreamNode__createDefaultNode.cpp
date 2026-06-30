// FUNC_NAME: AudioStreamNode::createDefaultNode
// Function address: 0x00650be0
// Creates a default AudioStreamNode (0x20 bytes) and registers it with the manager.
// Fields documented based on offsets from the constructed struct.

#include <cstdint>

// Forward declaration of the vtable
struct AudioStreamNodeVTable;

// Structure for an audio stream node, size 0x20 (32 bytes)
struct AudioStreamNode {
    AudioStreamNodeVTable* vtable; // +0x00
    int32_t field_0x04;           // +0x04 (initialized to 0)
    int32_t field_0x08;           // +0x08 (initialized to 0)
    int32_t isActive;             // +0x0C (initialized to 1)
    int32_t field_0x10;           // +0x10 (initialized to 0)
    void** dataPtrPtr;            // +0x14 (pointer to the data pointer)
    void* dataPtr;                // +0x18 (pointer to data, set to external)
    void (*callbackFunc)();        // +0x1C (function pointer, set to external)
};

// External function: memory allocation (size in bytes)
void* operator new(size_t size); // or custom allocator

// Function that registers/finalizes initialization of an AudioStreamNode
void AudioStreamNode::registerNode(AudioStreamNode* node); // FUN_0064ef60

// The static factory method
AudioStreamNode* AudioStreamNode::createDefaultNode() {
    AudioStreamNode* node = reinterpret_cast<AudioStreamNode*>(operator new(0x20));
    if (node != nullptr) {
        // Initialize fields
        node->field_0x04 = 0;
        node->field_0x08 = 0;
        node->field_0x10 = 0;
        node->isActive = 1;
        node->vtable = &vtable_AudioStreamNode;  // PTR_LAB_00e43038
        node->dataPtr = &externalData;           // PTR_LAB_00e43064
        node->callbackFunc = &externalCallback;   // LAB_00652770
        node->dataPtrPtr = &node->dataPtr;        // points to its own dataPtr member

        // Finalize registration
        AudioStreamNode::registerNode(node);
    } else {
        // If allocation failed, still call registration with null (error handling)
        AudioStreamNode::registerNode(nullptr);
    }
    return node;
}