// FUNC_NAME: GameObjectPair::getTransformDataPair
// Address: 0x005540a0
// Reconstructed from Ghidra decompiled output for The Godfather 2 (2008, x86 EARS engine)
// Assumes __thiscall with two object pointers: this (in EAX) and pOther (in ESI)

struct TransformData {
    float m_data[4]; // 16 bytes (quaternion or 4D vector)
};

struct InternalData {
    int m_relativeOffset; // +0x10: relative pointer (e.g., offset from 'this' to actual data)
    bool m_flag;         // +0x18: activation flag (0 or 1)
    // Possibly other fields omitted for brevity
};

struct GameObject {
    InternalData* m_pData; // +0x28: pointer to internal data structure
};

// Forward declaration of helper function (likely fills TransformData from given object)
extern void GetTransformData(GameObject* pObj, TransformData* pOut);

void __thiscall GameObjectPair::getTransformDataPair(GameObject* pOther) {
    TransformData data1;   // local_30 (16 bytes, zero-initialized)
    TransformData data2;   // local_20 (16 bytes, zero-initialized)
    InternalData* pInternal1;
    InternalData* pInternal2;

    // Process first object (this)
    pInternal1 = this->m_pData; // +0x28
    // Zero the local buffer (represented by zeroing 4 consecutive ints, but we use struct init)
    data1 = {0.0f, 0.0f, 0.0f, 0.0f};

    if (pInternal1 != nullptr) {
        bool flag = pInternal1->m_flag; // +0x18
        // Dereference relative offset: the actual data pointer is (base + relativeOffset)
        void* actualPtr = reinterpret_cast<char*>(pInternal1) + pInternal1->m_relativeOffset; // +0x10
        if (flag && actualPtr != nullptr) {
            GetTransformData(this, &data1);
        }
    }

    // Process second object (pOther)
    pInternal2 = pOther->m_pData; // +0x28
    data2 = {0.0f, 0.0f, 0.0f, 0.0f};

    if (pInternal2 != nullptr) {
        bool flag = pInternal2->m_flag; // +0x18
        void* actualPtr = reinterpret_cast<char*>(pInternal2) + pInternal2->m_relativeOffset; // +0x10
        if (flag && actualPtr != nullptr) {
            GetTransformData(pOther, &data2);
        }
    }

    // After function, data1 and data2 are available in local variables but are not used further in this function.
    // The caller(s) at 0x00554200 and 0x00554270 may use these stack values.
}