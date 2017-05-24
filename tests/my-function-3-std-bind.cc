#include <functional>

#include "./my-function.hh"

int fn(my::function<int (int)> const & wrap, int n)
{
    return wrap(n + 1);
}

int main(void)
{
    using namespace std::placeholders;

    my::function<int (int)> wrap;
    wrap = std::bind(&fn, std::ref(wrap), _1);

    return wrap(0);
}
