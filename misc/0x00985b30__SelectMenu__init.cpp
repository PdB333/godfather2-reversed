// FUNC_NAME: SelectMenu::init
void __fastcall SelectMenu::init(int this)
{
    char enabled;
    int itemState;
    undefined *text;
    undefined4 *menuItem;
    uint firstFreeIndex;
    uint index;
    undefined *localString;
    int stringLen;
    uint flags;
    code *callback;

    localString = DAT_01130378; // global string allocator
    stringLen = 0;
    flags = flags & 0xffffff00; // clear low byte
    constructString(&localString, 0); // initialize string

    firstFreeIndex = 0xffffffff;
    index = 0;
    if (*(int *)(this + 0x50) != 0) { // if menu item count > 0
        menuItem = &DAT_00e57600; // base of menu item definitions
        do {
            itemState = 2;
            switch(*menuItem) { // first int: item type
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
                itemState = 0; // visible/enabled
                break;
            case 4:
                itemState = 1; // disabled?
                // check if feature is available (global flags)
                if ((*(int *)(DAT_01129828 + 0xc) == 0) &&
                    ((~(byte)(*(uint *)(DAT_01129828 + 0x10) >> 7) & 1) != 0)) {
                    itemState = 0; // override to visible
                }
            }
            menuItem[2] = itemState; // store state at offset +8
            if ((firstFreeIndex == 0xffffffff) && (itemState == 0)) {
                firstFreeIndex = index; // remember first visible index
            }
            index++;
            menuItem = menuItem + 3; // next item (12 bytes stride)
        } while (index < *(uint *)(this + 0x50));
    }

    // set initial selected index if not set and we found a visible item
    if ((*(int *)(this + 100) == -1) && (firstFreeIndex != 0xffffffff)) {
        *(uint *)(this + 100) = firstFreeIndex;
    }

    sendUIMessage("InitSelectMenu", 0, &DAT_00d873d4, 0); // trigger UI initialization
    localString = NULL;
    stringLen = 0;
    flags = 0;
    callback = NULL;
    enabled = getSelectedMenuItemText(&localString); // get text for currently selected item
    text = PTR_DAT_00e575fc; // default text pointer
    if (((enabled != '\0') && (stringLen != 0)) && (text = localString, localString == NULL)) {
        text = &DAT_0120546e; // fallback empty string?
    }
    *(undefined **)(this + 0x5c) = text; // set text pointer
    sendUIMessage("UpdateTrickleText", 0, &DAT_00d873d4, 0); // update UI text display
    *(undefined **)(this + 0x5c) = PTR_DAT_00e575fc; // reset to default? (or store final pointer?)

    if (localString != NULL) {
        (*callback)(localString); // free allocated string?
    }
}