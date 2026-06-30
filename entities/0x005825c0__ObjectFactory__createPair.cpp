// FUNC_NAME: ObjectFactory::createPair
int* ObjectFactory::createPair() {
    int id = GetNextUniqueId(); // FUN_004dafd0 - likely generates unique identifier
    int flags = 0;
    int* pair = (int*)this->allocate(8, &flags); // virtual allocation: size=8, flags=0
    if (pair) {
        pair[0] = id;
        pair[1] = 0; // second field unused, always zero
    }
    return pair;
}