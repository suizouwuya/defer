#include <functional>
class Defer
{
    std::function<void()>     _f;
public:
    ~Defer() { if (_f) _f(); }
    Defer& operator=(const std::function<void()>& f) {
        _f = f;
        return *this;
    }
};
 
#define defer_expand_detail(mark) Defer _defer_expand_unic_## mark; _defer_expand_unic_## mark=[&]()
#define defer_expand(mark) defer_expand_detail(mark)
#define defer defer_expand(__COUNTER__)
