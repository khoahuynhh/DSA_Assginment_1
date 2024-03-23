#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template <typename T>
class DLinkedList : public List<T>
{
public:
    class Node;

protected:
    Node *head;
    Node *tail;
    int size;

public:
    DLinkedList();
    ~DLinkedList();
    DLinkedList(const DLinkedList<T> &other);
    DLinkedList<T> &operator=(const DLinkedList<T> &other);
    void sort();
    void push_back(T value) override;
    void push_front(T value) override;
    void insert(int index, T value) override;
    void remove(int index) override;
    T &get(int index) const override;
    int length() const override;
    void clear() override;
    void print() const override;
    void reverse() override;

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};

class Dataset
{
private:
    DLinkedList<DLinkedList<int> *> *data;
    DLinkedList<string> *label;
    // You may need to define more

public:
    Dataset();
    ~Dataset() = default;
    Dataset(const Dataset &other);
    Dataset &operator=(const Dataset &other);
    bool loadFromCSV(const char *fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int &nRows, int &nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    DLinkedList<DLinkedList<int> *> *getData() const;
    DLinkedList<string> *getLabel() const;
};

class kNN
{
private:
    int k;
    int X_train_rows;
    int y_train_rows;
    Dataset X_train;
    Dataset y_train;
    // You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset &X_train, const Dataset &y_train);
    double Euclidean(DLinkedList<int> *p1, DLinkedList<int> *p2) const;
    int predictLabel(DLinkedList<double> *dis, int k_nearest) const;
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test);

// Please add more or modify as needed