// FUNC_NAME: HashEntry::isEqual
class HashEntry {
public:
    int m_hash;   // +0x00: hash value (0 = empty slot)
    int m_pad;    // +0x04: unused/padding
    int m_key;    // +0x08: actual key (only meaningful if hash != 0)

    // Equality check: two entries are equal if:
    // - hashes match, AND
    // - either both hashes are zero (empty slots) OR keys match
    bool __thiscall isEqual(const HashEntry& other) const
    {
        bool result = false;
        if (m_hash == other.m_hash && (m_hash == 0 || m_key == other.m_key)) {
            result = true;
        }
        return result;
    }
};