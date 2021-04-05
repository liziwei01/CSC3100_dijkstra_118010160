#ifndef _lzw_io
#define _lzw_io
#include <stdio.h>
namespace lzw {
    bool rd_int(int &input_int) {
        bool negative = false; 
        int ch;
        input_int = 0;
        ch = getchar_unlocked(); 
        if (ch == '\n') {
            return false;
        }
        while ((ch < '0'|| ch > '9') && ch != '-') {
            ch = getchar_unlocked();
        }
        if (ch == '-') {
            negative = true; 
            ch = getchar_unlocked(); 
        }
        while( ch >= '0' && ch <= '9' ) {
            input_int = input_int * 10 + ch - '0';
            ch = getchar_unlocked();
        }
        if (negative) {
            input_int *= -1; 
        }
        return true;
    }
    bool pr_int (int n, char end = '\n') { 
        if (n == 0) {
            putchar_unlocked('0'); 
            putchar_unlocked(end); 
            return true;
        } 
        if (n < 0) {
            putchar_unlocked('-');
            n *= -1; 
        }
        int rev = n;
        int count = 0; 
        while ((rev % 10) == 0) { 
            count++; 
            rev /= 10;
        }
        rev = 0; 
        while (n != 0) { 
            rev = rev*10 + n % 10; 
            n /= 10;
        }
        while (rev != 0) { 
            putchar_unlocked(rev % 10 + '0'); 
            rev /= 10;
        } 
        while (count--) {
            putchar_unlocked('0'); 
        }
        putchar_unlocked(end);
        return true;
    }
}
#endif // _lzw_io

#ifndef _lzw_node
#define _lzw_node
namespace lzw {
    template<typename ValueType>
    class Node {
        public:
        ValueType index;
        ValueType weight;

        Node(ValueType i = 0, ValueType w = 0) {
            index = i;
            weight = w;
        }
        ~Node();
    };
}
#endif // _lzw_node

#ifndef _lzw_vector
#define _lzw_vector
#include <stdlib.h>
#define LZW_VECTOR_INITIAL_CAPACITY 5
#define LZW_VECTOR_EXPAND_SIZE 2
#define LZW_INSERTION_SORT 0
#define LZW_BUBBLE_SORT 1
#define LZW_QUICK_SORT 2
#define LZW_MERGE_SORT 3

namespace lzw {
    template <typename ValueType>
    class Vector {
    public:
        Vector();
        Vector(int n, ValueType value = ValueType());
        ~Vector();
        int size() const;
        bool isEmpty() const;
        void clear();
        ValueType at(int index) const;
        void set(int index, ValueType value);
        void insert(int index, ValueType value);
        void erase(int begin, int end);
        void erase(int index);
        void push_back(ValueType value);
        void sort(int sort_type = LZW_QUICK_SORT);
        void sort(int begin, int end, int sort_type = LZW_QUICK_SORT);
        Vector<ValueType> &sort(Vector<ValueType> &src, int sort_type = LZW_QUICK_SORT);
        Vector<ValueType> &sort(Vector<ValueType> &src, int begin, int end, int sort_type = LZW_QUICK_SORT);
        void reverse();
        Vector<ValueType> &reverse(Vector<ValueType> &src);
        ValueType &operator[](int index);
        Vector(const Vector<ValueType> &src);
        Vector<ValueType> &operator=(const Vector<ValueType> &src);
    protected:
        ValueType *array;
        int capacity;
        int count;

        void insertion_sort();
        void bubblesort();
        void quicksort(int p, int r);
        int quicksort_partition(int p, int r);
        void swap(int i, int j);
        void merge_sort();

        void deepCopy(const Vector<ValueType> & src);
        void expandCapacity();
    };

