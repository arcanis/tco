#include <boost/bind.hpp>

#include "./my-function.hh"

int fn(my::function<int (int)> const & wrap, int n)
{
    return wrap(n + 1);
}

int main(void)
{
    my::function<int (int)> wrap;
    wrap = boost::bind(&fn, std::ref(wrap), _1);

    return wrap(0);
}
