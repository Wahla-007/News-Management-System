#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

int MAX_POSTS = 10;

struct Post {
    string name;
    string category;
    string date;
    string content;
};

class Node {
public:
    Post post;
    Node* next;

    Node(Post p) : post(p), next(nullptr) {}
};

class BSTNode {
public:
    Post post;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Post p) : post(p), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

public:
    BST() : root(nullptr) {}

    // insrt a post into the BST
    BSTNode* insert(BSTNode* node, Post post) {
        if (node == nullptr) return new BSTNode(post);

        if (post.date < node->post.date)
            node->left = insert(node->left, post);
        else
            node->right = insert(node->right, post);

        return node;
    }

    // insertpost wil add post into the tree
    void insertPost(Post post) {
        root = insert(root, post);
    }

    // serch for post by date, reccursively checks left and right
    void searchByDate(BSTNode* node, const string& date, bool& found) {
        if (node == nullptr) return;

        if (node->post.date == date) {
            cout << "Name: " << node->post.name << "\n";
            cout << "Category: " << node->post.category << "\n";
            cout << "Date: " << node->post.date << "\n";
            cout << "Content: " << node->post.content << "\n\n";
            found = true;
        }

        searchByDate(node->left, date, found);
        searchByDate(node->right, date, found);
    }

    // serach name from tree, recursive approach
    void searchName(BSTNode* node, const string& name, bool& found) {
        if (node == nullptr) return;

        searchName(node->left, name, found);

        if (node->post.name == name) {
            cout << "Name: " << node->post.name << "\n";
            cout << "Category: " << node->post.category << "\n";
            cout << "Date: " << node->post.date << "\n";
            cout << "Content: " << node->post.content << "\n\n";
            found = true;
        }

        searchName(node->right, name, found);
    }

    // retruns the root node of the tree
    BSTNode* getRoot() { return root; }

    // serch for posts by date
    void searchPostsByDate(const string& date) {
        bool found = false;
        searchByDate(root, date, found);
        if (!found) cout << "No posts found on the given date.\n";
    }
};













class LNode {
private:
    string name;
    string category;
    string date;
    string content;
    LNode* next;

public:
    LNode(const string& n, const string& c, const string& d, const string& con)
        : name(n), category(c), date(d), content(con), next(nullptr) {
    }

    // getName functoin to retrun the name of the post
    string getName() const { return name; }
    // getCategory funtion to retrun the category
    string getCategory() const { return category; }
    // getDate function returns the date of the post
    string getDate() const { return date; }
    // getContent functoin retruns the content of the post
    string getContent() const { return content; }
    // getNext function to retrun the next node in the list
    LNode* getNext() const { return next; }

    // setNext funtion will set the next node in the list
    void setNext(LNode* nextNode) { next = nextNode; }
};

class userFunctions {
private:
    string file_name;
    LNode* head = nullptr;

    // adds a post to the viewed list
    void addToViewedPosts(const string& name, const string& category, const string& date, const string& content) {
        LNode* newNode = new LNode(name, category, date, content);
        newNode->setNext(head);
        head = newNode;
    }

public:
    userFunctions(const string& file) : file_name(file) {}

    // displys the post details based on the postName
    void displayPostDetails(const string& postName) {
        file_name = "post_details.txt";
        ifstream file(file_name);
        if (!file) {
            cout << "Error: Could not open the file '" << file_name << "'.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
                cout << "Error: File format is incorrect.\n";
                return;
            }

            string name = line.substr(0, pos1);
            string category = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string content = line.substr(pos3 + 1);

            if (name == postName) {
                cout << "\nPost Details:\n";
                cout << "Name: " << name << "\n";
                cout << "Category: " << category << "\n";
                cout << "Date: " << date << "\n";
                cout << "Content: " << content << "\n";

                addToViewedPosts(name, category, date, content);
                return;
            }
        }

