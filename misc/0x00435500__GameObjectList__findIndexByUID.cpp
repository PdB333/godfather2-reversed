// FUNC_NAME: GameObjectList::findIndexByUID
int GameObjectList::findIndexByUID(uint uid, int count) {
    int low = -1;
    int high = count;
    int mid;
    int index;
    
    if (count != 0) {
        do {
            mid = (high + low) >> 1;
            index = mid;
            // array is an 8-byte element array at this+0x? 
            // First uint of each element is the UID.
            if (array[mid].uid < uid) {
                index = high;
            }
            high = index;
        } while (low + 1 != index);
        
        if (index < count && array[index].uid == uid) {
            return index;
        }
    }
    return -1;
}