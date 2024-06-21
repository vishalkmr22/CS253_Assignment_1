// Disclaimer:-For Manager login:-The manager credentials are:
//  Manager name = vishal(small v )
//  Manager Password = 123456
//  Manager id = mm001
// Note that car Condition is defined as  worst,bad,average,good(all are in small keywords)
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
// Forward declarations for classes
class car_DBS;
class Customer_DBS;
class Employee_DBS;
class car_DBS
{
private:
    string Model;
    string Condition;
    int Is_Rented;
    string Renter_id;
    int Rent_Price;
    string Rent_Date;
    string Due_Date;

public:
    bool Search_model_no(string modelnumber)
    {
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (modelnumber == Model)
            {
                flag = 1;

                break;
            }
            line = "";
        }
        if (flag == 0)
            return false;
        else
            return true;
    }
    bool search_RenterId(string Renterid)
    {

        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (Renterid == Renter_id)
            {
                flag = 1;

                break;
            }
            line = "";
        }
        if (flag == 0)
            return false;
        else
            return true;
    }
    void Add_Car()
    {
        // file pointer
        fstream fout;

        // opens an existing csv file or creates a new file.
        fout.open("Car.csv", ios::app);
        int n;
        cout << "Enter the number of records you want to add" << endl;
        cin >> n;
        cout << "Enter the details of 'n' Cars:" << endl;

        // Read the input
        for (int i = 0; i < n; i++)
        {
            cout << "Model : ";
            cin >> Model;
            if (Search_model_no(Model) == 1)
            {
                cout << "The car with the model number is already there in the car database." << endl;
                return;
            }
            cout << "Condition : ";
            cin >> Condition;
            cout << "Is_Rented(fill 0) : ";
            cin >> Is_Rented;
            cout << "Renter_id (fill none): ";
            cin >> Renter_id;
            cout << "Rent_Price : ";
            cin >> Rent_Price;
            cout << "Due_Date (fill none): ";
            cin >> Due_Date;

            // Insert the data to file
            fout << Model << ","
                 << Condition << ","
                 << Is_Rented << ","
                 << Renter_id << ","
                 << Rent_Price << ","
                 << Due_Date << "\n";
        }
        fout.close();
    }
    void Display_Car(string Model_no)
    {
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;
            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (Model_no == Model)
            {
                flag = 1;

                cout << "Model : " << Model << endl;
                cout << "Condition : " << Condition << endl;
                Is_Rented = stoi(Is_Rented_str);
                cout << "Is_Rented : " << Is_Rented << endl;
                cout << "Renter_id : " << Renter_id << endl;
                Rent_Price = stoi(Rent_Price_str);
                cout << "Rent_Price : " << Rent_Price << endl;
            }
            line = "";
        }
        if (flag == 0)
            cout << "No Record Found !" << endl;
    }
    void updateRenter00(string userid, string modelnumber, string dueDate)
    {

        fstream read_file;
        read_file.open("Car.csv");

        vector<string> Car_lines;
        string line;
        int Car_line_num = 0;
        int Car_idx = 0;

        while (getline(read_file, line))
        {
            Car_lines.push_back(line);

            stringstream inputString(line);
            string curr_Car_id;
            getline(inputString, curr_Car_id, ',');
            if (curr_Car_id == modelnumber)
            {
                Car_idx = Car_line_num;
            }
            Car_line_num++;
        }
        read_file.close();

        // Get the current Car data
        vector<string> Car_data = extractCarData(modelnumber);

        if (!Car_data.empty())
        {

            Car_data[3] = userid;
            Car_data[2] = "1";
            Car_data[5] = dueDate;
            Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                 Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

            // Write the updated Car records back to the file
            ofstream write_file;
            write_file.open("Car.csv");
            if (write_file.fail())
            {
                cout << "Error opening file." << endl;
                return;
            }

            for (const string &Car_line : Car_lines)
            {
                write_file << Car_line << endl;
            }
            write_file.close();
        }
    }

    void Delete_Car(string Model_no);

    void Browse_Available_Cars(char c)
    {
        // c == 'C' for customer
        // c == 'E' for employee
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');
            if (c == 'C')
            {
                if (Is_Rented_str == "0")
                {
                    flag = 1;
                    cout << Model << " "
                         << " " << Condition << " " << Rent_Price_str << endl;
                }
            }
            if (c == 'E')
            {
                if (Is_Rented_str == "0")
                {
                    flag = 1;
                    cout << Model << " "
                         << " " << Condition << " " << stoi(Rent_Price_str) * 0.85 << endl;
                }
            }
            line = "";
        }
        if (flag == 0)
        {
            cout << "No Cars Available right now!" << endl;
        }
    }
    void Update_Car(string prev_Model_no);
    vector<string> Browse_currentlyRentedCars(string user_id)
    {
        vector<string> Currently_Rented_Cars;
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (user_id == Renter_id)
            {
                Currently_Rented_Cars.push_back(Model);
            }
            line = "";
        }

        return Currently_Rented_Cars;
    }

    string show_DueDateofCar(string modelNum)
    {
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (modelNum == Model)
            {
                flag = 1;
                return Due_Date;
            }
            line = "";
        }
        if (flag == 0)
        {
            cout << "No Record Found !" << endl;
            return "";
        }
        return "";
    }
    vector<string> extractCarData(string mod_no)
    {
        vector<string> StoreData;
        ifstream inputFile;
        inputFile.open("Car.csv");
        string line = "";

        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Model;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;

            getline(inputString, Model, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (mod_no == Model)
            {
                StoreData.push_back(Model);
                StoreData.push_back(Condition);
                StoreData.push_back(Is_Rented_str);
                StoreData.push_back(Renter_id);
                StoreData.push_back(Rent_Price_str);
                StoreData.push_back(Due_Date);
                break;
            }
            line = "";
        }
        return StoreData;
    }
};

