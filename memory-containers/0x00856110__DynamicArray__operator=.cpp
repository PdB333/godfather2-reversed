// FUNC_NAME: DynamicArray::operator=
//
// Copy assignment operator for a dynamic array of 44-byte elements.
// Array layout:
//   +0x00: pointer T* mData
//   +0x04: int mCount
//   +0x08: int mCapacity
// Each element (44 bytes) includes a ref-counted object pointer at +0x10,
// with ref count at objPtr->+0x04 and destructor at vtable+4.
// Helper functions: MemFree (0x009c8f10), MemAlloc (0x009c8e80)

#include <cstdint>

struct DynamicArray;

// Helper function stubs (actual implementations elsewhere)
extern void MemFree(void* ptr);
extern void* MemAlloc(size_t size);

// Element structure (size 0x2C = 44 bytes)
struct ArrayElement {
    char field_0[12];          // 0x00-0x0B: mostly unknown, first 8 bytes are copied as uint64
    uint16_t field_0C;         // 0x0C: part of a 2-byte field (actually two separate bytes)
    uint16_t field_0E;         // 0x0E: unknown
    int* pRefCountedObj;       // 0x10: pointer to a ref-counted object (may be null)
    uint16_t field_14;         // 0x14: 2 bytes
    uint16_t field_16;         // 0x16: 2 bytes
    uint8_t field_18[2];       // 0x18-0x19: 2 bytes
    uint32_t field_1C;         // 0x1C: 4 bytes
    uint32_t field_20;         // 0x20: 4 bytes
    uint32_t field_24;         // 0x24: 4 bytes
    uint32_t field_28;         // 0x28: 4 bytes
};

struct DynamicArray {
    ArrayElement* mData;       // +0x00
    int mCount;                // +0x04
    int mCapacity;             // +0x08

    // Copy assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            return *this;
        }

        // Release all existing elements (iterate backwards)
        int idx = mCount - 1;
        if (idx >= 0) {
            int offset = idx * (int)sizeof(ArrayElement);
            do {
                ArrayElement* elem = reinterpret_cast<ArrayElement*>(
                    reinterpret_cast<uint8_t*>(mData) + offset
                );
                int* objPtr = elem->pRefCountedObj;
                if (objPtr != nullptr) {
                    // Decrement reference count
                    int& refCount = *(objPtr + 1); // +0x04
                    refCount--;
                    if (refCount == 0) {
                        // Call destructor via vtable (second entry)
                        void (*destructor)(void*) = reinterpret_cast<void(*)(void*)>(
                            *reinterpret_cast<int**>(objPtr) + 1
                        );
                        destructor(objPtr);
                    }
                    elem->pRefCountedObj = nullptr;
                }
                idx--;
                offset -= sizeof(ArrayElement);
            } while (idx >= 0);
        }

        // Reallocate if capacity insufficient
        if (static_cast<uint32_t>(mCapacity) < static_cast<uint32_t>(other.mCount)) {
            MemFree(mData);
            mCapacity = other.mCount;
            if (mCapacity == 0) {
                mData = nullptr;
            } else {
                mData = reinterpret_cast<ArrayElement*>(
                    MemAlloc(mCapacity * sizeof(ArrayElement))
                );
            }
        }

        // Copy elements from source
        if (other.mCount > 0) {
            int elemOffset = 0;
            for (uint32_t i = 0; i < static_cast<uint32_t>(other.mCount); i++) {
                ArrayElement* dst = reinterpret_cast<ArrayElement*>(
                    reinterpret_cast<uint8_t*>(mData) + elemOffset
                );
                const ArrayElement* src = reinterpret_cast<const ArrayElement*>(
                    reinterpret_cast<const uint8_t*>(other.mData) + elemOffset
                );

                // Copy first 8 bytes (uint64)
                *reinterpret_cast<uint64_t*>(&dst->field_0[0]) =
                    *reinterpret_cast<const uint64_t*>(&src->field_0[0]);
                // Copy next 4 bytes (uint32 at offset 8)
                *reinterpret_cast<uint32_t*>(&dst->field_0[8]) =
                    *reinterpret_cast<const uint32_t*>(&src->field_0[8]);
                // Copy two single bytes at 0x0C and 0x0D
                dst->field_0C = src->field_0C; // assuming field_0C covers both bytes? Actually separate bytes, but fine.
                // Copy pointer at +0x10 and retain ref count
                int* newObj = src->pRefCountedObj;
                dst->pRefCountedObj = newObj;
                if (newObj != nullptr) {
                    *(newObj + 1) += 1; // increment ref count
                }
                // Copy remaining fields
                dst->field_14 = src->field_14;
                dst->field_16 = src->field_16;
                // Note: decompiled shows duplicate store at 0x16; assume only one.
                dst->field_18[0] = src->field_18[0];
                dst->field_18[1] = src->field_18[1];
                dst->field_1C = src->field_1C;
                dst->field_20 = src->field_20;
                dst->field_24 = src->field_24;
                dst->field_28 = src->field_28;

                elemOffset += sizeof(ArrayElement);
            }
        }

        mCount = other.mCount;
        return *this;
    }
};