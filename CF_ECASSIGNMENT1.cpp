//
// File Name: CF_ECASSIGNMENT1.cpp
// Author: Chris Flores
// Copyright: This program is not to be distributed. CF 2021
// Description: This program allows users to search and purchase tickets for up to 32 movies.
//  
// Date     Author          Comment
// 1.4.21  Chris Flores    Created Classes
// 1.5.21  Chris Flores    Trying to do Init function using pointer notation
// 1.6.21  Chris Flores    Trying to resolve "Expected ; after expression" in Sort function
//                         with string compare function
// 1.7.20  Chris Flores    Fixed infinite loop after bad cin input
// 1.9.20  Chris Flores    Debugged FindMovie function to return correct movie
// 1.10.20 Chris Flores    Changed temp Movie Object to instance instead of pointer to Movie
// 1.15.21 Chris Flores    Finally able to initialize remainining 24 elements in Init function
// 1.17.21 Chris Flores    Resolving Error: Cannot take addres of an rvalue of type Movie
// 1.18.21 Chris Flores    Resolving Error: member reference type string is not a pointer
// 1.19.21 Chris Flores    Finally able to bubble sort without bracket notation
// 1.20.21 Chris Flores    Realized I must use movie_count as loop index/updated accordingly

#include <iostream>
#include <iomanip>

using namespace std;

class Movie{
public:
    //Static Data
    static const string DEFAULT_MOVIE_NAME;
    static const int DEFAULT_SEATS;
    static const double DEFAULT_PRICE;
public:
    Movie();
    Movie(string movie_name, int number_of_seats, double ticket_price);
    ~Movie();
    //Mutators
    Movie set_movie_name(string movie_name);
    Movie set_number_of_seats(int number_of_seats);
    Movie set_ticket_price(double ticket_price);
    //Accessors
    string get_movie_name() const;
    int get_number_of_seats() const;
    double get_ticket_price() const;
    //Behavior Functions
    double PurchaseTicket(int number_of_tickets);
    void Display() const;
private:
    string movie_name;
    int number_of_seats;
    double ticket_price;
};

class MovieTicketMaster{
public:
    //Static Data
    static const string DEFAULT_THEATER_NAME;
    static const string DEFAULT_THEATER_LOCATION;
    static const int MAX_MOVIES = 32;
    static const int DEFAULT_MOVIE_COUNT;
public:
    MovieTicketMaster();
    MovieTicketMaster(string theater_name, string theater_location, int movie_count);
    ~MovieTicketMaster();
    //Mutators
    MovieTicketMaster set_theater_name(string theater_name);
    MovieTicketMaster set_theater_location(string theater_location);
    MovieTicketMaster set_movie_count(int movie_count);
    //Accessors
    string get_theater_name() const;
    string get_theater_location() const;
    int get_movie_count() const;
    //Member Functions
    void Init();
    void Run();
private:
    string theater_name;
    string theater_location;
    int movie_count;
    Movie * const p_movie_list;
    //Helper Functions
    void Sort();
    void Menu();
    void ViewMovies();
    void SearchMovie();
    Movie *FindMovie(string movie);
    void PurchaseTicket();
    void Quit();
};

int main(){
    MovieTicketMaster * MTM_temp_ptr = nullptr;
    MTM_temp_ptr = new MovieTicketMaster("Century Theaters", "The River and XD", 0);
    MTM_temp_ptr->Init();
    MTM_temp_ptr->Run();
    delete MTM_temp_ptr;
}

//-----------------------------------------------------------------------//
//________________________Movie Class Definitions________________________//
//Static Data
const string Movie::DEFAULT_MOVIE_NAME = "Mystery Movie";
const int Movie::DEFAULT_SEATS = 100;
const double Movie::DEFAULT_PRICE = 11.99;

//Constructors
Movie::Movie() : movie_name(Movie::DEFAULT_MOVIE_NAME), number_of_seats(Movie::DEFAULT_SEATS), ticket_price(Movie::DEFAULT_PRICE){}
Movie::Movie(string movie_name, int number_of_seats, double ticket_price) : movie_name(movie_name), number_of_seats(number_of_seats), ticket_price(ticket_price){}

// Destructor
Movie::~Movie() { cout << "\t\t\tMovie <" << movie_name << "> object is no longer showing...\n";}

