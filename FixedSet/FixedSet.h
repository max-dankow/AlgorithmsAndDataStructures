#include <vector>
#include <random>

static std::default_random_engine Generator;
static std::uniform_int_distribution<long> ValuesAlpha(1, 2000000010);
static std::uniform_int_distribution<long> ValuesBeta(0, 2000000010);
const long EMPTY_ELEMENT = std::numeric_limits<long>::max();

struct HashUniversalType
{
    long alpha, beta;
    static const long PRIME = 2000000011;

    void reInit()
    {
        alpha = ValuesAlpha(Generator);
        beta = ValuesBeta(Generator);
    }

    long F(const long key) const;
};

struct SimpleTable
{
    std::vector<long> Values;
    HashUniversalType Hash;

    void AddNumbers(long key);
    bool Contains(long key) const;
};

class FixedSet{
public:
    explicit FixedSet(const std::vector<long> &numbers);
    bool Contains(long number) const;
private:
    std::vector<SimpleTable> Table;
    void generateA_B(const std::vector<long> &numbers, std::vector<long> &Count);
    HashUniversalType Hash;
};
