# Event Management System

This is a **C++-based Event Management System** designed for managing posts efficiently with separate functionalities for Admin and User roles. The system supports user authentication, post creation, searching, and management, and stores data persistently using files.

---

## Features

### Admin Functionalities
1. **Add Post**: Create a new post with details like name, category, date, and content.
2. **Delete Post**: Remove a post by its name.
3. **Update Post**: Edit an existing post's details.
4. **Search Posts by Name**: Efficiently find posts using their name.
5. **Search Posts by Date**: Find all posts on a specific date.
6. **Save Posts**: Save all posts to a file for persistence.

### User Functionalities
1. **View Posts**: Browse all available posts.
2. **Search by Name**: Find posts using their name.
3. **Search by Category**: Filter posts by their category.
4. **View Viewed Posts**: Keep track of previously viewed posts.

### Authentication
- **Admin Registration and Login**: Separate credentials for administrators.
- **User Registration and Login**: Register and authenticate regular users.

---

## How to Run

1. **Compile the Code**:
   Use a C++ compiler like `g++`:
   ```bash
   g++ -o event_management main.cpp -std=c++17
