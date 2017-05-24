struct Base
{
    virtual int operator()(Base const & base, int n) const = 0;
};

struct Test : public Base
{
    virtual int operator()(Base const & test, int n) const
    {
        return test(test, n + 1);
    }
};

int main(void)
{
    Test test;

    return test(test, 0);
}
