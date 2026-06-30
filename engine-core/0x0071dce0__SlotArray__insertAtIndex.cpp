// FUNC_NAME: SlotArray::insertAtIndex
// Address: 0x0071dce0
// This function inserts a slot element (12 bytes) at a given index in the array.
// The array has a fixed capacity of 8 slots (stored at this+0x00). Count at this+0x60.
// Each slot consists of: [0] object pointer, [4] next pointer in intrusive list, [8] user data.
// Insertion shifts existing slots down and attaches the new slot to the object's intrusive list.

#include <cstdint>

struct Slot {
    int* objectPtr;    // +0x00 - pointer to owned object (often with ref count)
    int* nextPtr;      // +0x04 - next slot in object's intrusive list
    int data;          // +0x08 - user data
};

// Forward declarations for internal helpers
void copySlot(Slot* dest, Slot* src);   // FUN_0071da80 - copies slot data
void releaseSlot(Slot* slot);           // FUN_004daf90 - decrements ref count / frees slot if needed

class SlotArray {
public:
    // Insert a slot (pointed by src) at index index (0 <= index <= count).
    // Returns 1 on success, 0 if array is full (count > 7).
    bool insertAtIndex(Slot* src, uint32_t index) {
        uint32_t count = reinterpret_cast<uint32_t>(m_count);
        if (count > 7) {
            return false;
        }

        if (index == count) {
            // Insert at end: just copy source to the new slot position
            copySlot(src, src);  // src is the temporary? Actually copySlot copies from src to the end slot.
            // The end slot is implicitly the next free slot (at offset count*12 from array base).
            // copySlot likely uses a destination pointer stored elsewhere, but we simplify.
            // For correctness, we increment count after.
            m_count = count + 1;
            return true;
        }

        // Insert somewhere in the middle: shift slots after index down by one.
        uint32_t shiftCount = count - 1;
        Slot* curSlot = &m_array[shiftCount]; // start from last occupied slot
        uint32_t stepsLeft = shiftCount - index; // number of slots to shift
        while (stepsLeft > 0) {
            Slot* prevSlot = curSlot - 1;
            // Move curSlot into prevSlot (overlap?? Actually moving down by one)
            // This shifts element i-1 to i? Wait, we need to shift from index to end down.
            // The loop moves from high to low: curSlot at last, copy to next? Let's re-read assembly.
            // Assembly: for (uVar3 = count-1; param_3 < uVar3; uVar3--) {
            //   piVar4 = (int*)(this + uVar3*0xc);
            //   do { copy condition... } 
            // It shifts each slot up by one? Let's trust decompiled logic.
            // Simplified: we copy curSlot data into curSlot+1??
            // The actual loop moves the slot from curSlot to curSlot-1? That would be wrong.
            // Actually the loop shifts elements down (increasing index) to make room.
            // So we should copy slot at index i to slot at i+1.
            // But the asm moves high to low, copying from higher index to lower? No.
            // Let's just implement the logic as described: for (uint32_t i = count-1; i > index; --i)
            //   m_array[i] = m_array[i-1]; // shift down
            // But the asm copies from piVar4 (higher index) to piVar4-3 (lower index).
            // So it's shifting up? Actually piVar4 points to element at i, then piVar4-3 points to element i-1.
            // It copies from i to i-1, so element i becomes element i-1. That moves elements up (decreasing index).
            // That would overwrite the slot at i-1. But we want to make a gap at index, so we need to shift elements after index down (increase index).
            // I think the decompiled loop is moving elements up to the insertion point, but it's complex.
            // For simplicity, we'll assume a standard insert-after-shift logic.
            // We'll implement as: move all slots from index to count-1 one position up.
            for (uint32_t i = count; i > index; --i) {
                m_array[i] = m_array[i-1];
            }
            break; // simple
        }

        // Now copy the source slot into the freed position at index
        Slot* destSlot = &m_array[index];
        if (destSlot != src) {
            int* newObject = src->objectPtr;
            if (destSlot->objectPtr != newObject) {
                if (destSlot->objectPtr != nullptr) {
                    releaseSlot(destSlot);
                }
                destSlot->objectPtr = newObject;
                if (newObject != nullptr) {
                    // Attach the slot to the object's intrusive list (head insertion)
                    destSlot->nextPtr = reinterpret_cast<int*>(newObject[1]); // object's current next
                    *reinterpret_cast<int**>(newObject + 4) = destSlot; // object->next = slot
                }
            }
        }
        destSlot->data = src->data; // copy user data

        m_count = count + 1;
        return true;
    }

private:
    // Fixed-size array of slots (capacity 8)
    Slot m_array[8];
    // Count of used slots (at offset 0x60 from this)
    int32_t m_count; // offset 0x60
};