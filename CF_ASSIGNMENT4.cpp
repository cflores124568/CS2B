//===--------------------------------------------------------------------------------------------------===//
//  FileName: CF_ASSIGNMENT4.cpp
//  Description:    This program is an account managment system for phone numbers and their messages.
//                  Users can select up to 5 choices.
//
//Date      Author          Comment
//03.02.20  Chris Flores    Implementing Class Skeletons
//03.3.20   Chris Flores    Invalid operands to binary expression ('const char [9]' and 'const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::value_type *' (aka 'const char *'))
//03.07.21                  Finished Media and Message<T>
//03.08.21                  Stuck on Exception class error: Returning adress of local temporary object
//03.12.21                  Still stuck on Exception class
//03.15.21                  Member reference base type 'Message<Media> *const' is not a structure or union
//03.19.21                  Finished PurgeMessages and DeleteAccount
//03.20.21                  Program ran for first time
//                          Trying to resolve issue where ListAccounts() is showing each message's MB and total charge
//                          in a separate line as opposed to showing total MB and Dollars in a single line
//03.21.21                  Trying to format output by decimal but unable to add dollar sign without sacrificing format
//===--------------------------------------------------------------------------------------------------===//

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <exception>

using namespace std;

class AccountNotFoundException: public exception{
public:
    friend ostream & operator<<(ostream & outputstream, const AccountNotFoundException & other_account);
    static const string DEFAULT_PHONE_NUMBER;
    AccountNotFoundException();
    AccountNotFoundException(const string & phone_number);
    ~AccountNotFoundException() throw();
    virtual const char * what() const noexcept;
private:
    string phone_number;
};

class Media{
public:
    static const double DEFAULT_SIZE;
    static const double DEFAULT_CHARGE_PER_MB;
    static const double DEFAULT_MINIMUM_CHARGE;
    static const double DEFAULT_SIZE_THRESHOLD;
    Media();
    Media(double size);
    ~Media();
    void set_size(double size);
    double get_size() const;
    double GetCharge();
private:
    double size;
};

template <class T>
class Message{
public:
    static const string DEFAULT_RECIEVER_NUMBER;
    Message();
    Message(string to, T m_data);
    ~Message();
    void set_to(string to);
    string get_to() const;
    void set_data(T m_data);
    T get_data() const;
private:
    string to;
    T m_data;
    
};

class SmartCarrier{
public:
    static const string DEFAULT_CARRIER;
    static const bool IS_INIT;
    SmartCarrier();
    SmartCarrier(string carrier_name, bool isInit);
    ~SmartCarrier();
    void Init();
    void StartService();
private:
    string carrier_name;
    bool isInit;
    map<string, vector<Message<Media>*>> account_map;
    void Menu();
    int GetChoice();
    void ListAccounts() const;
    void InsertMessage();
    void PurgeLargeMessages();
    void DisconnectAccount();
    void Quit();
};

int main(){
    SmartCarrier * p_master_store = new SmartCarrier("CS2C Wireless", false);
    p_master_store->Init();
    p_master_store->StartService();
    delete p_master_store;
}

//********************************************************
//        AccountNotFoundException Definitions           *
//********************************************************
ostream & operator<<(ostream & outputstream, const AccountNotFoundException & other_account){ return outputstream << other_account.phone_number;}
const string AccountNotFoundException::DEFAULT_PHONE_NUMBER = "1-760-989-1474";
//Constructors
AccountNotFoundException::AccountNotFoundException() : exception(), phone_number(AccountNotFoundException::DEFAULT_PHONE_NUMBER){}
AccountNotFoundException::AccountNotFoundException(const string & phone_number) : exception(), phone_number("Account " + phone_number + " not found!"){}
//Destructor
AccountNotFoundException::~AccountNotFoundException() throw(){}
const char * AccountNotFoundException::what() const noexcept{
    return phone_number.c_str();
}

