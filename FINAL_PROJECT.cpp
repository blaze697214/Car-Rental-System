#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

class CAR
{
public:
    int CAR_ID;
    string model;
    string brand;
    float ppd;
    bool status;

    CAR(int car_id1, string model1, string brand1, float ppd1, bool status1)
    {
        CAR_ID = car_id1;
        model = model1;
        brand = brand1;
        ppd = ppd1;
        status = status1;
    }

    void display()
    {
        cout << left << setw(10) << CAR_ID
             << setw(15) << brand
             << setw(15) << model
             << right << setw(10) << fixed << setprecision(2) << ppd
             << setw(15) << (status ? "AVAILABLE" : "RENTED") << endl;
    }

    void savetofile(ofstream &ofcr)
    {
        ofcr << CAR_ID << " " << model << " " << brand << " " << ppd << " " << status << endl;
    }
};

class CUSTOMER
{
public:
    int CUSTOMER_ID;
    string CUSTOMER_NAME;

    CUSTOMER(int cID, string cname)
    {
        CUSTOMER_ID = cID;
        CUSTOMER_NAME = cname;
    }

    void savetofile(ofstream &ofcs)
    {
        ofcs << CUSTOMER_ID << " " << CUSTOMER_NAME << endl;
    }
};

class TRANSACTION
{
public:
    int TRANSACTION_ID;
    int CAR_ID;
    string BRAND;
    string MODEL;
    float PRICEPERDAY;
    int CUSTOMER_ID;
    float TOTALAMOUNT;
    int NOOFDAYS;
    string NAME;

    TRANSACTION(string name, int customer_id, int transid, int cID,string brand,string model, float ppd2, int nof)
    {
        TRANSACTION_ID = transid;
        CUSTOMER_ID = customer_id;
        CAR_ID = cID;
        BRAND=brand;
        MODEL=model;
        PRICEPERDAY = ppd2;
        NOOFDAYS = nof;
        TOTALAMOUNT = PRICEPERDAY * NOOFDAYS;
        NAME = name;
    }

    void displaybill()
    {
        cout << "\n----------------------------" << endl;
        cout << "    TRANSACTION DETAILS" << endl;
        cout << "----------------------------" << endl;
        cout << "Transaction ID : " << TRANSACTION_ID << endl;
        cout << "Customer ID    : " << CUSTOMER_ID << endl;
        cout << "Name           : " << NAME << endl;
        cout << "Car ID         : " << CAR_ID << endl;
        cout << "Car Brand      : " << BRAND << endl;
        cout << "Car Model      : " << MODEL << endl;
        cout << "Price Per Day  : $" << PRICEPERDAY << endl;
        cout << "No. of Days    : " << NOOFDAYS << endl;
        cout << "Total Amount   : $" << TOTALAMOUNT << endl;
    }

    void savetofile(ofstream &oftr)
    {
        oftr << NAME << " " << CUSTOMER_ID << " " << TRANSACTION_ID << " " << CAR_ID << " " << BRAND << " " << MODEL << " " << PRICEPERDAY << " " << NOOFDAYS << endl;
    }
};

class SYSTEM
{
    vector<CAR> car_vector;
    vector<TRANSACTION> transaction_vector;
    vector<CUSTOMER> customer_vector;

public:
    string pass = "owner";
    string model, brand;
    int nextcarid = 100;
    int nexttransid = 10100;
    int nextcustomerid = 500;
    float price;
    string name;
    int Carid, noofdays, Transid;

    SYSTEM()
    {
        load_car_vector();
        load_transaction_vector();
        load_customer_vector();
    }

