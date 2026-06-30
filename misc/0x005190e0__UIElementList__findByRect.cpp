// FUNC_NAME: UIElementList::findByRect
// Function at 0x005190e0
// Linear search for a UI element matching a given rectangle (x, y, width, height)
// Class offsets: this+0x08 = count, this+0x0C = array of pointers to elements
// Element offsets: +0x08 = x, +0x0C = y, +0x10 = width, +0x14 = height
int __thiscall UIElementList::findByRect(int key[4]) // key passed in ESI by caller, but modeled here as parameter
{
    int count = *(int*)(this + 0x08);
    if (count <= 0)
        return 0;

    int** items = *(int***)(this + 0x0C);
    for (int i = 0; i < count; i++)
    {
        int* element = items[i];
        if (key[0] == *(element + 0x08/4) && // x
            key[1] == *(element + 0x0C/4) && // y
            key[2] == *(element + 0x10/4) && // width
            key[3] == *(element + 0x14/4))   // height
        {
            return (int)items[i]; // return pointer to matching element
        }
    }
    return 0;
}