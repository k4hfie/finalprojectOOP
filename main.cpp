// NIU 558757
// 7: Laundry, Service, Wash Only, WashAndIron, kg
// 75 = K
// rate = K x 100
// max = 5 + (K % 6)
// TYPE1: costs = units x rate
// TYPE2: costs = units x rate x 2

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#define K 75
#define RATE(x) (x * 100)
#define MAX(x)  (5 + (x % 6))


class Service {
private:
    std::string type;
    int units;

public:
    //Constructor & Destructor
    Service(std::string t, int u) : type(t), units(u) {}
    virtual ~Service() = default;

    // Helper Functions
    std::string getType() const { return type; }
    int getUnits() const { return units; }
    virtual int calculateCost() const = 0;
};

class WashOnly : public Service {
public:
    using Service::Service;
    int calculateCost() const override {
        return getUnits() * RATE(K);
    }
};

class WashAndIron : public Service{
public:
    using Service::Service;
    int calculateCost() const override {
        return getUnits() * RATE(K) * 2;
    }
};

class Manager {
private:
    std::vector<std::unique_ptr<Service>> cart;

public:
    void add(std::unique_ptr<Service> item){
        cart.push_back(std::move(item));
    }

    int calculateTotalCost(){
        int total = 0;
        for (const auto& item : cart)
            total += item->calculateCost();
        return total;
    }

    void showCart(){
        std::cout << "\t\tSERVICE CART\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Type \t\t| Weight \t| Cost\n";
        for (const auto& item : cart){
            std::cout << item->getType() << "\t| " ;
            std::cout << item->getUnits() << " kg\t\t| ";
            std::cout << item->calculateCost() << " IDR\n";
        }
        std::cout << "---------------------------------------------\n";
        std::cout << "\t    TOTAL\t\t| " << calculateTotalCost() << " IDR\n";
        std::cout << "---------------------------------------------\n";
    }
};

int readInt(const std::string& prompt){
    int num = std::stoi(prompt);
    if (num < 0){
        std::cout << "> error: weight must be positive\n";
        return 0;
    }
    
    else if (num > MAX(K)){
        std::cout << "> error: weight must be 1 to " << MAX(K) << " kg\n";
        return 0;
    }

    else
        return num;
}

void showMenu(){
    std::cout << "\t\tLAUNDRY MENU\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "1. Wash Only\n";
    std::cout << "2. Wash & Iron\n";
    std::cout << "3. Show Cart\n";
    std::cout << "4. Exit\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "> ";
}

int main2(void) {
    Manager manager;

    manager.add(std::make_unique<WashOnly>("Wash Only", 2));
    manager.add(std::make_unique<WashAndIron>("Wash & Iron", 3));
    manager.showCart();

    return 0;
}

int main(void) {
    Manager manager;
    
    while(1){
        std::string prompt; 
        int choice;

        showMenu();
        std::cin >> choice;
        switch(choice){
            case 1:
                std::cout << "> enter amount of kg: ";
                std::cin >> prompt;

                if (!readInt(prompt))
                    break;

                else {
                    int units = readInt(prompt);
                    manager.add(std::make_unique<WashOnly>("Wash Only", units));
                }

                break;
                        
            case 2:
                std::cout << "> enter amount of kg: ";
                std::cin >> prompt;

                if(!readInt(prompt))
                    break;
                
                else {
                    int units = readInt(prompt);
                    manager.add(std::make_unique<WashAndIron>("Wash & Iron", units)); 
                }

                break;

            case 3:
                manager.showCart();
                break;

            case 4:
                std::cout << "> exiting program... \n";
                return 0;
            
            default:
                std::cout << "> error: invalid menu choice\n";
                break;
        }

        std::cout << "\n";
    }
}