#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Calculate letter grade by distance from exam average score
const char letterGrade(double examAverage, double studentScore) {
    double distFromAvg = examAverage - studentScore;
    char studentGrade;
    if (distFromAvg >= 15) {
        studentGrade = 'E';
    }
    else if (distFromAvg > 5 && distFromAvg < 15) {
        studentGrade = 'D';
    }
    else if (distFromAvg >= -5 && distFromAvg <= 5) {
        studentGrade = 'C';
    }
    else if (distFromAvg > -15 && distFromAvg < -5) {
        studentGrade = 'B';
    }
    else {
        studentGrade = 'A';
    }
    return studentGrade;
}

int main(int argc, const char * argv[]) {
    const char letterGrades[] = {'A', 'B', 'C', 'D', 'E'};
    // Read Files
    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in)  {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    ofstream out(argv[2]);
    
    // Create Storage Arrays
    int numStudents = 0;
    int numExams = 0;
    in >> numStudents;
    in >> numExams;
    in.ignore(numeric_limits<int>::max(), '\n');
    
    string *studentNames = new string[numStudents];
    double **studentScores = new double*[numStudents];
    for (int i = 0; i < numStudents; i++) {
        studentScores[i] = new double[numExams];
    }
    
    // Fill Out Names and Exam Scores
    for (int i = 0; i < numStudents; i++) {
        string firstName, lastName;
        in >> firstName >> lastName;
        studentNames[i] = firstName + " " + lastName;
        
        for (int j = 0; j < numExams; j++) {
            in >> studentScores[i][j];
        }
    }
    
    // Output Scores
    out << "Student Scores:" << endl;
    for (int i = 0; i < numStudents; i++) {
        out << setw(20) << studentNames[i];
        for (int j = 0; j < numExams; j++) {
            out << setw(6) << studentScores[i][j];
        }
        out << endl;
    }
    
    // Print and Store Averages
    out << "Exam Averages:" << endl;
    double examAverages[numExams];
    for (int i = 0; i < numExams; i++) {
        out << setw(21) << "Exam " + to_string(i + 1) + " Average = ";
        double examTotal = 0.0;
        
        for (int j = 0; j < numStudents; j++) {
            examTotal += studentScores[j][i];
        }
        examAverages[i] = examTotal / numStudents;
        out << setw(6) << fixed << setprecision(1) << examAverages[i] << endl;
    }
    
    // Print and Store Exam Grades
    out << "Student Exam Grades:" << endl;
    int numGrades[numExams][5];
    for (int i = 0; i < numExams; i++) {
        for (int j = 0; j < 5; j++) {
            numGrades[i][j] = 0;
        }
    }
    for (int i = 0; i < numStudents; i++) {
        out << setw(20) << studentNames[i];
        for (int j = 0; j < numExams; j++) {
            char studentGrade = letterGrade(examAverages[j], studentScores[i][j]);
            switch (studentGrade) {
                case 'A':
                    numGrades[j][0]++;
                    break;
                case 'B':
                    numGrades[j][1]++;
                    break;
                case 'C':
                    numGrades[j][2]++;
                    break;
                case 'D':
                    numGrades[j][3]++;
                    break;
                case 'E':
                    numGrades[j][4]++;
            }
            out << setw(7) << fixed << setprecision(0) << studentScores[i][j] << "(" << studentGrade << ")";
        }
        out << endl;
    }
    
    // Print Exam Totals
    out << "Exam Grades:" << endl;
    for (int i = 0; i < numExams; i++) {
        out << setw(11) << "Exam  " + to_string(i + 1);
        for (int j = 0; j < 5; j++) {
            out << setw(8) << to_string(numGrades[i][j]) + "(" + letterGrades[j] + ")";
        }
        out << endl;
    }
    
    // Student Final Grades
    out << "Student Final Grades:" << endl;
    double finalScores[numStudents];
    double classTotalScore = 0.0, classAverage = 0.0;
    
    for (int i = 0; i < numStudents; i++) {
        double totalScore = 0.0;
        for (int j = 0; j < numExams; j++) {
            totalScore += studentScores[i][j];
        }
        finalScores[i] = totalScore / numExams;
        classTotalScore += (totalScore / numExams);
    }
    classAverage = classTotalScore / numStudents;
    
    for (int i = 0; i < numStudents; i++) {
        out << setw(20) << studentNames[i] << setw(6) << fixed << setprecision(1)
            << finalScores[i] << "(" << letterGrade(classAverage, finalScores[i]) << ")" << endl;
    }
    out << "Class Average Score = " << fixed << setprecision(1) << classAverage << endl;
    
    // Free Memory
    for (int i = 0; i < numStudents; i++) {
        delete[] studentScores[i];
    }
    delete[] studentScores;
    delete[] studentNames;
    return 0;
}
