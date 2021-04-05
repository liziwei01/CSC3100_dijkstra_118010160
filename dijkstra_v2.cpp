#include <stdio.h>

struct Node {
    int index;
    int weight;
};

class MyList {
    
public:

    MyList();
    ~MyList();
    void clean(int &index);
    void initialize(int number_of_points);
    void initialize_list(int index, int size);
    int size() const;
    bool isEmpty() const;
    void add(int &index);
    void add_adjacenct_cell(int &index, int &adj, int &weight);
    Node *get_adjacency_head(int &index, int &position) const;

private:

    Node ***array;
    Node *null_node = new Node;
    int *num_edges;
    int count;
};

MyList::MyList() {
    null_node->index = 0;
    null_node->weight = 0;
}

MyList::~MyList() {
    delete [] array;
    delete [] num_edges;
}

void MyList::clean(int &index) {
    delete [] array[index];
}

void MyList::initialize(int number_of_points = 1) {
    array = new Node **[number_of_points + 2];
    array[0] = new Node *[2];
    for (int i = 0; i != 2; i++) {
        array[0][i] = null_node;
    }
    num_edges = new int[number_of_points + 2];
    for (int i = 0; i != number_of_points + 2; i++) {
        num_edges[i] = 0;
    }
    count = 0;
}

void MyList::initialize_list(int index = 1, int size = 1) {
    array[index] = new Node *[size + 2];
    for (int j = 0; j != size + 2; j++) {
        array[index][j] = null_node;
    }
}

int MyList::size() const {
    return count;
}

bool MyList::isEmpty() const {
    return (count == 0);
}

void MyList::add(int &index) {
    Node *np = new Node;
    np->index = index;
    np->weight = 0;
    count++;
    array[index][0] = np;
}

void MyList::add_adjacenct_cell(int &index, int &adj, int &weight) {
    Node *np = new Node;
    np->index = adj;
    np->weight = weight;
    num_edges[index]++;
    array[index][ num_edges[index] ] = np;
}

Node *MyList::get_adjacency_head(int &index, int &position) const {
    return array[index][position];
}

class MyHeap {

public:

    MyHeap();
    ~MyHeap();
    void initialize(int number_of_points);
    int size() const;
    bool isEmpty() const;
    void clear();
    void enqueue(Node *np);
    Node *dequeue();
    Node *peek() const;
    void relax(int &index, int &relaxed_weight);

private:

    int *position_array;
    Node **array;
    Node *null_node = new Node;
    int count;
    void min_heapify(int i);
    int heap_increase_level(int i);
    void heap_increase_node(int i);
    void swap(int i, int j);
    int parent(int i) const;
    int left(int i) const;
    int right(int i) const;
};

MyHeap::MyHeap() {
    null_node->index = 0;
    null_node->weight = 0;
    count = 0;
}

MyHeap::~MyHeap() {
    clear();
}

void MyHeap::initialize(int number_of_points = 1) {
    position_array = new int[number_of_points + 2];
    array = new Node *[number_of_points + 2];
    for (int i = 0; i != number_of_points + 2; i++) {
        position_array[i] = 0;
        array[i] = null_node;
    }
}

int MyHeap::size() const {
    return count;
}

bool MyHeap::isEmpty() const {
    return (count == 0);
}

void MyHeap::clear() {
    while (count != 0) {
        dequeue();
    }
}

void MyHeap::enqueue(Node *np) {
    count++;
    array[count] = np;
    position_array[np->index] = count;
    heap_increase_node(count);
}

Node *MyHeap::dequeue() {
    if (isEmpty()) {
        return null_node;
    }
    Node *minimum = array[1];
    position_array[array[count]->index] = 1;
    position_array[minimum->index] = 0;
    array[1] = array[count];
    array[count] = null_node;
    count--;
    min_heapify(1);
    return minimum;
}

Node *MyHeap::peek() const {
    if (isEmpty()) {
       return null_node;
    }
    return array[1];
}

void MyHeap::relax(int &index, int &relaxed_weight) {
    int i = position_array[index];
    bool max_num_bool = (array[i]->weight == 100000000);
    if (i == 0) {
        return;
    }
    if (array[i] == null_node) {
        return;
    }
    if (array[i]->weight > relaxed_weight) {
        array[i]->weight = relaxed_weight;
        if (max_num_bool) {
            i = heap_increase_level(i);
        }
        heap_increase_node(i);  
    }
}

