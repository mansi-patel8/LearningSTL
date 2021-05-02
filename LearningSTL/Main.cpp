/*
* Name: Mansi Patel
* Purpose: Purpose of this program is to learn STL.
*/

#include <iostream>
#include <vector>
#include <ctime>     // time()
#include <cstdlib>   // srand(), rand()
#include <algorithm> // min_element(), max_element(), sort()
#include <string>    // std::string, std::stoi

using namespace std;

class Student
{
private:
    string name_;
    int number_;
    vector<int> grades_;
    int num_courses_;

    /*
    * gen_name() method generates random name for student class
    * A name is a random string (a-zA-Z0-9) between 6 and 12 characters long
    */
    static string gen_name()
    {
        string complete_str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; //string with all the available vals for random string
        string random_str;                                                                      //var to store the randomly generated string
        bool flag = false;                                                                      //flag to check if the string length
        int position;                                                                           //var for string position
        int str_length = (rand() % 7) + 6;                                                      //generate random number between 6 - 12 for random string length

        //check if string length is between 6 to 12
        if (str_length > 5 || str_length < 13)
        {
            flag = true; //set the flag true when string length is between 6 to 12
        }
        else
        {
            cerr << "String length is not between 6 to 12 character." << endl;
        }

        //if falg is true
        if (flag == true)
        {
            //loop to create the random string with length = str_length
            for (int i = 0; i < str_length; i++)
            {
                position = ((rand() % (complete_str.size() - 1))); //get the random char from complete_str
                random_str += complete_str.substr(position, 1);    //assign the char to random_str at postion got from above
            }
            return random_str;
        }
    }

    /*
    * gen_number() method generates random number for student class
    * A number is a random integer between 201100000 and 201600000
    */
    static int gen_number()
    {
        int random_number = (rand() % 500001) + 201100000; //generate random number between 201100000 - 201600000
        return random_number;
    }

    /*
    * gen_grade() method generates random grades for student class
    * A grade is a random integer between 70 and 100
    */
    static int gen_grade()
    {
        int random_grade = (rand() % 31) + 70; //generate random number between 70 and 100
        return random_grade;
    }

public:
    //constructor with (name, number)
    Student(const string& name, int number) : name_(name), number_(number), num_courses_(5)
    {
        name_ = gen_name();     //setting name_ = gen_name() because static method as gen_name();
        number_ = gen_number(); //setting number_ = gen_number() because static method as gen_number()
        for (int i = 0; i < num_courses_; ++i)
        {
            grades_.push_back(gen_grade()); //total num_courses_ = 5 always, pushing back to vector<int> grades_;
        }
    }

    /*
    * print_grades() method prints member of student class name_, number_, grades_[5] using output string
    */
    void print_grades(ostream& os) const
    {
        os << "Name = " << name_ << ", Number = " << number_ << ", grades= ";
        for (int i = 0; i < num_courses_; ++i)
        {
            os << grades_[i] << ", ";
        }
        os << endl;
    }

    /*
    * friend operator<<() to print name_ and number_ using output string
    * A name is a random string (a-zA-Z0-9) between 6 and 12 characters long
    */
    friend ostream& operator<<(ostream& os, const Student& s)
    {
        os << "Name = " << s.name_ << ", Number = " << s.number_;
        return os;
    }

    /*
    * compute_average() method calculates average of the grades for each student and return the average as double
    */
    double compute_average()
    {
        double avg_grade_ = 0.00; //var to store the average value fo the grades
        if (grades_.size() != 0)  //if grades_ is not null
        {
            //go through the grades_ vector
            for (int i = 0; i < grades_.size(); i++)
            {
                avg_grade_ += grades_[i]; //sum all the grades
            }
            avg_grade_ = avg_grade_ / grades_.size(); //get the average
            return avg_grade_;
        }
    }

    /*
    * friend sort_by_name() to sort the stdudents by name in ascending order
    */
    friend bool sort_by_name(const Student& one, const Student& two);
};

