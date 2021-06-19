//===-------------------------------------------------------------------------------------------===//
//  FileName: CFASSIGNMENT3.cpp
//  Description:
//
//  Date        Author          Comment
//  2.10.21     Chris Flores    Implementing Phase 1
//  2.11.21                     Reading about Overloaded Operators
//  2.12.21                     Finished Name and Contact
//  2.13.21                     Finished EmployeeContact and ContractorContact Definitons
//  2.15.21                     Working on ContactList class
//  2.16.21                     Invalid operands to binary expression ('Name' and 'const Name')
//  2.22.21                     Switched operator== to Friend Function
//  2.25.21                     Finally able to move on after a long stump
//                              I was passing in non const parameters in my operator== function. Of course the compiler wasn't happy about my lack of const correctedness. So I introduced 2 temp name variables so I can "alter a const value" because without the temp variables it was impossible to modify a const
//  3.01.21                     Switched to Non Extra-Credit Mode Because my search function wouldn't work after InsertSort.

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Name{
public:
    static const string DEFAULT_FIRST_NAME;
    static const string DEFAULT_LAST_NAME;
    ~Name();
    Name();
    Name(string first_name, string last_name);
    void set_first_name(string first_name);
    void set_last_name(string last_name);
    string get_first_name() const;
    string get_last_name() const;
    string get_full_name() const;
    bool operator==(const Name & name_2) const;
    friend ostream & operator<<(ostream & outputstream, Name & name);
private:
    string first_name;
    string last_name;
};

class Contact{
public:
    static const string DEFAULT_BUSINESS_PHONE_NUMBER ;
    static const string DEFAULT_EMAIL;
    static const int DEFAULT_LOCATION;
    Contact();
    Contact(string first_name, string last_name, string business_phone, string email, int location);
    virtual ~Contact();
    void set_name(Name name);
    void set_business_phone(string business_phone);
    void set_email(string email);
    void set_location(int location);
    void set_next(Contact * p_contact);
    Name get_name() const;
    string get_business_phone() const;
    string get_email() const;
    int get_location() const;
    Contact * get_next() const;
    virtual void ShowContact() const = 0;
protected:
    Name name;
    string business_phone;
    string email;
    int location;
    int contact_count;
private:
    Contact * next;
};

class EmployeeContact : public Contact{
public:
    static const string DEFAULT_TITLE;
    static const string DEFAULT_DEPARTMENT;
    EmployeeContact();
    EmployeeContact(string first_name, string last_name, string business_phone, string email, int location, string title, string department);
    virtual ~EmployeeContact();
    void set_title(string title);
    void set_department(string department);
    string get_title() const;
    string get_department() const;
    virtual void ShowContact() const;
private:
    string title;
    string department;
};

class ContractorContact : public Contact{
public:
    static const string DEFAULT_COMPANY;
    static const int DEFAULT_DURATION;
    virtual ~ContractorContact();
    ContractorContact();
    ContractorContact(string first_name, string last_name, string business_phone, string email, int location, int duration, string company);
    void set_company(string company);
    void set_duration(int duration);
    string get_company() const;
    int get_duration() const;
    virtual void ShowContact() const;
private:
    string company;
    int duration;
};

class ContactList{
public:
    ContactList();
    ~ContactList();
    ContactList(const ContactList & copied_contact_list);
    void Init();
    void ShowAllContacts() const;
    void SearchByName(const Name & name2);
    void SearchByDepartment(const string & newdepartment);
private:
    Contact * head;
    Contact * FindContact(const Name & name2);
    void InsertFront(Contact * p_contact);
};

class AddressBook{
public:
    AddressBook();
    AddressBook(string company_name);
    ~AddressBook();
    void Init();
    void Run();
private:
    string company_name;
    ContactList linked_list;
    void Menu();
    int GetUserOption();
    void ShowAllContacts();
    void SearchByName();
    void SearchByDepartment();
    void Remove();
    void Quit();
};

int main(){
    AddressBook * p_master_contact_book = new AddressBook("Foothill CS TECH");
    p_master_contact_book->Init();
    p_master_contact_book->Run();
    delete p_master_contact_book;
}

