#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

// ANSI Terminal Colors for a premium console appearance
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN    = "\033[36m";
const string WHITE   = "\033[37m";

// ==========================================
// 1. PATIENTS LINKED LIST (PatientsLL)
// ==========================================
struct PatientNode {
    int patient_id;
    string name;
    string dob;
    string gender;
    PatientNode* next;

    PatientNode(int id, string n, string d, string g)
        : patient_id(id), name(n), dob(d), gender(g), next(nullptr) {}
};

class PatientsLL {
private:
    PatientNode* head;

public:
    PatientsLL() : head(nullptr) {}

    ~PatientsLL() {
        PatientNode* current = head;
        while (current != nullptr) {
            PatientNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Check if a patient exists by ID
    bool exists(int id) const {
        PatientNode* temp = head;
        while (temp != nullptr) {
            if (temp->patient_id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Register a new patient
    bool addPatient(int id, const string& name, const string& dob, const string& gender) {
        if (exists(id)) {
            cout << RED << BOLD << "\n  Error: Patient ID " << id << " already exists!\n" << RESET;
            return false;
        }

        PatientNode* newNode = new PatientNode(id, name, dob, gender);
        
        // Insert at the end to preserve registration order
        if (head == nullptr) {
            head = newNode;
        } else {
            PatientNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << GREEN << BOLD << "\n  Success: Patient successfully registered.\n" << RESET;
        return true;
    }

    // Retrieve name of a patient for display helper purposes
    string getPatientName(int id) const {
        PatientNode* temp = head;
        while (temp != nullptr) {
            if (temp->patient_id == id) {
                return temp->name;
            }
            temp = temp->next;
        }
        return "Unknown Patient";
    }

    // Display all patients
    void display() const {
        if (head == nullptr) {
            cout << YELLOW << "\n  No patient records found in PatientsLL.\n" << RESET;
            return;
        }

        cout << CYAN << BOLD << "\n" << string(70, '=') << "\n";
        cout << "                                          PATIENTS\n";
        cout << string(70, '=') << "\n" << RESET;
        cout << left << setw(12) << "Patient ID" 
             << setw(25) << "Full Name" 
             << setw(18) << "Date of Birth" 
             << setw(15) << "Gender" << "\n";
        cout << string(70, '-') << "\n";

        PatientNode* temp = head;
        while (temp != nullptr) {
            cout << left << setw(12) << temp->patient_id
                 << setw(25) << temp->name
                 << setw(18) << temp->dob
                 << setw(15) << temp->gender << "\n";
            temp = temp->next;
        }
        cout << CYAN << string(70, '=') << "\n" << RESET;
    }
};

// ==========================================
// 2. DOCTORS LINKED LIST (DoctorsLL)
// ==========================================
struct DoctorNode {
    int doctor_id;
    string name;
    string specialization;
    DoctorNode* next;

    DoctorNode(int id, string n, string spec)
        : doctor_id(id), name(n), specialization(spec), next(nullptr) {}
};

class DoctorsLL {
private:
    DoctorNode* head;

public:
    DoctorsLL() : head(nullptr) {}

    ~DoctorsLL() {
        DoctorNode* current = head;
        while (current != nullptr) {
            DoctorNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Check if a doctor exists by ID
    bool exists(int id) const {
        DoctorNode* temp = head;
        while (temp != nullptr) {
            if (temp->doctor_id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Register a new doctor
    bool addDoctor(int id, const string& name, const string& specialization) {
        if (exists(id)) {
            cout << RED << BOLD << "\n  Error: Doctor ID " << id << " already exists!\n" << RESET;
            return false;
        }

        DoctorNode* newNode = new DoctorNode(id, name, specialization);

        // Insert at the end to preserve registration order
        if (head == nullptr) {
            head = newNode;
        } else {
            DoctorNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << GREEN << BOLD << "\n  Success: Doctor successfully registered.\n" << RESET;
        return true;
    }

    // Retrieve name of a doctor for display helper purposes
    string getDoctorName(int id) const {
        DoctorNode* temp = head;
        while (temp != nullptr) {
            if (temp->doctor_id == id) {
                return temp->name;
            }
            temp = temp->next;
        }
        return "Unknown Doctor";
    }

    // Display all doctors
    void display() const {
        if (head == nullptr) {
            cout << YELLOW << "\n  No doctor records found in DoctorsLL.\n" << RESET;
            return;
        }

        cout << CYAN << BOLD << "\n" << string(70, '=') << "\n";
        cout << "                                          DOCTORS\n";
        cout << string(70, '=') << "\n" << RESET;
        cout << left << setw(12) << "Doctor ID" 
             << setw(28) << "Full Name" 
             << setw(30) << "Specialization" << "\n";
        cout << string(70, '-') << "\n";

        DoctorNode* temp = head;
        while (temp != nullptr) {
            cout << left << setw(12) << temp->doctor_id
                 << setw(28) << temp->name
                 << setw(30) << temp->specialization << "\n";
            temp = temp->next;
        }
        cout << CYAN << string(70, '=') << "\n" << RESET;
    }
};

// ==========================================
// 3. APPOINTMENTS LINKED LIST (AppointmentsLL)
// ==========================================
struct AppointmentNode {
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    AppointmentNode* next;

    AppointmentNode(int app_id, int pat_id, int doc_id, string date)
        : appointment_id(app_id), patient_id(pat_id), doctor_id(doc_id), appointment_date(date), next(nullptr) {}
};

class AppointmentsLL {
private:
    AppointmentNode* head;

public:
    AppointmentsLL() : head(nullptr) {}

    ~AppointmentsLL() {
        AppointmentNode* current = head;
        while (current != nullptr) {
            AppointmentNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    // Check if an appointment exists by ID
    bool exists(int id) const {
        AppointmentNode* temp = head;
        while (temp != nullptr) {
            if (temp->appointment_id == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Register a new appointment
    bool addAppointment(int app_id, int pat_id, int doc_id, const string& date,
                        const PatientsLL& patients, const DoctorsLL& doctors) {
        
        // 1. Verify Appointment ID uniqueness
        if (exists(app_id)) {
            cout << RED << BOLD << "\n  Error: Appointment ID " << app_id << " already exists!\n" << RESET;
            return false;
        }

        // 2. Verify Patient exists
        bool patientExists = patients.exists(pat_id);
        
        // 3. Verify Doctor exists
        bool doctorExists = doctors.exists(doc_id);

        if (!patientExists || !doctorExists) {
            cout << RED << BOLD << "\n  Error: ";
            if (!patientExists && !doctorExists) {
                cout << "Both Patient ID " << pat_id << " and Doctor ID " << doc_id << " do not exist!\n";
            } else if (!patientExists) {
                cout << "Patient ID " << pat_id << " does not exist!\n";
            } else {
                cout << "Doctor ID " << doc_id << " does not exist!\n";
            }
            cout << RESET;
            return false;
        }

        AppointmentNode* newNode = new AppointmentNode(app_id, pat_id, doc_id, date);

        // Insert at the end to preserve registration order
        if (head == nullptr) {
            head = newNode;
        } else {
            AppointmentNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << GREEN << BOLD << "\n  Success: Appointment successfully registered.\n" << RESET;
        return true;
    }

    // Display all appointments
    void display(const PatientsLL& patients, const DoctorsLL& doctors) const {
        if (head == nullptr) {
            cout << YELLOW << "\n  No appointment records found in AppointmentsLL.\n" << RESET;
            return;
        }

        cout << CYAN << BOLD << "\n" << string(90, '=') << "\n";
        cout << "                                         APPOINTMENTS\n";
        cout << string(90, '=') << "\n" << RESET;
        cout << left << setw(16) << "Appointment ID" 
             << setw(24) << "Patient (ID)" 
             << setw(28) << "Doctor (ID)" 
             << setw(22) << "Appointment Date" << "\n";
        cout << string(90, '-') << "\n";

        AppointmentNode* temp = head;
        while (temp != nullptr) {
            string patName = patients.getPatientName(temp->patient_id);
            string docName = doctors.getDoctorName(temp->doctor_id);

            string patientStr = patName + " (" + to_string(temp->patient_id) + ")";
            string doctorStr = docName + " (" + to_string(temp->doctor_id) + ")";

            cout << left << setw(16) << temp->appointment_id
                 << setw(24) << patientStr
                 << setw(28) << doctorStr
                 << setw(22) << temp->appointment_date << "\n";
            temp = temp->next;
        }
        cout << CYAN << string(90, '=') << "\n" << RESET;
    }
};

// ==========================================
// HELPER FUNCTIONS FOR ROBUST USER INPUT
// ==========================================

// Safely reads an integer from standard input, loops until valid
int readInteger(const string& prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        if (!getline(cin, input)) {
            // End of input stream reached (e.g. EOF)
            return 7; // Treat EOF as exit choice (7)
        }
        
        // Remove trailing/leading whitespaces if any
        size_t first = input.find_first_not_of(" \t");
        if (first == string::npos) {
            cout << RED << "  Error: Input cannot be empty. Please enter a valid number.\n" << RESET;
            continue;
        }
        size_t last = input.find_last_not_of(" \t");
        string trimmed = input.substr(first, (last - first + 1));

        try {
            size_t processed;
            value = stoi(trimmed, &processed);
            if (processed == trimmed.length()) {
                return value;
            }
        } catch (...) {}
        cout << RED << "  Error: Invalid integer. Please try again.\n" << RESET;
    }
}

// Safely reads a non-empty string from standard input
string readString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        if (!getline(cin, input)) {
            return "EOF_REACHED";
        }
        // Basic check for empty inputs or inputs with only whitespaces
        size_t first = input.find_first_not_of(" \t");
        if (first != string::npos) {
            return input;
        }
        cout << RED << "  Error: Field cannot be empty. Please enter a valid value.\n" << RESET;
    }
}

// Validates date format DD/MM/YYYY and checks standard calendar constraints
bool isValidDate(const string& dateStr) {
    // Trim whitespace
    size_t first = dateStr.find_first_not_of(" \t");
    if (first == string::npos) return false;
    size_t last = dateStr.find_last_not_of(" \t");
    string trimmed = dateStr.substr(first, (last - first + 1));

    stringstream ss(trimmed);
    string dayPart, monthPart, yearPart;
    if (!getline(ss, dayPart, '/') || !getline(ss, monthPart, '/') || !getline(ss, yearPart, '/')) {
        return false;
    }
    // Ensure there's no extra content after the year
    string extra;
    if (getline(ss, extra, '/')) {
        return false;
    }

    // Lambda helper to check if string contains only digits
    auto isDigits = [](const string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!isdigit(c)) return false;
        }
        return true;
    };

    if (!isDigits(dayPart) || !isDigits(monthPart) || !isDigits(yearPart)) {
        return false;
    }

    if (dayPart.length() < 1 || dayPart.length() > 2) return false;
    if (monthPart.length() < 1 || monthPart.length() > 2) return false;
    if (yearPart.length() != 4) return false;

    int day = stoi(dayPart);
    int month = stoi(monthPart);
    int year = stoi(yearPart);

    if (month < 1 || month > 12) return false;
    
    // Check days in month
    int maxDays = 31;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        maxDays = isLeap ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    }
    
    if (day < 1 || day > maxDays) return false;
    if (year < 1800 || year > 9999) return false;
    
    return true;
}

// Sanitizes and validates gender inputs to Male or Female
string sanitizeAndValidateGender(const string& genderStr) {
    size_t first = genderStr.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = genderStr.find_last_not_of(" \t");
    string trimmed = genderStr.substr(first, (last - first + 1));

    string lower = "";
    for (char c : trimmed) {
        lower += tolower(c);
    }

    if (lower == "male" || lower == "m") {
        return "Male";
    } else if (lower == "female" || lower == "f") {
        return "Female";
    }
    return "";
}

// Validates names (must contain letters, no digits allowed)
bool isValidName(const string& nameStr) {
    bool hasAlpha = false;
    for (char c : nameStr) {
        if (isdigit(c)) {
            return false;
        }
        if (isalpha(c)) {
            hasAlpha = true;
        }
    }
    return hasAlpha;
}

// Prompts and reads a valid name
string readName(const string& prompt) {
    while (true) {
        string name = readString(prompt);
        if (cin.eof() || name == "EOF_REACHED") {
            return "EOF_REACHED";
        }
        if (isValidName(name)) {
            return name;
        }
        cout << RED << "  Error: Invalid name. Numbers/digits are not allowed and it must contain letters.\n" << RESET;
    }
}

// Prompts and reads a valid date (DD/MM/YYYY format)
string readDate(const string& prompt) {
    while (true) {
        string date = readString(prompt);
        if (cin.eof() || date == "EOF_REACHED") {
            return "EOF_REACHED";
        }
        if (isValidDate(date)) {
            return date;
        }
        cout << RED << "  Error: Invalid date format or date value. Please enter in DD/MM/YYYY format.\n" << RESET;
    }
}

// Prompts and reads a valid gender
string readGender(const string& prompt) {
    while (true) {
        string gender = readString(prompt);
        if (cin.eof() || gender == "EOF_REACHED") {
            return "EOF_REACHED";
        }
        string validated = sanitizeAndValidateGender(gender);
        if (!validated.empty()) {
            return validated;
        }
        cout << RED << "  Error: Invalid gender. Please enter 'Male' or 'Female' (or M/F).\n" << RESET;
    }
}

// Main interactive execution loop
int main() {
    // Instantiate the 3 linked lists
    PatientsLL patientList;
    DoctorsLL doctorList;
    AppointmentsLL appointmentList;

    // Welcome Header
    cout << CYAN << BOLD;
    cout << "====================================================================\n";
    cout << "        RUHENGERI REFERRAL HOSPITAL - APPOINTMENT SYSTEM            \n";
    cout << "====================================================================\n" << RESET;

    while (true) {
        cout << "\n" << BOLD << WHITE << "--- SYSTEM MENU ---" << RESET << "\n";
        cout << "1. Register Patient\n";
        cout << "2. Register Doctor\n";
        cout << "3. Register Appointment\n";
        cout << "4. Display Patients\n";
        cout << "5. Display Doctors\n";
        cout << "6. Display Appointments\n";
        cout << "7. Exit\n";
        cout << "-------------------\n";

        int choice = readInteger(YELLOW + "Select an option (1-7): " + RESET);
        if (cin.eof()) {
            cout << GREEN << BOLD << "\nInput stream closed. Goodbye!\n" << RESET;
            break;
        }

        switch (choice) {
            case 1: {
                cout << CYAN << BOLD << "\n" << string(70, '=') << "\n";
                cout << "                       PATIENT REGISTRY\n";
                cout << string(70, '=') << "\n" << RESET;
                int id = readInteger("Enter Patient ID (Integer): ");
                if (cin.eof()) break;
                string name = readName("Enter Patient Full Name: ");
                if (cin.eof() || name == "EOF_REACHED") break;
                string dob = readDate("Enter Date of Birth (DD/MM/YYYY): ");
                if (cin.eof() || dob == "EOF_REACHED") break;
                string gender = readGender("Enter Gender (Male/Female): ");
                if (cin.eof() || gender == "EOF_REACHED") break;
                patientList.addPatient(id, name, dob, gender);
                break;
            }
            case 2: {
                cout << CYAN << BOLD << "\n" << string(70, '=') << "\n";
                cout << "                       DOCTOR REGISTRY\n";
                cout << string(70, '=') << "\n" << RESET;
                int id = readInteger("Enter Doctor ID (Integer): ");
                if (cin.eof()) break;
                string name = readName("Enter Doctor Full Name: ");
                if (cin.eof() || name == "EOF_REACHED") break;
                string spec = readString("Enter Specialization: ");
                if (cin.eof()) break;
                doctorList.addDoctor(id, name, spec);
                break;
            }
            case 3: {
                cout << CYAN << BOLD << "\n" << string(70, '=') << "\n";
                cout << "                       APPOINTMENT REGISTRY\n";
                cout << string(70, '=') << "\n" << RESET;
                int app_id = readInteger("Enter Appointment ID (Integer): ");
                if (cin.eof()) break;
                int pat_id = readInteger("Enter Patient ID (Integer): ");
                if (cin.eof()) break;
                int doc_id = readInteger("Enter Doctor ID (Integer): ");
                if (cin.eof()) break;
                string date = readDate("Enter Appointment Date (DD/MM/YYYY): ");
                if (cin.eof() || date == "EOF_REACHED") break;
                appointmentList.addAppointment(app_id, pat_id, doc_id, date, patientList, doctorList);
                break;
            }
            case 4:
                patientList.display();
                break;
            case 5:
                doctorList.display();
                break;
            case 6:
                appointmentList.display(patientList, doctorList);
                break;
            case 7:
                cout << GREEN << BOLD << "\nThank you for using Ruhengeri Referral Hospital System. Goodbye!\n" << RESET;
                return 0;
            default:
                cout << RED << "Invalid choice! Please select an option between 1 and 7.\n" << RESET;
                break;
        }
    }

    return 0;
}
