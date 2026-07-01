// FUNC_NAME: GenericList::getNextItem
int __fastcall GenericList::getNextItem(int *list) {
    if (*list == 0) {
        FUN_00b97aea(); // assert or error handler
    }
    if (list[1] == *(int *)(*list + 4)) {
        FUN_00b97aea(); // assert or error handler
    }
    return list[1] + 0xc; // return pointer to next item data (+0x0C offset from node)
}