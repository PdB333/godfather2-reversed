// FUNC_NAME: Handle::compareWithFlag
uint32 __thiscall Handle::compareWithFlag(int* thisOther1, int* other) // thisOther1 is actually this? Actually param_1 is first arg, but __thiscall implies ecx is this. We'll treat param_1 as this.
{
    // Offset 0: primaryID (int)
    // Offset 4: secondaryID (int)
    // Assert that primaryID is non-zero and equal between objects
    if ((thisOther1[0] == 0) || (thisOther1[0] != other[0])) {
        assertionFailure(); // FUN_00b97aea - likely debug assert
    }
    // Return combination: upper 24 bits of this's secondaryID OR'd with equality flag of secondaryID
    return (thisOther1[1] & 0xFFFFFF00) | ((thisOther1[1] == other[1]) ? 1 : 0);
}