class Customer_DBS
{
private:
    string Customer_id;
    string Customer_name;
    string Password;
    int Rented_cars;
    int Fine_due;
    string Customer_record;
    int Car_limit;

public:
    vector<string> search_id(string id_no)
    {
        vector<string> StoreData;
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";

        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (id_no == Customer_id)
            {
                StoreData.push_back(Customer_id);
                StoreData.push_back(Customer_name);
                StoreData.push_back(Password);
                StoreData.push_back(Rented_cars_str);
                StoreData.push_back(Fine_due_str);
                StoreData.push_back(Customer_record);
                StoreData.push_back(Car_limit_str);
                break;
            }
            line = "";
        }
        return StoreData;
    }

    bool search_Customer_id(string id_no)
    {
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (id_no == Customer_id)
            {
                flag = 1;
                break;
            }
            line = "";
        }
        if (flag == 0)
        {
            return false;
        }
        else
            return true;
    }
    bool search_customer_password(string pass)
    {
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (pass == Password)
            {
                flag = 1;
                break;
            }
            line = "";
        }
        if (flag == 0)
        {
            return false;
        }
        else
            return true;
    }
    void UpdateRentedCars(string CusId, int x)
    {

        fstream read_file;
        read_file.open("Customer.csv");

        vector<string> customer_lines;
        string line;
        int customer_line_num = 0;
        int customer_idx = 0;

        while (getline(read_file, line))
        {
            customer_lines.push_back(line);

            stringstream inputString(line);
            string curr_Customer_id;
            getline(inputString, curr_Customer_id, ',');
            if (curr_Customer_id == CusId)
            {
                customer_idx = customer_line_num;
            }
            customer_line_num++;
        }
        read_file.close();

        // Get the current customer data
        vector<string> customer_data = search_id(CusId);

        // Increase the rented cars count
        if (!customer_data.empty())
        {
            int rented_cars = stoi(customer_data[3]);
            if ((rented_cars >= 0 && x == 1) || (rented_cars > 0 && x == -1))
            {
                customer_data[3] = to_string(rented_cars + x);
                customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                               customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                // Write the updated customer records back to the file
                ofstream write_file;
                write_file.open("Customer.csv");
                if (write_file.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &customer_line : customer_lines)
                {
                    write_file << customer_line << endl;
                }
                write_file.close();
            }
        }
    }
    int ReturnRentedCar(string CusId)
    {
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (CusId == Customer_id)
            {
                return stoi(Car_limit_str);
            }
            line = "";
        }
        return -1;
    }
    int NoOfRentedCars(string customrid)
    {
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (customrid == Customer_id)
            {
                return stoi(Rented_cars_str);
            }
            line = "";
        }
        return -1;
    }
    void Add_Customer()
    {
        fstream fout;

        // opens an existing csv file or creates a new file.
        fout.open("Customer.csv", ios::app);
        int n;
        cout << "Enter the number of Customers you want to add" << endl;
        cin >> n;
        cout << "Enter the details of 'n' Customers:" << endl;

        // Read the input
        for (int i = 0; i < n; i++)
        {
            cout << "Customer_id : ";
            cin >> Customer_id;

            vector<string> DataCustomer = search_id(Customer_id);
            while (Customer_id == DataCustomer[0])
            {
                cout << "Customer_id : ";
                cin >> Customer_id;
                cout << "Customer with this id already exists in the Customer Database" << endl;
            }

            cout << "Customer_name :";
            cin >> Customer_name;
            cout << "Password : ";
            cin >> Password;
            cout << "Rented_cars : ";
            cin >> Rented_cars;
            cout << "Fine_due : ";
            cin >> Fine_due;
            cout << "Customer_record : ";
            cin >> Customer_record;
            cout << "Car_limit : ";
            cin >> Car_limit;

            // Insert the data to file
            fout << Customer_id << ","
                 << Customer_name << ","
                 << Password << ","
                 << Rented_cars << ","
                 << Fine_due << ","
                 << Customer_record << ","
                 << Car_limit << "\n";
        }
        fout.close();
    }

    void Display_Customer(string Customer_id_req)
    {
        ifstream inputFile;
        inputFile.open("Customer.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Customer_id;
            string Customer_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Customer_record;
            string Car_limit_str;

            getline(inputString, Customer_id, ',');
            getline(inputString, Customer_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Customer_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (Customer_id_req == Customer_id)
            {
                flag = 1;
                cout << "Customer_id : " << Customer_id << endl;
                cout << "Customer_name : " << Customer_name << endl;
                cout << "Password : " << Password << endl;
                Rented_cars = stoi(Rented_cars_str);
                cout << "Rented_cars : " << Rented_cars << endl;
                Fine_due = stoi(Fine_due_str);
                cout << "Fine_due : " << Fine_due_str << endl;
                cout << "Customer_record : " << Customer_record << endl;
                Car_limit = stoi(Car_limit_str);
                cout << "Car_limit : " << Car_limit << endl;

                break;
            }
            line = "";
        }
        if (flag == 0)
            cout << "No Record Found" << endl;
    }
    void Delete_Customer(string CustomerId);
    void Update_Customer(string prev_Cus_id)
    {
        car_DBS x0;
        string custid;
        if (search_Customer_id(prev_Cus_id) == 0)
        {
            cout << "The Customer with the given Customer id doesn't exist, so you can't update the record" << endl;
            return;
        }
        else
        {
            fstream read_file;
            read_file.open("Customer.csv");
            if (read_file.fail())
            {
                cout << "Error opening file." << endl;
                return;
            }

            vector<string> lines0;
            string line;
            int line_num = 0;
            int idx0 = 0;
            while (getline(read_file, line))
            {
                lines0.push_back(line);
                stringstream inputString(line);
                string curr_Customer_id;
                string Customer_name;
                string Cus_Password;
                string Rented_cars;
                string fine_due;
                string CustomerRec;
                string carLimit;
                getline(inputString, curr_Customer_id, ',');
                getline(inputString, Customer_name, ',');
                getline(inputString, Cus_Password, ',');
                getline(inputString, Rented_cars, ',');
                getline(inputString, fine_due, ',');
                getline(inputString, CustomerRec, ',');
                getline(inputString, carLimit, '\n');

                if (curr_Customer_id == prev_Cus_id)
                {
                    idx0 = line_num;
                }
                line_num++;
            }
            read_file.close();

            // Get new data from the user
            cout << "Enter new Customer details : " << endl;
            cout << "Customer_id : ";
            cin >> Customer_id;
            custid = Customer_id;
            cout << "Customer_name :";
            cin >> Customer_name;
            cout << "Password : ";
            cin >> Password;
            cout << "Rented_cars : ";
            cin >> Rented_cars;
            cout << "Fine_due : ";
            cin >> Fine_due;
            cout << "Customer_record : ";
            cin >> Customer_record;
            cout << "Car_limit : ";
            cin >> Car_limit;

            // Update the line in the vector
            lines0[idx0] = Customer_id + "," + Customer_name + "," + Password + "," + to_string(Rented_cars) + "," + to_string(Fine_due) + "," + Customer_record + "," + to_string(Car_limit);

            // Write the updated data back to the file
            ofstream write_file;
            write_file.open("Customer.csv");
            if (write_file.fail())
            {
                cout << "Error opening file." << endl;
                return;
            }
            for (int i = 0; i < lines0.size(); i++)
            {
                write_file << lines0[i] << endl;
            }
            write_file.close();
            int i = 0;
            fstream read_file1;
            read_file1.open("Car.csv");
            vector<string> Curr_Rented_car = x0.Browse_currentlyRentedCars(prev_Cus_id);
            string modelnumber;
            while (!Curr_Rented_car.empty())
            {
                modelnumber = Curr_Rented_car[i];
                i++;
                vector<string> Car_lines;
                string line;
                int Car_line_num = 0;
                int Car_idx = 0;

                while (getline(read_file1, line))
                {
                    Car_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Car_id;
                    getline(inputString, curr_Car_id, ',');
                    if (curr_Car_id == modelnumber)
                    {
                        Car_idx = Car_line_num;
                    }
                    Car_line_num++;
                }
                read_file1.close();

                // Get the current Car data
                vector<string> Car_data = x0.extractCarData(modelnumber);

                if (!Car_data.empty())
                {

                    Car_data[3] = custid;

                    Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                         Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                    // Write the updated Car records back to the file
                    ofstream write_file1;
                    write_file1.open("Car.csv");
                    if (write_file1.fail())
                    {
                        cout << "Error opening file." << endl;
                        return;
                    }

                    for (const string &Car_line : Car_lines)
                    {
                        write_file1 << Car_line << endl;
                    }
                    write_file1.close();
                }
            }

            cout << "Customer record updated successfully." << endl;
        }
        return;
    }
};

