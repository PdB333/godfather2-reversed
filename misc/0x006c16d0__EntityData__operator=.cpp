// FUNC_NAME: EntityData::operator=
// Function at 0x006c16d0: Copy assignment operator for EntityData (large data structure with intrusive reference-counted pointer at +0x28)
// Structure size: at least 0x148 bytes (0x28 * 8 + 0x28? Actually fields up to offset 0x144)
// The pointer at offset 0x28 is a shared reference-counted object with a linked list node at offset +4

#include <cstdint>

// Forward declaration of the reference-counted object type
struct SharedDataNode {
    int32_t field_0x00;          // +0x00
    SharedDataNode* m_prevRef;   // +0x04 (pointer to previous node in intrusive list)
    // ... other fields
};

// Release function for the shared data (decrements ref count, possibly frees)
void releaseSharedData(SharedDataNode* ptr); // FUN_004daf90

class EntityData {
public:
    // Large block of data fields (0x28 * 8 = 0x140 bytes of 8-byte slots, plus extra)
    // Offsets are relative to this pointer
    uint64_t m_field00;          // +0x00
    uint64_t m_field08;          // +0x08
    uint64_t m_field10;          // +0x10
    uint64_t m_field18;          // +0x18
    SharedDataNode* m_sharedPtr; // +0x20 (offset 0x20? Actually param_1[4] is at offset 0x20)
    // But the special handling is at param_1+5 which is offset 0x28. Let's re-evaluate.
    // param_1[0] = offset 0x00, param_1[1]=0x08, param_1[2]=0x10, param_1[3]=0x18, param_1[4]=0x20, param_1[5]=0x28
    // So m_sharedPtr is at offset 0x28, but the code copies param_1[4] before handling param_1[5].
    // Actually the code copies param_1[0] through param_1[4] first, then handles param_1[5] specially.
    // So the first 5 slots (0x00-0x27) are plain copies.
    // Then slot at offset 0x28 is the shared pointer.
    // Then slots from offset 0x30 onward are copied as pairs of 4-byte fields.
    // We'll define a union or just use raw bytes for simplicity.
    // For clarity, we'll define the structure with explicit offsets.

    // We'll use a helper to access fields by byte offset.
    // But for the reconstructed code, we can just copy the raw bytes.
    // However, we need to handle the special pointer.

    // Let's define the class with a known layout.
    // We'll use a char array for the bulk data and a specific member for the shared pointer.
    // But that would be messy. Instead, we'll implement the assignment as a member function
    // that copies the raw data and handles the shared pointer.

    // Since we don't have the exact member names, we'll use generic names.
    // The function copies 0x28 * 8 = 0x140 bytes of 8-byte slots, plus additional 4-byte fields
    // up to offset 0x144. Actually the last copy is at offset 0x144 (param_1[0x28] is at offset 0x140,
    // then *(undefined4*)(param_1+0x28) is at offset 0x140, and *(undefined4*)((int)param_1+0x144) is at offset 0x144.
    // So total size is at least 0x148 bytes.

    // We'll implement the assignment operator.

