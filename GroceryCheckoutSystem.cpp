#include <bits/stdc++.h>

using namespace std;
const int MAX_USER = 255;
int userCount = 0;

// Define a struct to represent a user with username, password, and role
struct User 
{
    string username; // Store the username of the user
    string password; // Store the password of the user
    string role; // 1 for normal user, 2 for admin, 3 for super admin to indicate the role of the user

    bool partialUsernameMatch(const string& partial) const 
    {
        return username.find(partial) != string::npos;
    }
};

// Define a struct for the user node in the linked list
struct UserNode 
{
    User user;
    UserNode* next;

    UserNode(const User& u) : user(u), next(nullptr) {}
};

// Define a struct for the admin node in the linked list
struct AdminNode 
{
    User user;
    AdminNode* next;

    AdminNode(const User& u) : user(u), next(nullptr) {}
};

// Create a class to handle the linked lists
class UserList 
{
public:
    UserNode* head;

    UserList() : head(nullptr) {}

    void addUser(const User& user) 
    {
        UserNode* newNode = new UserNode(user);
        newNode->next = head;
        head = newNode;
    }

};

class AdminList 
{
public:
    AdminNode* head;

    AdminList() : head(nullptr) {}

    void addAdmin(const User& user) 
    {
        AdminNode* newNode = new AdminNode(user);
        newNode->next = head;
        head = newNode;
    }

};


void mergeSort(string arr[], int l, int r, bool ascending = true);
int binarySearchUser(const User users[], int left, int right, const string& partial);

class LoginRegister 
{
public:
    User users[MAX_USER];
    UserList userList;
    AdminList adminList;

    // Function to register a new user with username and password
    void registerUser(const string& username, const string& password, const int& role) 
    {
        // Check if the user count is less than the maximum allowed users
        if (userCount < MAX_USER) 
        {
            // Check if the username already exists
            for (int i = 0; i < userCount; i++) 
            {
                if (users[i].username == username) 
                {
                    cout << "Username already exists. Please choose a different username." << endl;
                    return;  // Exit the function if username already exists
                }
            }

            // Store the username, password, and default role for the new user
            users[userCount].username = username;
            users[userCount].password = password;
            users[userCount].role = role;
            userCount++;
            cout << "User registered successfully." << endl;
    
            // Open user.txt file to append user information
            ofstream userFile("user.txt", ios::app);
    
            // Check if the file is successfully opened
            if (userFile.is_open()) 
            {
                // Write the username, password, and default role to the file
                userFile << username << "," << password << "," << role << "\n";
                userFile.close(); // Close the file after writing
            } 
            else 
            {
                // Display error message if the file cannot be opened
                cout << "Unable to open user.txt for writing." << endl;
            }
        } 
        else 
        {
            // Display error message if the maximum user limit is reached
            cout << "User registration failed. Maximum user limit reached." << endl;
        }
    }

    // Function to load users' information from a file
    void loadUsers() 
    {
        userCount = 0;  // Initialize user count
        ifstream userFile("user.txt");  // Open user.txt file for reading

        // Check if the file is opened successfully
        if (userFile.is_open()) 
        {
            string line;

            // Read each line of the file
            while (getline(userFile, line)) 
            {
                stringstream ss(line);
                string username, password, role;

                // Parse the line to extract username, password, and role
                getline(ss, username, ',');
                getline(ss, password, ',');
                getline(ss, role);

                // Store the user information based on the role
                if (role == "1") 
                {
                    User user;
                    user.username = username;
                    user.password = password;
                    user.role = role;
                    userList.addUser(user);
                } 
                else if (role == "2" || role == "3") 
                {
                    User admin;
                    admin.username = username;
                    admin.password = password;
                    admin.role = role;
                    adminList.addAdmin(admin);
                }

                // Store the user information in the users array
                users[userCount].username = username;
                users[userCount].password = password;
                users[userCount].role = role;

                userCount++;  // Increment user count
            }
            userFile.close();  // Close the file
        } 
        else 
        {
            cout << "Unable to open user.txt for reading." << endl;  // Display error message if file opening fails
        }
    }

    // Function to login a user using their username and password
    // Returns a pointer to the User object if the credentials are valid
    // Otherwise, returns nullptr
    User* loginUser(const string& username, const string& password) 
    {
        for (int i = 0; i < userCount; i++) 
        {
            if (users[i].username == username && users[i].password == password) 
            {
                return &users[i];  // Return pointer to the user if credentials are valid
            }
        }
        return nullptr;  // Return nullptr if credentials are invalid
    }

