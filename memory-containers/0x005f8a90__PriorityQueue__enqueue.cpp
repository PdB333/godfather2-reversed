// FUNC_NAME: PriorityQueue::enqueue
#include <cstdint>

// Heap structure (8 bytes per element, 1-indexed)
// +0x00: size (int)
// +0x04: capacity (int)
// +0x08: data array (HeapElement*) - elements are { int id; float priority; }
// HeapElement: +0x00 id, +0x04 priority

struct HeapElement {
    int id;
    float priority;
};

// Object structure (assumed) - has a flag byte at offset 0x0A (bit 0 = queued)
struct Object {
    // ... other fields ...
    uint8_t flags[0x0A]; // +0x0A: flags (bit 0 set when enqueued)
};

class PriorityQueue {
public:
    // @param in_EAX: previous handle (or 0) - top 24 bits preserved on failure, overwritten on success
    // @param unaff_EDI: pointer to Object to enqueue
    // @param in_XMM0_Da: priority value (float)
    // @return handle: success = ((data_ptr >> 8) & 0xFFFFFF) | 1, failure = in_EAX & 0xFFFFFF00
    uint32_t enqueue(uint32_t in_EAX, Object* item, float priority) {
        uint32_t retVal = in_EAX & 0xFFFFFF00;  // default return (failure/unchanged)
        
        if (size < capacity - 1) {
            int currentIdx = size + 1;
            size = currentIdx;
            
            // Sift up: place item at currentIdx, then bubble up
            while (currentIdx > 1) {
                int parentIdx = currentIdx / 2;
                int base = reinterpret_cast<int>(data);
                float parentPriority = *reinterpret_cast<float*>(base + 4 + parentIdx * 8);
                if (parentPriority <= priority) break;
                
                // Swap parent down
                *reinterpret_cast<uint32_t*>(base + currentIdx * 8) = *reinterpret_cast<uint32_t*>(base + parentIdx * 8);
                *reinterpret_cast<float*>(base + 4 + currentIdx * 8) = *reinterpret_cast<float*>(base + 4 + parentIdx * 8);
                currentIdx = parentIdx;
            }
            
            int base = reinterpret_cast<int>(data);
            *reinterpret_cast<int*>(base + currentIdx * 8) = reinterpret_cast<int>(item);
            *reinterpret_cast<float*>(base + 4 + currentIdx * 8) = priority;
            
            // Mark object as enqueued (bit 0 at offset 0x0A)
            item->flags[0x0A] |= 1;
            
            // Construct handle from data array pointer shifted right 8 bits plus low byte = 1
            retVal = (static_cast<uint32_t>(reinterpret_cast<int>(data)) >> 8) | 0x1;
        }
        return retVal;
    }
    
private:
    int size;      // +0x00
    int capacity;  // +0x04
    HeapElement* data; // +0x08
};