#include <stdio.h>
#include "../defer.h"
 
void aaa()
{
    {
        defer {
            puts("111");
        };
        defer {
            puts("111 - 2");
        };
    }
}
 
int main(){
    aaa();
    return 0;
}
 