//Mutators
Movie Movie::set_movie_name(string movie_name) {this ->movie_name = movie_name; return *this;}
Movie Movie::set_number_of_seats(int number_of_seats) {this ->number_of_seats = number_of_seats; return *this;}
Movie Movie::set_ticket_price(double ticket_price) {this ->ticket_price = ticket_price; return *this;}

//Accessors
string Movie::get_movie_name() const { return this->movie_name;}
int Movie::get_number_of_seats() const{ return this-> number_of_seats;}
double Movie::get_ticket_price() const{ return this -> ticket_price;}

//Behavior Functions
double Movie::PurchaseTicket(int number_of_tickets){
    double total_cost = 0.0;
    
    if(number_of_tickets > number_of_seats){
        return -1;
    }
    else{
        number_of_seats -= number_of_tickets;
        total_cost = static_cast<double>(number_of_tickets) * ticket_price;
        return total_cost;
    }
}

void Movie::Display() const{
    cout << fixed << setprecision(2);
    cout << "\n\n\t\t\tMovie Title: " << movie_name << "\t No. of Seats: " << number_of_seats << "\tTicket Price: $" << ticket_price << "\n";
}

//-----------------------------------------------------------------------------//
//___________________MovieTicketMaster Class Definitions_______________________//
//Static Data
const string MovieTicketMaster::DEFAULT_THEATER_NAME = "AMC";
const string MovieTicketMaster::DEFAULT_THEATER_LOCATION = "My City";
const int MovieTicketMaster::DEFAULT_MOVIE_COUNT = 0;

//Constructors
MovieTicketMaster::MovieTicketMaster() : theater_name(MovieTicketMaster::DEFAULT_THEATER_NAME), theater_location(MovieTicketMaster::DEFAULT_THEATER_LOCATION), movie_count(MovieTicketMaster::DEFAULT_MOVIE_COUNT), p_movie_list(new Movie[MovieTicketMaster::MAX_MOVIES]){}
MovieTicketMaster::MovieTicketMaster(string theater_name, string theater_location, int movie_count) :  theater_name(theater_name), theater_location(theater_location), movie_count(movie_count), p_movie_list(new Movie[MovieTicketMaster::MAX_MOVIES]){}

//Destructor
MovieTicketMaster::~MovieTicketMaster() { cout << "\t\t\tTheater <" << theater_name << "> at <" << theater_location << "> is currently closed\n"; delete [] p_movie_list;}

//Mutators
MovieTicketMaster MovieTicketMaster::set_theater_name(string theater_name) { this -> theater_name = theater_name; return *this;}
MovieTicketMaster MovieTicketMaster::set_theater_location(string theater_location) {this -> theater_location = theater_location; return *this;}
MovieTicketMaster MovieTicketMaster::set_movie_count(int movie_count) {this -> movie_count = movie_count; return *this;}

//Accesors
string MovieTicketMaster::get_theater_name() const { return this -> theater_name;}
string MovieTicketMaster::get_theater_location() const{ return this -> theater_location;}
int MovieTicketMaster::get_movie_count() const { return this -> movie_count;}

//Behavior Functions
void MovieTicketMaster::Init(){
    const int kMaxSize = 8;
    
    string movie_menu[kMaxSize] = { "Requiem For A Dream", "Vivarium", "Mortal Kombat", "Clifford The Big Red Dog", "Rent-A-Pal", "Soul", "Mission: Impossible 7", "Fast & Furious 9"};
    int seat_list[kMaxSize] = { 10, 6, 3, 5, 8, 13, 21, 34};
    double price_list[kMaxSize] = { 5.50, 6.98, 15.99, 13.99, 7.75, 10.99, 19.99, 25.99};
    
    Movie * p_movie_object = nullptr;
    string *p_movie_menu = nullptr;
    int *p_seat_list = nullptr;
    double *p_price_list = nullptr;
    
    p_movie_object = p_movie_list;
    p_movie_menu = movie_menu;
    p_seat_list = seat_list;
    p_price_list = price_list;
    
    for(int i = 0; i < kMaxSize; i++){
        p_movie_object->set_movie_name(*(p_movie_menu++));
        p_movie_object->set_number_of_seats(*(p_seat_list++));
        p_movie_object->set_ticket_price(*(p_price_list++));
        ++p_movie_object;
        ++movie_count;
    }
    Sort();
}