//********************************************************
//                     Name Definitions                  *
//********************************************************
//Friends
ostream & operator<<(ostream & outputstream, Name & name){
    return outputstream << name.first_name << name.last_name;
}
const string Name::DEFAULT_FIRST_NAME = "Chris";
const string Name::DEFAULT_LAST_NAME = "Flores";
Name::~Name(){}
Name::Name() : first_name(Name::DEFAULT_FIRST_NAME), last_name(Name::DEFAULT_LAST_NAME){}
Name::Name(string first_name, string last_name) : first_name(first_name), last_name(last_name){}
void Name::set_first_name(string first_name){this->first_name = first_name;}
void Name::set_last_name(string last_name){this->last_name = last_name;}
string Name::get_first_name() const{return first_name;}
string Name::get_last_name() const {return last_name;}
string Name::get_full_name() const {return first_name+" "+last_name;}
bool Name::operator==(const Name & name_2)const {
    string left_name = first_name + " " + last_name;
    string temp_name_2 = name_2.get_full_name();
    string final_name_1;
    string final_name_2;
    for(int i = 0; i < left_name.length(); i++){
        final_name_1 += tolower(left_name[i]);
    }
        for(int j = 0; j < temp_name_2.length(); j++){
            final_name_2 += tolower(temp_name_2[j]);
        }
    return (final_name_1 == final_name_2);
}

//********************************************************
//                  Contact Definitions                  *
//********************************************************
const string Contact::DEFAULT_BUSINESS_PHONE_NUMBER = "760-851-7516";
const string Contact::DEFAULT_EMAIL = "chrisf@tcpcommunications.com";
const int Contact::DEFAULT_LOCATION = 22;
//Constructors
Contact::Contact() : name(), business_phone(Contact::DEFAULT_BUSINESS_PHONE_NUMBER), email(Contact::DEFAULT_EMAIL), location(Contact::DEFAULT_LOCATION), next(nullptr){}
Contact::Contact(string first_name, string last_name, string business_phone, string email, int location) : name(first_name, last_name), business_phone(business_phone), email(email), location(location), next(nullptr){}
//Destructor
Contact::~Contact(){cout << "\n\t\t<" << name << "> has gone home!";}
//Mutators
void Contact::set_name(Name name){this->name = name;}
void Contact::set_business_phone(string business_phone){this->business_phone = business_phone;}
void Contact::set_email(string email){this->email = email;}
void Contact::set_location(int location){this->location = location;}
void Contact::set_next(Contact * p_contact){next = p_contact;}
//Accessors
Name Contact::get_name() const {return name;}
string Contact::get_business_phone() const {return business_phone;}
string Contact::get_email() const {return email;}
int Contact::get_location() const {return location;}
Contact * Contact::get_next() const {return next;}

//********************************************************
//              EmployeeContact Definitions              *
//********************************************************
//Friends
//Static Data
const string EmployeeContact::DEFAULT_TITLE = "Software Engineer";
const string EmployeeContact::DEFAULT_DEPARTMENT = "Computer Science";
//Constructors
EmployeeContact::EmployeeContact() : Contact(), title(EmployeeContact::DEFAULT_TITLE), department(EmployeeContact::DEFAULT_DEPARTMENT){}
EmployeeContact::EmployeeContact(string first_name, string last_name, string business_phone, string email, int location, string title, string department) : Contact(first_name, last_name, business_phone, email, location), title(title), department(department){}
EmployeeContact::~EmployeeContact(){}
//Mutators
void EmployeeContact::set_title(string title){this->title = title;}
void EmployeeContact::set_department(string department){this->department = department;}
//Accessors
string EmployeeContact::get_title() const {return title;}
string EmployeeContact::get_department() const {return department;}
void EmployeeContact::ShowContact() const {
    cout << "\n\t\t" << name.get_full_name() << " " << title << " " << department << " Room " << location << " " << business_phone << " " << email << "\n";
}

