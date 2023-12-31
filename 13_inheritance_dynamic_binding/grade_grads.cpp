// g++ grade_grads.cpp student_info.cpp -o grade_grads && ./grade_grads < "grads.csv"

#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include "student_info.h"

using namespace std;

int main()
{
    vector<Grad> students; // different type in the vector
    Grad record;           // different type into which to read
    string::size_type maxlen = 0;
    // read and store the data
    while (record.read(cin))
    { // read from Grad, not Core
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
    // alphabetize the student records
    sort(students.begin(), students.end(), compare);
    // write the names and grades
    for (vector<Grad>::size_type i = 0; i != students.size(); ++i)
    {
        cout << students[i].name()
             << string(maxlen + 1 - students[i].name().size(), ' ');
        try
        {
            double final_grade = students[i].grade(); // Grad::grade
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        }
        catch (domain_error e)
        {
            cout << e.what() << endl;
        }
    }
    return 0;
}