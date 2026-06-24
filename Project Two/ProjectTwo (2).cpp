//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Tajiona Thompson-Hervey
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : CS 300 Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

//Course structure
struct Course {
    string courseId;
    string title;
    vector<string> prereqs;
};

//Binary Search Tree Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// Used to store courses in alphanumeric order
class BinarySearchTree {
private:
    Node* root;

    //Insert a course into the binary search tree
    void insert(Node* node, Course course) {

        if (course.courseId < node->course.courseId) {

            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                insert(node->left, course);
            }
        }
        else {

            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                insert(node->right, course);
            }
        }
    }

    // Perform in-order traversal to print courses alphabetically
    void printInOrder(Node* node) {

        if (node == nullptr) {
            return;
        }

        printInOrder(node->left);

        cout << node->course.courseId
             << ", "
             << node->course.title
             << endl;

        printInOrder(node->right);
    }

    // Search for a course in the BST using course number
    Course search(Node* node, string courseId) {

        if (node == nullptr) {
            return Course();
        }

        if (node->course.courseId == courseId) {
            return node->course;
        }

        if (courseId < node->course.courseId) {
            return search(node->left, courseId);
        }

        return search(node->right, courseId);
    }

public:

    BinarySearchTree() {
        root = nullptr;
    }

    // Public function used to add a course to the tree.
    void Insert(Course course) {

        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            insert(root, course);
        }
    }

    void PrintCourseList() {
        printInOrder(root);
    }

    // Public function used to locate a course.
    Course Search(string courseId) {
        return search(root, courseId);
    }
};

// Load course data from the CSV file into the BST
void loadCourses(string fileName, BinarySearchTree& bst) {

	// Open course data file
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    // Read each line from the file
    while (getline(file, line)) {

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            continue;
        }

        // Create a course object from the CSV data
        Course course;
        course.courseId = tokens[0];
        course.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); i++) {
            course.prereqs.push_back(tokens[i]);
        }

        bst.Insert(course);
    }

    file.close();

    cout << "Data loaded successfully." << endl;
}

//Main program. Displays menu and processes user selection
int main() {

    BinarySearchTree bst;

    int choice = 0;
    bool loaded = false;

    cout << "Welcome to the course planner." << endl;

    // Continue displaying menu until the user exits
    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {

        // Load course data from the input file
        case 1: {

            string fileName;

            cout << "Enter file name: ";
            cin >> fileName;

            loadCourses(fileName, bst);
            loaded = true;

            break;
        }

        // Print all courses in sorted order
        case 2:

            if (!loaded) {
                cout << "Load the file first." << endl;
                break;
            }

            cout << endl;
            bst.PrintCourseList();
            break;

        // Display information for a specific course
        case 3: {

            if (!loaded) {
                cout << "Load the file first." << endl;
                break;
            }

            string courseId;

            cout << "What course do you want to know about? ";
            cin >> courseId;

            Course course = bst.Search(courseId);

            if (course.courseId.empty()) {
                cout << "Course not found." << endl;
            }
            else {

                cout << endl;
                cout << course.courseId
                     << ", "
                     << course.title
                     << endl;

                cout << "Prerequisites: ";

                if (course.prereqs.empty()) {
                    cout << "None";
                }
                else {

                    for (size_t i = 0; i < course.prereqs.size(); i++) {

                        cout << course.prereqs[i];

                        if (i < course.prereqs.size() - 1) {
                            cout << ", ";
                        }
                    }
                }

                cout << endl;
            }

            break;
        }

        //Exit program
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
