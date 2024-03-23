#include "kNN.hpp"
/* TODO: You can implement methods, functions that support your data structures here.
 * */
template <class T>
DLinkedList<T>::DLinkedList()
{
    head = tail = NULL;
    size = 0;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &other)
{
    head = tail = NULL;
    size = 0;
    for (int i = 0; i < other.length(); i++)
    {
        push_back(other.get(i));
    }
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &other)
{
    if (this != &other)
    {
        clear();
        for (int i = 0; i < other.length(); ++i)
        {
            push_back(other.get(i));
        }
    }
    return *this;
}

template <class T>
void DLinkedList<T>::push_back(T value)
{
    Node *pNew = new Node(value);
    if (head == NULL)
    {
        head = tail = pNew;
    }
    else
    {
        tail->next = pNew;
        pNew->previous = tail;
        tail = pNew;
    }
    size++;
}

template <class T>
void DLinkedList<T>::push_front(T value)
{
    Node *pNew = new Node(value);
    if (head == NULL)
    {
        head = tail = pNew;
    }
    else
    {
        head->previous = pNew;
        pNew->next = head;
        head = pNew;
    }
    size++;
}

template <class T>
void DLinkedList<T>::insert(int index, T value)
{
    if (index < 0 || index > size)
    {
        return;
    }
    else if (index == size)
    {
        push_back(value);
    }
    else if (index == 0)
    {
        push_front(value);
    }
    else
    {
        Node *pNew = new Node(value);
        Node *curNode = head;
        for (int i = 0; i < index - 1; i++)
        {
            curNode = curNode->next;
        }
        pNew->next = curNode->next;
        pNew->previous = curNode;
        curNode->next->previous = pNew;
        curNode->next = pNew;
        size++;
    }
}

template <class T>
void DLinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        return;
    }
    else if (size == 1)
    {
        delete head;
        head = tail = NULL;
        size = 0;
    }
    else if (index == 0)
    {
        Node *temp = head;
        head = head->next;
        if (head != NULL)
        {
            head->previous = NULL;
        }
        else
        {
            tail = NULL;
        }
        delete temp;
        size--;
    }
    else if (index == size - 1)
    {
        Node *p = tail;
        tail = tail->previous;
        tail->next = NULL;
        delete p;
        size--;
    }
    else
    {
        Node *curNode = head;
        for (int i = 0; i < index; i++)
        {
            curNode = curNode->next;
        }
        curNode->previous->next = curNode->next;
        curNode->next->previous = curNode->previous;
        delete curNode;
        size--;
    }
}

template <class T>
T &DLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= size)
    {
        throw out_of_range("get(): Out of range");
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

template <class T>
int DLinkedList<T>::length() const
{
    return size;
}

template <class T>
void DLinkedList<T>::clear()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = NULL;
    size = 0;
}

template <class T>
void DLinkedList<T>::print() const
{
    Node *temp = head;
    for (int i = 0; i < size - 1; i++)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << temp->data;
}

