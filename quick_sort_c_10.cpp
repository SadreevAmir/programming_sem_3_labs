#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <math.h>

struct vector
{
    double x, y, z, t;
};

double lenght(vector a)
{
    return(a.t*a.t + a.x*a.x + a.y*a.y + a.z*a.z);
}

void vector_coordinates(vector a, double x_coord, double y_coord, double z_coord, double t_coord)
{
    a.x = x_coord;
    a.y = y_coord;
    a.z = z_coord;
    a.t = t_coord;
}

void print_massive(int * mas, int mas_len)
{
    for (int i = 0; i < mas_len; i++)
    {
        std::cout << (mas[i]) << ' ';
    }
    std::cout << std::endl;
}

void print_vector_coords(vector a)
{
    std::cout << a.x << ' ' << a.y << ' ' << a.z << ' ' << a.t << std::endl;
}

void swap_func(void * x_ptr, void * y_ptr, std::size_t element_byte_size)
{
    void * tmp = malloc(element_byte_size);
    std::memcpy(tmp, x_ptr, element_byte_size);
    std::memcpy(x_ptr, y_ptr, element_byte_size);
    std::memcpy(y_ptr, tmp, element_byte_size);
    free(tmp);
}

int comparator(void * x, void * y)
{
    if ((*reinterpret_cast<int *> (x) ) < (*reinterpret_cast<int *> (y) ))
    {
        return 1;
    }
    if ((*reinterpret_cast<int *> (y) ) <= (*reinterpret_cast<int *> (x) ))
    {
        return 0;
    }
}

int comparator_vector(void * x, void * y)
{
    if (lenght(*reinterpret_cast<vector*>(x)) < lenght(*reinterpret_cast<vector*>(y)))
    {
        return 1;
    }
    if (lenght(*reinterpret_cast<vector*>(x)) == lenght(*reinterpret_cast<vector*>(y)))
    {
        return 0;
    }
    if (lenght(*reinterpret_cast<vector*>(x)) > lenght(*reinterpret_cast<vector*>(y)))
    {
        return -1;
    }
}

void qsort(void * mas, std::size_t type_size, int left, int right, int (*compare)(void *, void *))
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        void * basic = mas + (left + right) / 2 * type_size;
        int i = left, j = right;
        while (true)
        {
            while (compare(mas + i * type_size, basic))
            {
                i = i + 1;
            }
            while (basic, compare(basic, mas + j * type_size))
            {
                j = j - 1;
            }
            if (i >= j)
            {
                middle = j;
                break;
            }

            swap_func(mas + i * type_size, mas + j * type_size, sizeof(vector));
            i = i + 1;
            j = j - 1;
        }
        qsort(mas, type_size, left, middle, compare);
        qsort(mas, type_size, middle + 1, right, compare);
    }
}

int main()
{
    int (*compare[]) (void*, void*) = {comparator, comparator_vector}; 
    vector vector_list[5] = {};
    vector_list[0] = {1 ,2 ,3 ,4};
    vector_list[1] = {1 ,1 , 1 ,1};
    vector_list[2] = {1 ,1, 0, 1};
    vector_list[3] = {2, 3, 8, 0};
    vector_list[4] = {0, 0, 2, 1};
    for (int i = 0; i < 5; i++)
    {
        print_vector_coords(vector_list[i]);
    }
    std::cout << std::endl;
    qsort(vector_list, sizeof(vector), 0, 4, compare[1]);
    for (int i = 0; i < 5; i++)
    {
        print_vector_coords(vector_list[i]);
    }
    return 0;
}