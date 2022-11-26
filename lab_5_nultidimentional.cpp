#include <cassert>
#include <iostream>

template <typename T, size_t N>
class NDimGrid final
{
    public:
        using value_type = T;
        using size_type = size_t;

        T *data = nullptr;
        size_type sub_space_dim[N];
        long position;
        
        NDimGrid(T *point, size_type arr[])
        {
            position = 1;
            for (size_t i = 0; i < N; i++)
            {
                sub_space_dim[i] = arr[i];
                position = position * arr[i];
            }
            data = new T[position];
            for (long i = 0; i < position; i++)
            {
                *(data + i) = *(point + i);
            }
        }

        void fill_it(int i, value_type first)
        {
            data = new T[position];
            for (long i = 0; i < position; i++)
            {
                *(data + i) = first;
            }
        }

        template <typename CurrentLenght, typename... Args>
        void fill_it(int i, CurrentLenght current_lenght, Args... args)
        {
            sub_space_dim[i] = current_lenght;
            position = position * current_lenght;
            i = i + 1;
            fill_it(i, args...);
        }

        template <typename... Args>
        NDimGrid(Args... args)
        {
            position = 1;
            fill_it(0, args...);
        }

        T find_it(int i, T *point) const
        {
            return *point;
        }

        template <typename CurrentLenght, typename... Args>
        T find_it(int i, T *point, CurrentLenght current_lenght, Args... args) const
        {
            size_type mass = 1;
            for (size_type j = 1 + i; j < N; j++)
            {
                mass = mass * sub_space_dim[j];
            }
            i = i + 1;
            return find_it(i, (point + mass * current_lenght), args...);
        }

        template <typename... Args>
        T operator()(Args... args) const
        {
            T *point = data;
            return find_it(0, point, args...);
        }

        ~NDimGrid()
        {
            delete[] data;
        }
};

int main()
{
    NDimGrid <float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));
    NDimGrid <float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));
    return 0;
}