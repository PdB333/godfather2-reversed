// FUNC_NAME: AttributeMap::setFloatValue
class AttributeMap {
public:
    // +0x00: int m_count
    // +0x08: ParamEntry* m_entries  (array of size m_count+1, index 0 unused, id=0 invalid)
    struct ParamEntry {
        int id;      // +0x00
        float value; // +0x04
    };

    // __thiscall, paramId passed in EDI (unaff_EDI), newValue on stack
    void setFloatValue(int paramId, float newValue) {
        if (m_count == 0 || paramId == 0) {
            return;
        }

        // Search for the entry by ID (1-based indexing, skip index 0)
        int index = 1;
        while (index <= m_count) {
            if (m_entries[index].id == paramId) {
                break;
            }
            index++;
        }
        if (index > m_count) {
            // Not found; could assert or return (original code silently ignores)
            return;
        }

        float oldValue = m_entries[index].value;
        m_entries[index].value = newValue;

        // Notify direction of change
        if (newValue < oldValue) {
            onValueDecreased(paramId);  // calls FUN_005f8b00
        } else if (oldValue < newValue) {
            onValueIncreased(paramId);  // calls FUN_005f8b50
        }
    }

private:
    void onValueDecreased(int paramId); // FUN_005f8b00
    void onValueIncreased(int paramId); // FUN_005f8b50
};