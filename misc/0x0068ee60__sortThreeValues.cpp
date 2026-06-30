// FUNC_NAME: sortThreeValues
void sortThreeValues(undefined4 *a, undefined4 *b, undefined4 *c, code *comparator)
{
  undefined4 temp;
  char result;
  
  // Compare and swap a and b if needed
  result = (*comparator)(*b, *a);
  if (result != '\0') {
    temp = *b;
    *b = *a;
    *a = temp;
  }
  
  // Compare and swap b and c if needed
  result = (*comparator)(*c, *b);
  if (result != '\0') {
    temp = *c;
    *c = *b;
    *b = temp;
  }
  
  // Final compare and swap a and b to ensure full sort
  result = (*comparator)(*b, *a);
  if (result != '\0') {
    temp = *b;
    *b = *a;
    *a = temp;
  }
}