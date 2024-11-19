#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // for min function

using namespace std;

class Candidate {
public:
    string name;
    string email;
    string phone;
    int cgpa;                // CGPA out of 10
    string projects;         // Relevant projects
    int resumeScore;         // Resume score derived from projects and CGPA
    int telephonicScore;     // Telephonic score out of 100
    int technicalRound1;     // Score for Technical Round 1
    int technicalRound2;     // Score for Technical Round 2
    bool step1Qualified;     // Qualified in Resume Shortlisting
    bool step2Qualified;     // Qualified in Telephonic Round
    bool round1Qualified;    // Qualified in Technical Round 1

    Candidate(string n, string e, string p, int c, string prj)
        : name(n), email(e), phone(p), cgpa(c), projects(prj), resumeScore(0), telephonicScore(0),
          technicalRound1(0), technicalRound2(0), step1Qualified(false), step2Qualified(false), round1Qualified(false) {}

    void evaluateResume() {
        // Projects carry more weight than CGPA
        if (projects.length() > 10) { // Substantial project description
            resumeScore = min(100, cgpa * 7 + 30); // Projects get higher weight
        } else {
            resumeScore = min(100, cgpa * 10); // Default CGPA-based score
        }
        if (resumeScore >= 60) {
            step1Qualified = true;
        }
    }
};

class Google {
    vector<Candidate> candidates;
    map<int, string> interviewerPool;

public:
    Google() {
        interviewerPool[90] = "Interviewer A (Expert in AI/ML)";
        interviewerPool[80] = "Interviewer B (Senior Engineer)";
        interviewerPool[70] = "Interviewer C (Mid-Level Engineer)";
        interviewerPool[60] = "Interviewer D (Entry-Level Engineer)";
    }

    void addCandidate() {
        string name, email, phone, projects;
        int cgpa;

        cout << "\nEnter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter CGPA (out of 10): ";
        cin >> cgpa;
        cin.ignore();
        cout << "Enter Project Details: ";
        getline(cin, projects);

        candidates.push_back(Candidate(name, email, phone, cgpa, projects));
        cout << "Candidate added successfully!\n";
    }

    void evaluateResumes() {
        cout << "\nEvaluating Resumes...\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            candidates[i].evaluateResume();
            cout << "\nCandidate: " << candidates[i].name
                 << "\n**Projects**: " << candidates[i].projects
                 << "\nCGPA: " << candidates[i].cgpa
                 << "\nResume Score: " << candidates[i].resumeScore
                 << "\nStatus: " << (candidates[i].step1Qualified ? "Qualified" : "Disqualified") << "\n";
        }
    }

    void conductTelephonicRound() {
        cout << "\nConducting Telephonic Round...\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (!candidates[i].step1Qualified) {
                cout << candidates[i].name << " is disqualified from Step 1 and cannot proceed to Step 2.\n";
                continue;
            }

            cout << "\nTelephonic Interview for " << candidates[i].name << "...\n";
            int score;
            cout << "Enter Telephonic Score (out of 100): ";
            cin >> score;
            candidates[i].telephonicScore = score;

            if (candidates[i].telephonicScore >= 60) {
                candidates[i].step2Qualified = true;
            } else {
                cout << candidates[i].name << " did not qualify for Technical Round 1.\n";
            }
        }
    }

    void conductTechnicalRound1() {
        cout << "\nConducting Technical Round 1...\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (!candidates[i].step2Qualified) {
                cout << candidates[i].name << " did not qualify for Technical Round 1.\n";
                continue;
            }

            cout << "\nTechnical Round 1 for " << candidates[i].name << "...\n";
            int score;
            cout << "Enter Technical Round 1 Score (out of 100): ";
            cin >> score;
            candidates[i].technicalRound1 = score;

            if (candidates[i].technicalRound1 >= 60) {
                candidates[i].round1Qualified = true;
            } else {
                cout << candidates[i].name << " did not qualify for Technical Round 2.\n";
            }
        }
    }

    void conductTechnicalRound2() {
        cout << "\nConducting Technical Round 2...\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (!candidates[i].round1Qualified) {
                cout << candidates[i].name << " did not qualify for Technical Round 2.\n";
                continue;
            }

            cout << "\nTechnical Round 2 for " << candidates[i].name << "...\n";
            int score;
            cout << "Enter Technical Round 2 Score (out of 100): ";
            cin >> score;
            candidates[i].technicalRound2 = score;
        }
    }

    void displayResults() {
        cout << "\nFinal Results:\n";
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (!candidates[i].step1Qualified || !candidates[i].step2Qualified || !candidates[i].round1Qualified) {
                continue;
            }

            int avgTechScore = (candidates[i].technicalRound1 + candidates[i].technicalRound2) / 2;

            if (avgTechScore >= 70) {
                cout << "Congratulations " << candidates[i].name << "! You have cleared all rounds.\n";
            } else {
                cout << candidates[i].name << " did not qualify in the technical interviews.\n";
            }
        }
    }
};

void menu() {
    Google google;
    int choice;

    do {
        cout << "\n================= Google STEP Interview Simulation =================\n";
        cout << "1. Add Candidate\n";
        cout << "2. Evaluate Resumes\n";
        cout << "3. Conduct Telephonic Round\n";
        cout << "4. Conduct Technical Round 1\n";
        cout << "5. Conduct Technical Round 2\n";
        cout << "6. Display Final Results\n";
        cout << "7. Exit\n";
        cout << "====================================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                google.addCandidate();
                break;
            case 2:
                google.evaluateResumes();
                break;
            case 3:
                google.conductTelephonicRound();
                break;
            case 4:
                google.conductTechnicalRound1();
                break;
            case 5:
                google.conductTechnicalRound2();
                break;
            case 6:
                google.displayResults();
                break;
            case 7:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}