//********************************************************
//                   Media Definitions                   *
//********************************************************
//Static Data
const double Media::DEFAULT_SIZE = 0.0;
const double Media::DEFAULT_CHARGE_PER_MB = 0.05;
const double Media::DEFAULT_MINIMUM_CHARGE = 1.00;
const double Media::DEFAULT_SIZE_THRESHOLD = 100.0;
//Constructor
Media::Media() : size(Media::DEFAULT_SIZE_THRESHOLD){}
Media::Media(double size) : size(size){}
Media::~Media(){}
void Media::set_size(double size){this->size = size;}
double Media::get_size() const {return size;}
double Media::GetCharge(){
    double total_charge = size * Media::DEFAULT_CHARGE_PER_MB;
    return (total_charge > Media::DEFAULT_MINIMUM_CHARGE ? total_charge : Media::DEFAULT_MINIMUM_CHARGE);
}
//********************************************************
//                  Message Definitions                  *
//********************************************************
//Static Data
template <class T>
const string Message<T>::DEFAULT_RECIEVER_NUMBER = "000-000-0000";
template <class T>
Message<T>::Message() : to(Message::DEFAULT_RECIEVER_NUMBER){}
template <class T>
Message<T>::Message(string to, T m_data) : to(to), m_data(m_data){}
template <class T>
Message<T>::~Message(){}
template <class T>
void Message<T>::set_to(string to){this->to = to;}
template <class T>
string Message<T>::get_to() const{return to;}
template <class T>
void Message<T>::set_data(T m_data){this->m_data = m_data;}
template <class T>
T Message<T>::get_data() const{return m_data;}
//********************************************************
//               SmartCarrier Definitions                *
//********************************************************
//Static Data
const string SmartCarrier::DEFAULT_CARRIER = "CS2B WIRELESS";
const bool SmartCarrier::IS_INIT = false;
SmartCarrier::SmartCarrier() : carrier_name(SmartCarrier::DEFAULT_CARRIER), isInit(SmartCarrier::IS_INIT){}
SmartCarrier::SmartCarrier(string carrier_name, bool isInit) : carrier_name(carrier_name), isInit(isInit){}
SmartCarrier::~SmartCarrier(){
    for(map<string, vector<Message<Media>*>>::iterator account_iter = account_map.begin(); account_iter != account_map.end(); ++account_iter){
        for(vector<Message<Media>*>::iterator message_iter = account_iter->second.begin(); message_iter != account_iter->second.begin(); ++message_iter){
            delete *message_iter;
        }
    }
}
void SmartCarrier::Init(){
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-920-581-3908", Media(110.5)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-760-866-1069", Media(106.9)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-944-629-2778", Media(32.6)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-203-982-1823", Media(69.4)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-626-394-8026", Media(35.0)));
    account_map["1-818-449-8531"].push_back(new Message<Media>("1-418-603-9218", Media(110.0)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-919-472-8712", Media(65.2)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-760-346-4377", Media(34.5)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-562-759-6632", Media(77.4)));
    account_map["1-406-238-4299"].push_back(new Message<Media>("1-920-874-6294", Media(20.75)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-862-725-9524", Media(45.2)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-760-628-2731", Media(15.3)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-787-628-8752", Media(26.0)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-212-949-6448", Media(22.5)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-418-866-0352", Media(48.0)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-920-449-2383", Media(73.8)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-898-441-0452", Media(17.0)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-760-989-1474", Media(85.4)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-441-537-8633", Media(42.8)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-324-989-1876", Media(24.8)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-792-184-7293", Media(101.5)));
    account_map["1-406-238-4299"].push_back(new Message<Media>("1-989-819-0174", Media(34.7)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-341-932-1461", Media(45.0)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-462-531-9305", Media(109.6)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-911-711-3198", Media(18.6)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-800-407-1369", Media(135.0)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-442-696-8275", Media(50.9)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-562-072-8490", Media(62.5)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-760-947-1693", Media(113.1)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-989-175-5329", Media(86.4)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-862-725-9524", Media(27.9)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-219-432-4823", Media(15.0)));
    account_map["1-562-922-0117"].push_back(new Message<Media>("1-626-341-3814", Media(350.8)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-441-537-8633", Media(102.8)));
    account_map["1-760-291-8371"].push_back(new Message<Media>("1-120-439-7319", Media(133.8)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-818-214-7821", Media(43.9)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-218-672-7637", Media(97.5)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-940-106-8304", Media(49.4)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-442-299-3719", Media(12.7)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-794-925-5350", Media(100.0)));
    account_map["1-920-149-3805"].push_back(new Message<Media>("1-760-472-2778", Media(100.3)));
    account_map["1-205-941-3912"].push_back(new Message<Media>("1-536-816-2294", Media(150.6)));
    account_map["1-989-628-5103"].push_back(new Message<Media>("1-293-732-6448", Media(32.3)));
    account_map["1-442-823-2891"].push_back(new Message<Media>("1-626-625-3983", Media(49.9)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-319-294-7194", Media(189.4)));
    account_map["1-361-285-9964"].push_back(new Message<Media>("1-487-327-9447", Media(63.6)));
    account_map["1-800-324-4500"];
    account_map["1-787-462-1932"].push_back(new Message<Media>("1-421-234-8273", Media(38.5)));
    account_map["1-626-301-7924"].push_back(new Message<Media>("1-923-824-9127", Media(44.5)));
    isInit = true;
}

void SmartCarrier::StartService(){
    if(!isInit){
        cout << "System Initialization Failure! Aborting program...\n";
        Quit();
    }
    do{
        int choice = 0;
        try{
            Menu();
            choice = GetChoice();
            switch(choice)
            {
                case 1:
                    ListAccounts();
                    break;
                case 2:
                    InsertMessage();
                    break;
                case 3:
                    PurgeLargeMessages();
                    break;
                case 4:
                    DisconnectAccount();
                    break;
                case 5:
                    Quit();
                    break;
            }
        }
        catch(AccountNotFoundException & accexcp){
            cout << "\n\t\t" << accexcp.what() << "\n";
        }
        catch(...){
            cout << "\n\t\tPlease Enter a valid choice!\n";
            cin.clear();
        }
    }while(isInit);
}

void SmartCarrier::Menu(){
    cout << "\n\t\t========================================\n";
    cout << setw(28) << "" << "<" << carrier_name << ">\n";
    cout << setw(29) << "" << "Account Admin";
    cout << "\n\t\t========================================\n";
    cout << "\n\t\t1. View All Accounts";
    cout << "\n\t\t2. Add Message to an Account";
    cout << "\n\t\t3. Delete Message(s) from an Account";
    cout << "\n\t\t4. Disconnect an Account";
    cout << "\n\t\t5. Quit\n";
}

int SmartCarrier::GetChoice(){
    int choice = 0;
    cout << "\n\t\tEnter a choice from 1-5: ";
    cin >> choice;
    if(choice < 1 || choice > 5){
        throw "Try again!";
    }
    else{
        return choice;
    }
}

void SmartCarrier::ListAccounts() const{
    double total_MB = 0.0;
    double total_cost = 0.0;
    
    cout << fixed << setprecision(2);
    cout << "\nAccount:\t\tTotal messages:\t\tTotal messages' size (MB):\tCharge:(dollar)\n";
    for(map<string, vector<Message<Media>*>>::const_iterator account_iter = account_map.begin(); account_iter != account_map.end(); ++account_iter){
        cout << account_iter->first << "\t\t\t" << account_iter->second.size() << "\t";
        for(vector<Message<Media>*>::const_iterator message_iter = account_iter->second.begin(); message_iter != account_iter->second.end(); ++message_iter){
            total_MB += (*message_iter)->get_data().get_size();
            total_cost += (*message_iter)->get_data().GetCharge();
        }
        cout << setw(20) << right << total_MB << setw(28) << right << total_cost << "\n";
        total_MB = 0.0;
        total_cost = 0.0;
    }
}
void SmartCarrier::InsertMessage(){
    string phone_number;
    string reciever_number;
    double mb_size = 0.0;
    
    cout << "\n\t\tEnter the account phone number\n\t\tfor which you want to insert a message: ";
    cin>>phone_number;
    map<string, vector<Message<Media>*>>::iterator insert_iter = account_map.find(phone_number);
    if(insert_iter != account_map.end()){
        cout << "\n\t\tNow enter the amount of MB for " << phone_number << "'s message : ";
        cin >> mb_size;
        cout << "\n\t\tNow enter the message recipient's phone number: ";
        cin >> reciever_number;
        account_map[phone_number].push_back(new Message<Media>(reciever_number, Media(mb_size)));
        cout << "\n\t\tYour message of " << mb_size << " MB, to " << reciever_number << ", was succesfully inserted\n\t\tinto account[" << phone_number << "]\n";
    }
    else{
        throw AccountNotFoundException(phone_number);
    }
}

void SmartCarrier::PurgeLargeMessages(){
    string account_phone_number;
    double total_purged_MB = 0.0;
    
    cout << "\n\t\tEnter the phone number for the account who needs large messages purged: ";
    cin >> account_phone_number;
    
    map<string, vector<Message<Media>*>>::iterator account_iter = account_map.find(account_phone_number);
    if(account_iter != account_map.end()){
        for(vector<Message<Media>*>::iterator message_iter = account_iter->second.begin(); message_iter != account_iter->second.end();){
            if(((*message_iter)->get_data().get_size()) >= Media::DEFAULT_SIZE_THRESHOLD){
                total_purged_MB += (*message_iter)->get_data().get_size();
                delete *message_iter;
                message_iter = account_iter->second.erase(message_iter);
            }
            else{
                ++message_iter;
            }
        }
        cout << "\n\t\tTotal MB deleted for account[" << account_phone_number << "] : " << total_purged_MB << " MB\n";
    }
    else{
        throw AccountNotFoundException(account_phone_number);
    }
}

void SmartCarrier::DisconnectAccount(){
    string disconnect_phone_number;
    cout << "\n\t\tEnter the phone number of the account to be disconnected: ";
    cin >> disconnect_phone_number;
    
    map<string, vector<Message<Media>*>>::iterator disconnect_account_iter = account_map.find(disconnect_phone_number);
    if(disconnect_account_iter != account_map.end()){
        for(vector<Message<Media>*>::iterator disconnect_message_iter = disconnect_account_iter->second.begin(); disconnect_message_iter != disconnect_account_iter->second.end(); ++disconnect_message_iter){
            delete *disconnect_message_iter;
        }
        disconnect_account_iter->second.clear();
        account_map.erase(disconnect_account_iter);
        cout << "\n\t\tAccount[" << disconnect_phone_number << "] successfully deleted.\n";
    }
    else{
        throw AccountNotFoundException(disconnect_phone_number);
    }
}

void SmartCarrier::Quit(){
    cout << "\n\t\tGoodbye and thank you for going wireless with " << carrier_name << "!\n";
    isInit = false;
}
