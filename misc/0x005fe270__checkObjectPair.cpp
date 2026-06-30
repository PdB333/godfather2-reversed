// FUNC_NAME: checkObjectPair
// Address: 0x005fe270
// Role: Checks if a given pair of object pointers (objA, objB) matches one of two stored pairs in the current object.
// Returns: -3 if objB has a disabled flag and ignoreFlag is false, -2 if matches first pair, -1 if matches second pair, 0 otherwise.
// Inputs: objA (EDI), objB (ESI) passed via registers; ignoreFlag (param_1) as a char; self (EAX) is the implicit this pointer.

// Offsets used:
//   objB+0x18: flag field (ushort) – bit 0x4000 indicates disabled
//   self+0xb4: bitfield (uint) – bit 1 disables the pair check
//   self+0x7c: first object pointer (Entity*)
//   self+0x84: first associated value/pointer (int) – used as comparison for objB if self+0x7c non-null, else 0
//   self+0x70: second object pointer (Entity*)
//   self+0x78: second associated value/pointer (int) – similar logic

int __thiscall checkObjectPair()
{
    // Note: this function is __thiscall, with this in EAX.
    // Additional inputs are passed in registers:
    //   in_EAX = this pointer (self)
    //   unaff_EDI = objA (Entity*)
    //   unaff_ESI = objB (Entity*)
    //   param_1 = ignoreFlag (char, on stack/ECX)

    // In the actual implementation, these are register variables.
    // We'll simulate with local variables for clarity.
    Entity* objA;       // from unaff_EDI
    Entity* objB;       // from unaff_ESI
    char ignoreFlag;    // from param_1

    // Check if objB has the "disabled" flag and the caller hasn't requested to ignore it.
    if ((objB->flags & 0x4000) && (ignoreFlag == 0)) {
        return -3; // Disabled
    }

    // Check if the pair comparison is disabled in this object.
    if ((self->field_b4 >> 1) & 1) {
        return 0; // No match, comparison disabled
    }

    int firstAssociatedValue; // used for comparison with objB
    // First pair: self->field_7c is the first entity pointer, self->field_84 is an associated integer/pointer
    if (self->firstEntity == 0) {
        firstAssociatedValue = 0;
    } else {
        firstAssociatedValue = self->firstValue;
    }
    if ((objA == self->firstEntity) && (objB == firstAssociatedValue)) {
        return -2; // Matched the first pair
    }

    int secondAssociatedValue;
    // Second pair: self->field_70 and self->field_78
    if (self->secondEntity == 0) {
        secondAssociatedValue = 0;
    } else {
        secondAssociatedValue = self->secondValue;
    }
    if ((objA == self->secondEntity) && (objB == secondAssociatedValue)) {
        return -1; // Matched the second pair
    }

    return 0; // No match
}