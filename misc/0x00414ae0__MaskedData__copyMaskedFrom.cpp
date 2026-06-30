// FUNC_NAME: MaskedData::copyMaskedFrom
class MaskedData {
public:
    // +0x00: uint field0
    // +0x04: uint field1
    // +0x08: uint field2
    void __thiscall copyMaskedFrom(const MaskedData& other) {
        // Apply global mask to each component
        uint mask = s_mask; // Global DAT_00e44680 mask
        this->field0 = other.field0 & mask;
        this->field1 = other.field1 & mask;
        this->field2 = other.field2 & mask;
    }

private:
    uint field0;
    uint field1;
    uint field2;

    // Global mask constant from DAT_00e44680
    static const uint s_mask = 0; // Actual value unknown; defined elsewhere
};