        cout << "Post not found.\n";
    }

    // will view all the posts in the file
    void viewPosts() {
        ifstream file(file_name);
        if (!file) {
            cout << "Error: Could not open the file '" << file_name << "'.\n";
            return;
        }

        cout << "\nAvailable Posts:\n";
        string line;
        int count = 1;
        //to get the whitespace also ....
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos == string::npos) {
                cout << "Error: File format is incorrect.\n";
                return;
            }
            string name = line.substr(0, pos);
            cout << count++ << ". " << name << "\n";
        }

        file.close();

        cout << "\nEnter the name of the post you want to view:(OR Press 0 to return) ";
        string postName;
        cin.ignore();
        getline(cin, postName);
        if (postName == "0") return;

        displayPostDetails(postName);
    }

    // search a post by its name from the list
    void searchByName() {
        while (true) {
            cout << "\nEnter the name of the post to search (or press 0 to go back): ";
            string postName;
            getline(cin, postName);

            if (postName == "0") return;

            ifstream file(file_name);
            if (!file) {
                cout << "Error: Could not open the file.\n";
                return;
            }

            string line;
            bool found = false;
            while (getline(file, line)) {
                size_t pos = line.find('|');
                string name = line.substr(0, pos);

                if (name == postName) {
                    size_t pos1 = line.find('|');                           // finDing second '|' after the first one
                    size_t pos2 = line.find('|', pos1 + 1);                 // fiding third '|' after the second one
                    size_t pos3 = line.find('|', pos2 + 1);                  // fiding third '|' after the second one
                    // extracitng the category from the line using the positions
                    string category = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    // extracitng the content from the line, after the third '|'
                    string content = line.substr(pos3 + 1);

                    cout << "\nPost Found:\n";
                    cout << "Name: " << name << "\n";
                    cout << "Category: " << category << "\n";
                    cout << "Date: " << date << "\n";
                    cout << "Content: " << content << "\n";

                    addToViewedPosts(name, category, date, content);
                    found = true;
                    break;
                }
            }

            if (!found) cout << "Post not found. Try again.\n";
        }
    }

    // searches for posts by category
    void searchByCategory() {
        while (true) {
            cout << "\nEnter the category to search (or press 0 to go back): ";
            string categorySearch;
            getline(cin, categorySearch);

            if (categorySearch == "0") return;

            ifstream file(file_name);
            if (!file) {
                cout << "Error: Could not open the file.\n";
                return;
            }

            string line;
            bool found = false;
            cout << "\nPosts in Category \"" << categorySearch << "\":\n";

            while (getline(file, line)) {
                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                string category = line.substr(pos1 + 1, pos2 - pos1 - 1);

                if (category == categorySearch) {
                    size_t pos3 = line.find('|', pos2 + 1);
                    string name = line.substr(0, pos1);
                    string date = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    string content = line.substr(pos3 + 1);

                    cout << "\nName: " << name << "\n";
                    cout << "Date: " << date << "\n";
                    cout << "Content: " << content << "\n";

                    addToViewedPosts(name, category, date, content);
                    found = true;
                }
            }

            if (!found) cout << "No posts found in this category. Try again.\n";
        }
    }

    // views the posts that have been viewed already
    void viewViewedPosts() {
        if (head == nullptr) {
            cout << "\nNo posts viewed yet.\n";
            return;
        }

        cout << "\nViewed Posts:\n";
        LNode* current = head;
        int count = 1;

        while (current != nullptr) {
            cout << count++ << ". " << current->getName() << "\n";
            cout << "   Category: " << current->getCategory() << "\n";
            cout << "   Date: " << current->getDate() << "\n";
            cout << "   Content: " << current->getContent() << "\n\n";
            current = current->getNext();
        }
    }
};

class AdminFunctions {
private:
    Node* front;  // Front of the post queue
    Node* rear;   // Rear of the post queue
    BST bst;      // Binary search tree for efficient post searching
    string file_name;  // File name to load/save posts

    // Parse a line from the file into a Post object
    Post parsePost(const string& line) {
        Post post;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        post.name = line.substr(0, pos1);
        post.category = line.substr(pos1 + 1, pos2 - pos1 - 1);
        post.date = line.substr(pos2 + 1, pos3 - pos2 - 1);
        post.content = line.substr(pos3 + 1);

        return post;
    }

    // Format a Post object into a string suitable for saving
    string formatPost(const Post& post) {
        return post.name + "|" + post.category + "|" + post.date + "|" + post.content;
    }

public:
    // Constructor initializes the file and loads existing posts
    AdminFunctions(const string& file) : front(nullptr), rear(nullptr), file_name(file) {
        loadPostsFromFile();
    }

    ~AdminFunctions() {
        //savePostsToFile();  // Optionally save before destruction
    }

    // Load posts from a file into the queue and BST
    void loadPostsFromFile() {
        ifstream infile(file_name);
        if (!infile) {
            cerr << "Could not open file: " << file_name << "\n";
            return;
        }

        string line;
        while (getline(infile, line)) {
            if (line.empty()) continue; // Skip empty lines
            Post post = parsePost(line);

            Node* new_node = new Node(post);
            if (rear == nullptr) {
                front = rear = new_node;
            }
            else {
                rear->next = new_node;
                rear = new_node;
            }

            bst.insertPost(post);  // Insert into BST for efficient search
        }
        infile.close();
    }

    // Save posts to the file
    void savePostsToFile() {
        ofstream outfile(file_name, ios::trunc);
        if (!outfile) {
            cerr << "Could not open file: " << file_name << "\n";
            return;
        }

        Node* temp = front;
        while (temp != nullptr) {
            outfile << formatPost(temp->post) << "\n"; // Write each post to file
            temp = temp->next;
        }
        outfile.close();
    }

