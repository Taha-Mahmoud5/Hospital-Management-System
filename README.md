# Hospital Management System

## Overview of the Code

This C++ program implements a Hospital Management System that manages patient information, including personal details, health conditions, and financial records. The system reads and writes patient data to a text file (`Patient.txt`), which is updated when the program starts and exits.

## Key Points of the Code

### Libraries Used
- **vector**: For using dynamic arrays (vectors).
- **string**: For handling text strings.
- **fstream**: (ifstream and ofstream).
- **algorithm**:  `find_if` and `sort`.
- **windows.h**: For system commands like `CLS`.
- **cctype**: For character handling functions like `isalpha` and `isdigit`.
- **cstdlib**: For the `exit(0)` 

### Macro Definition
- `#define endl '\n'`: Uses `'\n'` instead of the traditional `endl` to avoid flushing the output buffer frequently.

### Classes

#### 1. `Financial` Class
Manages the financial aspects of patient care.

**Attributes:**
- `consulting_fee`: The consultation fee.
- `amount_paid`: The amount paid by the patient.
- `discount_percentage`: The discount percentage applied to the consultation fee.
- `discount_amount`: The discount amount based on the discount percentage.

**Methods:**
- **Constructors and Setters**: Initialize and modify attributes.
- `get_remaining_amount()`: Calculates and returns the remaining amount due after discount and payment.

#### 2. `Patient` Class (Inherits from `Financial`)
Handles patient details and management.

**Attributes:**
- `Patient_n`: A struct that stores individual patient details, including:
  - `name`: Patient's name.
  - `national_id`: Patient's national ID.
  - `room_num`: Patient's room number.
  - `age`: Patient's age.
  - `pressure`: Blood pressure status.
  - `diabetes`: Diabetes status.
  - `problem`: Description of the patient's problem.
  - `is_fully_paid`: Indicates if the patient has paid the fees in full.
- `patients`: A vector storing all patient records.

**Methods:**
- **Constructor**: Reads patient data from `Patient.txt` and initializes the patients vector.
- **Destructor**: Writes patient data back to `Patient.txt` when the program ends.
- `patient_exists()`: Checks if a patient with a given national ID exists.
- `handle_financials()`: Manages financial details for a new patient, including applying discounts and calculating the amount due.
- `add_patient()`: Adds a new patient, ensuring valid input and checking for duplicate national IDs.
- `display_patient()`: Displays details of a specific patient.
- `display_all_patients()`: Displays a list of all patients.
- `remove_patient()`: Removes a patient after verifying any outstanding balances.

### Main Function

Provides a user interface to interact with the Hospital Management System. The menu includes options to:
- Add a new patient.
- Display details of a specific patient.
- Display a list of all patients.
- Remove a patient.
- Exit the program.

The menu continues to display until the user chooses to exit.

### Important Points in the Code

- **File Reading and Writing**:
  - Patient data is read from `Patient.txt` at the start.
  - Patient data is written back to `Patient.txt` on exit.

- **Patient Management**:
  - Adds new patients with validated inputs such as name, national ID, and age.
  - Checks for duplicate national IDs to prevent redundancy.

- **Financial Handling**:
  - Applies discounts to consultation fees.
  - Calculates and verifies amounts due and paid.
  - Ensures all payments are settled before removing a patient from the system.

- **Information Display**:
  - Provides detailed information on specific patients, including general, health, and financial details.
  - Lists all patients in the system.

- **User Interface**:
  - Offers a simple menu for user interaction, including adding, displaying, and removing patients.
