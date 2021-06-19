//**********************************************************
// File Name: CFASSIGNMENT2.cpp
// Author: Chris Flores
// Copyright: This program is not to be distributed. CF 2021
// Description: This program allows users to view the prices of
// of orders placed from a text file
//
// Date        Author          Comment
// 1.20.20     Chris Flores     Initial Creation
// 1.21.20                     Finished InventoryItem and Product
// 1.22.20                     Working on InventorySystem
// 1.24.20                     Working on BuildInventory
// 1.25-28.20                  Stuck on Auto loop No viable begin function error
// 1.29.21                     Finished BuildInventory
// 1.30.21
// 2.01.21                     Working on Menu and Extra Credit while loop
// 2.02.21                     Debugging search only finding first element
// 2.03.21                     Debugging FindItem and Discontinue
// 2.04.21
// 2.6.21                      Realized that FindInventoryItem only finds items with
//                             item_id > 1000 so I must add leading zeros to user input
//                             item_id < 1000 in order to match setfill(0) item_id
// 2.8.21                      Had an epiphany and realized my binary search was
//                             worthless without a Sort function. None of which
//                             are mentioned in specs. Perhaps I should've stuck to linear search.
// 2.9.21                      Reverting to Non Extra Credit Mode in order to
//                             submit a working program.
                                    
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class InventoryItem{
public:
    static const int DEFAULT_ITEM_ID;
    static const bool DEFAULT_RESTOCK;
    InventoryItem();
    InventoryItem(int item_id, bool hasRestock);
    ~InventoryItem();
    InventoryItem set_item_id(int item_id);
    InventoryItem set_hasRestock(bool hasRestock);
    int get_item_id() const;
    bool get_hasRestock() const;
    string Display() const;
protected:
    int item_id;
    bool hasRestock;
};

class Product : public InventoryItem{
public:
    static const string DEFAULT_NAME;
    static const int DEFAULT_QUANTITY;
    static const double DEFAULT_PRICE;
    Product();
    Product(int item_id, bool hasRestock, string name, int quantity, double price);
    ~Product();
    Product set_name(string name);
    Product set_quantity(int quantity);
    Product set_price(double price);
    string get_name() const;
    int get_quantity() const;
    double get_price() const;
    string Display() const;
    double Cost(int & quantity);
private:
    string name;
    int quantity;
    double price;
};

class InventorySystem{
public:
    static const int MAX_ITEMS = 512;
    static const string DEFAULT_STORE_NAME;
    static const int DEFAULT_STORE_ID;
    static const int DEFAULT_PRODUCT_COUNT;
    static const string INPUT_FILE_NAME;
    static const string OUTPUT_FILE_NAME;
    InventorySystem set_store_name(string store_name);
    InventorySystem set_product_count(int product_count);
    string get_store_name() const;
    int get_store_id() const;
    int get_product_count() const;
    InventorySystem();
    InventorySystem(string store_name);
    ~InventorySystem();
    void BuildInventory();
    void ShowInventory();
    void UpdateInventory();
    void Terminate();
    void Discontinue();
    void Run();
    void Menu();
    void Quit();
private:
    string store_name;
    int product_count = 0;
    InventoryItem * product_list[InventorySystem::MAX_ITEMS];
    InventoryItem * FindInventoryItem(int item_id);
    void Sort();
};

int main(){
    InventorySystem * p_inventory_master = nullptr;
    p_inventory_master = new InventorySystem("CS2B 'Tronics'");
    p_inventory_master->BuildInventory();
    p_inventory_master->ShowInventory();
    p_inventory_master->UpdateInventory();
    p_inventory_master->Terminate();
    delete p_inventory_master;
}

//********************************************************
//              InventoryItem Definitions                *
//********************************************************
//Static Data
const int InventoryItem::DEFAULT_ITEM_ID = 9999;
const bool InventoryItem::DEFAULT_RESTOCK = false;

//Constructors
InventoryItem::InventoryItem() : item_id(InventoryItem::DEFAULT_ITEM_ID), hasRestock(InventoryItem::DEFAULT_RESTOCK){}
InventoryItem::InventoryItem(int item_id, bool hasRestock) : item_id(item_id), hasRestock(hasRestock){}

//Destructor
InventoryItem::~InventoryItem() { cout << "\n\t\tInventoryItem <" << item_id << "> with <" << hasRestock << "> restocking destroyed...\n"; }

//Mutators
InventoryItem InventoryItem::set_item_id(int item_id) {this->item_id = item_id; return *this;}
InventoryItem InventoryItem::set_hasRestock(bool hasRestock) {this->hasRestock = hasRestock;return*this;}

//Accesors
int InventoryItem::get_item_id() const { return this-> item_id;}
bool InventoryItem::get_hasRestock() const { return this-> hasRestock;}

