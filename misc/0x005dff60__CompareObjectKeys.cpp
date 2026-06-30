// FUNC_NAME: CompareObjectKeys
// Address: 0x005dff60
// Role: Compares two objects by their first field (type ID) and second field (key).  
// Returns a combined value: upper 24 bits from object A's second field, lower 8 bits = equality of second fields.
// Asserts that both objects have the same non-zero first field.

struct ObjectKey
{
    int m_typeId;    // +0x00
    int m_keyValue;  // +0x04
};

// __fastcall or __thiscall - registers ESI, EDI used for parameters
int CompareObjectKeys(const ObjectKey* objA, const ObjectKey* objB)
{
    // Assert: both objects must have a valid type ID, and they must match
    if (objB->m_typeId == 0 || objB->m_typeId != objA->m_typeId)
    {
        // Called when assertion fails - likely aborts or breaks
        FUN_00b97aea();
    }

    // Build result: upper 24 bits from objA's key value, low byte = 1 if key values match
    return (objA->m_keyValue & 0xFFFFFF00) | (objA->m_keyValue == objB->m_keyValue);
}