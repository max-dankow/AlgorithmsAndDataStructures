#include <iostream>
#include <vector>

class My_Fenwick_Tree_3D
{
public:
    explicit My_Fenwick_Tree_3D(const size_t data_size_x, const size_t data_size_y, const size_t data_size_z);
    void update_3D(size_t x_start, size_t y_start, size_t z_start, long long delta);
    size_t sum_3D(std::ptrdiff_t x_start, std::ptrdiff_t y_start, std::ptrdiff_t z_start) const;
    size_t sum_3D(std::ptrdiff_t x_first, std::ptrdiff_t y_first, std::ptrdiff_t z_first,
                  std::ptrdiff_t x_second, std::ptrdiff_t y_second, std::ptrdiff_t z_second) const;

private:
    size_t f_prev(size_t number) const;
    size_t f_next(size_t number) const;
    std::vector<std::vector<std::vector<long long>>> tree;
};

size_t My_Fenwick_Tree_3D::f_prev(size_t number) const
{
    return number & (number + 1);
}

size_t My_Fenwick_Tree_3D::f_next(size_t number) const
{
    return number | (number + 1);
}

void My_Fenwick_Tree_3D::update_3D(size_t x_start, size_t y_start, size_t z_start, long long delta)
{
    for (size_t x = x_start; x < tree.size(); x = f_next(x))
        for (size_t y = y_start; y < tree[x].size(); y = f_next(y))
            for (size_t z = z_start; z < tree[x][y].size(); z = f_next(z))
                tree[x][y][z] += delta;
}

My_Fenwick_Tree_3D::My_Fenwick_Tree_3D(const size_t data_size_x, const size_t data_size_y, const size_t data_size_z)
{
    tree.assign (data_size_x, std::vector <std::vector <long long>>
                 (data_size_y, std::vector <long long> (data_size_z, 0)));
}

size_t My_Fenwick_Tree_3D::sum_3D(std::ptrdiff_t x_start, std::ptrdiff_t y_start, std::ptrdiff_t z_start) const
{
    size_t result = 0;

    for (std::ptrdiff_t x = x_start; x >= 0; x = std::ptrdiff_t (f_prev(size_t (x))) - 1)
        for (std::ptrdiff_t y = y_start; y >= 0; y = std::ptrdiff_t (f_prev(size_t (y))) - 1)
            for (std::ptrdiff_t z = z_start; z >= 0; z = std::ptrdiff_t (f_prev(size_t (z))) - 1)
                result += tree[x][y][z];

    return result;
}

size_t My_Fenwick_Tree_3D::sum_3D(std::ptrdiff_t x_first, std::ptrdiff_t y_first, std::ptrdiff_t z_first,
                                  std::ptrdiff_t x_second, std::ptrdiff_t y_second, std::ptrdiff_t z_second) const
{
    return sum_3D(x_second, y_second, z_second)
        - sum_3D(x_first - 1, y_second, z_second)
        - sum_3D(x_second, y_first - 1, z_second)
        - sum_3D(x_second, y_second, z_first - 1)
        + sum_3D(x_first - 1, y_first - 1, z_second)
        + sum_3D(x_first - 1, y_second, z_first - 1)
        + sum_3D(x_second, y_first - 1, z_first - 1)
        - sum_3D(x_first - 1, y_first - 1, z_first - 1);

}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    My_Fenwick_Tree_3D fenwick(n, n, n);

    std::vector<long long> answer;

    while (true)
    {
        size_t code;
        std::cin >> code;

        if (code == 3)
            break;
        else
        {
            if (code == 1)
            {
                size_t x, y, z;
                long long d;
                std::cin >> x >> y >> z >> d;
                fenwick.update_3D(x, y, z, d);
            }
            else
            {
                size_t x1, y1, z1, x2, y2, z2;
                std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                answer.push_back(fenwick.sum_3D(x1, y1, z1, x2, y2, z2));
            }
        }
    }

    for (long long value : answer)
    {
        std::cout << value << '\n';
    }

    return 0;
}