class Employee_DBS
{
private:
    string Employee_id;
    string Employee_name;
    string Password;
    int Rented_cars;
    int Fine_due;
    string Employee_record;
    int Car_limit;

public:
    vector<string> search_id(string id_no)
    {
        vector<string> StoreData;
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";

        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (id_no == Employee_id)
            {
                StoreData.push_back(Employee_id);
                StoreData.push_back(Employee_name);
                StoreData.push_back(Password);
                StoreData.push_back(Rented_cars_str);
                StoreData.push_back(Fine_due_str);
                StoreData.push_back(Employee_record);
                StoreData.push_back(Car_limit_str);
                break;
            }
            line = "";
        }
        return StoreData;
    }

    bool search_Employee_id(string id_no)
    {
        int flag = 0;
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";

        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (id_no == Employee_id)
            {
                flag = 1;
                break;
            }
            line = "";
        }
        if (flag == 0)
        {
            return false;
        }
        else
            return true;
    }

    bool search_Employee_Password(string pass00)
    {
        int flag = 0;
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";

        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (pass00 == Password)
            {
                flag = 1;
                break;
            }
            line = "";
        }
        if (flag == 0)
        {
            return false;
        }
        else
            return true;
    }
    int ReturnCarLim_emp(string EmpId)
    {
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (EmpId == Employee_id)
            {
                return stoi(Car_limit_str);
            }
            line = "";
        }
        return -1;
    }
    int NoOfRentedCars_emp(string empid)
    {
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (empid == Employee_id)
            {
                return stoi(Rented_cars_str);
            }
            line = "";
        }
        return -1;
    }
    void Add_Employee()
    {
        fstream fout;

        // opens an existing csv file or creates a new file.
        fout.open("Employee.csv", ios::app);
        int n;
        cout << "Enter the number of Employees you want to add" << endl;
        cin >> n;
        cout << "Enter the details of 'n' Customers:" << endl;

        // Read the input
        for (int i = 0; i < n; i++)
        {

            cout << "Employee_id : ";
            cin >> Employee_id;
            vector<string> Data22 = search_id(Employee_id);
            while (Employee_id == Data22[0])
            {
                cout << "Employee with this Employee id already exist" << endl;
                cout << "Employee_id : ";
                cin >> Employee_id;
            }
            cout << "Employee_name :";
            cin >> Employee_name;
            cout << "Password : ";
            cin >> Password;
            cout << "Rented_cars : ";
            cin >> Rented_cars;
            cout << "Fine_due : ";
            cin >> Fine_due;
            cout << "Employee_record : ";
            cin >> Employee_record;
            cout << "Car_limit : ";
            cin >> Car_limit;

            // Insert the data to file
            fout << Employee_id << ","
                 << Employee_name << ","
                 << Password << ","
                 << Rented_cars << ","
                 << Fine_due << ","
                 << Employee_record << ","
                 << Car_limit << "\n";
        }
        fout.close();
    }
    void UpdateRentedCars_emp(string EmpId, int x)
    {

        fstream read_file;
        read_file.open("Employee.csv");

        vector<string> Employee_lines;
        string line;
        int Employee_line_num = 0;
        int Employee_idx = 0;

        while (getline(read_file, line))
        {
            Employee_lines.push_back(line);

            stringstream inputString(line);
            string curr_Employee_id;
            getline(inputString, curr_Employee_id, ',');
            if (curr_Employee_id == EmpId)
            {
                Employee_idx = Employee_line_num;
            }
            Employee_line_num++;
        }
        read_file.close();

        // Get the current Employee data
        vector<string> Employee_data = search_id(EmpId);

        // Increase the rented cars count
        if (!Employee_data.empty())
        {
            int rented_cars = stoi(Employee_data[3]);
            if ((rented_cars >= 0 && x == 1) || (rented_cars > 0 && x == -1))
            {
                Employee_data[3] = to_string(rented_cars + x);
                Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                               Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                // Write the updated Employee records back to the file
                ofstream write_file;
                write_file.open("Employee.csv");
                if (write_file.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &Employee_line : Employee_lines)
                {
                    write_file << Employee_line << endl;
                }
                write_file.close();
            }
        }
    }
    void Display_Employee(string Employee_id_req)
    {
        ifstream inputFile;
        inputFile.open("Employee.csv");
        string line = "";
        int flag = 0;
        while (getline(inputFile, line))
        {

            stringstream inputString(line);
            string Employee_id;
            string Employee_name;
            string Password;
            string Rented_cars_str;
            string Fine_due_str;
            string Employee_record;
            string Car_limit_str;

            getline(inputString, Employee_id, ',');
            getline(inputString, Employee_name, ',');
            getline(inputString, Password, ',');
            getline(inputString, Rented_cars_str, ',');
            getline(inputString, Fine_due_str, ',');
            getline(inputString, Employee_record, ',');

            getline(inputString, Car_limit_str, '\n');

            if (Employee_id_req == Employee_id)
            {
                flag = 1;
                cout << "Employee_id : " << Employee_id << endl;
                cout << "Employee_name : " << Employee_name << endl;
                cout << "Password : " << Password << endl;
                Rented_cars = stoi(Rented_cars_str);
                cout << "Rented_cars : " << Rented_cars << endl;
                Fine_due = stoi(Fine_due_str);
                cout << "Fine_due : " << Fine_due_str << endl;
                cout << "Employee_record : " << Employee_record << endl;
                Car_limit = stoi(Car_limit_str);
                cout << "Car_limit : " << Car_limit << endl;

                break;
            }
            line = "";
        }
        if (flag == 0)
            cout << "No Record Found" << endl;
    }
    void Update_Employee(string prev_Emp_id)
    {
        car_DBS x0;
        string empid;
        if (search_Employee_id(prev_Emp_id) == 0)
        {
            cout << "The Employee with the given Cusyomer id doesn't exist, so you can't update the record" << endl;
            return;
        }
        else
        {
            fstream read_file;
            read_file.open("Employee.csv");
            if (read_file.fail())
            {
                cout << "Error opening file." << endl;
                return;
            }

            vector<string> lines0;
            string line;
            int line_num = 0;
            int idx0 = 0;
            while (getline(read_file, line))
            {
                lines0.push_back(line);
                stringstream inputString(line);
                string curr_Employee_id;
                string Employee_name;
                string Cus_Password;
                string Rented_cars;
                string fine_due;
                string EmployeeRec;
                string carLimit;
                getline(inputString, curr_Employee_id, ',');
                getline(inputString, Employee_name, ',');
                getline(inputString, Cus_Password, ',');
                getline(inputString, Rented_cars, ',');
                getline(inputString, fine_due, ',');
                getline(inputString, EmployeeRec, ',');
                getline(inputString, carLimit, '\n');

                if (curr_Employee_id == prev_Emp_id)
                {
                    idx0 = line_num;
                }
                line_num++;
            }
            read_file.close();

            // Get new data from the user
            cout << "Enter new Employee details : " << endl;
            cout << "Employee_id : ";
            cin >> Employee_id;
            empid = Employee_id;
            cout << "Employee_name :";
            cin >> Employee_name;
            cout << "Password : ";
            cin >> Password;
            cout << "Rented_cars : ";
            cin >> Rented_cars;
            cout << "Fine_due : ";
            cin >> Fine_due;
            cout << "Employee_record : ";
            cin >> Employee_record;
            cout << "Car_limit : ";
            cin >> Car_limit;

            // Update the line in the vector
            lines0[idx0] = Employee_id + "," + Employee_name + "," + Password + "," + to_string(Rented_cars) + "," + to_string(Fine_due) + "," + Employee_record + "," + to_string(Car_limit);

            // Write the updated data back to the file
            ofstream write_file;
            write_file.open("Employee.csv");
            if (write_file.fail())
            {
                cout << "Error opening file." << endl;
                return;
            }
            for (int i = 0; i < lines0.size(); i++)
            {
                write_file << lines0[i] << endl;
            }
            write_file.close();
            int i = 0;
            fstream read_file1;
            read_file1.open("Car.csv");
            vector<string> Curr_Rented_car = x0.Browse_currentlyRentedCars(prev_Emp_id);
            string modelnumber;
            while (!Curr_Rented_car.empty())
            {
                modelnumber = Curr_Rented_car[i];
                i++;
                vector<string> Car_lines;
                string line;
                int Car_line_num = 0;
                int Car_idx = 0;

                while (getline(read_file1, line))
                {
                    Car_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Car_id;
                    getline(inputString, curr_Car_id, ',');
                    if (curr_Car_id == modelnumber)
                    {
                        Car_idx = Car_line_num;
                    }
                    Car_line_num++;
                }
                read_file1.close();

                // Get the current Car data
                vector<string> Car_data = x0.extractCarData(modelnumber);

                if (!Car_data.empty())
                {

                    Car_data[3] = empid;

                    Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                         Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                    // Write the updated Car records back to the file
                    ofstream write_file1;
                    write_file1.open("Car.csv");
                    if (write_file1.fail())
                    {
                        cout << "Error opening file." << endl;
                        return;
                    }

                    for (const string &Car_line : Car_lines)
                    {
                        write_file1 << Car_line << endl;
                    }
                    write_file1.close();
                }
            }

            cout << "Employee record updated successfully." << endl;
        }
        return;
    }
    void Delete_Employee(string EmployeeId);
};

