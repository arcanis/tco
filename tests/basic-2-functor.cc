struct Test
{
    int operator()(int n) const
    {
        return (*this)(n + 1);
    }
};

int main(void)
{
    Test test;

    return test(0);
}