//Behavior Function
string InventoryItem::Display() const{
    ostringstream outputstream;
        if(item_id < 1000){
            outputstream << "\n\t\t" << setfill('0') << setw(4) << item_id << "\tRestock = " << hasRestock;
        }
        else{
            outputstream << "\n\t\t" << item_id << "\tRestock = " << hasRestock;
        }
    return outputstream.str();
}

//*******************************************************
//                  Product Definitions                 *
//*******************************************************
//Static Data
const string Product::DEFAULT_NAME = "No Product";
const int Product::DEFAULT_QUANTITY = 0;
const double Product::DEFAULT_PRICE = 0.99;

//Constructors
Product::Product() : InventoryItem(), name(Product::DEFAULT_NAME), quantity(Product::DEFAULT_QUANTITY), price(Product::DEFAULT_PRICE){}
Product::Product(int item_id, bool hasRestock, string name, int quantity, double price) : InventoryItem(item_id, hasRestock), name(name), quantity(quantity), price(price){}

//Destructor
Product::~Product() { cout << "\n\t\tProduct: <" << InventoryItem::item_id << ">, Name<" << name << ">, quantity<" << quantity << ">, price<" << price << ">, restocking<" << InventoryItem::hasRestock << "> destroyed...\n";}

//Mutators
Product Product::set_name(string name) {this-> name = name; return *this;}
Product Product::set_quantity(int quantity) {this-> quantity = quantity; return *this;}
Product Product::set_price(double price) {this-> price = price; return *this;}

//Accessors
string Product::get_name() const {return this-> name;}
int Product::get_quantity() const {return this-> quantity;}
double Product::get_price() const {return this-> price;}

//Behavior Functions
string Product::Display() const{
    ostringstream outputstream;
    outputstream << fixed << setprecision(2);
    InventoryItem::Display();
    if(InventoryItem::hasRestock){
        outputstream << "*****" << name << "*****" << quantity << "*****$" << price;
    }
    else{
        outputstream << "\t" << name << "\t" << quantity << "\t$" << price;
    }
    return outputstream.str();
}

double Product::Cost(int &quantity){return static_cast<double>(price)*quantity;}

//****************************************************
//          InventorySystem Definitions              *
//****************************************************
//Static Data
const string InventorySystem::DEFAULT_STORE_NAME = "My Store";
const int InventorySystem::DEFAULT_PRODUCT_COUNT = 0;
const string InventorySystem::INPUT_FILE_NAME = "//Users/chrisflores/Documents/ProductList.txt";
const string InventorySystem::OUTPUT_FILE_NAME = "NewProductList.txt";
//Constructors
InventorySystem::InventorySystem() : store_name(InventorySystem::DEFAULT_STORE_NAME), product_count(InventorySystem::DEFAULT_PRODUCT_COUNT){
    for(auto & p_product : product_list){
        p_product = nullptr;
    }
}
InventorySystem::InventorySystem(string store_name) : store_name(store_name){
    for(auto & p_product : product_list){
        p_product = nullptr;
    }
}

//Destructor
InventorySystem::~InventorySystem(){
    for(int i = 0; i < product_count; i++){
        delete static_cast<Product *>(product_list[i]);
    }
}

//Mutators
InventorySystem InventorySystem::set_store_name(string store_name){ this->store_name = store_name; return *this;}
InventorySystem InventorySystem::set_product_count(int product_count){ this->product_count = product_count; return *this;}

//Accessors
string InventorySystem::get_store_name() const { return this->store_name;}
int InventorySystem::get_product_count() const { return this->product_count;}

//Member Functions
InventoryItem * InventorySystem::FindInventoryItem(int item_id){
    InventoryItem * p_item = nullptr;
    int first_index = 0;
    int mid_index = 0;
    int last_index = product_count - 1;

    while(first_index <= last_index){
        mid_index = (first_index + last_index) / 2;
        p_item = product_list[mid_index];
        if(p_item->InventoryItem::get_item_id() == item_id){
            return p_item;
        }
        else if(p_item->InventoryItem::get_item_id() > item_id){
            last_index = mid_index - 1;
        }
        else{
            first_index = mid_index + 1;
        }
    }
    return nullptr;
}