    template <typename ValueType>
    Vector<ValueType>::Vector() {
        capacity = LZW_VECTOR_INITIAL_CAPACITY;
        count = 0;
        array = new ValueType[capacity];
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(int n, ValueType value) {
        capacity = (n > LZW_VECTOR_INITIAL_CAPACITY) ? n : LZW_VECTOR_INITIAL_CAPACITY;
        array = new ValueType[capacity];
        count = n;
        for (int i = 0; i < n; i++) {
            array[i] = value;
        }
    }

    template <typename ValueType>
    Vector<ValueType>::~Vector() {
        delete[] array;
    }

    template <typename ValueType>
    int Vector<ValueType>::size() const {
        return count;
    }

    template <typename ValueType>
    bool Vector<ValueType>::isEmpty() const {
        return count == 0;
    }

    template <typename ValueType>
    void Vector<ValueType>::clear() {
        count = 0;
    }

    template <typename ValueType>
    ValueType Vector<ValueType>::at(int index) const {
        if (index < 0 || index >= count) {
            throw "Vector<>::at: index out of range\n";
        }
        return array[index];
    }

    template <typename ValueType>
    void Vector<ValueType>::set(int index, ValueType value) {
        if (index < 0 || index >= count) {
            throw "Vector<>::set: index out of range\n";
        }
        array[index] = value;
    }

    template <typename ValueType>
    ValueType & Vector<ValueType>::operator[](int index) {
        if (index < 0 || index >= count) {
            throw "Vector<>::[]: index out of range\n";
        }
        return array[index];
    }

    template <typename ValueType>
    void Vector<ValueType>::push_back(ValueType value) {
        insert(count, value);
    }

    // #define LZW_INSERTION_SORT 0
    // #define LZW_BUBBLE_SORT 1
    // #define LZW_QUICK_SORT 2
    // #define LZW_MERGE_SORT 3
    template <typename ValueType>
    void Vector<ValueType>::sort(int sort_type) {
        if (sort_type == LZW_INSERTION_SORT) {
            insertion_sort();
        } else if (sort_type == LZW_BUBBLE_SORT) {
            bubblesort();
        } else if (sort_type == LZW_QUICK_SORT) {
            quicksort(0, count - 1);
        } else if (sort_type == LZW_MERGE_SORT) {
            merge_sort();
        } else {
            throw "Vector<>::sort: unknown type of sort\n";
        }
    }

    template <typename ValueType>
    void Vector<ValueType>::sort(int begin, int end, int sort_type) {
        if (sort_type == LZW_INSERTION_SORT) {
            insertion_sort();
        } else if (sort_type == LZW_BUBBLE_SORT) {
            bubblesort();
        } else if (sort_type == LZW_QUICK_SORT) {
            quicksort(begin, end);
        } else if (sort_type == LZW_MERGE_SORT) {
            merge_sort();
        } else {
            throw "Vector<>::sort: unknown type of sort\n";
        }
    }

    template <typename ValueType>
    Vector<ValueType> &Vector<ValueType>::sort(Vector<ValueType> &src, int sort_type) {
        return src.sort(sort_type);
    }

    template <typename ValueType>
    Vector<ValueType> &Vector<ValueType>::sort(Vector<ValueType> &src, int begin, int end, int sort_type) {
        return src.sort(begin, end, sort_type);
    }

    template <typename ValueType>
    void Vector<ValueType>::reverse() {
        ValueType *old_array = array;
        array = new ValueType[capacity];
        for (int i = 0; i < count; i++) {
            array[i] = old_array[count - i - 1];
        }
        delete[] old_array;
    }

    template <typename ValueType>
    Vector<ValueType> &Vector<ValueType>::reverse(Vector<ValueType> &src) {
        return src.reverse();
    }

    template <typename ValueType>
    void Vector<ValueType>::insert(int index, ValueType value) {
        if (count == capacity) {
            expandCapacity();
        }
        if (index < 0 || index > count) {
            throw "Vector<>::insert: index out of range\n";
        }
        for (int i = count; i != index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        count++;
    }

    // erase from begin to end but keep end
    template <typename ValueType>
    void Vector<ValueType>::erase(int begin, int end) {
        if (begin == end) {
            erase(begin);
            return;
        }
        if (begin < 0 || begin >= count || end < 0 || end >= count) {
            throw "Vector<>::erase: index out of range\n";
        }
        for (int i = 0; i != count - end; i++) {
            array[begin + i] = array[end + i];
        }
        count = count - (end - begin);
    }

    template <typename ValueType>
    void Vector<ValueType>::erase(int index) {
        if (index < 0 || index >= count) {
            throw "Vector<>::erase: index out of range\n";
        }
        for (int i = index; i != count - 1; i++) {
            array[i] = array[i + 1];
        }
        count--;
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(const Vector<ValueType> &src) {
        deepCopy(src);
    }

    template <typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator=(const Vector<ValueType> &src) {
        if (this != &src) {
            delete[] array;
            deepCopy(src);
        }
        return *this;
    }

    template <typename ValueType>
    void Vector<ValueType>::insertion_sort() {

    }

    template <typename ValueType>
    void Vector<ValueType>::bubblesort() {

    }

    template <typename ValueType>
    void Vector<ValueType>::quicksort(int p, int r) {
        if (p < r) {
            int q = quicksort_partition(p, r);
            quicksort(p, q - 1);
            quicksort(q + 1, r);
        }
    }

    template <typename ValueType>
    int Vector<ValueType>::quicksort_partition(int p, int r) {
        // int pivot_index = p + (rand() % (r - p));
        int pivot_index = r;
        ValueType pivot = array[pivot_index];
        int i = p - 1;
        for (int j = p; j != r; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(i, j);
            }
        }
        swap(i + 1, r);
        return i + 1;
    }

    template <typename ValueType>
    void Vector<ValueType>::swap(int i, int j) {
        if (i < 0 || i >= count || j < 0 || j >= count) {
            throw "Vector<>::swap: index out of range\n";
        }
        ValueType old_value = array[i];
        array[i] = array[j];
        array[j] = old_value;
    }

    template <typename ValueType>
    void Vector<ValueType>::merge_sort() {

    }

    template <typename ValueType>
    void Vector<ValueType>::deepCopy(const Vector<ValueType> &src) {
        capacity = src.count + LZW_VECTOR_INITIAL_CAPACITY;
        this->array = new ValueType[capacity];
        for (int i = 0; i < src.count; i++) {
            array[i] = src.array[i];
        }
        count = src.count;
    }

    template <typename ValueType>
    void Vector<ValueType>::expandCapacity() {
        ValueType *old_array = array;
        capacity *= LZW_VECTOR_EXPAND_SIZE;
        array = new ValueType[capacity];
        for (int i = 0; i < count; i++) {
            array[i] = old_array[i];
        }
        delete[] old_array;
    }
}
#endif // _lzw_vector

#ifndef _lzw_adjacency_list
#define _lzw_adjacency_list
namespace lzw {
    template<typename ValueType>
    class AdjacencyList {
    public:
        AdjacencyList(int number_of_points = 1);
        ~AdjacencyList();
        int size() const;
        bool isEmpty() const;
        void add_adjacenct_cell(int index, int adj, int weight);
        ValueType *get_next_adjacency_cell(int index) const;
        ValueType *get_adjacency_cell(int index, int position) const;
        void show() const;
    protected:
        lzw::Vector<lzw::Vector<ValueType*>> vec;
        int *num_edges;
        int *getting_num_edges;
        int count;
    };

    template<typename ValueType>
    AdjacencyList<ValueType>::AdjacencyList(int number_of_points) {
        vec = lzw::Vector<lzw::Vector<ValueType*>>(number_of_points + 2);
        num_edges = new int[number_of_points + 2];
        getting_num_edges = new int[number_of_points + 2];
        for (int i = 0; i != number_of_points + 2; i++) {
            num_edges[i] = 0;
            getting_num_edges[i] = 0;
        }
        count = number_of_points;
    }

    template<typename ValueType>
    AdjacencyList<ValueType>::~AdjacencyList() {

    }

    template<typename ValueType>
    int AdjacencyList<ValueType>::size() const {
        return count;
    }

    template<typename ValueType>
    bool AdjacencyList<ValueType>::isEmpty() const {
        return (count == 0);
    }

    template<typename ValueType>
    void AdjacencyList<ValueType>::add_adjacenct_cell(int index, int adj, int weight) {
        ValueType *np = new ValueType;
        np->index = adj;
        np->weight = weight;
        num_edges[index]++;
        vec[index].push_back(np);
    }

    template<typename ValueType>
    ValueType *AdjacencyList<ValueType>::get_next_adjacency_cell(int index) const {
        if (index < 0 || index > count) {
            throw "AdjacencyList::get_next_adjacency_cell: index out of range\n";
        }
        getting_num_edges[index]++;
        return  get_adjacency_cell(index, getting_num_edges[index] - 1);
    }

    template<typename ValueType>
    ValueType *AdjacencyList<ValueType>::get_adjacency_cell(int index, int position) const {
        if (index < 0 || index > count) {
            throw "AdjacencyList::get_adjacency_cell: index out of range\n";
        }
        if (position < 0 || position > num_edges[index]) {
            throw "AdjacencyList::get_adjacency_cell: position out of range\n";
        }
        return vec.at(index).at(position);
    }

    template<typename ValueType>
    void AdjacencyList<ValueType>::show() const {
        for (int i = 1; i != count + 1; i++) {
            printf("%d: ", i);
            for (int j = 0; j != num_edges[i]; j++) {
                printf("%d::%d ", vec.at(i).at(j)->index, vec.at(i).at(j)->weight);
            }
            putchar('\n');
        }
    }
}
#endif // _lzw_adjacency_list

#ifndef _lzw_priority_node_queue
#define _lzw_priority_node_queue
namespace lzw {
    template<typename ValueType>
    class PriorityNodeQueue {
    public:
        PriorityNodeQueue(int num_of_points = 0);
        ~PriorityNodeQueue();
        int size() const;
        bool isEmpty() const;
        void enqueue(ValueType *np);
        ValueType *dequeue();
        ValueType *peek() const;
        void relax(int index, int relaxed_weight);
        void show() const;
    private:
        int *position_array;
        int count;
        Vector<ValueType*> array;
        void min_heapify(int i);
        int heap_increase_level(int i);
        void heap_increase_node(int i);
        void swap(int i, int j);
        int parent(int i) const;
        int left(int i) const;
        int right(int i) const;
    };

    template<typename ValueType>
    PriorityNodeQueue<ValueType>::PriorityNodeQueue(int num_of_points) {
        ValueType *np = new ValueType;
        array.push_back(np);
        count = 0;
        position_array = new int[num_of_points + 2];
        for (int i = 0; i != num_of_points + 2; i++) {
            position_array[i] = 0;
        }
    }

    template<typename ValueType>
    PriorityNodeQueue<ValueType>::~PriorityNodeQueue() {
        delete [] array;
    }

    template<typename ValueType>
    int PriorityNodeQueue<ValueType>::size() const {
        return count;
    }

    template<typename ValueType>
    bool PriorityNodeQueue<ValueType>::isEmpty() const {
        return count == 0;
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::enqueue(ValueType *np) {
        array.push_back(np);
        count++;
        position_array[np->index] = count;
        heap_increase_node(count);
    }

    template<typename ValueType>
    ValueType *PriorityNodeQueue<ValueType>::dequeue() {
        if (isEmpty()) {
            throw "PriorityNodeQueue<>::dequeue: empty queue\n";
        }
        ValueType *minimum = array[1];
        position_array[array[count]->index] = 1;
        position_array[minimum->index] = 0;
        array[1] = array[count];
        array[count] = NULL;
        count--;
        min_heapify(1);
        return minimum;
    }

    template<typename ValueType>
    ValueType *PriorityNodeQueue<ValueType>::peek() const {
        if (isEmpty()) {
            throw "PriorityNodeQueue<>::peek: empty queue\n";
        }
        return array[1];
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::relax(int index, int relaxed_weight) {
        if (index < 0) {
            throw "PriorityNodeQueue<>::relax: negative index\n";
        }
        int i = position_array[index];
        if (i == 0) {
            return;
        }
        if (array[i]->weight > relaxed_weight) {
            array[i]->weight = relaxed_weight;
            heap_increase_node(i);  
        }
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::show() const {
        for (int i = 0; i != count; i++) {
            pr_int(i, ' ');
            pr_int(array.at(i)->index, ' ');
            putchar(':');
            pr_int(array.at(i)->weight);
        }
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::min_heapify(int i) {
        if (i > count) {
            return;
        }
        if (left(i) > count) {
            return;
        }
        if (right(i) > count) {
            if (array[i]->weight >= array[left(i)]->weight) {
                swap(i, left(i));
                min_heapify(left(i));
            }
            return;
        }
        if (array[i]->weight <= array[left(i)]->weight && array[i]->weight <= array[right(i)]->weight) {
            return;
        }
        if (array[left(i)]->weight <= array[i]->weight && array[left(i)]->weight <= array[right(i)]->weight) {
            swap(i, left(i));
            min_heapify(left(i));
        } else {
            swap(i, right(i));
            min_heapify(right(i));
        }
    }

    template<typename ValueType>
    int PriorityNodeQueue<ValueType>::heap_increase_level(int i) {
        int original = i;
        while (i != 1 && array[parent(i)]->weight == 100000000) {
            i = parent(i);
        }
        swap(i, original);
        return i;
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::heap_increase_node(int i) {
        while (i != 1 && array[parent(i)]->weight > array[i]->weight) {
            swap(parent(i), i);
            i = parent(i);
        }
    }

    template<typename ValueType>
    void PriorityNodeQueue<ValueType>::swap(int i, int j) {
        int ip = position_array[array[i]->index];
        position_array[array[i]->index] = position_array[array[j]->index];
        position_array[array[j]->index] = ip;
        ValueType *middle = array[i];
        array[i] = array[j];
        array[j] = middle;
    }

    template<typename ValueType>
    int PriorityNodeQueue<ValueType>::parent(int i) const {
        return i / 2;
    }

    template<typename ValueType>
    int PriorityNodeQueue<ValueType>::left(int i) const {
        return 2 * i;
    }

    template<typename ValueType>
    int PriorityNodeQueue<ValueType>::right(int i) const {
        return 2 * i + 1;
    }
};
#endif // _lzw_priority_node_queue

#include <iostream>
int main() {
    // try {
        lzw::Node<int> *np;
        lzw::Node<int> *neighbor_point;
        int number_of_points, number_of_rows, source, starting_point, end_point, weight, position;
        
        lzw::rd_int(number_of_points);
        lzw::rd_int(number_of_rows);
        lzw::rd_int(source);
        lzw::AdjacencyList<lzw::Node<int>> *list = new lzw::AdjacencyList<lzw::Node<int>>(number_of_points);
        lzw::PriorityNodeQueue<lzw::Node<int>> *queue = new lzw::PriorityNodeQueue<lzw::Node<int>>(number_of_points);

        int *shortest_path_list = new int[number_of_points + 1];
        int *number_of_edges = new int[number_of_points + 1];
        
        for (int i = 0; i != number_of_points + 1; i++) {
            shortest_path_list[i] = 0;
            number_of_edges[i] = 0;
        }

        for (int i = 1; i != number_of_rows + 1; i++) {
            lzw::rd_int(starting_point);
            lzw::rd_int(end_point);
            lzw::rd_int(weight);
            list->add_adjacenct_cell(starting_point, end_point, weight);
            number_of_edges[starting_point]++;
        }

        // list->show();

        for (int i = 0; i != number_of_points; i++) {
            if (source == i + 1) {
                continue;
            }
            lzw::Node<int> *node = new lzw::Node<int>;
            node->index = i + 1;
            node->weight = 100000000;
            queue->enqueue(node);
        }

        shortest_path_list[source] = 0;
        position = 0;
        while(position != number_of_edges[source]) {
            neighbor_point = list->get_adjacency_cell(source, position);
            queue->relax(neighbor_point->index, neighbor_point->weight);
            position++;
        }
        
        while (!queue->isEmpty()) {
            np = queue->dequeue();
            if (np->weight == 100000000) {
                shortest_path_list[np->index] = -1;
                continue;
            }
            shortest_path_list[np->index] = np->weight;
            position = 0;
            while (position != number_of_edges[np->index]) {
                neighbor_point = list->get_adjacency_cell(np->index, position);
                queue->relax(neighbor_point->index, np->weight + neighbor_point->weight);
                position++;
            }
        }
        delete [] number_of_edges;

        for (int i = 1; i != number_of_points + 1; i++) {
            lzw::pr_int(shortest_path_list[i], '\n');
        }
        return 0;
    // } catch (const char* mesg) {
    //     std::cerr << mesg << std::endl;
    // } catch (...) {

    // }
}
