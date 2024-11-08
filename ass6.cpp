#include <iostream>
#include <cstring>
#define max 20 //representing the maximum size of arrays.


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
        r[i][i] = 0; //r[i][i] is the root index for an empty subtree. It is set to 0 because no root exists when there are no keys. This initialization is just a placeholde
        w[i][i] = q[i];  //w[i][i] represents the total weight (or probability sum) of an empty subtree between positions i and i. Since there are no keys, this weight is equal to the probability of an unsuccessful search at position i, which is q[i]. This means if we search for something not found between two keys, we incur the cost q[i]
    }

    for (i = 0; i < n; i++) {
     
        w[i][i + 1] = p[i + 1] + q[i] + q[i + 1]; //If i = 0, we have a subtree from K1 to K1
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
                float cost = c[i][k - 1] + c[k][j] + w[i][j];//c[i][k - 1]: Cost of the left subtree.c[k][j]: Cost of the right subtree.w[i][j]: Weight of the current subtree.
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

/*Enter the number of keys in the tree: 3

Enter the probability of successful search (p[i]):
p[1]: 0.15
p[2]: 0.10
p[3]: 0.5

Enter the probability of unsuccessful search (q[i]):
q[0]: 0.5
q[1]: 0.10
q[2]: 0.5
q[3]: 0.5
Table of OBST:
_____________

Weight table :
w[0][0] = 0.5   w[0][1] = 0.75  w[0][2] = 1.35  w[0][3] = 2.35
w[1][1] = 0.1   w[1][2] = 0.7   w[1][3] = 1.7
w[2][2] = 0.5   w[2][3] = 1.5
w[3][3] = 0.5

Cost table:
c[0][0] = 0     c[0][1] = 0.75  c[0][2] = 2.05  c[0][3] = 4.4
c[1][1] = 0     c[1][2] = 0.7   c[1][3] = 2.4
c[2][2] = 0     c[2][3] = 1.5
c[3][3] = 0

Root table :
r[0][0] = 0     r[0][1] = 1     r[0][2] = 1     r[0][3] = 3
r[1][1] = 0     r[1][2] = 2     r[1][3] = 3
r[2][2] = 0     r[2][3] = 3
r[3][3] = 0

Cost of Optimal BST:  4.4*/