//********************************************************
//              ContractorContract Definitions           *
//********************************************************
//Static Data
const string ContractorContact::DEFAULT_COMPANY = "Foothill Consulting";
const int ContractorContact::DEFAULT_DURATION = 7;
//Constructors
ContractorContact::ContractorContact() : Contact(), company(ContractorContact::DEFAULT_COMPANY), duration(ContractorContact::DEFAULT_DURATION){}
ContractorContact::ContractorContact(string first_name, string last_name, string business_phone, string email, int location, int duration, string company): Contact(first_name, last_name, business_phone, email, location), duration(duration), company(company){}
//Destructor
ContractorContact::~ContractorContact(){}
//Mutators
void ContractorContact::set_company(string company){this->company = company;}
void ContractorContact::set_duration(int duration){this->duration = duration;}
//Accessors
string ContractorContact::get_company() const {return company;}
int ContractorContact::get_duration() const {return duration;}
void ContractorContact::ShowContact() const {
    cout << "\n\t\t" << name.get_full_name() << " " << duration << " months (contractor) " << company << " Room " << location << " " << business_phone << " " << email << "\n";
}
//********************************************************
//                  ContactList Definitions              *
//********************************************************
//Constructor
ContactList::ContactList() : head(nullptr){}
//Destructor
ContactList::~ContactList(){
    Contact * p_contact_node = nullptr;
    while(head != nullptr){
        p_contact_node = head;
        head = head->get_next();
        delete p_contact_node;
    }
}
//Member Functions
void ContactList::Init(){
    InsertFront(new ContractorContact("Edward", "Capaldi", "1-760-626-9751", "edcapaldi@a1solutions.com", 13, 5, "GDB Enterprises"));
    InsertFront(new EmployeeContact("Faith", "Richards", "1-760-949-1474", "faithr@bdeconsultings.com", 26, "Data Scientist", "Information Analytics"));
    InsertFront(new EmployeeContact("Denwin", "Summers", "1-818-626-1968", "denwins@tpcommunicatons.com", 44, "Network Specialist", "Information Tech Systems"));
    InsertFront(new ContractorContact("Geoff", "Lopez", "1-408-790-2020", "glopez@cpplogistics.com", 54, 6, "CPP Logistics"));
    InsertFront(new EmployeeContact("Bobby", "Nichols", "1-408-922-1100", "bnichols@ibm.com", 35, "Senior Advisor", "Data Science"));
    InsertFront(new EmployeeContact("Pat", "Christie", "1-302-5761", "pchristie@tpcommunications.com", 11, "Back End Developer", "Software Development"));
    InsertFront(new ContractorContact("Jeff", "Pesos", "1-717-470-2859", "jpesos@eddsolutions.com", 12, 3, "Accounting"));
    InsertFront(new ContractorContact("Susie", "Jones", "1-626-925-3748", "sjones@cpplogistics.com", 7, 10, "Human Resources"));
    InsertFront(new EmployeeContact("Kylie", "Pitts", "1-939-760-9817", "kpitts@dynamicsignal.com", 6, "Director of Marketing", "Advertising"));
    InsertFront(new ContractorContact("Ireland", "Olson", "1-408-213-4519", "iolson@centuriontech.com", 11, 9, "Centurion Tech"));
    InsertFront(new EmployeeContact("Jimmy", "Rivers", "1-760-204-8320", "jrivers@vectorunited.com", 46, "Forensic Technician", "Data Science"));
    InsertFront(new EmployeeContact("Buddy", "Waters", "1-323-981-6395", "bwaters@bdeconsultings.com", 23, "Electrical Engineer", "Engineering"));
    InsertFront(new EmployeeContact("Nick", "Rogers", "1-818-395-1742", "nrogers@statikselect.com", 30, "Chemical Engineer", "Engineering"));
    InsertFront(new ContractorContact("Matt", "Grohl", "1-323-791-2239", "mgrohl@eddsolutions.com", 13, 5, "Edd Solutions"));
    InsertFront(new EmployeeContact("Gloria", "Sparks", "1-212-982-4789", "gsparks@vectorunited.com", 41, "System Technician", "Communications"));
    InsertFront(new ContractorContact("Mary", "Smith", "1-626-729-6527", "msmith@statikselect.com", 54, 11, "Statik Select"));
}
void ContactList::ShowAllContacts() const{
    Contact * p_contact = head;
    cout << "\n\t\tName\tTitle\tDepartment\tLocation\tBusiness Phone\tEmail\n";
    while(p_contact != nullptr){
        p_contact->ShowContact();
        p_contact = p_contact->get_next();
    }
}
void ContactList::SearchByName(const Name &name2){
    Contact * p_found_contact = FindContact(name2);
    if(p_found_contact != nullptr){
        p_found_contact->ShowContact();
    }
    else{
        cout << "\n\t\tWe're sorry but " << name2.get_full_name() << " doesn't work here\n";
    }
}
void ContactList::SearchByDepartment(const string &newdepartment){
    bool foundDepartment = false;
    Contact * p_contact = head;
    EmployeeContact * p_employee_contact = nullptr;
    while(p_contact != nullptr){
        p_employee_contact = dynamic_cast<EmployeeContact *>(p_contact);
        if(p_employee_contact != nullptr && p_employee_contact->get_department() == newdepartment){
            p_employee_contact->ShowContact();
            foundDepartment = true;
        }
        p_contact = p_contact->get_next();
    }
    if(!foundDepartment){
        cout << "\n\t\tSorry we don't have employees in the " << newdepartment << " department\n";
    }
}
//Helper Functions
Contact * ContactList::FindContact(const Name & name_2){
    Contact * p_contact = head;
    while(p_contact != nullptr){
        if(p_contact->get_name() == name_2){
        return p_contact;
        }
        else{
        p_contact = p_contact->get_next();
        }
    }
    return nullptr;
}

