// Xbox PDB: AptString::GetHash
// FUNC_NAME: AptValue::getHash
// Function address: 0x005ba580
// Role: Lazily computes and caches a hash value for an AptValue object.

#include <cassert>

class AptValue {
public:
    static const int BOGUS_HASH_VALUE = -0x41103114; // 0xBEEFCEEC

    int __thiscall getHash() {
        // +0x20: m_hash
        if (m_hash == BOGUS_HASH_VALUE) {
            int computed = computeHash(); // FUN_005b87d0 : calculates real hash
            m_hash = computed;
            if (computed == BOGUS_HASH_VALUE) {
                // assert failure: hash should never remain BOGUS after computation
                assertMsg("hashVal != BOGUS_HASH_VALUE",
                          "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h",
                          0x34f, 2, &DAT_0112915c); // FUN_0059bf00
            }
        }
        return m_hash;
    }

private:
    int computeHash(); // defined elsewhere, likely calculates string/int hash
    int m_hash; // +0x20
};