// FUNC_NAME: spawnRandomScaledPair
void spawnRandomScaledPair(uint parent1, uint parent2, uint template1, uint template2, int baseValue)
{
    uint index;
    int object;
    uint handle;
    int scaledValue;
    int local_40;

    // Get some global handle or state (maybe a random seed or a manager)
    handle = getSomeHandle();

    // Compute index into scaling factor table using a bitmask and incrementing counter
    index = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;

    // Scale the base value by a random factor from the table and round to integer
    scaledValue = (int)(float)((float)baseValue * *(float *)(&DAT_010c2680 + index * 4));
    local_40 = scaledValue;

    // Create first object from template1 with the scaled attribute
    object = createObjectWithAttribute(template1, &local_40);
    if (object != 0) {
        attachObjectToParent(object, parent1);
    }

    // Get another handle (maybe for a different context)
    handle = getSomeHandle();

    // Create second object from template2 with the handle (not scaled value)
    object = createObjectWithAttribute(template2, handle);
    if (object != 0) {
        attachObjectToParent(object, parent2);
    }
}