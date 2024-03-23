#include "kNN.hpp"

void tc1()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract();
    dataset_extract.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

int main()
{
    tc1();
    return 0;
}