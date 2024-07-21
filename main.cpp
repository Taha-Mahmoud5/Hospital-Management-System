// C++ program to implement the Hospital
// Management System

#include <iostream> // Library for input and output operations
#include <vector>   //  (dynamic array , vector)
#include <string>   // (handling text strings)
#include <fstream>  //  ( ifstream and ofstream)
#include <algorithm>//  ( find if and sort)
#include <windows.h>//  (system("CLS"))
#include <cctype>   //  (isalpha and isdigit)
#include <cstdlib>  //  (exit(0))


#define endl '\n'  // Uses '\n' instead of the traditional endl

using namespace std;

class Financial {

protected: // To participate in the second class
    double consulting_fee;
    double amount_paid;
    double discount_percentage;
    double discount_amount;

public:
    Financial() : consulting_fee(0.0), amount_paid(0.0), discount_percentage(0.0), discount_amount(0.0) {} // Add initial values

    void set_consulting_fee(double fee)
    {
        consulting_fee = fee;
        discount_amount = (consulting_fee * discount_percentage) / 100.0 ;
    }

    void set_amount_paid(double amount) // Set amount paid
    {
        amount_paid = amount;
    }

    void set_discount_percentage(double x)
    {
        discount_percentage = x;
        discount_amount = (consulting_fee * discount_percentage) / 100.0;
    }

    double get_remaining_amount() const
    {
        return (consulting_fee - discount_amount) - amount_paid;
    }

    double get_discount_amount() const
    {
        return discount_amount;
    }

    double get_consulting_fee() const
    {
        return consulting_fee;
    }

    double get_amount_paid() const
    {
        return amount_paid;
    }
};

  // The Medical class inherits the Finance class (public inheritance)
class Patient : public Financial {

private:
    struct Patient_n
    {
        string name;
        string national_id;
        int room_num;
        int age;
        char pressure;
        char diabetes;
        string problem;
        bool is_fully_paid;

    };

    vector<Patient_n> patients;

public:
    Patient()  // Constructor to take from files
    {
        ifstream data("Patient.txt"); // Open the file "Patient.txt" for reading
        Patient_n one; // Create a Patient_n object to hold patient data

        // Read patient data from the file
        while (data >> one.name >> one.national_id >> one.room_num >> one.age >> one.diabetes >> one.pressure )
        {
            getline(data, one.problem); // Read the problem description
            patients.push_back(one); // Add the patient data to the vector
        }

        data.close(); // Close the file
    }

    ~Patient() // Destructor to add to files
    {
        ofstream data("Patient.txt"); // Open the file "Patient.txt" for writing
        for (const auto& one : patients) // Loop to add patient to file
        {
            data << one.name << " " << one.national_id << " " << one.room_num << " "
                 << one.age << " " << one.diabetes << " " << one.pressure << " "
                 << one.problem << endl; // Write patient data to the file
        }

        data.close();
}

    bool patient_exists(const string& national_id) const // Check if a patient with the given national ID exists in the list
    {
        for (const auto& patient : patients) // Loop to check
        {
            if (national_id == patient.national_id) // Check if the national ID matches
            {
                return true;
            }
        }
        return false; // Patient does not exist
    }

    void handle_financials(Patient_n& new_patient) // Handle the financial aspects for a new patient
    {
        char apply_discount;
        cout << "Apply discount? (y/n): "; // We will make a discount
        cin >> apply_discount;

        if (apply_discount == 'y' || apply_discount == 'Y') // If we do discount
        {
            cout << "Enter discount percentage: ";
            cin >> discount_percentage;
            while (discount_percentage < 0 || discount_percentage > 100) // Validate discount percentage
            {
                cout << "Invalid percentage. Enter discount percentage between 0 and 100: ";
                cin >> discount_percentage;
            }
            set_discount_percentage(discount_percentage); // Set the discount percentage and update discount amount
        }
        else
        {
            set_discount_percentage(0.0); // we don't do discount
        }

        cout << "Enter consulting fee: ";
        cin >> consulting_fee;
        set_consulting_fee(consulting_fee); //Take the consulting fee

        // Calculate the amount to be paid
        double amount_due = get_remaining_amount();
        cout << "Amount due: " << amount_due << endl;

        if (amount_due > 0) // If there is an amount due
        {
            cout << "Enter amount paid: ";
            cin >> amount_paid;
            while (amount_paid < 0 || amount_paid > amount_due) // Validate amount paid
            {
                cout << "Invalid amount. Enter amount paid again (not exceeding the amount due): ";
                cin >> amount_paid;
            }
            set_amount_paid(amount_paid); // Take the amount paid
        }
        else
        {
            set_amount_paid(0); // No payment needed if the amount due is 0
        }

        new_patient.is_fully_paid = (get_remaining_amount() <= 0);
    }