    // Function to update the "user.txt" file with user information
    void updateFile() const 
    {
        // Open the "user.txt" file for writing, clearing its contents
        ofstream userFile("user.txt", ios::trunc);
        // Check if the file was successfully opened
        if (userFile.is_open()) 
        {
            // Iterate through the users and write their information to the file
            for (int i = 0; i < userCount; i++) 
            {
                userFile << users[i].username << "," << users[i].password << "," << users[i].role << "\n";
            }
            // Close the file after writing
            userFile.close();
        } 
        else 
        {
            // Display an error message if the file could not be opened for writing
            cout << "Unable to open user.txt for writing." << endl;
        }
    }
};

class Admin : public User {
    // Add admin-specific properties and methods
};

class SuperAdmin : public Admin 
{
    LoginRegister* loginRegister;

public:
    SuperAdmin(LoginRegister* loginReg) 
    {
        loginRegister = loginReg;
    }

    void displayUser() const 
    {
        int count = 0;
        string border = "+-----+---------------++-----+---------------++-----+---------------++-----+---------------++-----+---------------+\n";
        cout << border;
        
        // Traverse the user list and display user information
        UserNode* currentNode = loginRegister->userList.head;
        while (currentNode != nullptr) {
            cout << "| " << setw(3) << left << (count + 1) << " | " << setw(13) << left << currentNode->user.username << " |";
            currentNode = currentNode->next;
            if (++count % 5 == 0) 
            {
                cout << endl << border;
            }
        }
        if (count % 5 != 0) {
            cout << endl << string(border.length() - 1, '-') << endl;
        }
    }

    void displayStaff() const 
    {
        int count = 0;
        string border = "+-----+---------------++-----+---------------++-----+---------------++-----+---------------++-----+---------------+\n";
        cout << border;

        // Traverse the admin list and display admin information
        AdminNode* currentNode = loginRegister->adminList.head;
        while (currentNode != nullptr) {
            cout << "| " << setw(3) << left << (count + 1) << " | " << setw(13) << left << currentNode->user.username << " |";
            currentNode = currentNode->next;
            if (++count % 5 == 0) {
                cout << endl << border;
            }
        }
        if (count % 5 != 0) {
            cout << endl << string(border.length() - 1, '-') << endl;
        }
    }

    // Function to display users matching a partial username
    void searchUser(const string& partial) const 
    {
        int foundIndex = binarySearchUser(loginRegister->users, 0, userCount - 1, partial);
        if (foundIndex != -1) 
        {
            // Display matching user
            cout << "Found user: " << loginRegister->users[foundIndex].username <<  " at " << foundIndex << endl;
            system("pause");
        } 
        else 
        {
            cout << "No user found matching the provided partial username." << endl;
            system("pause");
        }
    }

    void searchStaff(const string& partial) const 
    {
        int foundIndex = binarySearchUser(loginRegister->users, 0, userCount - 1, partial);
        if (foundIndex != -1) 
        {
            // Display matching user
            cout << "Found user: " << loginRegister->users[foundIndex].username <<  " at " << foundIndex << endl;
            system("pause");
        } 
        else 
        {
            cout << "No user found matching the provided partial username." << endl;
            system("pause");
        }
    }

    // Function to sort the usernames in alphabetical order and updates the users array and file accordingly
    void sortUsersAZ() 
    {
        auto start = chrono::steady_clock::now();
        // Create an array to store the usernames
        string usernames[MAX_USER];

        // Copy usernames from loginRegister to the usernames array
        for (int i = 0; i < userCount; i++) 
        {
            usernames[i] = loginRegister->users[i].username;
        }

        // Apply merge sort to the usernames array to sort them in alphabetical order
        mergeSort(usernames, 0, userCount - 1, true);

        // Rearrange the users array based on the sorted usernames
        for (int i = 0; i < userCount; i++) 
        {
            for (int j = 0; j < userCount; j++) 
            {
                // Find the index of the username in the users array 
                if (usernames[i] == loginRegister->users[j].username) 
                {
                    // Swap the users to match the alphabetical order
                    swap(loginRegister->users[i], loginRegister->users[j]);
                    break;
                }
            }
        }

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        // Update the file with the sorted user data
        loginRegister->updateFile();

        cout << "Sorting spend " << elapsed_seconds.count() * 1000 << " milliseconds\n " << endl;
        system("pause");
    }

