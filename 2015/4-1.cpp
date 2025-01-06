
#include <iostream>
#include <string>
#include <sstream>
#include "md5.h"
#include <iomanip>

using namespace std;

int main() {
    unsigned char digest[16];
    MD5_CTX ctx;
    string myinput("yzbqklnj");
    u_long x = 0;

    for (x = 0;; x++) {
        ostringstream oss;
        oss << myinput << dec << x;
        MD5Init(&ctx);
        MD5Update(&ctx, (const unsigned char *)oss.str().c_str(), oss.str().length());
        MD5Final(digest, &ctx);
        if (digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xf0) == 0)
            break;
    }


    cout << dec << x << " " << hex << x << endl;
    for (int x = 0; x < 16; x++)
        cout << setfill('0') << setw(2) << hex << (uint)digest[x];
    cout << endl;

}