    void load_car_vector()
    {
        int temp_CAR_ID;
        string temp_model;
        string temp_brand;
        float temp_ppd;
        bool temp_status;

        ifstream ifcr("p_cars.txt");

        if (ifcr.is_open())
        {
            while (ifcr >> temp_CAR_ID >> temp_model >> temp_brand >> temp_ppd >> temp_status)
            {
                if(temp_CAR_ID>nextcarid)
                    nextcarid=temp_CAR_ID;
                car_vector.emplace_back(temp_CAR_ID, temp_model, temp_brand, temp_ppd, temp_status);
            }
        }
        else
            cout << "\nOpening Error!!" << endl;

        ifcr.close();
    }
    void load_transaction_vector()
    {
        int temp_TRANSACTION_ID;
        int temp_CAR_ID;
        float temp_PRICEPERDAY;
        int temp_CUSTOMER_ID;
        string temp_brand;
        string temp_model;
        float temp_TOTALAMOUNT;
        int temp_NOOFDAYS;
        string temp_NAME;

        ifstream iftr("p_transactions.txt");

        if (iftr.is_open())
        {
            while (iftr >> temp_NAME >> temp_CUSTOMER_ID >> temp_TRANSACTION_ID >> temp_CAR_ID >> temp_brand>> temp_model >> temp_PRICEPERDAY >> temp_NOOFDAYS)
            {
                if(temp_TRANSACTION_ID>nexttransid)
                    nexttransid=temp_TRANSACTION_ID;
                transaction_vector.emplace_back(temp_NAME, temp_CUSTOMER_ID, temp_TRANSACTION_ID, temp_CAR_ID, temp_brand, temp_model, temp_PRICEPERDAY, temp_NOOFDAYS);
            }
        }
        else
            cout << "\nOpening Error!!" << endl;
    }
    void load_customer_vector()
    {
        int temp_CUSTOMER_ID;
        string temp_CUSTOMER_NAME;

        ifstream ifcs("p_customers.txt");

        if (ifcs.is_open())
        {
            while (ifcs >> temp_CUSTOMER_ID >> temp_CUSTOMER_NAME)
            {
                if(temp_CUSTOMER_ID>nextcustomerid)
                    nextcustomerid=temp_CUSTOMER_ID;
                customer_vector.emplace_back(temp_CUSTOMER_ID, temp_CUSTOMER_NAME);
            }
        }
        else
            cout << "\nOpening Error!!" << endl;
    }

    void save_data()
    {
        save_car_vector();
        save_transaction_vector();
        save_customer_vector();
    }

    void save_car_vector()
    {
        ofstream ofcr("p_cars.txt", ios::trunc);
        for (auto obj : car_vector)
        {
            obj.savetofile(ofcr);
        }
        ofcr.close();
    }
    void save_transaction_vector()
    {
        ofstream oftr("p_transactions.txt", ios::trunc);
        for (auto obj : transaction_vector)
        {
            obj.savetofile(oftr);
        }
        oftr.close();
    }
    void save_customer_vector()
    {
        ofstream ofcs("p_customers.txt", ios::trunc);
        for (auto obj : customer_vector)
        {
            obj.savetofile(ofcs);
        }
        ofcs.close();
    }

    // owner functions
    void add()
    {
        cout << "\nEnter the Car Brand: ";
        cin >> brand;
        cout << "Enter the model: ";
        cin >> model;
        cout << "Enter the Price per day: ";
        cin >> price;
        car_vector.emplace_back(++nextcarid, model, brand, price, true);
        cout << "\nThe Car has been Added!!" << endl;
    }

    void remove()
    {
        int rID;
        cout << "Enter the Car ID to remove: ";
        cin >> rID;
        for (auto it = car_vector.begin(); it != car_vector.end(); ++it)
        {
            if (it->CAR_ID == rID)
            {
                if (it->status == false)
                {
                    cout << "\nThe Car is currently rented !!" << endl;
                    return;
                }
                car_vector.erase(it);
                cout << "\nThe Car has been Removed!!" << endl;
                return;
            }
        }
        cout << "\nInvalid Car ID!!" << endl;
    }

    void displayallcars()
    {
        if (car_vector.empty())
        {
            cout << "\nNo Cars Available!!" << endl;
            return;
        }
        display_header();
        for (auto &obj : car_vector)
        {
            obj.display();
        }
        
    }

