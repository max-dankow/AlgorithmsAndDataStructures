#include <vector>
#include <iostream>
#include "FixedSet.h"

int main()
{
    size_t n;
    std::cin >> n;
    std::vector<long> numbers;
    numbers.reserve(n);

    for (size_t i = 0; i < n; ++i)
    {
        long InputValue;
        std::cin >> InputValue;
        numbers.push_back(InputValue);
    }

    FixedSet MySet(numbers);

    size_t m;
    std::cin >> m;
    std::vector<bool> answer(m);

    for (size_t i = 0; i < m; ++i)
    {
        long InputValue;
        std::cin >> InputValue;
        answer[i] = MySet.Contains(InputValue);
    }

    for(auto result : answer)
    {
        if (result)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}
