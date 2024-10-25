#include <iostream>  
// Include the input-output stream library
using namespace std; 
// Use the standard namespace

// Function to generate and print the Fibonacci series
void fibonacci(int n) {
    int first = 0, second = 1, next;  
    // Initialize the first two terms

    // Print the first two terms
    cout << "Fibonacci series: " << first << " " << second << " ";

    // Loop to calculate the rest of the series
    for (int i = 2; i < n; i++) {
        next = first + second; 
         // Calculate the next term
        cout << next << " ";   
         // Print the next term
        first = second;        
         // Update the first term
        second = next;         
         // Update the second term
    }
    cout << endl;
      // End the line after printing the series
}

int main() {
    int n;  
    // Variable to store the number of terms

    // Ask the user to enter the number of terms
    cout << "Enter the number of terms: ";
    /* hello this is 
    prince jaiswal*/
    cin >> n; 
     // Read the user's input

    // Check if the input is a positive integer
    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
    } else {
        fibonacci(n); 
         // Call the Fibonacci function with the user input
    }

    return 0;  
    // End the program
}
