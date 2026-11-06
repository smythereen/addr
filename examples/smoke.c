#include <addr.h>
int main(void) {
    u32 a = Numbers_To_Address(1, 2, 3, 4);
    return a != 0x01020304U || Address_To_Machine_Number(a) != 1;
}