    void display_header()
    {
        cout << "\n------------------------------------------------------------------" << endl;
        cout << left << setw(10) << "CAR ID"
             << setw(15) << "Brand"
             << setw(15) << "Model"
             << right << setw(10) << "Price(in $)"
             << setw(15) << "Status" << endl;
        cout << "------------------------------------------------------------------" << endl;
    }

    void display_customers()
    {
        if(customer_vector.empty())
        {
            cout << "\nNo Customers are Registered !!" << endl;
            return;
        }
        cout << "\n-----------------------------" << endl;
        cout << left << setw(15) << "Customer ID" << setw(20) <<  "Customer Name" << endl;
        cout << "-----------------------------" << endl;
        for(auto obj:customer_vector)
        {
            cout << right << setw(7) << obj.CUSTOMER_ID << setw(20) <<  obj.CUSTOMER_NAME << endl;
        }
    }

    void displayalltransactions()
    {
        if(transaction_vector.empty())
        {
            cout << "\nNo Transactions made !!" << endl;
            return;
        }
        cout << "\n--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(18) << "Transaction ID" 
        << setw(15) << "Customer ID" 
        << setw(10) << "Name" 
        << setw(10) << "Car ID"
        << setw(12) << "Car Brand"
        << setw(9) << "Car Model" 
        << right << setw(23) << "Price per Day(in $)" 
        << setw(15) << "No. of Days" 
        << setw(21) << "Total Amount(in $)" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        for(auto obj:transaction_vector)
        {
            cout << left << setw(18) << obj.TRANSACTION_ID
            << setw(15) << obj.CUSTOMER_ID
            << setw(10) << obj.NAME
            << setw(10) << obj.CAR_ID 
            << setw(12) << obj.BRAND
            << setw(9) << obj.MODEL
            << right << setw(15) << obj.PRICEPERDAY 
            << setw(17) << obj.NOOFDAYS
            << setw(20) << obj.TOTALAMOUNT << endl;
        }
    }

    // customer functions
    void registercustomer()
    {
        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, name);

        customer_vector.emplace_back(++nextcustomerid, name);
        cout << "\nYour Customer ID is : " << nextcustomerid << endl;
    }

    int findcustomerid(string name2)
    {
        for (auto &obj : customer_vector)
        {
            if (obj.CUSTOMER_NAME == name2)
            {
                return obj.CUSTOMER_ID;
            }
        }
        return -1;
    }

    void availablecars()
    {
        if (car_vector.empty())
        {
            cout << "\nNo Cars Available!!" << endl;
        }
        else
        {
            display_header();
            for (auto &obj : car_vector)
            {
                if (obj.status == true)
                {
                    obj.display();
                }
            }
        }
    }

    void rentcars()
    {
        if (car_vector.empty())
        {
            cout << "\nNo Cars are available to rent !!" << endl;
            return;
        }
        cout << "Enter your name : ";
        cin.ignore();
        getline(cin, name);
        int Customerid = findcustomerid(name);
        if (Customerid == -1)
        {
            cout << "\nCustomer NOT Addded !!" << endl;
            cout << "Register the Customer" << endl;
            return;
        }
        cout << "Enter the Car ID to rent: ";
        cin >> Carid;

        for (auto &obj : car_vector)
        {
            if (obj.CAR_ID == Carid && obj.status)
            {
                cout << "Enter the number of days: ";
                cin >> noofdays;
                obj.status = false;
                cout << "\nCar has been Rented!!" << endl;
                transaction_vector.emplace_back(name, Customerid, ++nexttransid, obj.CAR_ID, obj.brand, obj.model, obj.ppd, noofdays);
                cout << "Your Transaction ID is : " << nexttransid << endl;
                return;
            }
        }
        cout << "\nCar ID NOT found!!" << endl;
    }

    void returncars()
    {
        if (transaction_vector.empty())
        {
            cout << "\nNone of the cars are Rented !!" << endl;
            cout << "First rent the car !" << endl;
            return;
        }
        cout << "Enter the Car ID to return: ";
        cin >> Carid;

        for (auto &obj : car_vector)
        {
            if (obj.CAR_ID == Carid && !obj.status)
            {
                obj.status = true;
                cout << "\nCar returned successfully!" << endl;
                return;
            }
        }
        cout << "\nCar ID NOT found!!" << endl;
    }

    void bill()
    {
        if (transaction_vector.empty())
        {
            cout << "\nNone of the cars are Rented !!" << endl;
            cout << "Rent a Car to generate bill." << endl;
            return;
        }
        cout << "Enter the Transaction ID: ";
        cin >> Transid;

        for (auto &obj : transaction_vector)
        {
            if (obj.TRANSACTION_ID == Transid)
            {
                obj.displaybill();
                return;
            }
        }
        cout << "\nInvalid Transaction ID!!" << endl;
    }

    bool verify_pass(string ippass)
    {
        return pass == ippass;
    }
};

