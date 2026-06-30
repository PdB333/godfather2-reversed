// FUNC_NAME: VFX::setRandomAttributes
void VFX::setRandomAttributes(void)
{
    // Generate four random sums from pairs of random ints, and zero the next two fields.
    // This likely initializes per-particle random offsets (e.g., velocity, color, scale, etc.)
    int random1 = getRandomInt();  // FUN_00676010
    int random2 = getRandomInt();
    *(int *)(this + 0xe0) = random1 + random2;

    random1 = getRandomInt();
    random2 = getRandomInt();
    *(int *)(this + 0xe4) = random1 + random2;

    random1 = getRandomInt();
    random2 = getRandomInt();
    *(int *)(this + 0xe8) = random1 + random2;

    random1 = getRandomInt();
    random2 = getRandomInt();
    *(int *)(this + 0xec) = random1 + random2;

    // Zero remaining fields
    *(int *)(this + 0xf0) = 0;
    *(int *)(this + 0xf4) = 0;
}