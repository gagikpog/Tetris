#include "CRC_code.h"
/* Table of CRCs of all 8-bit messages. */
unsigned long crc__table[256];

/* Flag: has the table been computed? Initially false. */
int crc_table__computed = 0;
 
/* Make the table for a fast CRC. */
void make_crc__table(void)
{
  unsigned long c;
  int n, k;
  for (n = 0; n < 256; n++) 
  {
    c = (unsigned long) n;
    for (k = 0; k < 8; k++) 
    {
      if (c & 1){
        c = 0xedb88320L ^ (c >> 1);
      } else {
        c = c >> 1;
      }
    }
    crc__table[n] = c;
  }
  crc_table__computed = 1;
}
  
/*Update a running CRC with the bytes buf[0..len-1]--the CRC
  should be initialized to all 1's, and the transmitted value
  is the 1's complement of the final running CRC (see the
  crc() routine below). */
unsigned long update__crc(unsigned long crc, unsigned char *buf, int len)
{
  unsigned long c = crc;
  int n;

  if (!crc_table__computed)
    make_crc__table();
  for (n = 0; n < len; n++) {
    c = crc__table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
  }
  return c;
}
  
/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long getCRC(unsigned char *buf, int len)
{
  return update__crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}