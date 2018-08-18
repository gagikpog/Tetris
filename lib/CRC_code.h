#ifndef CRC_CODE_H
#define CRC_CODE_H
/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long getCRC(unsigned char *buf, int len);
#endif // CRC_CODE_H