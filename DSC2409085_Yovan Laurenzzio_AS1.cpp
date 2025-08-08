#include <iostream>
#include <string> // Allows us to us functions like .size() .length() etc.
#include <vector> // We chose to use vector to be able to use functions like push_back etc.

using namespace std;

// The Class representing the contact
class Contact {
private:
    string name;
    string phone;
    string email;

public:
    // Constructor
    Contact(string nameParameter, string phoneParameter, string emailParameter)
    {
        name = nameParameter;
        phone = phoneParameter;
        email = emailParameter;
    }


    // Getters
    string getName() const
    {
        return name;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return email;
    }

    // Function to display contact information
    void displayContact() const
    {
        cout << "Name: " << name << "\n";
        cout << "Phone: " << phone << "\n";
        cout << "Email: " << email << "\n";
        cout << "-----------------------\n";
    }
};

// Boolean Function to Validate the names
bool isValidName(const string &name)
{
    for (int i = 0; i < name.size(); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

// Boolean Function to Validate the phone numbers
bool isValidPhoneNumber(const string &phone)
{
    if (phone.length() != 10)
    {
        return false;
    }
    for (int i = 0; i < phone.size(); i++)
    {
        if (!isdigit(phone[i]))
        {
            return false;
        }
    }
    return true;
}

// Boolean Function to Validate the emails
bool isValidEmail(const string &email)
{
    bool hasAt = false, hasDot = false; // hasAt for (@) and hasDot for (.)

    for (char c : email) //range type loop
    {
        if (c == '@')
        {
            hasAt = true;
        }
        else if (c == '.')
        {
            hasDot = true;
        }
    }

    return hasAt && hasDot;
}


class ContactManager
{
private:
    vector<Contact> contacts; // Declaring the vector
    static const int MAX_CONTACTS = 50; // Set the max number of contacts to 50

    // Function to Check if a phone number already exists
    bool isPhoneNumberUnique(const string &phone)
    {
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].getPhone() == phone)
            {
                return false;
            }
        }
        return true;
    }


    // Function to Check if an email already exists
    bool isEmailUnique(const string &email)
    {
        for (size_t i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].getEmail() == email)
            {
                return false;
            }
        }
        return true;
    }


public:
    // Function to add new contact
    void addContact()
    {
        if (contacts.size() >= MAX_CONTACTS)
        {
            cout << "Contact list is full. Cannot add more than " << MAX_CONTACTS << " contacts.\n";
            return;
        }

        string name, phone, email;

        // Looping to Validate the name inputs
        do
        {
            cout << "Enter name: ";
            getline(cin, name);
            if (!isValidName(name))
            {
                cout << "Invalid name. Only alphabetic characters and spaces are allowed.\n";
            }
        } while (!isValidName(name));

        // Looping to Validate phone number inputs
        do
        {
            cout << "Enter phone number: ";
            getline(cin, phone);

            if (!isValidPhoneNumber(phone))
            {
                cout << "Invalid phone number. It should contain exactly 10 digits.\n";
            }
            else if (!isPhoneNumberUnique(phone))
            {
                cout << "Phone number already in use. Please enter a different number.\n";
            }
        } while (!isValidPhoneNumber(phone) || !isPhoneNumberUnique(phone));

        // Looping to Validate email inputs
        do
        {
            cout << "Enter email: ";
            getline(cin, email);

            if (!isValidEmail(email))
            {
                cout << "Invalid email. It should contain '@' and a domain.\n";
            }
            else if (!isEmailUnique(email))
            {
                cout << "Email already in use. Please enter a different email.\n";
            }
        } while (!isValidEmail(email) || !isEmailUnique(email));

        // Using the push_back funtion to Create and add contacts
        contacts.push_back(Contact(name, phone, email));
        cout << "Contact added successfully!\n";
    }

    // Function to delete a contact
    void deleteContact()
    {
        string name;
        cout << "Enter the name of the contact to delete: ";
        getline(cin, name);
        bool found = false;

        for (int i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].getName() == name)
            {
                contacts.erase(contacts.begin() + i); // The .erase() function is used to easily delete a contact.
                cout << "Contact deleted successfully!\n";
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Contact not found.\n";
        }
    }

    // Function to search for a contact
    void searchContact()
    {
        string name;
        cout << "Enter the name of the contact to search: ";
        getline(cin, name);
        bool found = false;

        for (int i = 0; i < contacts.size(); i++)
        {
            if (contacts[i].getName() == name)
            {
                cout << "Contact found:\n";
                contacts[i].displayContact();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Contact not found.\n";
        }
    }

    // Function to display all contacts
    void displayAllContacts()
    {
        if (contacts.empty())
        {
            cout << "No contacts available.\n";
            return;
        }
        cout << "All Contacts:\n";
        for (int i = 0; i < contacts.size(); i++)
        {
            contacts[i].displayContact();
        }
    }
};

// Function to ensure a valid choice in the menu
int getValidChoice()
{
    int choice;
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) // ,.fail() signals an invalid input
        {
            cin.clear();    // .clear() is used to clear the flag error
            cin.ignore(1000, '\n'); // .ignore() is used to discard the invalid input
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
        }
        else if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
        else
        {
            cin.ignore(); // .ignore() is used again to clear input buffer for the next inputs
            return choice;
        }
    }
}

// The Main function
int main()
{
    ContactManager manager; //Declaring manager representing the ContactManager class
    int choice;

    //Looping for menu and switch
    do
    {
        cout << "Contact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";

        choice = getValidChoice();

        switch (choice)
        {
            case 1:
                manager.addContact(); //Calls the function for adding contacts
                break;
            case 2:
                manager.deleteContact(); //Calls the function for deleting contacts
                break;
            case 3:
                manager.searchContact(); //Calls the function for searching contacts
                break;
            case 4:
                manager.displayAllContacts(); //Calls the function for displaying contacts
                break;
            case 5:
                cout << "Exiting program... Thankyou!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
