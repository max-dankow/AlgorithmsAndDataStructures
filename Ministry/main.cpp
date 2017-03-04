#include <iostream>
#include <vector>

const int NO_BACK_WAY = -1;

void read_data(size_t &rooms_number, size_t &floors_number, std::vector<std::vector<long long>> &fee)
{
    std::cin >> floors_number >> rooms_number;
    fee.resize(floors_number);

    for (size_t floor = 0; floor < floors_number; ++floor)
    {
        fee[floor].reserve(rooms_number);

        for (size_t cabinet = 0; cabinet < rooms_number; ++cabinet)
        {
            long long input_value;
            std::cin >> input_value;
            fee[floor].push_back(input_value);
        }
    }
}

void solution(const std::vector<std::vector<long long>> &fee, std::vector<std::vector<long long>> &dp,
              std::vector<std::vector<std::ptrdiff_t>> &previous, const size_t rooms_number, const size_t floors_number)
{
    dp.assign(floors_number, std::vector<long long> (rooms_number, 0));
    previous.assign(floors_number, std::vector<std::ptrdiff_t> (rooms_number, NO_BACK_WAY));

    dp[0] = fee[0];

    for (size_t floor = 1; floor < floors_number; ++floor)
    {
        dp[floor][0] = dp[floor - 1][0] + fee[floor][0];
        previous[floor][0] = 0;

        for (size_t cabinet = 1; cabinet < rooms_number; ++cabinet)
        {
            if (dp[floor - 1][cabinet] < dp[floor][cabinet - 1])
            {
                dp[floor][cabinet] = dp[floor - 1][cabinet] + fee[floor][cabinet];
                previous[floor][cabinet] = cabinet;
            }
            else
            {
                dp[floor][cabinet] = dp[floor][cabinet - 1] + fee[floor][cabinet];
                previous[floor][cabinet] = cabinet - 1;
            }
        }

        for (std::ptrdiff_t cabinet = rooms_number - 2; cabinet >= 0; --cabinet)
        {
            if (dp[floor][cabinet + 1] + fee[floor][cabinet] < dp[floor][cabinet])
            {
                dp[floor][cabinet] = dp[floor][cabinet + 1] + fee[floor][cabinet];
                previous[floor][cabinet] = cabinet + 1;
            }
        }
    }
}

void restore_way(const std::vector<std::vector<std::ptrdiff_t>> &previous, const std::vector<std::vector<long long>> &dp,
                 std::vector<size_t> &answer, const size_t rooms_number, const size_t floors_number)
{
    size_t final_cabinet = 0;

    for (size_t i = 1; i < rooms_number; ++i)
    {
        if (dp[floors_number - 1][i] < dp[floors_number - 1][final_cabinet])
            final_cabinet = i;
    }

    std::ptrdiff_t current_cabinet = final_cabinet, current_floor = floors_number - 1;
    answer.clear();

    while (current_cabinet != NO_BACK_WAY)
    {
        answer.push_back(current_cabinet);

        if (previous[current_floor][current_cabinet] == current_cabinet)
            --current_floor;
        else
            current_cabinet = previous[current_floor][current_cabinet];
    }
}

void write_answer(const std::vector<size_t> &answer)
{
    for (std::ptrdiff_t cabinet = answer.size() - 1; cabinet >= 0; --cabinet)
        std::cout << answer[cabinet] + 1 << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t rooms_number, floors_number;

    std::vector<std::vector<long long>> fee;
    read_data(rooms_number, floors_number, fee);

    std::vector<std::vector<long long>> dp;
    std::vector<std::vector<std::ptrdiff_t>> previous;
    solution(fee, dp, previous, rooms_number, floors_number);

    std::vector<size_t> answer;
    restore_way(previous, dp, answer, rooms_number, floors_number);

    write_answer(answer);

    return 0;
}
