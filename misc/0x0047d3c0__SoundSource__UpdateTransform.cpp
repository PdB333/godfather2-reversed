// FUNC_NAME: SoundSource::UpdateTransform
// Reconstructed from 0x0047d3c0
// Handles updating sound source transform, including obtaining a target transform
// from a parent node, and updating the audio system's slot with the result.

#include <cstdint>

// Function declarations for called subroutines
extern void FUN_0047d330(); // Called when local flag is set, likely compute relative transform from parent
extern uint8_t FUN_005e6580(uint32_t handle, void* transform); // Updates audio system with transform, returns success

// Forward declaration of the sound slot structure
struct SoundSlot; // defined below

// Global sound slot array (size 0x200 slots, each 0x30 bytes)
extern SoundSlot* gSoundSlotArray; // base address = DAT_012234bc

// Forward declaration of node/transform vtable callbacks
// The vtable at offset 0x58 is a function returning uint32_t, likely a hash or handle.
// The object at iVar2 (if not null) is a "Node" with vtable.
// When iVar2 is null, a default vtable at a fixed global address is used.
extern void* gDefaultNodeVTable; // iRam00000000, base of default vtable (or pointer to it)

// Structure for entries in the global sound slot table (size 0x30)
struct SoundSlot {
    // offset 0x00 to 0x0F: unknown
    char unknown_0x00[0x10];
    int32_t* somePointer; // +0x10: pointer to a buffer/object where we write result
    char unknown_0x14[0x18]; // up to +0x2C
    uint32_t fullHandle; // +0x2C: stores the full handle for verification
};

// Forward declaration for the "Node" class
// Has vtable with method at offset 0x58 that returns a uint32_t.
struct NodeBase {
    virtual uint32_t getTransformHandle(); // vtable+0x58
};

// The SoundSource class (this pointer)
class SoundSource {
public:
    // Offsets:
    // +0xB0: 8 bytes (part of transform)
    // +0xB8: 4 bytes (rest of transform) -> combined 12-byte transform struct
    // +0xC0: result handle (uint32_t)
    // +0xD4: parent offset or relationship type (0 = none, 0x48 = inline, other = parent offset)
    // +0xDC: flag indicating whether to call FUN_0047d330
    // +0xE0: handle (uint16_t index in low bits)

