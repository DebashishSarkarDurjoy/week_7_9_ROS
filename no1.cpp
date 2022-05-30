#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct VarInd {
    static int objectCount;
    string string_name;
    int int_index;

    VarInd(string name) {
        string_name = name;
        int_index = objectCount;
        objectCount++;
    }

    int showIndex()
};
int VarInd::objectCount = 1;

vector<VarInd> var_vect;

int total_clause = 0;
int total_variable = 0;

bool isUnique(VarInd target) {
    for (auto atom: var_vect) {
        if (atom.string_name == target.string_name) {
            return false;
        }
    }
    return true;
}

void f_one_num_grid(int boardSize) {
    // cout << "F_One_Num_Grid: " << endl;
    string name;
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            for (int k = 1; k <= boardSize; k++) {

                for (int l = 1; l <= 9; l++) {
                    if (l == k) continue;
                    cout << "-G_" << i << "_" << j << "_" << k << " ";
                    name = "G_" + to_string(i) + "_" + to_string(j) + "_" + to_string(k);
                    VarInd atom1(name);
                    if (isUnique(atom1)) var_vect.push_back(atom1);

                    // cout << "-G_" << i << "_" << j << "_" << l << " ";
                    // name = "-G_" + to_string(i) + "_" + to_string(j) + "_" + to_string(k);
                    // VarInd atom2(name);
                    if (isUnique(atom2)) var_vect.push_back(atom2);
                    cout << "-" << atom1.showIndex(name);
                    // cout << endl;
                    total_clause++;
                }
                // cout << endl;
                total_clause++;
            }
        }
    }
    // cout << endl;
}

void f_subgrid_to_grid(int boardSize, int subGridSize) {
    // cout << "Subgrid to Grid: " << endl;
    for (int si = 1; si <= subGridSize; si++) {
        for (int sj = 1; sj <= subGridSize; sj++) {
            for (int num = 1; num <= boardSize; num++) {
                string SB = "-SB_" + to_string(si) + "_" + to_string(sj) + "_" + to_string(num);
                VarInd atom2(SB);
                var_vect.push_back(atom2);
                // cout << "-SB_" << si << "_" << sj << "_" << num << " ";

                for (int gi = (si*3) - 3 + 1; gi <= si*3; gi++) {
                    for (int gj = (sj*3) - 3 + 1; gj <= sj*3; gj++) {
                        string name = "G_" + to_string(gi) + "_" + to_string(gj) + "_" + to_string(num);
                        VarInd atom(name);
                        var_vect.push_back(name);
                        total_variable++;
                        // cout << "G_" << gi << "_" << gj << "_" << num << " ";

                    }
                }
                // cout << endl;
                total_clause++;
            }
        }
    }
    // cout << endl;
}

void f_row_to_grid(int boardSize) {
    // cout << "F_Row_To_Grid: " << endl;
    // cout << "Row to Grid: " << endl;;
    for (int i = 1, r_j = 1; i <= boardSize; i++, r_j++) {
        string R = "-R_" + to_string(i) + "_" + to_string(r_j);
        VarInd atom1(R);
        var_vect.push_back(atom1);
        // cout << "-R_" << i << "_" << r_j << " ";
        for (int j = 1; j <= boardSize; j++) {
            string G = "G_" + to_string(i) + "_" + to_string(j) + "_" + to_string(r_j);
            VarInd atom2(G);
            var_vect.push_back(atom2);
            total_variable++;
            // cout << "G_" << i << "_" << j << "_" << r_j << " " ;
        }
        // cout << endl;
        total_clause++;
    }
    // cout << endl;
}

void f_col_to_grid(int boardSize) {
    // cout << "F_Col_To_Grid: " << endl;
    // cout << "Col to Grid: " << endl;
    for (int i = 1, c_j = 1; i <= boardSize; i++, c_j++) {
        string C = "-C_" + to_string(i) + "_" + to_string(c_j);
        VarInd atom1(C);
        var_vect.push_back(atom1);
        // cout << "-C_" << i << "_" << c_j << " ";
        for (int j = 1; j <= boardSize; j++) {
            string G = "G_" + to_string(j) + "_" + to_string(i) + "_" + to_string(c_j);
            VarInd atom2(G);
            var_vect.push_back(atom2);
            total_variable++;
            // cout << "G_" << j << "_" << i << "_" << c_j << " ";
        }
        // cout << endl;
        total_clause++;
    }
    // cout << endl;
}

void f_mentions(int boardSize, int subGridSize) {
    // cout << "F_Mentions: ";
    // cout << endl;

    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            string name = "R_" + to_string(i) + "_" + to_string(j);
            VarInd atom(name);
            var_vect.push_back(atom);
            total_variable++;
            // cout << "R_" << i << "_" << j << " ";
        }
        // cout << endl;
        total_clause++;
    }

    cout << endl;
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            string name = "C_" + to_string(j) + "_" + to_string(i);
            VarInd atom(name);
            var_vect.push_back(atom);
            total_variable++;
            // cout << "C_" << j << "_" << i << " ";
        }
        // cout << endl;
        total_clause++;
    }

    // cout << endl;
    for (int si = 1; si <= subGridSize; si++) {
        for (int sj = 1; sj <= subGridSize; sj++) {
            for (int num = 1; num <= boardSize; num++) {
                string name = "SB_" + to_string(si) + "_" + to_string(sj) + "_" + to_string(num);
                VarInd atom(name);
                var_vect.push_back(atom);
                total_variable++;
                // cout << "SB_" << si << "_" << sj << "_" << num << " ";

            }
            // cout << endl;
            total_clause++;
        }
    }

    // cout << endl;
}



void custom_unit_clauses(vector<vector<int>> &board) {
    int n = board.size();
    int m = board[0].size();

    int num = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] != 0) {
                // cout << "G_" << i+1 << "_" << j+1 << "_" << num << endl;
                string atom = "G_" + to_string(i+1) + "_" + to_string(j+1) + "_" + to_string(num);
                VarInd temp(atom);
                if (isUnique(temp)) var_vect.push_back(temp);
                total_variable++;
                total_clause++;
            }

        }
    }
}

int main(void) {
    int boardSize = 9;
    int subGridSize = 3;


    f_mentions(boardSize, subGridSize); // (1)
    f_row_to_grid(boardSize); // (2)
    f_col_to_grid(boardSize); // (3)
    f_subgrid_to_grid(boardSize, subGridSize); // (4)
    f_one_num_grid(boardSize); // (5)

    vector<vector<int>> board(boardSize, vector<int> (boardSize, 0));
    board = {
        {5, 0, 0, 1, 2, 0, 6, 0, 4},
        {0, 0, 0, 0, 0, 8, 2, 9, 3},
        {0, 0, 0, 4, 0, 0, 0, 7, 0},
        {0, 0, 2, 6, 8, 5, 4, 1, 0},
        {8, 0, 5, 0, 7, 0, 9, 0, 6},
        {0, 6, 7, 9, 4, 2, 3, 0, 0},
        {0, 7, 0, 0, 0, 6, 0, 0, 0},
        {2, 8, 6, 7, 0, 0, 0, 0, 0},
        {3, 0, 1, 0, 9, 4, 0, 0, 2},
    };

    custom_unit_clauses(board);

    cout << "Output from var vect\n";
    // cout << "p " << "cnf " << total_clause << " " << total_variable << endl;
    for (auto atom: var_vect) {
        cout << atom.int_index << " ";

    }

}