void MyHeap::min_heapify(int i) {
    if (array[i] == null_node || i > count) {
        return;
    }
    if (array[left(i)] == null_node || left(i) > count) {
        return;
    }
    if (array[right(i)] == null_node || right(i) > count) {
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

int MyHeap::heap_increase_level(int i) {
    int original = i;
    while (i != 1 && array[parent(i)]->weight == 100000000) {
        i = parent(i);
    }
    swap(i, original);
    return i;
}

void MyHeap::heap_increase_node(int i) {
    while (i != 1 && array[parent(i)]->weight > array[i]->weight) {
        swap(parent(i), i);
        i = parent(i);
    }
}

void MyHeap::swap(int i, int j) {
    int ip = position_array[array[i]->index];
    position_array[array[i]->index] = position_array[array[j]->index];
    position_array[array[j]->index] = ip;
    Node *middle = array[i];
    array[i] = array[j];
    array[j] = middle;
}

int MyHeap::parent(int i) const {
    return i / 2;
}

int MyHeap::left(int i) const {
    return 2 * i;
}

int MyHeap::right(int i) const {
    return 2 * i + 1;
}

void pr_uint(int n) {
    if (n / 10 != 0) {
        pr_uint(n / 10);
    }
    putchar_unlocked((n % 10) + '0');
}

void pr_int(int n) {
    if (n == -1) {
        putchar_unlocked('-');
        n = -n;
    }
    pr_uint(n);
}

int main() {
    Node *np;
    Node *neighbor_point;
    MyList *list = new MyList;
    MyHeap *queue = new MyHeap;
    bool non_linked = true;
    int number_of_points, number_of_rows, source, starting_point, end_point, weight, position, edge_num, new_weight, input_int;
    
    input_int = 0;
    char ch = getchar_unlocked();
    while (ch < '0'|| ch > '9') {
        ch = getchar_unlocked();
    }
    while( ch >= '0' && ch <= '9' ) {
        input_int = input_int * 10 + ch - '0';
        ch=  getchar_unlocked();
    }
    number_of_points = input_int;
    input_int = 0;
    while (ch < '0'|| ch > '9') {
        ch = getchar_unlocked();
    }
    while( ch >= '0' && ch <= '9' ) {
        input_int = input_int * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    number_of_rows = input_int;
    input_int = 0;
    while (ch < '0'|| ch > '9') {
        ch = getchar_unlocked();
    }
    while( ch >= '0' && ch <= '9' ) {
        input_int = input_int * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    source = input_int;
    list->initialize(number_of_points);
    queue->initialize(number_of_points);
    int *shortest_path_list = new int[number_of_points + 2];
    int *number_of_edges = new int[number_of_points + 2];
    int *sp_input = new int[number_of_rows + 2];
    int *e_input = new int[number_of_rows + 2];
    int *w_input =new int[number_of_rows + 2];
    
    for (int i = 0; i != number_of_points + 2; i++) {
        shortest_path_list[i] = 0;
        number_of_edges[i] = 0;
    }
    for (int i = 0; i != number_of_rows + 2; i++) {
        sp_input[i] = 0;
        e_input[i] = 0;
        w_input[i] = 0;
    }
    
    for (int i = 1; i != number_of_rows + 1; i++) {
        input_int = 0;
        char ch = getchar_unlocked();
        while (ch < '0'|| ch > '9') {
            ch = getchar_unlocked();
        }
        while( ch >= '0' && ch <= '9' ) {
            input_int = input_int * 10 + ch - '0';
            ch=  getchar_unlocked();
        }
        starting_point = input_int;
        input_int = 0;
        while (ch < '0'|| ch > '9') {
            ch = getchar_unlocked();
        }
        while( ch >= '0' && ch <= '9' ) {
            input_int = input_int * 10 + ch - '0';
            ch = getchar_unlocked();
        }
        end_point = input_int;
        input_int = 0;
        while (ch < '0'|| ch > '9') {
            ch = getchar_unlocked();
        }
        while( ch >= '0' && ch <= '9' ) {
            input_int = input_int * 10 + ch - '0';
            ch = getchar_unlocked();
        }
        weight = input_int;
        sp_input[i] = starting_point;
        e_input[i] = end_point;
        w_input[i] = weight;
        if (starting_point == source) {
            non_linked = false;
        }
        number_of_edges[starting_point]++;
    }

    if (non_linked) {
        for (int i = 0; i != number_of_points; i++) {
            if ((i + 1) == source) {
                printf("%d\n", 0);
            } else {
                printf("%d\n", -1);
            }
        }
        return 0;
    }

    for (int i = 1; i != number_of_points + 1; i++) {
        list->initialize_list(i, number_of_edges[i]);
    }

    for (int i = 1; i != number_of_points + 1; i++) {
        list->add(i);
    }

    for (int i = 1; i != number_of_rows + 1; i++) {
        starting_point = sp_input[i];
        end_point = e_input[i];
        weight = w_input[i];
        list->add_adjacenct_cell(starting_point, end_point, weight);
    }
    delete [] sp_input;
    delete [] e_input;
    delete [] w_input;
    
    for (int i = 0; i != number_of_points; i++) {
        if (source == i + 1) {
            continue;
        }
        Node *node = new Node;
        node->index = i + 1;
        
        node->weight = 100000000;
        queue->enqueue(node);
    }

    shortest_path_list[source] = 0;
    edge_num = number_of_edges[source];
    position = 1;
    while(position != (edge_num + 1)) {
        neighbor_point = list->get_adjacency_head(source, position);
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
        edge_num = number_of_edges[np->index];
        position = 1;
        while (position != (edge_num + 1)) {
            neighbor_point = list->get_adjacency_head(np->index, position);
            new_weight = np->weight + neighbor_point->weight;
            queue->relax(neighbor_point->index, new_weight);
            position++;
        }
    }

    for (int i = 1; i != number_of_points + 1; i++) {
        pr_int(shortest_path_list[i]);
        putchar_unlocked('\n');
    }
    return 0;
}
