// #include <cstdlib>
#include <iostream> // including/importing various libraries
#include <string>
#include <random>

#include "student.h" // include student object file

using namespace std;

float randomRan(int min, int max) {
    return min + (int64_t) (rand() / (double) (RAND_MAX + 1.0) * (max - min + 1)); // finds a random number between min and max
}

float randomX() { // uses the randomRan method to find a random number between 0 and 1
    float a = randomRan(0, 9999999);
    return a / 10000000;
}

int main() {
    srand((unsigned)time(NULL)); // sets a random seed for the random number generator

    int runs = 30000; // number of times simulation is run

    int days_student_1_sick = 0; // counter for the times a certain student (just chose student 1) got sick
    int days_num_sick = 0; // counter for times more than 10 people got sick

    // ====================================================================================================
    // START OF SIMULATION, runs "runs" times
    // ====================================================================================================
    for(int d = 0; d < runs; d++) { // for loop to run through all simulations

        student arr[300]; // initializes array of student objects
        arr[0].sick = true; // sets student 0 as the first sick person

        int num_sick = 1; // start counter for number of people sick
        int i = 0; // start counter for days in a single simulation
        bool student_1_sick = false; // boolean if student 1 (random student that we chose) gets sick
        bool passed_if_1 = false; // boolean if student 1 got sick
        bool passed_if_2 = false; // boolean if 10 or more people got sick

        // RUNS ACTUAL SIMULATION
        while(num_sick >= 1 && (!passed_if_1 || !passed_if_2)) {
            cout << "Day " << i << ":" << endl; // prints the day in simulation

            for(int j = 0; j < 300; j++) { // runs through each student in simulation

                if(arr[j].sick) { // check if the student is sick

                    if(arr[j].days_sick > 3 && arr[j].days_sick <= 5) { // if the sick is in his "contagious period", run below code

                        for(int h = 0; h < 300; h++) { // run through every other student for encountering in simulation
                            if(randomX() < 0.04 && j != h && arr[j].sick != arr[h].sick) { // chance to encounter someone 
                                if(randomX() < 0.05) { // chance they get infected
                                    arr[h].sick = true; // sets that student to sick if they get infected
                                }
                            }
                        }
                    }

                    arr[j].days_sick++; // increments number of days sick in the students object

                    if(arr[j].days_sick == 6) { // once student has been sick for 5 days, they become not sick
                        arr[j].sick = false;
                        arr[j].days_sick = 0; // reset days_sick field in students object
                    }
                }
            }

            num_sick = 0; // simply counts how many students were sick at the end of the day 
            for(int j = 0; j < 300; j++) {
                if(arr[j].sick) {
                    num_sick++;
                }
            }

            cout << "Number sick after day " << i << " is " << num_sick << endl; // prints out number sick after a certain day
            cout << endl; // print statement for cleaning up output

            if(arr[1].sick && !passed_if_1) { // checks if our random student (student 1) got sick
                student_1_sick = true;
                cout << "Student 1 got sick!" << endl; // prints out status for certain simulation
                days_student_1_sick++;
                passed_if_1 = true; // sets the boolean if student 1 got sick to true
            }

            if(num_sick > 10 && !passed_if_2) { // checks if at least 10 students got sick
                days_num_sick++;
                cout << "More than 10 students got sick!" << endl; // prints out status for certain simulation
                passed_if_2 = true; // sets the boolean if at least 10 students got sick to true
            }

            i++; // increments day counter by 1
        }
    }
    // ====================================================================================================
    // END OF SIMULATION
    // ====================================================================================================

    cout << "Probability Student 1 gets sick is " << (double) days_student_1_sick / (double) runs << endl; // prints out cumulative probability of student 1 getting sick for every simulation
    cout << "Probability 10 or more students get sick is " << (double) days_num_sick / (double) runs << endl; // prints out cumulative probability of at least 10 students getting sick for every simulation
}