    // Function to sort the usernames in alphabetical order and updates the users array and file descending
    void sortUsersZA() 
    {
        auto start = chrono::steady_clock::now();
        // Array to store usernames
        string usernames[MAX_USER];
    
        // Copying usernames from users array to usernames array
        for (int i = 0; i < userCount; i++) 
        {
            usernames[i] = loginRegister->users[i].username;
        }
    
        // Sorts the usernames array using merge sort algorithm
        mergeSort(usernames, 0, userCount - 1, false);
    
        // Rearranges the users array based on the sorted usernames array
        for (int i = 0; i < userCount; i++) 
        {
            for (int j = 0; j < userCount; j++) 
            {
                // Swaps the user objects if the usernames match
                if (usernames[i] == loginRegister->users[j].username) 
                {
                    swap(loginRegister->users[i], loginRegister->users[j]);
                    break;
                }
            }
        }

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
    
        // Updates the file with the updated user list
        loginRegister->updateFile();

        cout << "Sorting spend " << elapsed_seconds.count() * 1000 << " milliseconds\n " << endl;
        system("pause");
    }
};

// Function to merge two subarrays of arr[]
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
// ascending parameter determines the sorting order
void merge(string arr[], int l, int m, int r, bool ascending) 
{
    // Calculate sizes of two subarrays to be merged
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    string* L = new string[n1];
    string* R = new string[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) 
    {
        // Compare elements and merge based on the sorting order
        if ((ascending && L[i] <= R[j]) || (!ascending && L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Deallocate memory used for temporary arrays
    delete[] L;
    delete[] R;
}

// Function to perform merge sort on an array of strings
// arr: The array of strings to be sorted
// l: Left index of the subarray
// r: Right index of the subarray
// ascending: Boolean flag to indicate sorting order (true for ascending, false for descending)
void mergeSort(string arr[], int l, int r, bool ascending) 
{
    // If the subarray has more than one element
    if (l < r) 
    {
        // Calculate the middle index
        int m = l + (r - l) / 2;
        // Recursively sort the left and right halves
        mergeSort(arr, l, m, ascending);
        mergeSort(arr, m + 1, r, ascending);
        // Merge the sorted halves
        merge(arr, l, m, r, ascending);
    }
}

// Function to perform binary search on an array of User objects based on partial username
// Returns the index of the found user or -1 if not found
int binarySearchUser(const User users[], int left, int right, const string& partial) 
{
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;
        // Check if the partial username matches the user's username
        if (users[mid].partialUsernameMatch(partial)) 
        {
            return mid;  // Return index if partial match found
        }
        // If partial is less than the current username, search left half
        if (partial < users[mid].username) 
        {
            right = mid - 1;
        }
        // If partial is greater than the current username, search right half
        else 
        {
            left = mid + 1;
        }
    }
    return -1;  // Return -1 if not found
}

// The main function to start the program
int main() 
{
    // Create an instance of the LoginRegister class
    LoginRegister loginRegister;
    // Initialize the choice variable for user input
    int choice;
    // Initialize the currentUser pointer to null
    User* currentUser = nullptr;

    // Main program loop
    do 
    {
        // Load user data from file
        loginRegister.loadUsers();

        cout << "Main Menu" << endl;
        // Display main menu options
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Process user choice
        switch (choice) 
        {
            // Login option
            case 1: 
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                // Attempt to login user and get the current user object
                currentUser = loginRegister.loginUser(username, password);

                // If login successful
                if (currentUser != nullptr) 
                {
                    system("cls");

                    // Proceed to user roles
                    if (currentUser->role == "1") 
                    {
                            cout << "Welcome to the Grocery Checkout System, " << currentUser->username << "!" << endl;
                            system("pause");
                            system("cls");
                    } 
                    else if (currentUser->role == "2") 
                    {
                            cout << "Welcome to the Cashier Management System, " << currentUser->username << "!" << endl;
                            system("pause");
                            system("cls");
                    } 
                    else if (currentUser->role == "3") 
                    {
                        // Create a SuperAdmin object with access to loginRegister
                        SuperAdmin superAdmin(&loginRegister);

                        int superAdminChoice;
                        int userChoice;
                        string partial;

                        // Super admin menu loop
                        do {
                            cout << "Welcome to the Cashier Management System, " << currentUser->username << "!" << endl;
                            system("pause");
                            system("cls");
                            cout << "Super Admin Menu" << endl;
                            cout << "1. User Function" << endl;
                            cout << "2. Staff Function" << endl;
                            cout << "2. Logout" << endl;
                            cout << "Enter your choice: ";
                            cin >> superAdminChoice;

                            // Process super admin menu choice
                            switch (superAdminChoice) {
                                // User function option
                                case 1:
                                    // User function menu loop
                                    do {
                                        system("cls");
                                        cout << "User Function Menu" << endl;
                                        cout << "1. Display all users" << endl;
                                        cout << "2. Sort users A-Z" << endl;
                                        cout << "3. Sort users Z-A" << endl;
                                        cout << "4. Search users" << endl;
                                        cout << "5. Back to Super Admin Menu" << endl;
                                        cout << "Enter your choice: ";
                                        cin >> userChoice;

                                        // Process user function menu choice
                                        switch (userChoice) 
                                        {
                                            case 1:
                                                cout << "Display Customer data: " << endl;
                                                superAdmin.displayUser();
                                                system("pause");
                                                break;
                                            case 2:
                                                superAdmin.sortUsersAZ();
                                                break;
                                            case 3:
                                                superAdmin.sortUsersZA();
                                                break;
                                            case 4:
                                                cout << " Please enter the name you want to search: ";
                                                cin >> partial;
                                                superAdmin.searchUser(partial);
                                                break;
                                            case 5:
                                                cout << "Going back to Super Admin Menu" << endl;
                                                system("pause");
                                                system("cls");
                                                break;
                                            default:
                                                cout << "Invalid choice. Please try again." << endl;
                                                break;
                                        }
                                    } while (userChoice != 5);
                                    break;
                                // Staff function option
                                case 2:
                                {
                                    // Staff function menu loop
                                    do {
                                        system("cls");
                                        cout << "Staff Function Menu" << endl;
                                        cout << "1. Display all staff" << endl;
                                        cout << "2. Sort users A-Z" << endl;
                                        cout << "3. Sort users Z-A" << endl;
                                        cout << "4. Search staff" << endl;
                                        cout << "5. Add staff" << endl;
                                        cout << "6. Back to Super Admin Menu" << endl;
                                        cout << "Enter your choice: ";
                                        cin >> userChoice;

                                        string username, password;

                                        // Process user function menu choice
                                        switch (userChoice) 
                                        {
                                            case 1:
                                                cout << "Display Staff data: " << endl;
                                                superAdmin.displayStaff();
                                                system("pause");
                                                break;
                                            case 2:
                                                superAdmin.sortUsersAZ();
                                                break;
                                            case 3:
                                                superAdmin.sortUsersZA();
                                                break;
                                            case 4:
                                                cout << " Please enter the name you want to search: ";
                                                cin >> partial;
                                                superAdmin.searchStaff(partial);
                                                break;
                                            case 5:
                                                cout << "Please enter the username and password for the new staff member " << endl;
                                                cout << "Enter username: ";
                                                cin >> username;
                                                cout << "Enter password: ";
                                                cin >> password;
                                                loginRegister.registerUser(username, password,2);
                                                break;
                                            case 6:
                                                cout << "Going back to Super Admin Menu" << endl;
                                                system("pause");
                                                system("cls");
                                                break;
                                            default:
                                                cout << "Invalid choice. Please try again." << endl;
                                                break;
                                        }
                                    } while (userChoice != 6);
                                    break;
                                }
                                // Logout option
                                case 3:
                                    cout << "Logging out" << endl;
                                    system("pause");
                                    system("cls");
                                    break;
                                default:
                                    cout << "Invalid choice. Please try again." << endl;
                                    break;
                            }
                        } while (superAdminChoice != 3);
                    }
                } else {
                    cout << "Invalid username or password. Please try again." << endl;
                }
                break;
            }
            // Register option
            case 2: 
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                // Register a new user
                loginRegister.registerUser(username, password,1);

                break;
            }
            // Exit option
            case 3:
                cout << "Thanks for using the Grocery Checkout System. Hope to see you again soon." << endl;
                break;
            // Invalid input
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
