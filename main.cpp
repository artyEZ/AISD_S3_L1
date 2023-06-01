#include <iostream>
#include <vector>
#include <algorithm>

class Set {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* copyTree(const Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);

        return newNode;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    void print_(const Node* node) const {
        if (node == nullptr) {
            return;
        }

        print_(node->left);
        std::cout << node->value << " ";
        print_(node->right);
    }

    bool insert_(Node*& node, int key) {
        if (node == nullptr) {
            node = new Node(key);
            return true;
        }

        if (key < node->value) {
            return insert_(node->left, key);
        }
        else if (key > node->value) {
            return insert_(node->right, key);
        }

        return false;
    }

    bool contains_(const Node* node, int key) const {
        if (node == nullptr) {
            return false;
        }

        if (key < node->value) {
            return contains_(node->left, key);
        }
        else if (key > node->value) {
            return contains_(node->right, key);
        }

        return true;
    }

    Node* findMinValueNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    bool erase_(Node*& node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key < node->value) {
            return erase_(node->left, key);
        }
        else if (key > node->value) {
            return erase_(node->right, key);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* minValueNode = findMinValueNode(node->right);
                node->value = minValueNode->value;
                erase_(node->right, minValueNode->value);
            }

            return true;
        }
    }

public:
    Set() : root(nullptr) {}

    Set(const Set& other) {
        root = copyTree(other.root);
    }

    ~Set() {
        clear();
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root);
        }
        return *this;
    }

    void print() const {
        print_(root);
        std::cout << std::endl;
    }

    bool insert(int key) {
        return insert_(root, key);
    }

    bool contains(int key) const {
        return contains_(root, key);
    }

    bool erase(int key) {
        return erase_(root, key);
    }
};


//Тесты
size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}
double avg(const double* arr) {
    double sum = 0;
    for (size_t i = 0; i < 100; ++i) {
        sum += arr[i];
    }
    return sum / 100;
}

double avg1000(const double* arr) {
    double sum = 0;
    for (size_t i = 0; i < 1000; ++i) {
        sum += arr[i];
    }
    return sum / 1000;
}

