int hextoi(char c) {
  if (c <= '9') return c - '0';
  if (c <= 'f') return c - 'a' + 10;
  return c - 'A' + 10;
}