void car_DBS::Update_Car(string prev_Model_no)
{
    string prev_Renter_id;
    Customer_DBS c0;
    Employee_DBS e0;
    if (Search_model_no(prev_Model_no) == 0)
    {
        cout << "The Car with the given Model number doesn't exist, so you can't update the record" << endl;
        return;
    }
    else
    {
        fstream read_file;
        read_file.open("Car.csv");
        if (read_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines0;
        string line;
        int line_num = 0;
        int idx0 = 0;
        while (getline(read_file, line))
        {
            lines0.push_back(line);
            stringstream inputString(line);
            string curr_Model_no;
            string condition;
            string Is_Rented_str;
            string Renter_id;
            getline(inputString, curr_Model_no, ',');
            getline(inputString, condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            prev_Renter_id = Renter_id;

            if (curr_Model_no == prev_Model_no)
            {
                idx0 = line_num;
            }
            line_num++;
        }
        read_file.close();

        // Get new data from the user
        cout << "Enter the new details for the car:" << endl;
        cout << "Model : ";
        cin >> Model;
        cout << "Condition : ";
        cin >> Condition;
        cout << "Is_Rented(0 or 1) : ";
        cin >> Is_Rented;
        cout << "If you don't want to rent the car to someone.Please write 'None' for Renter_id" << endl;
        cout << "Renter_id : ";

        cin >> Renter_id;
        if (Renter_id != prev_Renter_id && Renter_id == "None")
        {
            if (c0.search_Customer_id(prev_Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Customer.csv");

                vector<string> customer_lines;
                string line;
                int customer_line_num = 0;
                int customer_idx = 0;

                while (getline(read_file, line))
                {
                    customer_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Customer_id;
                    getline(inputString, curr_Customer_id, ',');
                    if (curr_Customer_id == prev_Renter_id)
                    {
                        customer_idx = customer_line_num;
                    }
                    customer_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> customer_data = c0.search_id(prev_Renter_id);

                // Decrease the rented cars count
                if (!customer_data.empty())
                {
                    int rented_cars = stoi(customer_data[3]);
                    if (rented_cars > 0)
                    {
                        customer_data[3] = to_string(rented_cars - 1);
                        customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                                       customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Customer.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &customer_line : customer_lines)
                        {
                            write_file << customer_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
            else if (e0.search_Employee_id(prev_Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Employee.csv");

                vector<string> Employee_lines;
                string line;
                int Employee_line_num = 0;
                int Employee_idx = 0;

                while (getline(read_file, line))
                {
                    Employee_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Employee_id;
                    getline(inputString, curr_Employee_id, ',');
                    if (curr_Employee_id == prev_Renter_id)
                    {
                        Employee_idx = Employee_line_num;
                    }
                    Employee_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> Employee_data = c0.search_id(prev_Renter_id);

                // Decrease the rented cars count
                if (!Employee_data.empty())
                {
                    int rented_cars = stoi(Employee_data[3]);
                    if (rented_cars > 0)
                    {
                        Employee_data[3] = to_string(rented_cars - 1);
                        Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                                       Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Employee.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &Employee_line : Employee_lines)
                        {
                            write_file << Employee_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
        }
        else if (Renter_id != prev_Renter_id && Renter_id != "None")
        {
            if (c0.search_Customer_id(prev_Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Customer.csv");

                vector<string> customer_lines;
                string line;
                int customer_line_num = 0;
                int customer_idx = 0;

                while (getline(read_file, line))
                {
                    customer_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Customer_id;
                    getline(inputString, curr_Customer_id, ',');
                    if (curr_Customer_id == prev_Renter_id)
                    {
                        customer_idx = customer_line_num;
                    }
                    customer_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> customer_data = c0.search_id(prev_Renter_id);

                // Decrease the rented cars count
                if (!customer_data.empty())
                {
                    int rented_cars = stoi(customer_data[3]);
                    if (rented_cars > 0)
                    {
                        customer_data[3] = to_string(rented_cars - 1);
                        customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                                       customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Customer.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &customer_line : customer_lines)
                        {
                            write_file << customer_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
            else if (e0.search_Employee_id(prev_Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Employee.csv");

                vector<string> Employee_lines;
                string line;
                int Employee_line_num = 0;
                int Employee_idx = 0;

                while (getline(read_file, line))
                {
                    Employee_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Employee_id;
                    getline(inputString, curr_Employee_id, ',');
                    if (curr_Employee_id == prev_Renter_id)
                    {
                        Employee_idx = Employee_line_num;
                    }
                    Employee_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> Employee_data = c0.search_id(prev_Renter_id);

                // Decrease the rented cars count
                if (!Employee_data.empty())
                {
                    int rented_cars = stoi(Employee_data[3]);
                    if (rented_cars > 0)
                    {
                        Employee_data[3] = to_string(rented_cars - 1);
                        Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                                       Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Employee.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &Employee_line : Employee_lines)
                        {
                            write_file << Employee_line << endl;
                        }
                        write_file.close();
                    }
                }
            }

            if (c0.search_Customer_id(Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Customer.csv");

                vector<string> customer_lines;
                string line;
                int customer_line_num = 0;
                int customer_idx = 0;

                while (getline(read_file, line))
                {
                    customer_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Customer_id;
                    getline(inputString, curr_Customer_id, ',');
                    if (curr_Customer_id == Renter_id)
                    {
                        customer_idx = customer_line_num;
                    }
                    customer_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> customer_data = c0.search_id(Renter_id);

                // Decrease the rented cars count
                if (!customer_data.empty())
                {
                    int rented_cars = stoi(customer_data[3]);
                    if (rented_cars >= 0)
                    {
                        customer_data[3] = to_string(rented_cars + 1);
                        customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                                       customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Customer.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &customer_line : customer_lines)
                        {
                            write_file << customer_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
            else if (e0.search_Employee_id(Renter_id) == 1)
            {
                // Inside the Customer_DBS class

                fstream read_file;
                read_file.open("Employee.csv");

                vector<string> Employee_lines;
                string line;
                int Employee_line_num = 0;
                int Employee_idx = 0;

                while (getline(read_file, line))
                {
                    Employee_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Employee_id;
                    getline(inputString, curr_Employee_id, ',');
                    if (curr_Employee_id == Renter_id)
                    {
                        Employee_idx = Employee_line_num;
                    }
                    Employee_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> Employee_data = c0.search_id(Renter_id);

                // Decrease the rented cars count
                if (!Employee_data.empty())
                {
                    int rented_cars = stoi(Employee_data[3]);
                    if (rented_cars >= 0)
                    {
                        Employee_data[3] = to_string(rented_cars + 1);
                        Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                                       Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Employee.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &Employee_line : Employee_lines)
                        {
                            write_file << Employee_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
        }

        cout << "Rent_Price : ";
        cin >> Rent_Price;
        cout << "Due_Date : ";
        cin >> Due_Date;

        // Update the line in the vector
        lines0[idx0] = Model + "," + Condition + "," + to_string(Is_Rented) + "," + Renter_id + "," + to_string(Rent_Price) + "," + Due_Date;

        // Write the updated data back to the file
        ofstream write_file;
        write_file.open("Car.csv");
        if (write_file.fail())
        {
            cout << "Error opening file." << endl;
            return;
        }
        for (int i = 0; i < lines0.size(); i++)
        {
            write_file << lines0[i] << endl;
        }
        write_file.close();

        cout << "Car record updated successfully." << endl;
        return;
    }
}

void car_DBS::Delete_Car(string Model_no)
{
    Customer_DBS C1;
    Employee_DBS E1;
    string UserId;
    if (Search_model_no(Model_no) == 0)
    {
        cout << "The Car with given Model number doesn't exists,So you can't delete the record" << endl;
        return;
    }
    else
    {
        fstream read_file;
        read_file.open("Car.csv");
        if (read_file.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        vector<string> lines;
        string line;
        int line_num = 0;
        int idx = 0;
        while (getline(read_file, line))
        {
            lines.push_back(line);
            stringstream inputString(line);
            string curr_Model_no;
            string Condition;
            string Is_Rented_str;
            string Renter_id;
            string Rent_Price_str;
            string Due_Date;
            getline(inputString, curr_Model_no, ',');
            getline(inputString, Condition, ',');
            getline(inputString, Is_Rented_str, ',');
            getline(inputString, Renter_id, ',');
            getline(inputString, Rent_Price_str, ',');
            getline(inputString, Due_Date, '\n');

            if (curr_Model_no == Model_no)
            {
                idx = line_num;
                UserId = Renter_id;
                if (C1.search_Customer_id(UserId) == 1)
                {
                    C1.UpdateRentedCars(UserId, -1);
                }
                else if (E1.search_Employee_id(UserId) == 1)
                {
                    E1.UpdateRentedCars_emp(UserId, -1);
                }
            }
            line_num++;
        }
        read_file.close();

        ofstream write_file;
        write_file.open("Car.csv");
        if (write_file.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        for (int i = 0; i < lines.size(); i++)
        {
            if (i != idx)
                write_file << lines[i] << endl;
        }
        write_file.close();

        return;
    }
}

void Customer_DBS ::Delete_Customer(string CustomerId)
{
    car_DBS x0;
    string CId;
    if (search_Customer_id(CustomerId) == 0)
    {
        cout << "The Customer with given id number doesn't exists,So you can't delete the record" << endl;
        return;
    }
    else
    {
        fstream read_file0;
        read_file0.open("Customer.csv");
        if (read_file0.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        vector<string> lines;
        string line;
        int line_num = 0;
        int idx = 0;
        while (getline(read_file0, line))
        {
            lines.push_back(line);
            stringstream inputString(line);
            string curr_Customer_id;
            getline(inputString, curr_Customer_id, ',');
            if (curr_Customer_id == CustomerId)
            {
                idx = line_num;
                CId = curr_Customer_id;
            }
            line_num++;
        }
        read_file0.close();

        ofstream write_file0;
        write_file0.open("Customer.csv");
        if (write_file0.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        for (int i = 0; i < lines.size(); i++)
        {
            if (i != idx)
                write_file0 << lines[i] << endl;
        }
        write_file0.close();
        int i = 0;
        fstream read_file1;
        read_file1.open("Car.csv");
        vector<string> Curr_Rented_car = x0.Browse_currentlyRentedCars(CId);
        string modelnumber;
        while (!Curr_Rented_car.empty())
        {
            modelnumber = Curr_Rented_car[i];
            i++;
            vector<string> Car_lines;
            string line;
            int Car_line_num = 0;
            int Car_idx = 0;

            while (getline(read_file1, line))
            {
                Car_lines.push_back(line);

                stringstream inputString(line);
                string curr_Car_id;
                getline(inputString, curr_Car_id, ',');
                if (curr_Car_id == modelnumber)
                {
                    Car_idx = Car_line_num;
                }
                Car_line_num++;
            }
            read_file1.close();

            // Get the current Car data
            vector<string> Car_data = x0.extractCarData(modelnumber);

            if (!Car_data.empty())
            {

                Car_data[3] = "none";
                Car_data[1] = "average";
                Car_data[2] = "0";
                Car_data[5] = "none";
                Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                     Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                // Write the updated Car records back to the file
                ofstream write_file1;
                write_file1.open("Car.csv");
                if (write_file1.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &Car_line : Car_lines)
                {
                    write_file1 << Car_line << endl;
                }
                write_file1.close();
            }
        }
        cout << "Customer Record deleted succesfully<<endl ";
        return;
    }
}

void Employee_DBS ::Delete_Employee(string EmployeeId)
{
    car_DBS x0;
    string CId;
    if (search_Employee_id(EmployeeId) == 0)
    {
        cout << "The Employee with given id number doesn't exists,So you can't delete the record" << endl;
        return;
    }
    else
    {
        fstream read_file0;
        read_file0.open("Employee.csv");
        if (read_file0.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        vector<string> lines;
        string line;
        int line_num = 0;
        int idx = 0;
        while (getline(read_file0, line))
        {
            lines.push_back(line);
            stringstream inputString(line);
            string curr_Employee_id;
            getline(inputString, curr_Employee_id, ',');
            if (curr_Employee_id == EmployeeId)
            {
                idx = line_num;
                CId = curr_Employee_id;
            }
            line_num++;
        }
        read_file0.close();

        ofstream write_file0;
        write_file0.open("Employee.csv");
        if (write_file0.fail())
        {
            std::cout << "Error opening file." << endl;
            return;
        }
        for (int i = 0; i < lines.size(); i++)
        {
            if (i != idx)
                write_file0 << lines[i] << endl;
        }
        write_file0.close();
        int i = 0;
        fstream read_file1;
        read_file1.open("Car.csv");
        vector<string> Curr_Rented_car = x0.Browse_currentlyRentedCars(CId);
        string modelnumber;
        while (!Curr_Rented_car.empty())
        {
            modelnumber = Curr_Rented_car[i];
            i++;
            vector<string> Car_lines;
            string line;
            int Car_line_num = 0;
            int Car_idx = 0;

            while (getline(read_file1, line))
            {
                Car_lines.push_back(line);

                stringstream inputString(line);
                string curr_Car_id;
                getline(inputString, curr_Car_id, ',');
                if (curr_Car_id == modelnumber)
                {
                    Car_idx = Car_line_num;
                }
                Car_line_num++;
            }
            read_file1.close();

            // Get the current Car data
            vector<string> Car_data = x0.extractCarData(modelnumber);

            if (!Car_data.empty())
            {

                Car_data[3] = "none";
                Car_data[1] = "average";
                Car_data[2] = "0";
                Car_data[5] = "none";
                Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                     Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                // Write the updated Car records back to the file
                ofstream write_file1;
                write_file1.open("Car.csv");
                if (write_file1.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &Car_line : Car_lines)
                {
                    write_file1 << Car_line << endl;
                }
                write_file1.close();
            }
        }
        cout << " Employee Record deleted  Succesfully" << endl;
    }
}

class User
{

protected:
    string id;
    string name;
    string Password;

public:
    void Input_name()
    {
        cin >> name;
    }
    void Input_id()
    {
        cin >> id;
    }
    void Input_Password()
    {
        cin >> Password;
    }
};

class Manager : public User
{

public:
    car_DBS c;
    Customer_DBS cus;
    Employee_DBS EE;
    bool Verify_Manager()
    {
        if (id == "mm001" && Password == "123456" && name == "vishal")
        {
            return true;
        }
        else
            return false;
    }
    void modify_records()
    {
        cout << "Edit : " << endl;
        cout << "Car_record : "
             << "1" << endl;
        cout << "Customer_record : "
             << "2" << endl;
        cout << "Employee_record : "
             << "3" << endl;

        int modify_choice;
        cin >> modify_choice;

        if (modify_choice == 1)
        {

            cout << "What do you want to do?" << endl;
            cout << "Add_cars: "
                 << "1" << endl;
            cout << "Display_car_details: "
                 << "2" << endl;
            cout << "Update_car_record: "
                 << "3" << endl;
            cout << "Delete_car_record: "
                 << "4" << endl;
            int car_choice;
            cin >> car_choice;

            string model_number;

            if (car_choice == 1)
            {

                c.Add_Car();
            }
            else if (car_choice == 2)
            {
                cout << "Enter Model_number " << endl;
                cin >> model_number;
                c.Display_Car(model_number);
            }
            else if (car_choice == 3)
            {
                cout << "Enter Model_number " << endl;
                cin >> model_number;
                c.Update_Car(model_number);
            }

            else if (car_choice == 4)
            {
                cout << "Enter Model_number" << endl;
                cin >> model_number;
                c.Delete_Car(model_number);
            }
        }

        if (modify_choice == 2)
        {

            cout << "What do you want to do?" << endl;
            cout << "Add_customers: "
                 << "1" << endl;
            cout << "Display_customer_details: "
                 << "2" << endl;
            cout << "Update_customer_record: "
                 << "3" << endl;
            cout << "Delete_customer_record: "
                 << "4" << endl;
            int customer_choice;
            cin >> customer_choice;

            string customerid;
            if (customer_choice == 1)
            {

                cus.Add_Customer();
            }
            else if (customer_choice == 2)
            {
                cout << "Enter Customer_id : ";
                cin >> customerid;
                cus.Display_Customer(customerid);
            }
            else if (customer_choice == 3)
            {
                cout << "Enter Customer_id : ";
                cin >> customerid;
                cus.Update_Customer(customerid);
            }
            else if (customer_choice == 4)
            {
                cout << "Enter Customer_id : ";
                cin >> customerid;
                cus.Delete_Customer(customerid);
            }
        }

        else if (modify_choice == 3)
        {
            cout << "What do you want to do?" << endl;
            cout << "Add_Employees: "
                 << "1" << endl;
            cout << "Display_Employee_details: "
                 << "2" << endl;
            cout << "Update_Employee_record: "
                 << "3" << endl;
            cout << "Delete_Employee_record: "
                 << "4" << endl;
            int Employee_choice;
            cin >> Employee_choice;

            string Employeeid;

            if (Employee_choice == 1)
            {

                EE.Add_Employee();
            }
            else if (Employee_choice == 2)
            {

                cout << "Enter Employee id : ";
                cin >> Employeeid;
                EE.Display_Employee(Employeeid);
            }
            else if (Employee_choice == 3)
            {

                cout << "Enter Employee id : ";
                cin >> Employeeid;
                EE.Update_Employee(Employeeid);
            }
            else if (Employee_choice == 4)
            {
                cout << "Enter Employee id : ";
                cin >> Employeeid;
                EE.Delete_Employee(Employeeid);
            }
        }
    }
};

class Customer : public User
{
public:
    Customer_DBS cc;
    car_DBS tempcar;
    bool verify_Customer()
    {

        vector<string> StoreData1 = cc.search_id(id);
        if (StoreData1.size() == 0)
        {
            return false;
        }
        else if (id == StoreData1[0] && Password == StoreData1[2] && name == StoreData1[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void BrowseCurrentlyRentedCars()
    {

        vector<string> Currently_RentedCars = tempcar.Browse_currentlyRentedCars(id);
        for (int i = 0; i < Currently_RentedCars.size(); i++)
        {
            cout << Currently_RentedCars[i] << endl;
        }
    }

    void Customer_signup()
    {
        string Customername;
        string Password1;
        string id0;

        cout << "Register yourself:-" << endl;
        fstream fout;

        // opens an existing csv file or creates a new file.
        fout.open("Customer.csv", ios::app);

        cout << "Enter any 4 digit id(including numbers and alphabets) : ";
        cin >> id0;
        while (cc.search_Customer_id(id0) == 1)
        {
            cout << "Please enter a new id,the previous one already exists : ";
            cin >> id0;
        }
        cout << "Enter your name(without spaces) : ";
        cin >> Customername;

        cout << "Enter your password: ";
        cin >> Password1;
        while (cc.search_customer_password(Password1) == 1)
        {
            cout << "Please enter a new Password,the previous one already exists : ";
            cin >> Password1;
        }
        // Insert the data to file
        fout << id0 << ","
             << Customername << ","
             << Password1 << ","
             << "0"
             << ","
             << "0"
             << ","
             << "average"
             << ","
             << "3"
             << "\n";

        fout.close();
    }
    void Return_Request()
    {
        // fine per day is 20rs

        car_DBS cx;
        Customer_DBS cy;
        int days;
        string model_number;
        string condition;
        cout << "Enter the model number of car you are returning : ";
        cin >> model_number;
        cout << "Enter the condition of the car(namely worst,bad,average,good) : ";
        cin >> condition;
        cout << "Enter the number of extra days after due date you are returning the car : ";
        cin >> days;
        x:
        vector<string> RentedCars = cx.Browse_currentlyRentedCars(id);
        int flag = 0;

        
        for (int i=0;i<RentedCars.size();i++)
        {
            if (RentedCars[i] == model_number)
            {
                flag = 1;
                break;
            }
            i++;
        }
        int fine = 20 * days;
        if (flag == 0)
        {
            cout << "The car Model number you entered doesn't match the car model number's you are corrently renting"<<endl;
            cout << "Please re-enter the car model number you want to return : ";
            cin >> model_number;
            goto x;

        }
        else
        {
            fstream read_file1;
            read_file1.open("Car.csv");

            vector<string> Car_lines;
            string line;
            int Car_line_num = 0;
            int Car_idx = 0;

            while (getline(read_file1, line))
            {
                Car_lines.push_back(line);

                stringstream inputString(line);
                string curr_Car_id;
                getline(inputString, curr_Car_id, ',');
                if (curr_Car_id == model_number)
                {
                    Car_idx = Car_line_num;
                }
                Car_line_num++;
            }
            read_file1.close();

            // Get the current Car data
            vector<string> Car_data = cx.extractCarData(model_number);

            if (!Car_data.empty())
            {

                Car_data[3] = "none";
                Car_data[1] = "average";
                Car_data[2] = "0";
                Car_data[5] = "none";
                Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                     Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                // Write the updated Car records back to the file
                ofstream write_file1;
                write_file1.open("Car.csv");
                if (write_file1.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &Car_line : Car_lines)
                {
                    write_file1 << Car_line << endl;
                }
                write_file1.close();
            }

            cout << "Your Current fine is : " << fine;
            if (fine == 0)
            {
                fstream read_file;
                read_file.open("Customer.csv");

                vector<string> customer_lines;
                string line;
                int customer_line_num = 0;
                int customer_idx = 0;

                while (getline(read_file, line))
                {
                    customer_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Customer_id;
                    getline(inputString, curr_Customer_id, ',');
                    if (curr_Customer_id == id)
                    {
                        customer_idx = customer_line_num;
                    }
                    customer_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> customer_data = cy.search_id(id);

                // Decrease the rented cars count
                if (!customer_data.empty())
                {
                    int rented_cars = stoi(customer_data[3]);
                    if (rented_cars > 0)
                    {
                        customer_data[3] = to_string(rented_cars - 1);
                        customer_data[4] = "0";
                        if (stoi(customer_data[6]) < 4)
                        {
                            int x = stoi(customer_data[6]) + 1;
                            customer_data[6] = to_string(x);
                        }
                        if (customer_data[5] == "worst")
                        {
                            customer_data[5] = "bad";
                        }
                        else if (customer_data[5] == "bad")
                        {
                            customer_data[5] = "average";
                        }
                        else if (customer_data[5] == "average")
                        {
                            customer_data[5] = "good";
                        }
                        customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                                       customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Customer.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &customer_line : customer_lines)
                        {
                            write_file << customer_line << endl;
                        }
                        write_file.close();
                    }
                }
            }

            else if (fine > 0)
            {
                fstream read_file;
                read_file.open("Customer.csv");

                vector<string> customer_lines;
                string line;
                int customer_line_num = 0;
                int customer_idx = 0;

                while (getline(read_file, line))
                {
                    customer_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Customer_id;
                    getline(inputString, curr_Customer_id, ',');
                    if (curr_Customer_id == id)
                    {
                        customer_idx = customer_line_num;
                    }
                    customer_line_num++;
                }
                read_file.close();

                // Get the current customer data
                vector<string> customer_data = cy.search_id(id);

                // Decrease the rented cars count
                if (!customer_data.empty())
                {
                    int rented_cars = stoi(customer_data[3]);
                    if (rented_cars > 0)
                    { 
                        customer_data[4] = to_string(fine);
                        customer_data[3] = to_string(rented_cars - 1);
                        if (stoi(customer_data[6]) > 1)
                        {
                            int x = stoi(customer_data[6])-1;
                            customer_data[6] = to_string(x);

                        }
                        if (customer_data[5] == "bad")
                        {
                            customer_data[5] = "worst";
                        }
                        else if (customer_data[5] == "good")
                        {
                            customer_data[5] = "average";
                        }
                        else if (customer_data[5] == "average")
                        {
                            customer_data[5] = "bad";
                        }
                        customer_lines[customer_idx] = customer_data[0] + "," + customer_data[1] + "," + customer_data[2] + "," +
                                                       customer_data[3] + "," + customer_data[4] + "," + customer_data[5] + "," + customer_data[6];

                        // Write the updated customer records back to the file
                        ofstream write_file;
                        write_file.open("Customer.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &customer_line : customer_lines)
                        {
                            write_file << customer_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
        }
    }
    void Customer_Rent_request()
    {
        Customer_DBS cusdbs;
        string modelnumber;
        string date;
        car_DBS c00;
        string If_is_Rented;
        int rentcarLimit = cc.ReturnRentedCar(id);
        int RentedCarsNo = cc.NoOfRentedCars(id);
        if ((rentcarLimit == 1 && RentedCarsNo >= 1) || (rentcarLimit == 2 && RentedCarsNo >= 2) || (rentcarLimit == 3 && RentedCarsNo >= 3) || (rentcarLimit == 4 && RentedCarsNo >= 4))
        {
            cout << "You can't rent a car beacause it exceeds the rent limit" << endl;
        }
        else
        {
            cout << "Enter the model number of the car which is available(search using browse Available cars)" << endl;
            cin >> modelnumber;
            vector<string> Data = c00.extractCarData(modelnumber);
            If_is_Rented = Data[2];
            while (If_is_Rented == "1")
            {

                cout << "The car is already rented to someone.Please enter new car model number : ";
                cin >> modelnumber;
                vector<string> Data = c00.extractCarData(modelnumber);
                If_is_Rented = Data[2];
            }
            cout << "Enter the date (in dd-mm-yyyy format)till  you want to rent the car "
                 << " : ";
            cin >> date;
            cusdbs.UpdateRentedCars(id, +1);
            c00.updateRenter00(id, modelnumber, date);
            cout << "Congratulations! You have succesfully rented a car" << endl;
        }
    }
};
class Employee : public User
{
public:
    bool verify_Employee()
    {
        Employee_DBS ee1;
        vector<string> Store2 = ee1.search_id(id);
        if (Store2.size() == 0)
        {
            return false;
        }
        else if (id == Store2[0] && Password == Store2[2] && name == Store2[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void BrowseCurrentlyRentedCars()
    {
        car_DBS tempcar0;
        vector<string> Currently_RentedCars = tempcar0.Browse_currentlyRentedCars(id);
        for (int i = 0; i < Currently_RentedCars.size(); i++)
        {
            cout << Currently_RentedCars[i] << endl;
        }
    }

    void Employee_signup()
    {
        Employee_DBS ee2;
        string Employeename;
        string Password10;
        string id00;

        cout << "Register yourself:-" << endl;
        fstream fout;

        // opens an existing csv file or creates a new file.
        fout.open("Employee.csv", ios::app);

        cout << "Enter your id : ";
        cin >> id00;
        while (ee2.search_Employee_id(id00) == 1)
        {
            cout << "Enter any 4 digit id(including numbers and alphabets) : ";
            cin >> id00;
        }
        cout << "Enter your name(without spaces) : ";
        cin >> Employeename;

        cout << "Enter your password: ";
        cin >> Password10;
        while (ee2.search_Employee_Password(Password10) == 1)
        {
            cout << "Please enter a new Password,the previous one already exists : ";
            cin >> Password10;
        }
        // Insert the data to file
        fout << id00 << ","
             << Employeename << ","
             << Password10 << ","
             << "0"
             << ","
             << "0"
             << ","
             << "average"
             << ","
             << "3"
             << "\n";

        fout.close();
    }
    void Employee_Rent_request()
    {
        Employee_DBS empdbs;
        string modelnumber;
        car_DBS c00;
        string If_is_Rented;
        string date;
        int rentcarLimit = empdbs.ReturnCarLim_emp(id);
        int RentedCarsNo = empdbs.NoOfRentedCars_emp(id);
        if ((rentcarLimit == 1 && RentedCarsNo >= 1) || (rentcarLimit == 2 && RentedCarsNo >= 2) || (rentcarLimit == 3 && RentedCarsNo >= 3) || (rentcarLimit == 4 && RentedCarsNo >= 4))
        {
            cout << "You can't rent a car beacause it exceeds the rent limit" << endl;
        }
        else
        {
            cout << "Enter the model number of the car which is available(search using browse Available cars)" << endl;
            cin >> modelnumber;
            vector<string> Data = c00.extractCarData(modelnumber);
            If_is_Rented = Data[2];
            while (If_is_Rented == "1")
            {

                cout << "The car is already rented to someone.Please enter new car model number : ";
                cin >> modelnumber;
                vector<string> Data = c00.extractCarData(modelnumber);
                If_is_Rented = Data[2];
            }
            cout << "Enter the date (in dd-mm-yyyy format)till  you want to rent the car "
                 << " : ";
            cin >> date;
            empdbs.UpdateRentedCars_emp(id, +1);
            c00.updateRenter00(id, modelnumber, date);
            cout << "Congratulations! You have succesfully rented a car" << endl;
        }
    }
    void Return_Request()
    {
        // fine per day is 20rs

        car_DBS cx;
        Employee_DBS cy;
        int days;
        string model_number;
        string condition;
        cout << "Enter the model number of car you are returning : ";
        cin >> model_number;
        cout << "Enter the condition of the car(namely worst,bad,average,good) : ";
        cin >> condition;
        cout << "Enter the number of extra days after due date you are returning the car : ";
        cin >> days;
        x:
        vector<string> RentedCars = cx.Browse_currentlyRentedCars(id);
        int flag = 0;

        
        for (int i=0;i<RentedCars.size();i++)
        {
            if (RentedCars[i] == model_number)
            {
                flag = 1;
                break;
            }
            i++;
        }
        int fine = 20 * days;
        if (flag == 0)
        {
            cout << "The car Model number you entered doesn't match the car model number's you are corrently renting"<<endl;
            cout << "Please re-enter the car model number you want to return : ";
            cin >> model_number;
            goto x;

        }
        else
        {
            fstream read_file1;
            read_file1.open("Car.csv");

            vector<string> Car_lines;
            string line;
            int Car_line_num = 0;
            int Car_idx = 0;

            while (getline(read_file1, line))
            {
                Car_lines.push_back(line);

                stringstream inputString(line);
                string curr_Car_id;
                getline(inputString, curr_Car_id, ',');
                if (curr_Car_id == model_number)
                {
                    Car_idx = Car_line_num;
                }
                Car_line_num++;
            }
            read_file1.close();

            // Get the current Car data
            vector<string> Car_data = cx.extractCarData(model_number);

            if (!Car_data.empty())
            {

                Car_data[3] = "none";
                Car_data[1] = "average";
                Car_data[2] = "0";
                Car_data[5] = "none";
                Car_lines[Car_idx] = Car_data[0] + "," + Car_data[1] + "," + Car_data[2] + "," +
                                     Car_data[3] + "," + Car_data[4] + "," + Car_data[5];

                // Write the updated Car records back to the file
                ofstream write_file1;
                write_file1.open("Car.csv");
                if (write_file1.fail())
                {
                    cout << "Error opening file." << endl;
                    return;
                }

                for (const string &Car_line : Car_lines)
                {
                    write_file1 << Car_line << endl;
                }
                write_file1.close();
            }

            cout << "Your Current fine is : " << fine;
            if (fine == 0)
            {
                fstream read_file;
                read_file.open("Employee.csv");

                vector<string> Employee_lines;
                string line;
                int Employee_line_num = 0;
                int Employee_idx = 0;

                while (getline(read_file, line))
                {
                    Employee_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Employee_id;
                    getline(inputString, curr_Employee_id, ',');
                    if (curr_Employee_id == id)
                    {
                        Employee_idx = Employee_line_num;
                    }
                    Employee_line_num++;
                }
                read_file.close();

                // Get the current Employee data
                vector<string> Employee_data = cy.search_id(id);

                // Decrease the rented cars count
                if (!Employee_data.empty())
                {
                    int rented_cars = stoi(Employee_data[3]);
                    if (rented_cars > 0)
                    {
                        Employee_data[3] = to_string(rented_cars - 1);
                        Employee_data[4] = "0";
                        if (stoi(Employee_data[6]) < 4)
                        {
                            int x = stoi(Employee_data[6]) + 1;
                            Employee_data[6] = to_string(x);
                        }
                        if (Employee_data[5] == "worst")
                        {
                            Employee_data[5] = "bad";
                        }
                        else if (Employee_data[5] == "bad")
                        {
                            Employee_data[5] = "average";
                        }
                        else if (Employee_data[5] == "average")
                        {
                            Employee_data[5] = "good";
                        }
                        Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                                       Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                        // Write the updated Employee records back to the file
                        ofstream write_file;
                        write_file.open("Employee.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &Employee_line : Employee_lines)
                        {
                            write_file << Employee_line << endl;
                        }
                        write_file.close();
                    }
                }
            }

            else if (fine > 0)
            {
                fstream read_file;
                read_file.open("Employee.csv");

                vector<string> Employee_lines;
                string line;
                int Employee_line_num = 0;
                int Employee_idx = 0;

                while (getline(read_file, line))
                {
                    Employee_lines.push_back(line);

                    stringstream inputString(line);
                    string curr_Employee_id;
                    getline(inputString, curr_Employee_id, ',');
                    if (curr_Employee_id == id)
                    {
                        Employee_idx = Employee_line_num;
                    }
                    Employee_line_num++;
                }
                read_file.close();

                // Get the current Employee data
                vector<string> Employee_data = cy.search_id(id);

                // Decrease the rented cars count
                if (!Employee_data.empty())
                {
                    int rented_cars = stoi(Employee_data[3]);
                    if (rented_cars > 0)
                    { 
                        Employee_data[4] = to_string(fine);
                        Employee_data[3] = to_string(rented_cars - 1);
                        if (stoi(Employee_data[6]) > 1)
                        {
                            int x = stoi(Employee_data[6])-1;
                            Employee_data[6] = to_string(x);

                        }
                        if (Employee_data[5] == "bad")
                        {
                            Employee_data[5] = "worst";
                        }
                        else if (Employee_data[5] == "good")
                        {
                            Employee_data[5] = "average";
                        }
                        else if (Employee_data[5] == "average")
                        {
                            Employee_data[5] = "bad";
                        }
                        Employee_lines[Employee_idx] = Employee_data[0] + "," + Employee_data[1] + "," + Employee_data[2] + "," +
                                                       Employee_data[3] + "," + Employee_data[4] + "," + Employee_data[5] + "," + Employee_data[6];

                        // Write the updated Employee records back to the file
                        ofstream write_file;
                        write_file.open("Employee.csv");
                        if (write_file.fail())
                        {
                            cout << "Error opening file." << endl;
                            return;
                        }

                        for (const string &Employee_line : Employee_lines)
                        {
                            write_file << Employee_line << endl;
                        }
                        write_file.close();
                    }
                }
            }
        }
    }
};

int main()
{
    car_DBS car00;
    Manager Manager00;
    Customer Customer00;
    Employee Employee00;
    string modelnum;
    cout << "Main_Menu" << endl;

    cout << "Are you a : "
         << "Manager : 1" << endl;
    cout << "Are you an : "
         << "Employee : 2" << endl;
    cout << "Are you a : "
         << "Customer : 3" << endl;
    int num;
    cin >> num;
    switch (num)
    {
    case 1:

        cout << "Enter your name : ";
        Manager00.Input_name();
        cout << "Enter your id : ";
        Manager00.Input_id();
        cout << "Enter your password : ";
        Manager00.Input_Password();
        if (Manager00.Verify_Manager() == 1)
        {
            Manager00.modify_records();
        }
        else
        {
            cout << "Invalid credentials!"
                 << " Go to Main_Menu" << endl;
        }
        break;

    case 2:
        cout << "Are you a new employee(y/n)";
        char ch0;
        cin >> ch0;
        if (ch0 == 'y')
        {
            Employee00.Employee_signup();
            goto login_employee;
        }
        else if (ch0 == 'n')
        {
        login_employee:
            cout << "Please enter your credentials to login : " << endl;
            cout << "Enter your name : ";
            Employee00.Input_name();
            cout << "Enter your id : ";
            Employee00.Input_id();
            cout << "Enter your password : ";
            Employee00.Input_Password();
            if (Employee00.verify_Employee() == 1)
            {
                cout << endl;
                cout << "Please select : " << endl;
                cout << "Browse available cars"
                     << " : 1" << endl;
                cout << "Browse cars currently rented by you"
                     << " : 2" << endl;
                cout << "Show car due date"
                     << " : 3" << endl;
                cout << "Rent Request"
                     << " : 4" << endl;
                cout << "Return Request"
                     << " : 5" << endl;

                int Employee_choice;
                cin >> Employee_choice;
                switch (Employee_choice)
                {
                case 1:
                    cout << "NOTE:Available Cars are displayed using model number" << endl;
                    cout << "The price of each car is available at 15% discount to you" << endl;
                    car00.Browse_Available_Cars('E');
                    break;
                case 2:

                    cout << "NOTE:Cars currently rented by you are displayed using model number" << endl;
                    Employee00.BrowseCurrentlyRentedCars();
                    break;
                case 3:
                    cout << "Enter model number of car whose due date you want to check"
                         << " : ";
                    cin >> modelnum;
                    car00.show_DueDateofCar(modelnum);
                    break;
                case 4:
                    Employee00.Employee_Rent_request();

                    break;
                case 5:
                    Employee00.Return_Request();
                    break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Inavlid Credentials"
                     << " : Go to Main_Menu" << endl;
            }
            break;
        }
    case 3:
        cout << "Are you a new Customer (y/n)";
        char ch;
        cin >> ch;
        if (ch == 'y')
        {
            Customer00.Customer_signup();
            cout << "Please login" << endl;
            goto login_customer;
        }
        if (ch == 'n')
        {
        login_customer:
            cout << "Enter your name : ";
            Customer00.Input_name();
            cout << "Enter your id : ";
            Customer00.Input_id();
            cout << "Enter your password : ";
            Customer00.Input_Password();
            if (Customer00.verify_Customer() == 1)
            {
                cout << endl;
                cout << "Please select : " << endl;
                cout << "Browse available cars"
                     << " : 1" << endl;
                cout << "Browse cars currently rented by you"
                     << " : 2" << endl;
                cout << "Show car due date"
                     << " : 3" << endl;
                cout << "Rent Request"
                     << " : 4" << endl;
                cout << "Return Request"
                     << " : 5" << endl;
                int Customer_choice;
                cin >> Customer_choice;
                switch (Customer_choice)
                {
                case 1:
                    cout << "NOTE:Available Cars are displayed using model number" << endl;
                    car00.Browse_Available_Cars('C');
                    break;
                case 2:

                    cout << "NOTE:Cars currently rented by you are displayed using model number" << endl;
                    Customer00.BrowseCurrentlyRentedCars();
                    break;
                case 3:
                    cout << "Enter model number of car whose due date you want to check"
                         << " : ";
                    cin >> modelnum;
                    car00.show_DueDateofCar(modelnum);
                    break;
                case 4:
                    Customer00.Customer_Rent_request();

                    break;
                case 5:
                    Customer00.Return_Request();
                    break;
                default:
                    break;
                }
            }
            else
            {
                cout << "Inavlid Credentials"
                     << " : Go to signup/login" << endl;
            }
            break;
        }
    }

    return 0;
}

// Manager name = vishal
// Manager Password = 123456
// Manager id = mm001