template <class T>
void DLinkedList<T>::reverse()
{
    Node *curNode = head;
    Node *temp = NULL;
    for (int i = 0; i < size; i++)
    {
        temp = curNode->previous;
        curNode->previous = curNode->next;
        curNode->next = temp;
        curNode = curNode->previous;
    }
    if (temp != NULL)
    {
        head = temp;
    }
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
    Node *temp = head;
    while (temp != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

Dataset::Dataset()
{
    data = new DLinkedList<DLinkedList<int> *>();
    label = new DLinkedList<string>();
}

Dataset::Dataset(const Dataset &other)
{
    this->data = new DLinkedList<DLinkedList<int> *>(*other.data);
    this->label = new DLinkedList<string>(*other.label);
}

Dataset &Dataset::operator=(const Dataset &other)
{
    if (this != &other)
    {
        delete data;
        delete label;
        this->data = new DLinkedList<DLinkedList<int> *>(*other.data);
        this->label = new DLinkedList<string>(*other.label);
    }
    return *this;
}

bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream fName(fileName);
    if (fName.is_open())
    {
        string line;
        bool check = 1;
        while (getline(fName, line))
        {
            if (check == 1)
            {
                string tmp;
                stringstream ss(line);
                while (getline(ss, tmp, ','))
                {
                    label->push_back(tmp);
                }
                check = 0;
            }
            else
            {
                DLinkedList<int> *newList = new DLinkedList<int>();
                string tmp;
                stringstream ss(line);
                while (getline(ss, tmp, ','))
                {
                    int a = stoi(tmp);
                    newList->push_back(a);
                }
                data->push_back(newList);
            }
        }
        fName.close();
        return true;
    }
    return false;
}

void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
    {
        return;
    }
    int new_nCols = min(nCols, label->length());
    if (nCols > 0)
    {
        if (new_nCols == 1)
        {
            cout << label->get(0);
        }
        else
        {
            for (int i = 0; i < new_nCols - 1; i++)
            {
                cout << label->get(i) << " ";
            }
            cout << label->get(new_nCols - 1);
        }
        cout << endl;
    }
    if (nRows > 0)
    {
        int new_nRows = min(nRows, data->length());
        for (int i = 0; i < new_nRows; i++)
        {
            List<int> *newData = data->get(i);
            if (label->length() == 1)
            {
                cout << newData->get(0);
            }
            else
            {
                for (int j = 0; j < new_nCols - 1; j++)
                {
                    cout << newData->get(j) << " ";
                }
                cout << newData->get(new_nCols - 1);
            }
            if (i != new_nRows - 1)
            {
                cout << endl;
            }
        }
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
    {
        return;
    }
    int new_nCols = min(nCols, label->length());
    if (nCols > 0)
    {
        if (new_nCols == 1)
        {
            cout << label->get(0);
        }
        else
        {
            for (int i = label->length() - new_nCols; i < label->length() - 1; i++)
            {
                cout << label->get(i) << " ";
            }
            cout << label->get(label->length() - 1);
        }
        cout << endl;
    }
    if (nRows > 0)
    {
        int new_Rows = max(0, data->length() - nRows);
        for (int i = new_Rows; i < data->length(); i++)
        {
            List<int> *newData = data->get(i);
            if (label->length() == 1)
            {
                cout << newData->get(0);
            }
            else
            {
                for (int j = label->length() - nCols; j < label->length() - 1; j++)
                {
                    cout << newData->get(j) << " ";
                }
                cout << newData->get(label->length() - 1);
            }
            if (i != (data->length() - 1))
            {
                cout << endl;
            }
        }
    }
}

void Dataset::getShape(int &nRows, int &nCols) const
{
    nRows = data->length();
    nCols = label->length();
}

void Dataset::columns() const
{
    label->print();
}

bool Dataset::drop(int axis, int index, string columns)
{
    if (axis != 0 && axis != 1)
    {
        return false;
    }
    else if (axis == 0)
    {
        if (index >= data->length() || index < 0)
        {
            return false;
        }
        else
        {
            data->get(index)->clear();
            return true;
        }
    }
    else
    {
        for (int i = 0; i < label->length(); i++)
        {
            if (columns == label->get(i))
            {
                label->remove(i);
                for (int j = 0; j < data->length(); j++)
                {
                    data->get(j)->remove(i);
                }
                return true;
            }
        }
        return false;
    }
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset extractedData;
    if (endRow < -1 || endCol < -1 || startRow < 0 || startCol < 0)
    {
        extractedData.data->get(0)->get(-2);
    }
    if (endRow == -1)
    {
        endRow = data->length() - 1;
    }
    if (endCol == -1)
    {
        endCol = label->length() - 1;
    }
    if (endCol != -1)
    {
        for (int i = endCol; i >= startCol; i--)
        {
            extractedData.label->push_front(label->get(i));
        }
    }
    if (endRow != -1)
    {
        for (int i = endRow; i >= startRow; i--)
        {
            if (i < 0 || i >= data->length())
                continue;
            DLinkedList<int> *newData = new DLinkedList<int>;
            for (int j = endCol; j >= startCol; j--)
            {
                if (j < 0 || j >= data->get(i)->length())
                    continue;
                newData->push_front(data->get(i)->get(j));
            }
            extractedData.data->push_front(newData);
        }
    }
    return extractedData;
}

DLinkedList<DLinkedList<int> *> *Dataset::getData() const
{
    return this->data;
}

DLinkedList<string> *Dataset::getLabel() const
{
    return this->label;
}

kNN::kNN(int k)
{
    this->k = k;
}

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    X_train_rows = X_train.getData()->length();
    y_train_rows = y_train.getData()->length();
    if (X_train_rows != y_train_rows)
    {
        return;
    }
    else
    {
        this->X_train = X_train;
        this->y_train = y_train;
    }
}

