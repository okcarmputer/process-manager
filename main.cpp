#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    char process_type;
    cout << "Would you like to manage Windows (W) or Linux (L) processes? ";
    cin >> process_type;
    cin.ignore(); // remove leftover newline

    while (true) {
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
            cout << "Invalid choice. Exiting.\n";
            break;
        }

        system(list_cmd.c_str());

        string input;
        cout << "\nEnter PID(s) to kill (separate with spaces, press Enter to exit): ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Exiting...\n";
            break;
        }

        stringstream ss(input);
        vector<int> pids;
        int pid;
        while (ss >> pid) {
            pids.push_back(pid);
        }
        if (pids.empty()) {
            cout << "No valid PIDs entered.\n";
            continue;
        }

        for (int pid : pids) {
            string kill_cmd = kill_base_cmd + to_string(pid);
            if (process_type == 'W') kill_cmd += " /F"; // force for Windows

            int result = system(kill_cmd.c_str());
            if (result == 0) {
                cout << "Process " << pid << " killed.\n";
            } else {
                cout << "Failed to kill process " << pid
            }
        }
    }

    return 0;
}
