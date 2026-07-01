// FUNC_NAME: getStatStringTable
char** getStatStringTable(int statIndex)
{
  // Returns a pointer into a table of stat string pointers.
  // The table at 0x00e51d64 contains entries of 3 pointers each (likely
  // name, description, and maybe a format string or icon).
  // statIndex selects which stat's group of 3 strings to return.
  return (&PTR_s_HEALTH_PERCENTAGE_00e51d64)[statIndex * 3];
}