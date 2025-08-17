#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    while (true) {
        char process_type;
        cout << "\nSelect process type: Windows (W), Linux (L), Quit (Q): ";
        cin >> process_type;
        cin.ignore(); // remove leftover newline

        if (process_type == 'Q' || process_type == 'q') {
            cout << "Exiting program.\n";
            break;
        }

        string list_cmd, kill_base_cmd;
        if (process_type == 'W' || process_type == 'w') {
            cout << "\nRunning Windows processes:\n";
            list_cmd = "tasklist.exe";
            kill_base_cmd = "taskkill.exe /PID ";
        } else if (process_type == 'L' || process_type == 'l') {
            cout << "\nRunning Linux processes:\n";
            list_cmd = "ps aux";
            kill_base_cmd = "kill -9 ";
        } else {
            cout << "Invalid choice. Try again.\n";
            continue; // back to menu
        }

        while (true) {
            system(list_cmd.c_str()); // show processes

            string input;
            cout << "\nEnter PID(s) to kill (space-separated), 'M' to change menu: ";
            getline(cin, input);

            if (input.empty() || input == "M" || input == "m") {
                break; // go back to main menu
            }

            stringstream ss(input);
            vector<int> pids;
            int pid;
            while (ss >> pid) pids.push_back(pid);

            if (pids.empty()) {
                cout << "No valid PIDs entered.\n";
                continue;
            }

            for (int pid : pids) {
                string kill_cmd = kill_base_cmd + to_string(pid);
                if (process_type == 'W') kill_cmd += " /F";

                int result = system(kill_cmd.c_str());
                if (result == 0) {
                    cout << "Process " << pid << " killed.\n";
                } else {
                    cout << "Failed to kill process " << pid << ".\n";
                }
            }
        }
    }

    return 0;
}
