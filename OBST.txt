#include <iostream>
#include <cstring>
#define max 20

using namespace std;

int i, j, k, n, min_cost, r[max][max];
float p[max], q[max], w[max][max], c[max][max];
string leaf[max];

void OBST();      

void print_tab();  

int main() {
    cout << "\nEnter the number of keys in the tree: ";
    cin >> n;

     cout << "\nEnter the probability of successful search (p[i]):\n";
    for (i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

   
    cout << "\nEnter the probability of unsuccessful search (q[i]):\n";
    for (i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }

    OBST();
    print_tab();
   
    return 0;
}


void OBST() {
    for (i = 0; i <= n; i++) {
       
        c[i][i] = 0;  
        r[i][i] = 0;
        w[i][i] = q[i];  
    }

    for (i = 0; i < n; i++) {
     
        w[i][i + 1] = p[i + 1] + q[i] + q[i + 1];
        c[i][i + 1] = w[i][i + 1];
        r[i][i + 1] = i + 1;  
    }

    w[n][n] = q[n];
    c[n][n] = 0;
    r[n][n] = 0;

    for (int m = 2; m <= n; m++) {
        for (i = 0; i <= n - m; i++) {
            j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

       
            c[i][j] = 99999;

       
            for (k = i + 1; k <= j; k++) {
                float cost = c[i][k - 1] + c[k][j] + w[i][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;  
                    r[i][j] = k;    
                }
            }
        }
    }
}





void print_tab() {
    cout << "Table of OBST:\n";
    cout << "_____________\n";

   
    cout << "\nWeight table :\n";
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++) {
            cout << "w[" << i << "][" << j << "] = " << w[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\nCost table:\n";
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++) {
            cout << "c[" << i << "][" << j << "] = " << c[i][j] << "\t";
        }
        cout << "\n";
    }

   
    cout << "\nRoot table :\n";
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++) {
            cout << "r[" << i << "][" << j << "] = " << r[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\nCost of Optimal BST:  " << c[0][n] << "\n";
 
}