void insert_tree(size_t count) {
    double time[100]{};
    for (size_t i = 0; i < 100; ++i) {
        Set tree;
        clock_t begin = clock();
        for (size_t j = 0; j < count; ++j) {
            tree.insert(static_cast<int>(lcg()));
        }
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время заполнения двоичного дерева поиска: " << avg(time) << std::endl;
}

void insert_vector(size_t count) {
    double time[100]{};
    for (size_t i = 0; i < 100; ++i) {
        std::vector<size_t> vector;
        clock_t begin = clock();
        for (size_t j = 0; j < count; ++j) {
            vector.push_back(lcg());
        }
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время заполнения вектора: " << avg(time) << std::endl;
}

void search_tree(size_t count) {
    double time[1000]{};
    Set tree;
    for (size_t j = 0; j < count; ++j) {
        tree.insert(static_cast<int>(lcg()));
    }
    for (size_t i = 0; i < 1000; ++i) {
        clock_t begin = clock();
        tree.contains(static_cast<int>(lcg()));
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время поиска случайного числа в двоичном дереве поиска: " << avg1000(time) << std::endl;
}

void search_vector(size_t count) {
    double time[1000]{};
    std::vector<size_t> vector;
    for (size_t j = 0; j < count; ++j) {
        vector.push_back(static_cast<int>(lcg()));
    }
    for (size_t i = 0; i < 1000; ++i) {
        size_t elem = lcg();
        clock_t begin = clock();
        for (auto it = vector.begin(); it != vector.end(); ++it) {
            if (*it == elem) {
                break;
            }
        }
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время поиска случайного числа в векторе: " << avg1000(time) << std::endl;
}

void add_tree(size_t count) {
    double time[1000]{};
    for (size_t i = 0; i < 1000; ++i) {
        Set tree;
        for (size_t j = 0; j < count; ++j) {
            tree.insert(static_cast<int>(lcg()));
        }
        clock_t begin = clock();
        tree.insert(static_cast<int>(lcg()));
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время добавления случайного числа в двоичное дерево поиска: " << avg1000(time) << std::endl;
}

void add_vector(size_t count) {
    double time[1000]{};
    for (size_t i = 0; i < 1000; ++i) {
        std::vector<size_t> vector;
        for (size_t j = 0; j < count; ++j) {
            vector.push_back(static_cast<int>(lcg()));
        }
        clock_t begin = clock();
        vector.push_back(lcg());
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время добавления случайного числа в вектор: " << avg1000(time) << std::endl;
}

void erase_tree(size_t count) {
    double time[1000]{};
    for (size_t i = 0; i < 1000; ++i) {
        Set tree;
        for (size_t j = 0; j < count; ++j) {
            tree.insert(static_cast<int>(lcg()));
        }
        clock_t begin = clock();
        tree.erase(static_cast<int>(lcg()));
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время удаления случайного числа в двоичное дерево поиска: " << avg1000(time) << std::endl;
}

void erase_vector(size_t count) {
    double time[1000]{};
    for (size_t i = 0; i < 1000; ++i) {
        std::vector<size_t> vector;
        for (size_t j = 0; j < count; ++j) {
            vector.push_back(static_cast<int>(lcg()));
        }
        size_t elem = lcg();
        clock_t begin = clock();
        for (auto it = vector.begin(); it != vector.end(); ++it) {
            if (*it == elem) {
                vector.emplace(it);
                break;
            }

        }
        clock_t end = clock();
        time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
    }
    std::cout << "Среднее время удаления случайного числа в векторе: " << avg1000(time) << std::endl;
}

std::vector<int> getUniqueElements(const std::vector<int>& input) {
    std::vector<int> uniqueElements;

    for (int num : input) {
        if (std::find(uniqueElements.begin(), uniqueElements.end(), num) == uniqueElements.end()) {
            uniqueElements.push_back(num);
        }
    }

    return uniqueElements;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Set set;

    // Вставка элементов
    set.insert(5);
    set.insert(2);
    set.insert(7);
    set.insert(3);
    set.insert(1);
    set.insert(6);
    set.insert(4);

    // Печать содержимого
    set.print(); // Ожидаемый вывод: 1 2 3 4 5 6 7

    // Проверка наличия элемента
    bool contains1 = set.contains(4);
    bool contains2 = set.contains(8);

    std::cout << "Contains 4: " << std::boolalpha << contains1 << std::endl; // Ожидаемый вывод: true
    std::cout << "Contains 8: " << std::boolalpha << contains2 << std::endl; // Ожидаемый вывод: false

    // Удаление элемента
    bool erase1 = set.erase(3);
    bool erase2 = set.erase(9);

    std::cout << "Erase 3: " << std::boolalpha << erase1 << std::endl; // Ожидаемый вывод: true
    std::cout << "Erase 9: " << std::boolalpha << erase2 << std::endl; // Ожидаемый вывод: false

    // Печать содержимого после удаления элемента
    set.print(); // Ожидаемый вывод: 1 2 4 5 6 7


    // Задача по варианту 
    std::vector<int> input = { 3, 2, 2, 4 };
    std::vector<int> uniqueElements = getUniqueElements(input); // Ожидаемый вывод: 3 2 4

    std::cout << "Unique elements:";
    for (int num : uniqueElements) {
        std::cout << " " << num;
    }
    std::cout << std::endl;

    /*system("cls");
    insert_tree(1000);
    insert_tree(10000);
    insert_tree(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    insert_vector(1000);
    insert_vector(10000);
    insert_vector(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    search_tree(1000);
    search_tree(10000);
    search_tree(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    search_vector(1000);
    search_vector(10000);
    search_vector(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    add_tree(1000);
    add_tree(10000);
    add_tree(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    add_vector(1000);
    add_vector(10000);
    add_vector(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    erase_tree(1000);
    erase_tree(10000);
    erase_tree(100000);
    std::cout << "-------------------------------------------------------------------" << std::endl;
    erase_vector(1000);
    erase_vector(10000);
    erase_vector(100000);*/

    return 0;
}