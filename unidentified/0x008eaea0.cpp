// Func at 0x008eaea0: SomeObject::validateAndReturnToken
// Validates two object pointers and returns a combined token from second field.
// Checks that both objects have same first field (non-null). Returns second field with low byte replaced by inequality flag (1 if second fields differ, else 0).

class SomeObject {
public:
    int field0;  // offset 0x00: first field (type ID or pointer)
    int field4;  // offset 0x04: second field (packed data)
    
public:
    // __thiscall at 0x008eaea0
    int validateAndReturnToken(const SomeObject& other) const {
        // Assert that this is valid and types match
        if (field0 == 0 || field0 != other.field0) {
            FUN_00b97aea();  // assertionFailed() or handleError()
        }
        // Return field4 with low byte cleared, replaced by 1 if second fields differ
        return (field4 & 0xFFFFFF00) | ((field4 != other.field4) ? 1 : 0);
    }
};