void InventorySystem::BuildInventory(){
    int item_id = 0;
    bool isRestock = false;
    string product_name;
    int quantity = 0;
    double price = 0.0;
    istringstream string_to_component;
    string product_component;
    ifstream input_file(InventorySystem::INPUT_FILE_NAME);
    
    if(!input_file){
        cout << "\n\t\tCaution: File failed to load!\n";
    }
    
    while(getline(input_file, product_component, ';') && product_count < InventorySystem::MAX_ITEMS){
        string_to_component.str(product_component);
        string_to_component >> item_id;
        string_to_component.clear();
        getline(input_file, product_component, ';');
        product_name = product_component;
        getline(input_file, product_component, ';');
        string_to_component.str(product_component);
        string_to_component >> quantity;
        if(quantity <= 0){
            isRestock = true;
        }
        string_to_component.clear();
        getline(input_file, product_component, '\n');
        string_to_component.str(product_component);
        string_to_component >> price;
        string_to_component.clear();
        product_list[product_count++] = new Product(item_id, isRestock, product_name, quantity, price);
    }
    input_file.close();
    Sort();
}

void InventorySystem::ShowInventory(){
    cout << fixed << setprecision(2);
    for(int i = 0; i < product_count; i++){
        if(product_list[i] != nullptr){
        cout << product_list[i]->InventoryItem::Display();
        cout << static_cast<Product *>(product_list[i])->Product::Display();
        }
    }
}

void InventorySystem::UpdateInventory(){
    int item_id = 0;
    int quantity = 0;
    double found_price = 0.0;
    InventoryItem * p_found_item = nullptr;
    Product * p_found_product = nullptr;
    
    cout << "\n\n\t\tEnter the item ID for your product: ";
    cin >> item_id;
    
    p_found_item = FindInventoryItem(item_id);
    
    if(p_found_item != nullptr){
        cout << "\n\t\tNext enter the quantity for product <" << item_id << ">: ";
        cin >> quantity;
        p_found_product = static_cast<Product *>(p_found_item);
        found_price = p_found_product->Cost(quantity);
        cout << "\n\t\tTotal price for " << quantity << " orders of " << p_found_product->get_name() << ": $" << found_price << "\n";
                p_found_product->set_quantity((p_found_product->get_quantity()) - quantity);
                if(p_found_product->get_quantity() <= 0){
                    p_found_product->InventoryItem::set_hasRestock(true);
                    
                }
    }
    else{
        cout << "\n\t\tSorry we dont have the product corresponding to item ID <" << item_id << ">!\n";
    }
}

void InventorySystem::Terminate(){
    ofstream output_file(InventorySystem::OUTPUT_FILE_NAME);
    if(!output_file){
        cout << "\n\t\tCAUTION: File failed to load!";
    }
    
    for(int i = 0; i < product_count; i++){
        if(product_list[i] != nullptr){
        output_file << product_list[i]->InventoryItem::Display() << static_cast<Product *>(product_list[i])->Product::Display();
        }
    }
}

void InventorySystem::Discontinue(){
    InventoryItem * p_discontinue_product = nullptr;
    
    int item_id = 0;
    cout << "\n\t\tEnter the item ID of the product being discontinued: ";
    cin >> item_id;
    
    p_discontinue_product = FindInventoryItem(item_id);
    
    if(p_discontinue_product != nullptr){
        delete p_discontinue_product;
        if(p_discontinue_product != product_list[InventorySystem::product_count-1]){
            for(int i = 0; i < product_count-1; i++){
                if(product_list[i] != nullptr){
            product_list[i] = product_list[i+1];
                }
            }
        }
        --product_count;
        cout << "\n\t\tItem <" << item_id << "> has been Deleted";
    }
    else{
        cout << "\n\t\tSorry we dont have the product with item ID: <" << item_id << "!\n";
    }
}

void InventorySystem::Menu(){
    cout << "\n\t\tWelcome to " << store_name;
    cout << "\n\t\t==========================================\n";
    cout << setw(30) << "" << "<" << store_name << ">\n";
    cout << setw(23) << "" << "A FOOTHILL ELECTRONIC STORE";
    cout << "\n\t\t==========================================\n";
    cout << "\n\t\t1. Quit";
    cout << "\n\t\t2. Continue";
}

void InventorySystem::Quit(){
    cout << "\n\t\tThanks for choosing " << store_name << ", your favorite FOOTHILL electronic store!\n";
}

void InventorySystem::Run(){
    int choice = 0;
    
    do{
        Menu();
        cout << "\n\t\tEnter a choice to keep discontinuing products or quit: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                Quit();
                break;
            case 2:
                continue;
                break;
            default:
                cout << "\n\t\tEnter a valid choice!";
                cin.clear();
                break;
        }
    }while(choice !=1);
}

void InventorySystem::Sort(){
    bool didSwap = true;
    InventoryItem * p_temp_item;
    while(didSwap){
        didSwap = false;
        for(int i = 0; i < product_count - 1; i ++){
            if(product_list[i]->InventoryItem::get_item_id() > product_list[i+1]->InventoryItem::get_item_id()){
                p_temp_item = product_list[i];
                product_list[i] = product_list[i+1];
                product_list[i+1] = p_temp_item;
                didSwap = true;
            }
        }
    }
}