    // Add a new post to the queue and BST
    void addPost() {
        string name, category, date, content;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter post name: ";
        getline(cin, name);
        cout << "Enter post category: ";
        getline(cin, category);
        cout << "Enter post date (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter post content: ";
        getline(cin, content);

        Post new_post = { name, category, date, content };

        Node* new_node = new Node(new_post);
        if (rear == nullptr) {
            front = rear = new_node;
        }
        else {
            rear->next = new_node;
            rear = new_node;
        }

        bst.insertPost(new_post);  // Insert the new post into BST

        cout << "Post added successfully!\n";
        MAX_POSTS++;  // Update post count
    }

    // Search for posts by name in the BST
    void searchPostsByName() {
        try {
            string name;
            cout << "Enter the name of the post to search: ";
            getline(cin, name);

            if (name.empty()) {
                cout << "Error: Post name cannot be empty.\n";
                return;
            }

            cout << "\nSearching for posts by name: " << name << "\n";

            bool found = false;
            bst.searchName(bst.getRoot(), name, found); // Search in BST

            if (!found) {
                cout << "No posts found with the name \"" << name << "\".\n";
            }

        }
        catch (...) {
            cout << "An unexpected error occurred during the search.\n";
        }
    }

    // Delete a post by name from the queue and BST
    void deletePost() {
        if (front == nullptr) {
            cout << "No posts available to delete.\n";
            return;
        }

        cout << "\nPosts in Queue:\n";
        Node* temp = front;
        while (temp != nullptr) {
            cout << "- " << temp->post.name << "\n";  // Display post names
            temp = temp->next;
        }

        string post_name;
        cout << "Enter the name of the post to delete: ";
        getline(cin, post_name);

        temp = front;
        Node* prev = nullptr;

        while (temp != nullptr && temp->post.name != post_name) {
            prev = temp;
            temp = temp->next;
        }

        if (temp != nullptr) {
            if (prev == nullptr) {
                front = front->next;
            }
            else {
                prev->next = temp->next;
            }

            if (temp == rear) {
                rear = prev;
            }

            delete temp;  // Free memory
            cout << "Post deleted successfully!\n";
            MAX_POSTS--;  // Update post count
        }
        else {
            cout << "Post not found.\n";
        }
    }

    // Update an existing post's details
    void updatePost() {
        if (front == nullptr) {
            cout << "No posts available to update.\n";
            return;
        }

        cout << "\nPosts in Queue:\n";
        Node* temp = front;
        while (temp != nullptr) {
            cout << "- " << temp->post.name << "\n";  // Display post names
            temp = temp->next;
        }

        string post_name;
        cout << "Enter the name of the post to update: ";
        getline(cin, post_name);

        temp = front;

        while (temp != nullptr && temp->post.name != post_name) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            cout << "Current post details:\n";
            cout << "Name: " << temp->post.name << "\n";
            cout << "Category: " << temp->post.category << "\n";
            cout << "Date: " << temp->post.date << "\n";
            cout << "Content: " << temp->post.content << "\n";

            cout << "\nEnter new details for the post:\n";
            cout << "Enter post name: ";
            getline(cin, temp->post.name);
            cout << "Enter post category: ";
            getline(cin, temp->post.category);
            cout << "Enter post date (YYYY-MM-DD): ";
            getline(cin, temp->post.date);
            cout << "Enter post content: ";
            getline(cin, temp->post.content);

            cout << "Post updated successfully!\n";
        }
        else {
            cout << "Post not found.\n";
        }
    }

    // Search posts by a specific date
    void searchPostsByDate() {
        string date;
        cout << "Enter the date to search posts (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "\nSearching for posts on date: " << date << "\n";
        bst.searchPostsByDate(date);  // Search in BST
    }
};


class login_system {
private:
    string admin_file;  // File to store admin credentials
    string user_file;   // File to store user credentials

    // Attempt to log in using provided username and password
    bool login(const string& username, const string& password, const string& file) {
        try {
            ifstream infile(file);
            if (!infile) {
                throw runtime_error("Error opening file for login.");
            }

            string stored_username, stored_password;
            while (infile >> stored_username >> stored_password) {
                if (stored_username == username && stored_password == password) {
                    return true;  // Successfully logged in
                }
            }
            return false;  // Credentials don't match
        }
        catch (const exception&) {
            cerr << "An error occurred while running the program.\n";
            return false;  // Error during login process
        }
    }

