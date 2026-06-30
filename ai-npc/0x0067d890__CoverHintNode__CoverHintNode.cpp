// FUNC_NAME: CoverHintNode::CoverHintNode

#include <cstdint>

class CoverHintNode {
public:
    // Vtable pointer (offset +0x00)
    void* vtable;

    CoverHintNode(uint8_t deletionFlag);
    ~CoverHintNode();  // Destructor at 0x009c8eb0
};

CoverHintNode::CoverHintNode(uint8_t deletionFlag) {
    // Set vtable to CoverHintNode's vtable (0x00d57fa8)
    this->vtable = reinterpret_cast<void*>(0x00d57fa8);

    // Call base class constructor at 0x004149b0 (likely SimObject or similar base)
    // The base initialization is performed here but not reconstructed.

    // If deletionFlag's lowest bit is set, call destructor for cleanup
    if (deletionFlag & 1) {
        this->~CoverHintNode();
    }
}

CoverHintNode::~CoverHintNode() {
    // Destructor body at 0x009c8eb0 – not provided, likely frees resources
}