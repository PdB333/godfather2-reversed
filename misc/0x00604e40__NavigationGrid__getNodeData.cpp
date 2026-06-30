// FUNC_NAME: NavigationGrid::getNodeData
int NavigationGrid::getNodeData(int index, int subIndex) {
    // +0x8: pointer to an array of node structures (each 12 bytes)
    char* nodeArray = *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 8);
    // +0x8 within each node: an integer base value
    int base = *reinterpret_cast<int*>(nodeArray + index * 12 + 8);
    // +0xC: pointer to a data array (each element 16 bytes)
    int dataBase = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 12);
    return (base + subIndex) * 16 + dataBase;
}