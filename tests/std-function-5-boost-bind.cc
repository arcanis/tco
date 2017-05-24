#include <functional>

#include <boost/bind.hpp>

int fn(std::function<int (int)> const & wrap, int n)
{
    return wrap(n + 1);
}

int main(void)
{
    std::function<int (int)> wrap;
    wrap = boost::bind(&fn, std::ref(wrap), _1);

    return wrap(0);
}
