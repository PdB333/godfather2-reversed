// FUNC_NAME: SomeClass::getConditionalValue
// Address: 0x00504190
// Role: Returns a value from an internal data structure if a flag is set; otherwise returns 0.
// Structure offsets:
//   this+0x4: pointer to internal data (m_pData)
//   m_pData+0xC: some identifier (e.g., resource ID or index)

typedef int (*HelperFunc)(void* obj, int id); // assumed signature of FUN_00504fc0

class SomeClass {
public:
    int __thiscall getConditionalValue(bool flag) {
        if (flag) {
            // Call helper function with this and the value at internal data offset 0xC
            return helperFunc(this, m_pData->field_0x0C);
        }
        return 0;
    }

private:
    struct InternalData {
        int field_0x00;      // +0x00: unknown
        int field_0x04;      // +0x04: unknown
        int field_0x08;      // +0x08: unknown
        int field_0x0C;      // +0x0C: the value used in the call
    }* m_pData;              // +0x04

    static HelperFunc helperFunc; // points to FUN_00504fc0
};