    void add_patient() // Add a new patient to the system
    {
        Patient_n new_patient;

        // Get name
        cout << "Enter patient's name: ";
        cin.ignore(); // Clear
        getline(cin, new_patient.name); // Read the full name including spaces
        // Validate the name
        while (new_patient.name.empty() || new_patient.name.size() > 15)
        {
            cout << "Invalid name. Enter patient's name: ";
            getline(cin, new_patient.name);
        }

        while (new_patient.name.size() < 15)
        {
            new_patient.name += " ";
        }

        // Check if the National ID already exists
        bool id_exists;
        do {
            cout << "Enter National ID (14 digits): ";
            cin >> new_patient.national_id;

            id_exists = patient_exists(new_patient.national_id); // Check National ID
            if (id_exists)
            {
                int choice;
                cout << "National ID already exists." << endl;
                cout << "1. Enter a different National ID" << endl;
                cout << "2. Contact the police" << endl;
                cout << "Enter your choice (1-2): ";
                cin >> choice;

                if (choice == 2)
                {
                    cout << "Please contact the police for further action." << endl;
                    cout << "Call 123." << endl; // police contact information
                }
            }
        } while (id_exists); // Repeat until a unique National ID is entered

        // Get the patient's age
        cout << "Enter patient's age: ";
        cin >> new_patient.age;
        // Validate the age
        while (new_patient.age <= 0)
        {
            cout << "Invalid age. Enter patient's age (positive integer): ";
            cin >> new_patient.age;
        }

        // Get the diabetes status
        cout << "Does the patient have diabetes (y/n): ";
        cin >> new_patient.diabetes;
        while (new_patient.diabetes != 'y' && new_patient.diabetes != 'n')
        {
            cout << "Invalid input. Enter 'y' or 'n': ";
            cin >> new_patient.diabetes;
        }

        // Get the blood pressure status
        cout << "Does the patient have blood pressure (y/n): ";
        cin >> new_patient.pressure;
        // Validate to  blood pressure status
        while (new_patient.pressure != 'y' && new_patient.pressure != 'n')
        {
            cout << "Invalid input. Enter 'y' or 'n': ";
            cin >> new_patient.pressure;
        }

        // Get the problem description
        cout << "Enter patient's problem description: ";
        cin.ignore(); // Clear
        getline(cin, new_patient.problem);

        // Handle financial information for the new patient
        handle_financials(new_patient);

        new_patient.room_num = patients.size() + 1;
        // Add patient to the vector
        patients.push_back(new_patient);

        // Display the remaining amount to be paid
        cout << "Remaining amount to be paid: " << get_remaining_amount() << endl;
    }