/*
* friend sort_by_name() to sort the stdudents by name in ascending order
* takes Student class as parameters twice as pass by reference to compare the values
*/
bool sort_by_name(const Student& one, const Student& two)
{
    return (one.number_ < two.number_);
}

int main(int argc, char* argv[])
{
    srand(time(NULL)); //initialize random seed

    int studentNoArg; //vars for cmd input

    //check if the cmd line has the studentNoArg
    if (argc == 2)
    {
        vector<Student> StudentRecordsVector;          //vector of Student class
        vector<pair<Student, double>> Student2DVector; //2D vector <Student, double> with student and avg garde info

        double avg_grade_by_student = 0.00; //var to store the average grades for each student

        string temp_str = argv[1];     //taking cmd line arguments and setting the varibles
        studentNoArg = stoi(temp_str); //converting cmd argument to int

        //loop to create the StudentRecordsVector based on cmd imput for number of stduents
        for (int i = 0; i < studentNoArg; ++i)
        {
            //push_back() Stddent instance with student name and number
            StudentRecordsVector.push_back(Student("temp", 123));

            //print grades for each student using public method print_grades
            Student(StudentRecordsVector.at(i)).print_grades(cout);

            //storing the calcuated average values of stduent in avg_grade_by_student var
            avg_grade_by_student = Student(StudentRecordsVector.at(i)).compute_average();

            //dispalying avg_grade_by_student
            cout << "Grade Average is: " << avg_grade_by_student << endl;
        }

        cout << endl
            << "Sorting by Name in ascending order: " << endl;
        //using STL sort() with sort_by_name()
        sort(StudentRecordsVector.begin(), StudentRecordsVector.end(), sort_by_name);

        //displying sorted StudentRecordsVector by name in ascending order
        for (int i = 0; i < StudentRecordsVector.size(); i++)
        {
            Student(StudentRecordsVector.at(i)).print_grades(cout);
        }

        //copying StudentRecordsVector to Student2DVector as student, grade info
        for (int i = 0; i < StudentRecordsVector.size(); i++)
        {
            avg_grade_by_student = Student(StudentRecordsVector.at(i)).compute_average();
            Student2DVector.push_back(make_pair(StudentRecordsVector[i], avg_grade_by_student));
        }

        //sorting Student2DVector by grades in ascending order
        sort(Student2DVector.begin(), Student2DVector.end(), [](const pair<Student, double>& left, const pair<Student, double>& right) {
            return left.second < right.second;
            });

        cout << endl
            << "Sorting by average grade in ascending order:" << endl;
        cout << "Name \t  \t  Number \t\t Average Grade" << endl;
        //displying sorted StudentRecordsVector by average grades in ascending order
        for (int i = 0; i < Student2DVector.size(); i++)
        {
            cout << Student2DVector[i].first << "\t" << Student2DVector[i].second << endl;
        }

        //displaying student record with the highest average grade
        cout << endl
            << "Student record with the highest Grade:" << endl;
        cout << "Name \t \t  Number \t \t Average Grade" << endl;
        int n = Student2DVector.size(); //getting Student2DVector size

        //since Student2DVector is alreday sorted by average grade in ascending order, last element will have the highest average grade
        cout << Student2DVector[n - 1].first << "\t" << Student2DVector[n - 1].second << endl;

        /* Second method to get the Student record with the highest grade:
        * using stl max_element, return the element with the gighest grade
        */

        // cout << endl << "Student record with the highest Grade:" << endl;
        // auto highestgrade = max_element(Student2DVector.begin(), Student2DVector.end(), [](pair<Student, double>& prod1, pair<Student, double>& prod2)
        //     {
        //         return (prod1.second < prod2.second);
        //     });
        // cout << endl << highestgrade->first <<  "\t" << highestgrade->second << endl;
    }
    else //else error for invalid number for cmd input
    {
        cout << "Invalid command. \nPlease try again.\nMake sure to add student#.\n";
    }
    return 0;
}