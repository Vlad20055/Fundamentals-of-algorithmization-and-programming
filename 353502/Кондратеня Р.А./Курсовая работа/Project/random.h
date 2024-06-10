#include <iostream>
#include <ctime>

class Random64
{
public:
    typedef unsigned long long uint64;
    typedef uint64 RandomValue;

    Random64()
    {
        // Инициализация зерна на основе текущего времени
        X = static_cast<uint64>(std::time(nullptr));
    }

    Random64& operator=(uint64 seed)
    {
        X = seed;
        return *this;
    }

    uint64 operator()(uint64 seed = uint64(-1))
    {
        const uint64 a = 3202034522624059733ULL;
        const uint64 c = 1ULL;

        if (seed != uint64(-1))
            X = seed;

        uint64 Y = a * X + c;
        X = a * Y + c;
        Y = (Y & 0xFFFFFFFF00000000ULL) | (X >> 32);
        return Y;
    }

    uint64 operator()(uint64 min, uint64 max)
    {
        return (*this)() % (max - min) + min;
    }

private:
    uint64 X;
};

int main()
{
    Random64 random;

    // Генерация случайных чисел с разными зернами
    for (int i = 0; i < 5; ++i) {
        unsigned long long randomNumber = random();
        std::cout << "Random number with seed: " << randomNumber << std::endl;
    }

    return 0;
}
