#include <iostream>
#include <vector>

template <typename T>

struct Comparator{
    virtual bool operator()(T const &, T const &) = 0;
};

template <typename T>
class PriorityQueue{
    private:
        std::vector<T> vec;
        Comparator<T> &comp;

        int parent(int i)
        { 
             return (i - 1)/2; 
        }
        int element_left(int i)
        {
            return (2 * i + 1);
        }
        int element_right(int i)
        {
            return (2 * i + 2);
        }

        void ShiftUp(int i)
        {
            while(i > 0 && comp(vec[parent(i)], vec[i]))
            {
                std::swap(vec[parent(i)], vec[i]);
                i = parent(i);
            }
        }

        void ShiftDown(int i){
            if(element_right(i) < vec.size() && comp(vec[i], vec[element_right(i)]) && comp(vec[element_left(i)], vec[element_right(i)])){
                std::swap(vec[element_right(i)], vec[i]);
                ShiftDown(element_right(i));
            }

            else if(element_left(i) < vec.size() && comp(vec[i], vec[element_left(i)]) && not comp(vec[element_left(i)], vec[element_right(i)])){
                std::swap(vec[element_left(i)], vec[i]);
                ShiftDown(element_left(i));
            }
        }

    public:
        void push(T element){
            vec.push_back(element);
            ShiftUp(vec.size() - 1);
        }

        T peek(){
            return vec[0];
        }

        void poll(){
            vec[0] = vec.back();
            vec.pop_back();
            ShiftDown(0);
        }
        
        bool is_empty(){
            return vec.empty();
        }

    PriorityQueue(Comparator<T> &comp): comp(comp) { }
    PriorityQueue(std::vector<T> arr, Comparator<T> &comp): PriorityQueue(comp){
        for(int i = 0; i < arr.size(); i++){
            push(arr[i]);
        }
    }
};


struct IntComparator final: Comparator<int>{
    bool operator()(int const &lha,int const &rha) override{
       return (lha < rha);
    }
};

int main()
{
    IntComparator comp;
    std::vector<int> arr = {4, 6, 2, 7, 9, 72, 6, 32, 89, 23, 76, 45, 5, 7, 12};
    PriorityQueue<int> queue(arr, comp);
    for (int i = 0; i < 14; i++)
    {
        std::cout << queue.peek() << ' ';
        queue.poll();
    }
    return(0);
}