int main()
{
    SYSTEM obj;
    int choice, owner_choice, customer_choice;
    string password;

    cout << "\n\n\n************WELCOME*************\n";
    cout << "-----The Car Rental Service-----\n";

    do
    {
        cout << "\n-------------------------";
        cout << "\n MAIN INTERFACE";
        cout << "\n-------------------------";
        cout << "\n1.Owner";
        cout << "\n2.Customer";
        cout << "\n3.Exit";
        cout << "\n-------------------------";
        cout << "\nEnter your choice :: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the password :: ";
            cin >> password;

            if (obj.verify_pass(password))
            {
                do
                {
                    cout << "\n-------------------------";
                    cout << "\n OWNER INTERFACE";
                    cout << "\n-------------------------";
                    cout << "\n1.Add a Car";
                    cout << "\n2.Remove a Car";
                    cout << "\n3.Display Registered Customers";
                    cout << "\n4.Display all Cars";
                    cout << "\n5.Display all Transactions";
                    cout << "\n6.Exit";
                    cout << "\n-------------------------";
                    cout << "\nEnter your choice :: ";
                    cin >> owner_choice;

                    switch (owner_choice)
                    {
                    case 1:
                        obj.add();
                        break;
                    case 2:
                        obj.remove();
                        break;
                    case 3:
                        obj.display_customers();
                        break;
                    case 4:
                        obj.displayallcars();
                        break;
                    case 5:
                        obj.displayalltransactions();
                        break;
                    case 6:
                        cout << "\nExiting the Owner Interface ..." << endl;
                        break;
                    default:
                        cout << "\nInvalid choice !!" << endl;
                        break;
                    }

                } while (owner_choice != 6);
            }
            else
            {
                cout << "\nIncorrect Password !!" << endl;
            }
            break;

        case 2:
            do
            {
                cout << "\n-------------------------";
                cout << "\n CUSTOMER INTERFACE";
                cout << "\n-------------------------";
                cout << "\n1.Register the Customer";
                cout << "\n2.Display Available Cars";
                cout << "\n3.Rent a Car";
                cout << "\n4.Return a Car";
                cout << "\n5.Generate Bill";
                cout << "\n6.Exit";
                cout << "\n--------------------------";
                cout << "\nEnter your choice :: ";
                cin >> customer_choice;

                switch (customer_choice)
                {
                case 1:
                    obj.registercustomer();
                    break;
                case 2:
                    obj.availablecars();
                    break;
                case 3:
                    obj.rentcars();
                    break;
                case 4:
                    obj.returncars();
                    break;
                case 5:
                    obj.bill();
                    break;
                case 6:
                    cout << "\nExiting the Customer Interface ..." << endl;
                    break;
                default:
                    cout << "\nInvalid Choice!!" << endl;
                    break;
                }

            } while (customer_choice != 6);
            break;

        case 3:
            cout << "\nExiting the Main Interface ..." << endl;
            cout << "Thanks you for using..." << endl;
            break;

        default:
            cout << "\nInvalid Choice !!" << endl;
            break;
        }

    } while (choice != 3);

    obj.save_data();

    return 0;
}
