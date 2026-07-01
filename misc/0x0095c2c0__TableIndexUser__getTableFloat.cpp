// FUNC_NAME: TableIndexUser::getTableFloat
// Address: 0x0095c2c0
// Role: Retrieves a float from a global lookup table using an index stored in the object at offset 0x20.

class TableIndexUser {
public:
    int m_tableIndex; // +0x20 - Index into the global float table
    float getTableFloat() const;
};

extern float s_floatTable[]; // DAT_00d8cc90

float __thiscall TableIndexUser::getTableFloat() const {
    return s_floatTable[this->m_tableIndex];
}