void ContactList::InsertFront(Contact * p_contact){
    p_contact->set_next(head);
    head = p_contact;
}

//********************************************************
//                  AddressBook Definitions              *
//*******************************************************/
//Constructor
AddressBook::AddressBook(){}
AddressBook::AddressBook(string company_name) : company_name(company_name){}
//Destructor
AddressBook::~AddressBook(){}
//Public Member Functions
void AddressBook::Init(){
    linked_list.Init();
}
void AddressBook::Run(){
    int choice = 0;
    do{
        Menu();
        choice = GetUserOption();
        switch(choice)
        {
            case 1:
                ShowAllContacts();
                break;
            case 2:
                SearchByName();
                break;
            case 3:
                SearchByDepartment();
                break;
            case 4:
                Quit();
        }
    }while(choice != 4);
}

//Private Helper Functions
void AddressBook::Menu(){
    cout << "\n\t\t==========================================\n";
    cout << setw(20) << "" << "<" << company_name << ">\n";
    cout << setw(20) << "" << "Address Book Menu";
    cout << "\n\t\t==========================================\n";
    cout << "\t\t1. View All Contacts\n";
    cout << "\t\t2. Search by name\n";
    cout << "\t\t3. Search by department\n";
    cout << "\t\t4. Quit\n";
}

int AddressBook::GetUserOption(){
    int choice = 0;
    do{
    cout << "\n\t\tSelect an option from 1-4:";
    cin >> choice;
    }while(choice < 1 || choice > 4);
    return choice;
}

void AddressBook::ShowAllContacts(){
    linked_list.ShowAllContacts();
}
void AddressBook::SearchByName(){
    Name * new_name = nullptr;
    string first_name;
    string last_name;
    cout << "\n\t\tEnter a first name: ";
    cin >> first_name;
    cout << "\n\t\tEnter a last name: ";
    cin >> last_name;
    new_name = new Name(first_name, last_name);
    linked_list.SearchByName(*new_name);
    delete new_name;
}
void AddressBook::SearchByDepartment(){
    string departmentsearch;
    cout << "\n\t\tEnter a department: ";
    cin.ignore();
    getline(cin, departmentsearch);
    linked_list.SearchByDepartment(departmentsearch);
}

void AddressBook::Quit(){
    cout << "\n\t\tGoodbye and thank you for choosing " << company_name << " Address Book!";
}