    void display_patient(const string& name) const // Display details of a patient
    {
        // Search about patient
        for (int i = 0; i < patients.size(); i++)
        {
            if (name == patients[i].name)
            {
                // Patient found display their information
                bool more_info = true;
                while (more_info)
                    {
                    int choice;
                    // Ask user what information they would like to see
                    do {
                        cout << "\nWhat information would you like to see for this patient?" << endl;
                        cout << "1. General Information" << endl;
                        cout << "2. Health Information" << endl;
                        cout << "3. Financial Information" << endl;
                        cout << "Enter your choice (1-3): ";
                        cin >> choice;
                    } while (choice < 1 || choice > 3); // Validate choice

                    switch (choice)
                    {
                        case 1:
                            // Display general information
                            cout << "\nGeneral Information:" << endl;
                            cout << "Room Number: " << patients[i].room_num << endl;
                            cout << "Name: " << patients[i].name << " | Age: " << patients[i].age << endl;
                            break;

                        case 2:
                            // Display health information
                            cout << "\nHealth Information:" << endl;
                            cout << "Diabetes condition: " << (patients[i].diabetes == 'y' ? "Yes" : "No") << " | High blood pressure: " << (patients[i].pressure == 'y' ? "Yes" : "No") << endl;
                            cout << "Problem description: " << patients[i].problem << endl;
                            break;

                        case 3:
                            // Display financial information
                            cout << "\nFinancial Information:" << endl;
                            cout << "Consulting fee: " << get_consulting_fee() << endl;
                            cout << "Discount percentage: " << discount_percentage << "%" << endl;
                            cout << "Discount amount: " << get_discount_amount() << endl;
                            cout << "Amount paid: " << get_amount_paid() << endl;
                            cout << "Fully paid: " << (patients[i].is_fully_paid ? "Yes" : "No") << endl;
                            cout << "Remaining amount: " << get_remaining_amount() << endl;
                            break;
                    }

                    cout << "---------------------------" << endl;

                    // Ask user if they want to see more information about this patient
                    char response;
                    cout << "Would you like to see more information about this patient? (y/n): ";
                    cin >> response;
                    more_info = (response == 'y' || response == 'Y'); // Continue if user inputs 'y' or 'Y'
                }
                return; // Exit the function
            }
        }

        // If patient not found
        cout << "\nPatient with name " << name << " not found." << endl;
    }

    void display_all_patients() const // Function to display the list of all patients
    {
        if (patients.empty())
        {
            // No patients in the system
            cout << "No patients found.\n" << endl;
            return;
        }
        // Display all patients in the system
        cout << "\nAll patients in our system: " << endl;
        for (int i = 0; i < patients.size(); i++)
        {
            cout << "  " << i + 1 << "--> Name: " << patients[i].name << endl; // List patient names
        }
    }


    void remove_patient(const string& name) // Delete patient
    {
        // Search for the patient in the vector
        for (auto it = patients.begin(); it != patients.end(); it++)
        {
            if (it->name == name)
            {

                double remaining_amount = get_remaining_amount();
                if (remaining_amount > 0)
                {

                    cout << "Patient " << it->name << " has an outstanding balance of " << remaining_amount << ". Cannot remove patient." << endl;
                    return;
                }


                cout << "Removing patient: " << it->name << endl;
                patients.erase(it); // Remove the patient from the list
                cout << "Patient removed successfully." << endl;
                return; // Exit the function after removing the patient
            }
        }

        // If patient was not found
        cout << "Patient not found." << endl;
    }


};

int main() {
    Patient patient_obj;

    bool continue_program = true;
    while (continue_program) {
            // The primary interface .
        cout << "\n\n->  Welcome to the Hospital Management System" << endl;
        cout << "      Please choose an option:" << endl;
        cout << "        1. Add patient" << endl;
        cout << "        2. Display patient" << endl;
        cout << "        3. Display all patients" << endl;
        cout << "        4. Remove patient" << endl;
        cout << "        5. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                patient_obj.add_patient();
                break;
            case 2:
            {
                cout << "Enter patient's name: ";
                string name;
                cin.ignore();
                getline(cin, name);
                patient_obj.display_patient(name);
                break;
            }
            case 3:
                patient_obj.display_all_patients();
                break;
            case 4:
            {
                cout << "Enter patient's name: ";
                string name;
                cin.ignore();
                getline(cin, name);
                patient_obj.remove_patient(name);
                break;
            }
            case 5:
                continue_program = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 5)
        {

            char cont_choice;
            cout << "Do you want to continue? (y/n): ";
            cin >> cont_choice;
            system("CLS");
            continue_program = (cont_choice == 'y' || cont_choice == 'Y');
        }
    }

    return 0;
}
