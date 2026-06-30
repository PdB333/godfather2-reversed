// FUNC_NAME: sortByPredicate
void sortByPredicate(undefined4 *begin, undefined4 *end)
{
  undefined4 *i;
  char cVar2;
  undefined4 *j;
  undefined4 *k;
  undefined4 *pivot;
  
  if ((begin != end) && (i = begin + 1, i != end)) {
    j = begin + 2;
    do {
      cVar2 = FUN_00587780(*begin);
      if (cVar2 == '\0') {
        cVar2 = FUN_00587780(j[-2]);
        pivot = j + -2;
        if (cVar2 != '\0') {
          do {
            k = pivot;
            cVar2 = FUN_00587780(k[-1]);
            pivot = k + -1;
          } while (cVar2 != '\0');
          if ((k != i) && (i != j)) {
            FUN_00588e00(k,j);
          }
        }
      }
      else if ((begin != i) && (i != j)) {
        FUN_00588e00(begin,j);
      }
      i = i + 1;
      j = j + 1;
    } while (i != end);
  }
  return;
}