// FUNC_NAME: Destructible::initRandomParameters
void Destructible::initRandomParameters() {
    int rand1 = getRandomInt();  // FUN_00676010
    int rand2 = getRandomInt();
    this->mRandomOffsets[0] = rand1 + rand2; // +0xe0

    rand1 = getRandomInt();
    rand2 = getRandomInt();
    this->mRandomOffsets[1] = rand1 + rand2; // +0xe4

    rand1 = getRandomInt();
    rand2 = getRandomInt();
    this->mRandomOffsets[2] = rand1 + rand2; // +0xe8

    rand1 = getRandomInt();
    rand2 = getRandomInt();
    this->mRandomOffsets[3] = rand1 + rand2; // +0xec

    this->mFieldF0 = 0; // +0xf0
    this->mFieldF4 = 0; // +0xf4
}