void MovieTicketMaster::Run(){
    int choice = 0;
    
    do{
        Menu();
        cout << "\n\t\t\tSelect a choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                ViewMovies();
                break;
            case 2:
                SearchMovie();
                break;
            case 3:
                PurchaseTicket();
                break;
            case 4:
                Quit();
                break;
            default:
                cout << "\n\t\t\tPlease enter a choice between 1 and 4!";
                cin.clear();
                cin.ignore(100, '\n');
                break;
        }
    }while(choice !=4);
}

//Helper Functions
void MovieTicketMaster::Sort(){
    bool didSwap = true;
    Movie * p_p_movie_list = p_movie_list;
    Movie temp_movie;
    while(didSwap){
        didSwap = false;
        for(int i = 0; i < movie_count-1; i++){
            if((p_p_movie_list+i)->get_movie_name().compare((p_p_movie_list+i+1)->get_movie_name()) >0){
                temp_movie = *(p_p_movie_list+i);
                *(p_p_movie_list+i) = *(p_p_movie_list+i+1);
                *(p_p_movie_list+i+1) = temp_movie;
                didSwap = true;
            }
        }
    }
}

void MovieTicketMaster::Menu(){
    cout << "\n\n\t\t\tMOVIE TICKET MASTER\n\n\t\t\tTheater: <" << theater_name << "> at <" << theater_location << ">\n\n\t\t\t=================================================\n" << setw(24) << "" << "FOOTHILL CS HOME-THEATER\n\t\t\t=================================================\n\n\t\t\t1. View all movies\n\t\t\t2. Search a movie\n\t\t\t3. Purchase a ticket\n\t\t\t4. Quit\n";
}

void MovieTicketMaster::ViewMovies(){
    Movie *p_movie_viewer = nullptr;
    p_movie_viewer = p_movie_list;
    for(int i = 0; i < movie_count; i++){
        (p_movie_viewer++)->Display();
    }
}

void MovieTicketMaster::SearchMovie(){
    Movie *p_found_index = nullptr;
    string movie;
    
    cout << "\n\t\t\tEnter a movie to search: ";
    cin.ignore();
    getline(cin, movie);
    
    p_found_index = FindMovie(movie);
    
    if(p_found_index != nullptr){
        p_found_index->Display();
    }
    else{
        cout << "\n\t\t\tWe're sorry we don't have " << movie << "!\n";
        cin.clear();
        cin.ignore();
    }
}

Movie * MovieTicketMaster::FindMovie(string movie){
    Movie * p_movie_finder = nullptr;
    int first_index = 0;
    int mid_index = 0;
    int last_index = movie_count - 1;
    
    while(first_index <= last_index){
        mid_index = (first_index+last_index)/2;
        p_movie_finder = p_movie_list+mid_index;
        if(p_movie_finder->get_movie_name() == movie){
            return p_movie_finder;
        }
        else if(p_movie_finder->get_movie_name() > movie){
            last_index = mid_index - 1;
        }
        else{
            first_index = mid_index + 1;
        }
    }
    return nullptr;
}

void MovieTicketMaster::PurchaseTicket(){
    string movie_choice;
    int number_of_tickets = 0;
    Movie * p_movie_choice = nullptr;
    double found_ticket_price = 0.0;
    
    cout << "\n\t\t\tEnter the movie you want to purchase a ticket for: ";
    cin.ignore();
    getline(cin, movie_choice);
    
    p_movie_choice = FindMovie(movie_choice);
    
    if(p_movie_choice != nullptr){
        cout << "\n\n\t\t\tHow many tickets do you want to purchase? ";
        cin >> number_of_tickets;

        found_ticket_price = p_movie_choice->PurchaseTicket(number_of_tickets);
        
        if(found_ticket_price != -1){
            cout << "\n\n\t\t\tTotal price for " << number_of_tickets << " tickets: $" << found_ticket_price << "\n";
        }
        else{
            cout << "\n\n\t\t\tThe show has been sold out or not enough tickets available per your request!\n";
            return;
        }
    }
    else if(p_movie_choice == nullptr){
        cout << "\n\n\t\t\tWe're sorry but " << movie_choice << " is NOT playing!\n";
        cin.clear();
        cin.ignore();
    }
}

void MovieTicketMaster::Quit(){
    cout << "\n\t\t\tThanks for choosing FOOTHILL CS HOME THEATER! Bye!\n\n";
}
