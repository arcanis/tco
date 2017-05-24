#include <functional>

#include "./my-function.hh"

int main(void)
{
    my::function<int (int)> fn;

    fn = [&fn](int n) { return fn(n + 1); };

    return fn(0);
}
