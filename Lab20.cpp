#include <iostream>
#include <iomanip>
#include <random> // for random numbers
#include <ctime> // for time

using namespace std;
const int SIZE = 3;

class Chair {
private:
    int legs;
    double * prices;
public:
    // constructors
    Chair() {
        prices = new double[SIZE];
        legs = rand() % (4-3+1) + 3;
        for (int i = 0; i < SIZE; i++)
            prices[i] = rand() % ((99999 - 10000 + 1) + 10000) / (double) 100; // random numbers between 100 and 999.99
    }
    Chair(int l, double priceArr[]) { // added array as second parameter
        prices = new double[SIZE];
        legs = l;
        for (int i = 0; i < SIZE; i++)
            prices[i] = priceArr[i]; // setting prices[i] to array
    }

    // setters and getters
    void setLegs(int l)      { legs = l; }
    int getLegs()            { return legs; }

    void setPrices(double p1, double p2, double p3) { 
        prices[0] = p1; prices[1] = p2; prices[2] = p3; 
    }

    double getAveragePrices() {
        double sum = 0;
        for (int i = 0; i < SIZE; i++)
            sum += prices[i];
        return sum / SIZE;
    }

    void print() {
        cout << "CHAIR DATA - legs: " << legs << endl;
        cout << "Price history: " ;
        for (int i = 0; i < SIZE; i++)
            cout << prices[i] << " ";
        cout << endl << "Historical avg price: " << getAveragePrices();
        cout << endl << endl;
    }
};

int main() {
    srand(time(0)); // RNG start
    cout << fixed << setprecision(2);

    //creating pointer to first chair object
    Chair *chairPtr = new Chair;
    chairPtr->setLegs(4);
    chairPtr->setPrices(121.21, 232.32, 414.14);
    chairPtr->print();

    //creating dynamic chair object with constructor
    double priceArr[SIZE]; // creating new priceArr array for parameter constructor, filling with random values
    for (int i = 0; i < SIZE; ++i) {
        priceArr[i] = rand() % ((99999 - 10000 + 1) + 10000) / (double) 100;
    }

    Chair *livingChair = new Chair(3, priceArr);
    livingChair->print();
    delete livingChair;
    livingChair = nullptr;

    //creating dynamic array of chair objects
    Chair *collection = new Chair[SIZE];
    for (int i = 0; i < SIZE; i++)
        collection[i].print();
    
    return 0;
}