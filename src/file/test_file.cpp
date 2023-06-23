#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

int main() {
    try {
        // Create an output file stream for writing to a file
        std::shared_ptr<std::fstream> fh = std::make_shared<std::fstream>();
        fh -> open("data1.txt", ios::out | ios::binary);

        fstream outFile("data.txt", ios::out | ios::binary);

        if (!outFile) {
            throw runtime_error("Error: could not open file for writing");
        }

        // Write data to the file
        int num1 = 42;
        double num2 = 3.14;
        string str = "Hello, world!";

        outFile.write(reinterpret_cast<char*>(&num1), sizeof(num1));
        outFile.write(reinterpret_cast<char*>(&num2), sizeof(num2));
        outFile.write(str.c_str(), str.size() + 1);

        // Close the file
        outFile.close();

        // Open the file for reading and writing
        fstream inFile("data.txt", ios::in | ios::out | ios::binary);

        if (!inFile) {
            throw runtime_error("Error: could not open file for reading and writing");
        }

        // Read the data from the file
        inFile.read(reinterpret_cast<char*>(&num1), sizeof(num1));
        inFile.read(reinterpret_cast<char*>(&num2), sizeof(num2));
        char buffer[100];
        inFile.read(buffer, sizeof(buffer));

        // Print the data read from the file
        cout << "num1 = " << num1 << endl;
        cout << "num2 = " << num2 << endl;
        cout << "str = " << buffer << endl;

        // Close the file
        inFile.close();

    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