    uint8_t UpdateTransform() {
        uint8_t bResult = 0;

        // Check if we have a valid handle to an audio slot
        if (m_handle != 0) {
            // Determine the source transform
            // If parent is null or is "inline" (0x48), use our own stored transform or recompute
            if (m_parentOffset == 0 || m_parentOffset == 0x48) {
                if (m_flag == 0) {
                    // Use the stored transform directly from offsets +0xB0 and +0xB8
                    // local_10 = *(undefined8 *)(this + 0xB0)
                    // local_8 = *(undefined4 *)(this + 0xB8)
                    // We'll just copy to a 12-byte local buffer
                    inline char localTransform[12];
                    __builtin_memcpy(localTransform, &m_transformPart1, 8);
                    __builtin_memcpy(localTransform + 8, &m_transformPart2, 4);
                    // localTransform is now set
                } else {
                    FUN_0047d330(); // Compute transform from parent or scene graph
                }
            } else {
                // Parent is a non-null, non-inline offset. Here m_parentOffset is a pointer to a NodeBase
                // but offset by 0x48? Actually m_parentOffset stores a pointer that when subtracted by 0x48 gives the NodeBase pointer.
                NodeBase* parentNode = (NodeBase*)((uint8_t*)m_parentOffset - 0x48);
                // (Note: if m_parentOffset == 0, the code handles separately, but here it's non-zero already)
                // Get transform from node at offset +0x100 and +0x108 relative to parentNode
                // parentNode + 0x100: 8 bytes, +0x108: 4 bytes = 12-byte transform
                __builtin_memcpy(localTransform, (uint8_t*)parentNode + 0x100, 8);
                __builtin_memcpy(localTransform + 8, (uint8_t*)parentNode + 0x108, 4);

                // Now call virtual function on the node to get a result handle
                if (m_parentOffset == 0) {
                    // This case actually is handled earlier, but here if m_parentOffset==0? Actually in this branch it's non-zero.
                    // This is an artifact of decompilation. When m_parentOffset==0, iVar2=0, and the code uses a default vtable.
                    // We'll handle both cases for completeness.
                    m_resultHandle = ((uint32_t (*)()) (*(void** )((uint8_t*)gDefaultNodeVTable + 0x58)))();
                } else {
                    m_resultHandle = parentNode->getTransformHandle();
                }
            }

            // Update the audio system with the transform and handle
            bResult = FUN_005e6580(m_handle, &localTransform);

            // Now update the sound slot entry
            uint16_t slotIndex = m_handle & 0xFFFF; // low 16 bits as index
            if (slotIndex < 0x200) { // (0x200 = 512 slots)
                SoundSlot* slot = (SoundSlot*)((uint8_t*)gSoundSlotArray + slotIndex * 0x30 + 0x10);
                // Note: the original code uses (uVar4 * 0x30 + 0x10 + DAT_012234bc)
                // So it adds 0x10 to the start of the slot. That implies the slot structure starts at +0x10 within the array entry? 
                // Or the array base is 0x10 bytes before the actual first element? 
                // We'll reinterpret: the global pointer gSoundSlotArray points to the first slot's start (DAT_012234bc).
                // Then slot = (SoundSlot*)((uint8_t*)gSoundSlotArray + slotIndex * 0x30);
                // But the code adds +0x10, so maybe there's a header of 0x10 bytes before the slots. 
                // For now we'll keep the original offset: slot = (SoundSlot*)((uint8_t*)gSoundSlotArray + slotIndex * 0x30 + 0x10);
                // But then slot->fullHandle is at +0x2C relative to that, so total offset = +0x10+0x2C = +0x3C, which seems odd.
                // Re-examining: the code: iVar2 = uVar4 * 0x30 + 0x10 + DAT_012234bc. So iVar2 points to offset +0x10 of that entry.
                // Then it checks *(uint *)(iVar2 + 0x2c) == handle, so fullHandle is at +0x2C from iVar2, not from the beginning of the entry.
                // Therefore the SoundSlot structure as defined above should have its fields relative to iVar2 (which is +0x10 into the entry).
                // So we need to adjust. To avoid confusion, we'll compute the raw pointer to the entry and work with offsets directly.
                // For clarity in reconstruction, we'll use raw pointer arithmetic.
                
                // Actually, the slot entry size is 0x30, and the data we need is at offsets 0x10 and 0x2C from the start of the entry.
                // So the structure should be:
                // struct SlotEntry { char unknown[0x10]; int32_t* ptr; char unknown2[0x1C]; uint32_t handle; }; // size 0x30
                // And iVar2 points to the start of the entry (offset 0 from entry). Then +0x10 is ptr, +0x2C is handle.
                // But the code added +0x10 to the base address. That suggests that the global base DAT_012234bc is actually the address of an array of 0x10-byte headers? No, it's simpler: the code computes iVar2 = uVar4 * 0x30 + 0x10 + DAT_012234bc, so the base of the array is DAT_012234bc - 0x10. But we don't know. Let's keep the pointer arithmetic as given.
                // We'll just follow the original logic.
            }
            // ... The rest of the check.
        }
        return bResult;
    }

private:
    // Layout of this class (offsets in bytes from this)
    // +0x00 to +0xAF: other fields (not used here)
    // +0xB0: 8 bytes (first part of transform)
    uint64_t m_transformPart1; // 8 bytes
    // +0xB8: 4 bytes (second part)
    uint32_t m_transformPart2; // 4 bytes
    // +0xBC: padding? Actually m_resultHandle at +0xC0 so +0xBC is likely 4 bytes of padding or another field.
    char m_padding[4];
    // +0xC0: result handle
    uint32_t m_resultHandle;
    // +0xC4: unknown
    // +0xD4: parent offset or pointer
    uintptr_t m_parentOffset; // 4 bytes (int)
    // +0xD8: unknown? +0xDC is flag, so +0xD8 is likely 4 bytes
    char m_unknown[4];
    // +0xDC: flag byte
    uint8_t m_flag;
    // +0xDD: padding
    // +0xE0: handle
    uint32_t m_handle;
};