#include <stdio.h>
 
#define UNICVAR_CON_EXPAND(a, b) a## b
#define UNICVAR_CON(a, b) UNICVAR_CON_EXPAND(a, b)
#define UNICVAR UNICVAR_CON(_internal_unic_var_, __COUNTER__)
 
 
#include <functional>
class Defer
{
    std::function<void()>     _f;
public:
    Defer(const std::function<void()>& func):_f(func){}
    Defer(){}
    ~Defer() {
        if (_f)
            _f();
    }
    Defer& operator=(const std::function<void()>& f) {
        _f = f;
        return *this;
    }
};
 
// 1.这是一种方案
#define defer1(block) Defer UNICVAR([]()block)
 
// 2.这是一种方案
#define defer_expand2(name) Defer name; name=[&]()
#define defer2 defer_expand2(UNICVAR)
 
// 3.这是一种方案
#define defer_expand_detail(mark) Defer _defer_expand_unic_## mark; _defer_expand_unic_## mark=[&]()
#define defer_expand(mark) defer_expand_detail(mark)
#define defer defer_expand(__COUNTER__)
 
void aaa()
{
    {
        int UNICVAR = 1;
 
        Defer UNICVAR([]() {
            puts("defer 111");
        });
 
        puts("222");
        Defer UNICVAR([]() {
            puts("defer 33");
        });
        Defer aa;
        aa = [](){
            puts("defer 44");
        };
    }
    {
        defer1({
            printf("defer %d %d\n", 1, 1);
        });
        defer1({
            printf("defer %d %d\n", 1, 2);
        });
        defer1({
            printf("defer %d %d\n", 1, 3);
        });
    }
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
}
