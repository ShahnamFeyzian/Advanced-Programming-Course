#include <iostream>
#include "CartManager.hpp"
using namespace std;

int main()
{
    CartManager cart_manager;
    cart_manager.add_item(1, 2, 3);
    cart_manager.add_item(1, 4, 5);
    cout << cart_manager.evaluate_cart() << '\n';
}