double kNN::Euclidean(DLinkedList<int> *p1, DLinkedList<int> *p2) const
{
    double sum = 0.0;
    for (int i = 0; i < p1->length(); i++)
    {
        double temp = p1->get(i) - p2->get(i);
        sum += temp * temp;
    }
    sum = sqrt(sum);
    return sum;
}

int kNN::predictLabel(DLinkedList<double> *dis, int k_nearest) const
{
    DLinkedList<double> *new_dis = new DLinkedList<double>();
    DLinkedList<int> *index = new DLinkedList<int>();
    for (int i = 0; i < dis->length(); i++)
    {
        new_dis->push_back(dis->get(i));
        index->push_back(i);
    }

    // sort
    if (dis->length() > k)
    {
        for (int i = 0; i < k; i++)
        {
            int minIndex = i;
            double minDis = new_dis->get(i);
            for (int j = i + 1; j < new_dis->length(); j++)
            {
                if (new_dis->get(j) < minDis)
                {
                    minIndex = j;
                    minDis = new_dis->get(j);
                }
            }
            if (minIndex != i)
            {
                swap(new_dis->get(i), new_dis->get(minIndex));
                swap(index->get(i), index->get(minIndex));
            }
        }
    }

    // find y
    int predict_y = y_train.getData()->get(index->get(0))->get(0);
    int count = 1;
    for (int i = 0; i < k && i < new_dis->length(); i++)
    {
        int curVal = y_train.getData()->get(index->get(i))->get(0);
        int curCount = 0;
        for (int j = 0; j < k && j < new_dis->length(); j++)
        {
            if (y_train.getData()->get(index->get(j))->get(0) == curVal)
            {
                curCount++;
            }
        }
        if (count < curCount)
        {
            count = curCount;
            predict_y = curVal;
        }
        else if (count == curCount)
        {
            if (predict_y > curVal)
            {
                predict_y = curVal;
            }
        }
    }
    delete new_dis;
    delete index;
    return predict_y;
}

Dataset kNN::predict(const Dataset &X_test)
{
    Dataset predictedData;
    if (X_train.getLabel()->length() != 0)
    {
        predictedData.getLabel()->push_back("label");
    }
    for (int i = 0; i < X_test.getData()->length(); i++)
    {
        DLinkedList<double> *dis = new DLinkedList<double>();
        for (int j = 0; j < X_train.getData()->length(); j++)
        {
            dis->push_back(Euclidean(X_train.getData()->get(j), X_test.getData()->get(i)));
        }
        int label_y_train = predictLabel(dis, this->k);
        DLinkedList<int> *temp = new DLinkedList<int>();
        temp->push_back(label_y_train);
        predictedData.getData()->push_back(temp);
    }
    return predictedData;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    double correct = 0.0;
    for (int i = 0; i < y_test.getData()->length(); i++)
    {
        if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0))
        {
            correct++;
        }
    }
    double accuracy = correct / y_test.getData()->length();
    return accuracy;
}
void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int train_set_size = int(X.getData()->length() * (1 - test_size));
    X_train = X.extract(0, train_set_size - 1, 0, -1);
    X_test = X.extract(train_set_size, -1, 0, -1);
    y_train = y.extract(0, train_set_size - 1, 0, -1);
    y_test = y.extract(train_set_size, -1, 0, -1);
}