    // Register a new user with a username and password
    void register_user(const string& username, const string& password, const string& file) {
        try {
            ifstream infile(file);
            string stored_username, stored_password;
            // Check if username already exists
            while (infile >> stored_username >> stored_password) {
                if (stored_username == username) {
                    cout << "Username already exists. Please choose another.\n";
                    return;
                }
            }

            // Open file in append mode and register user
            ofstream outfile(file, ios::app);
            if (!outfile) {
                throw runtime_error("Error opening file for registration.");
            }
            outfile << username << " " << password << endl;
            outfile.close();
            cout << "User registered successfully!\n";
        }
        catch (const exception& e) {
            cerr << e.what() << "\n";  // Handle any exceptions during registration
        }
    }

public:
    // Constructor initializes file names for admin and user credentials
    login_system(const string& admin_file_name, const string& user_file_name)
        : admin_file(admin_file_name), user_file(user_file_name) {
    }

    // Register a new admin user
    void admin_register(const string& username, const string& password) {
        register_user(username, password, admin_file);
    }

    // Register a new regular user
    void user_register(const string& username, const string& password) {
        register_user(username, password, user_file);
    }

    // Login as admin with provided credentials
    bool admin_login(const string& username, const string& password) {
        return login(username, password, admin_file);
    }

    // Login as regular user with provided credentials
    bool user_login(const string& username, const string& password) {
        return login(username, password, user_file);
    }
};




int main() {
    try {
        login_system system("admin_credentials.txt", "user_credentials.txt");
        AdminFunctions adminFunctions("post_details.txt");
        userFunctions pos("post_details.txt");

        int choice;
        string username, password;

        do {
            cout << "\nMain Menu:\n";
            cout << "1. Register as Admin\n";
            cout << "2. Register as User\n";
            cout << "3. Login as Admin\n";
            cout << "4. Login as User\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (choice) {
            case 1:
                cout << "Enter admin username: ";
                cin >> username;
                cout << "Enter admin password: ";
                cin >> password;
                system.admin_register(username, password);
                break;

            case 2:
                cout << "Enter user username: ";
                cin >> username;
                cout << "Enter user password: ";
                cin >> password;
                system.user_register(username, password);
                break;

            case 3: {  // Admin login
                cout << "Enter admin username: ";
                cin >> username;
                cout << "Enter admin password: ";
                cin >> password;

                if (system.admin_login(username, password)) {
                    cout << "Admin login successful!\n";
                    int adminChoice;
                    do {
                        cout << "\nAdmin Menu:\n";
                        cout << "1. Add Post\n";
                        cout << "2. Delete Post\n";
                        cout << "3. Update Post\n";
                        cout << "4. Search Posts by Date\n";
                        cout << "5. Search Posts by Name\n";
                        cout << "6. Save Data to File\n";
                        cout << "7. Exit\n";
                        cout << "Enter your choice: ";

                        cin >> adminChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number.\n";
                            continue;
                        }

                        switch (adminChoice) {
                        case 1: adminFunctions.addPost(); break;
                        case 2: adminFunctions.deletePost(); break;
                        case 3: adminFunctions.updatePost(); break;
                        case 4: adminFunctions.searchPostsByDate(); break;
                        case 5: adminFunctions.searchPostsByName(); break;
                        case 6: adminFunctions.savePostsToFile(); break;
                        case 7: cout << "Exiting Admin Menu...\n"; break;
                        default: cout << "Invalid choice. Please try again.\n";
                        }

                        if (adminChoice == 7) break;
                    } while (true);
                }
                else {
                    cout << "Invalid admin username or password.\n";
                }
                break;
            }

            case 4: {  // User login
                cout << "Enter user username: ";
                cin >> username;
                cout << "Enter user password: ";
                cin >> password;

                if (system.user_login(username, password)) {
                    cout << "User login successful!\n";
                    int userChoice;
                    do {
                        cout << "\nUser Menu:\n";
                        cout << "1. View Posts\n";
                        cout << "2. Search Post by Name\n";
                        cout << "3. Search Post by Category\n";
                        cout << "4. Viewed Posts\n";
                        cout << "5. Exit\n";
                        cout << "Enter your choice: ";

                        cin >> userChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input. Please enter a number.\n";
                            continue;
                        }

                        switch (userChoice) {
                        case 1: pos.viewPosts(); break;
                        case 2: pos.searchByName(); break;
                        case 3: pos.searchByCategory(); break;
                        case 4: pos.viewViewedPosts(); break;
                        case 5: cout << "Exiting User Menu...\n"; break;
                        default: cout << "Invalid choice. Please try again.\n";
                        }

                        if (userChoice == 5) break;
                    } while (true);
                }
                else {
                    cout << "Invalid user username or password.\n";
                }
                break;
            }

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
    catch (...) {
        cerr << "An unexpected error occurred.\n";
    }

    return 0;
}