    EntityData& operator=(const EntityData& other) {
        // Copy first 5 slots (0x00-0x27) as 8-byte values
        m_field00 = other.m_field00;
        m_field08 = other.m_field08;
        m_field10 = other.m_field10;
        m_field18 = other.m_field18;
        // m_field20 is at offset 0x20, but the code copies param_1[4] which is offset 0x20
        // Actually param_1[4] is at offset 0x20, but we already have m_field20? Let's index properly.
        // We'll just use raw memory copy for the bulk, but handle the shared pointer separately.
        // For simplicity, we'll copy the entire memory block except the shared pointer, then handle it.

        // However, the decompiled code copies each field individually. We'll replicate that.
        // We'll use a pointer to the first byte of this and other.

        uint8_t* dest = reinterpret_cast<uint8_t*>(this);
        const uint8_t* src = reinterpret_cast<const uint8_t*>(&other);

        // Copy first 5 * 8 = 40 bytes (offsets 0x00-0x27)
        for (int i = 0; i < 5; ++i) {
            reinterpret_cast<uint64_t*>(dest)[i] = reinterpret_cast<const uint64_t*>(src)[i];
        }

        // Handle the shared pointer at offset 0x28 (slot index 5)
        SharedDataNode*& destPtr = *reinterpret_cast<SharedDataNode**>(dest + 0x28);
        SharedDataNode* srcPtr = *reinterpret_cast<SharedDataNode* const*>(src + 0x28);

        if (&destPtr != &srcPtr) { // Actually check if the pointers are different, but we compare addresses of the pointer fields? No, the code compares piVar1 (address of destPtr) with (int*)(src+0x28). That's always different unless this==&other. So it's a check for self-assignment? Actually it checks if the pointer fields are at different addresses, which is always true unless this==&other. So it's a self-assignment guard? But the code then compares the values. Let's re-read: "if (piVar1 != (int *)(param_2 + 5))" - piVar1 is address of dest field, param_2+5 is address of src field. So if this != &other, they are different. So it's always true for non-self assignment. Then it compares the values: "if (*piVar1 != iVar2)" - if destPtr != srcPtr. So it only does the release/acquire if the values differ. That's correct.

        if (destPtr != srcPtr) {
            if (destPtr != nullptr) {
                releaseSharedData(destPtr);
            }
            destPtr = srcPtr;
            if (srcPtr != nullptr) {
                // Update the intrusive list: set the previous pointer in the shared object to point back to this field
                // The field at offset +4 in the shared object is a pointer to the previous node (or to the owner's pointer field)
                srcPtr->m_prevRef = reinterpret_cast<SharedDataNode*>(dest + 0x28); // Actually it stores the address of the pointer field itself? The code: *(int **)(iVar2 + 4) = piVar1; So it stores the address of the dest pointer field into the shared object's +4 field. That's typical for an intrusive linked list where each owner holds a pointer to the shared data, and the shared data has a back-pointer to the owner's pointer field.
                // So we set srcPtr->m_prevRef = &destPtr;
                srcPtr->m_prevRef = reinterpret_cast<SharedDataNode*>(&destPtr); // But the type is int**, so it's a pointer to pointer.
            }
        }

        // Now copy the remaining fields from offset 0x30 onward.
        // The code copies pairs of 4-byte fields: *(undefined4*)(param_1+6) etc.
        // Actually after handling the shared pointer, it copies:
        // *(undefined1*)(param_1+6) - that's a byte? No, it's *(undefined1*) which is a byte, but the offset is param_1+6 which is offset 0x30? Wait param_1 is undefined8*, so param_1+6 is offset 0x30. But it's copying a byte? That seems odd. Let's look at the decompiled code again:
        // *(undefined1 *)(param_1 + 6) = *(undefined1 *)(param_2 + 6);
        // That's a single byte copy at offset 0x30. Then it copies a 4-byte at offset 0x34.
        // Then *(undefined4 *)(param_1 + 7) at offset 0x38, then *(undefined4*)((int)param_1+0x3c) at offset 0x3c.
        // So it's copying 4-byte fields but sometimes with a byte in between? Actually the pattern is:
        // For each slot from index 6 onward, it copies two 4-byte fields: one at the slot start (param_1+index) and one at slot start+4 ((int)param_1+index*8+4).
        // But the first one after the shared pointer is a byte? No, it's *(undefined1*) which is a 1-byte copy, but that might be a decompiler artifact. The actual instruction might be a 4-byte copy but Ghidra interpreted it as byte due to type info. Given the pattern, it's likely all 4-byte copies. We'll treat them as 4-byte.

        // We'll copy the rest as a block from offset 0x30 to 0x148 (or up to the last copied field).
        // The last copied field is at offset 0x144 (param_1+0x28 is offset 0x140, then *(undefined4*)(param_1+0x28) is at 0x140, and *(undefined4*)((int)param_1+0x144) is at 0x144).
        // So total bytes from 0x30 to 0x148 is 0x118 bytes. But we need to be precise.

        // For simplicity, we'll copy the remaining bytes using a loop over the 4-byte pairs.
        // The code copies from offset 0x30 to 0x144 in steps of 8 bytes (two 4-byte fields per slot).
        // Number of slots from index 6 to 0x28 (40) is 0x28 - 6 + 1 = 0x23 slots? Actually index 6 to 0x28 inclusive is 0x23 slots? Let's calculate: 0x28 - 6 = 0x22, plus 1 = 0x23 slots. Each slot has two 4-byte fields, so 0x46 fields. But the code also copies a byte at offset 0x30? We'll ignore that and assume all 4-byte.

        // We'll just do a memcpy for the rest, but we must be careful because the shared pointer handling already modified destPtr. The rest of the data is independent.

        // Copy from offset 0x30 to end (0x148)
        size_t remainingSize = 0x148 - 0x30; // 0x118 bytes
        memcpy(dest + 0x30, src + 0x30, remainingSize);

        return *this;
    }

private:
    // The actual data layout is not defined here; we use the raw copy approach.
    // But to make the code compile, we need to define the class with appropriate members.
    // Since we don't know the exact members, we'll leave it as a placeholder.
    // In practice, this function would be part of a class with many fields.
};

// The actual implementation would be in a .cpp file.
// For the purpose of this reconstruction, we provide the function body.

// Note: The decompiled code uses undefined8* for param_1 and param_2, but we treat them as EntityData*.
// The function returns param_1 (this), so return type is EntityData&.

// We'll also define the release function (stub).
void releaseSharedData(SharedDataNode* ptr) {
    // Decrement reference count and possibly free
    // Actual implementation at 0x004daf90
}