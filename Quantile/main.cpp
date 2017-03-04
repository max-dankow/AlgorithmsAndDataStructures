#include <iostream>
#include <vector>

template <typename Comparator>
class MyHeap
{
public:
    explicit MyHeap(const Comparator &init_comparator = Comparator()) : comparator(init_comparator)
    {
        comparator = init_comparator;
    }
    void add(long long value);
    long long pop();
    long long get_root_value() const;
    size_t get_size() const;
private:
    void sift_down(size_t element_number);
    void sift_up(std::ptrdiff_t element_number);
    std::vector<long long> tree;
    Comparator comparator;
};

template <typename Comparator>
void MyHeap<Comparator>::sift_down(size_t element_number)
{
    while (true)
    {
        size_t left_son = 2 * element_number + 1;
        size_t right_son = 2 * element_number + 2;
        size_t maximum = element_number;

        if ((left_son < tree.size()) && (comparator(tree[left_son], tree[maximum])))
            maximum = left_son;
        if ((right_son < tree.size()) && (comparator(tree[right_son], tree[maximum])))
            maximum = right_son;

        if (maximum != element_number)
        {
            std::swap(tree[element_number], tree[maximum]);
            element_number = maximum;
        }
        else
        {
            return;
        }
    }
}

template <typename Comparator>
void MyHeap<Comparator>::sift_up(std::ptrdiff_t element_number)
{
    while (true)
    {
        std::ptrdiff_t parent = (element_number - 1) / 2;

        if ((element_number > 0) && (!comparator(tree[parent], tree[element_number])))
        {
            std::swap(tree[parent], tree[element_number]);
            element_number = parent;
        }
        else
        {
            return;
        }

    }
}

template <typename Comparator>
void MyHeap<Comparator>::add(long long value)
{
    tree.push_back(value);
    sift_up(tree.size() - 1);
}

template <typename Comparator>
long long MyHeap<Comparator>::pop()
{
    long long root_element = tree[0];
    std::swap(tree[0], tree[tree.size() - 1]);
    tree.pop_back();
    sift_down(0);

    return root_element;
}

template <typename Comparator>
long long MyHeap<Comparator>::get_root_value() const
{
    return tree[0];
}

template <typename Comparator>
size_t MyHeap<Comparator>::get_size() const
{
    return tree.size();
}

size_t get_order(std::ptrdiff_t N, double alpha)
{
    return long ((N - 1) * alpha);
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::vector<long long> data;
    size_t number;
	double alpha;
	std::cin >> number >> alpha;

	for (size_t i = 0; i < number; ++i)
    {
        long long input_number;
        std::cin >> input_number;
        data.push_back(input_number);
    }

    MyHeap <std::less<long long>> min_heap = MyHeap<std::less<long long>>();
    MyHeap <std::greater<long long>> max_heap = MyHeap<std::greater<long long>>();

    min_heap.add(data[0]);
    max_heap.add(data[0]);

    std::cout << max_heap.get_root_value() << '\n';

    for (size_t i = 1; i < number; ++i)
    {
        if (data[i] > max_heap.get_root_value())
        {
            if (i - get_order(i + 1, alpha) > min_heap.get_size() - 1)
            {
                min_heap.add(data[i]);
            }
            else
            {
                min_heap.pop();
                min_heap.add(data[i]);
                max_heap.add(min_heap.get_root_value());
            }
        }
        else
        {
            if (get_order(i + 1, alpha) > (max_heap.get_size() - 1))
            {
                max_heap.add(data[i]);
            }
            else
            {
                max_heap.pop();
                max_heap.add(data[i]);
                min_heap.add(max_heap.get_root_value());
            }
        }
        std::cout << max_heap.get_root_value() << '\n';
    }

    return 0;
}
