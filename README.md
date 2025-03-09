# Library Management System

This is a simple library management system implemented in C. It allows users to register, login, view books, borrow books, and request books. Admin users have additional functionalities such as adding books, extending user licenses, viewing book requests, and marking books as available.

## Features

- User Registration
- User Login
- View Available Books
- Borrow Books
- Request Books
- Admin Functions:
  - Add Books
  - Extend User Licenses
  - View Book Requests
  - Mark Books as Available

## Default Data

The system comes with some default books and users:

### Default Books

1. The Great Gatsby (Available)
2. 1984 (Borrowed by user1, Due Date: 2025-03-23)
3. To Kill a Mockingbird (Available)

### Default Users

1. admin (Admin User, Password: admin123)
2. user1 (Regular User, Password: password1)
3. user2 (Regular User, Password: password2)

### Default Book Requests

1. The Catcher in the Rye (Requested by user2)

## How to Run

1. Open the terminal in Visual Studio Code.
2. Navigate to the directory containing your `main.c` file:
    ```sh
    cd "d:\@025\c_c++\back_c\new\"
    ```
3. Compile your `main.c` file using `gcc`:
    ```sh
    gcc main.c -o main
    ```
4. Run the compiled executable:
    ```sh
    .\main
    ```

## Usage

1. When you run the program, you will be presented with the following options:
    ```
    1. Register
    2. Login
    3. Exit
    Enter choice:
    ```
2. Choose an option by entering the corresponding number.

### Register

- Enter a username and password to register a new user.

### Login

- Enter your username and password to login.
- Admin users will have additional options.

### Admin Functions

- Admin users can add books, extend user licenses, view book requests, and mark books as available.

### User Functions

- Regular users can view available books, borrow books, and request books.

## Notes

- The system locks a user account after 3 failed login attempts. The account can only be unlocked by an admin.
- Borrowed books are due in 2 weeks from the date of borrowing.

## License

This project is licensed under the MIT License.