// FUNC_NAME: Entity::compareIDAndReturnPacked
// Address: 0x006229f0
// This member function validates that both objects are of the same type (non‑zero mTypeID)
// and returns a packed 32‑bit value combining the upper 24 bits of mObjectID with
// a boolean flag indicating equality of the two mObjectID fields.
// If validation fails, it calls an assertion/debug function.

class Entity {
public:
    int mTypeID;       // +0x00 – non‑zero type identifier; must match for comparison
    int mObjectID;     // +0x04 – unique object ID (full 32‑bit value)

    // __thiscall: this in ECX, other in EDX? Actually unaff_EDI = this, unaff_ESI = &other
    int compareIDAndReturnPacked(const Entity& other) const {
        // Validate that both objects have a valid type and that the types match.
        if (mTypeID == 0 || mTypeID != other.mTypeID) {
            // Debug assertion / error handler (could be __debugbreak or abort)
            FUN_00b97aea();  // likely assert failure
        }

        // Pack result: high 24 bits = mObjectID >> 8 (upper three bytes),
        // low byte = 1 if mObjectID == other.mObjectID, else 0.
        return (int)((uint)mObjectID >> 8) << 8 | (int)(mObjectID == other.mObjectID);
        // Equivalent to: CONCAT31((int3)((uint)unaff_EDI[1] >> 8), unaff_EDI[1] == unaff_ESI[1])
    }
};