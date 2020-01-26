#ifndef STUDENT_H_
#define STUDENT_H_


class student { // declaration of the student object
    public:
        student(bool infected) { // constructor that initializes student with bool infected
            sick = infected;
            days_sick = 0;
        };
        student() { // null constructor
            sick = false;
            days_sick = 0;
        }
        bool sick; // student object has 2 fields - sick which is a boolean (gives if a student is sick) and days_sick (which gives the days the student has been sick)
        int days_sick;
};

#endif