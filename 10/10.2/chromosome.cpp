#include "chromosome.h"
#include "funzioni.h"

Chromosome :: Chromosome (unsigned int N, Random* rand) {
    m_N = N;
    m_rand = rand;
    
    for (int i=0; i<m_N; i++) m_chrom.push_back(i); // creo cromosoma ordinato
    for (int i=0; i<m_N; i++) { // setto a zero la matrice delle distanze
        vector<double> dist_i(m_N,0);
        m_dist.push_back(dist_i);
    }
}

void Chromosome :: Square () {
    vector<double> x;
    vector<double> y;
    
    /*ofstream fout("init_square.dat");
    if (!fout) cerr << "Non posso creare il file init_square.dat" << endl;
    for (int i=0; i<m_N; i++) {
        x.push_back(m_rand->Rannyu(-m_l/2.,m_l/2.));
        y.push_back(m_rand->Rannyu(-m_l/2.,m_l/2.));
        fout << i << " " << x[i] << " " << y[i] << endl;
    }
    
    fout.close(); */
    
    ifstream Cit("init_square.dat");
    // ifstream Cit("init_square.dat");
    if (Cit.is_open()){
        int city;
        double x_c, y_c;
        for (int i=0; i<m_N; i++){
            Cit >> city >> x_c >> y_c;
            // cout << city << " " << x_c << " " << y_c << endl;
            m_chrom[i]=city;
            x.push_back(x_c);
            y.push_back(y_c);
        }
    } else cerr << endl <<"PROBLEM: Unable to open file " << "init_square.dat" << endl;
    Cit.close();
    
    for (int i=0; i<x.size(); i++) {
        for (int j=0; j<x.size(); j++) {
            m_dist[i][j] = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
        }
    }
}


void Chromosome :: Check () {
    vector<int> count(m_chrom.size(),0);
    if(m_chrom.size()!=m_N) cout << "Problem: l'array non ha la grandezza giusta" << endl;
    if (m_chrom[0]!=0) cout << "Problem: the first city is not at position 1" << endl;
    for (int i=0; i<m_chrom.size(); i++) count[m_chrom[i]] += 1;
    for (int i=0; i<m_chrom.size(); i++) {
        if (count[i]>1) cout << "Problem: the city " << count[i] << " appears twice" << endl;
        if (count[i]==0) cout << "Problem: the city " << count[i] << " is not present" << endl;
    }
}

double Chromosome :: Cost () {
    double cost=0.;
    for (int i=0; i<m_chrom.size(); i++) {
        if (i==m_chrom.size()-1) cost += m_dist[m_chrom[i]][m_chrom[0]]; // tragitto necessario per tornare al punto di partenza
        else cost += m_dist[m_chrom[i]][m_chrom[i+1]];
    }
    return cost;
}

void Chromosome :: Gen_Rand () {
    for (int i=m_chrom.size()-1; i>0; i--) {
        // Pick a random index from 0 to i
        int j = int(m_rand->Rannyu(1,i+1));
        // Swap arr[i] with the element
        // at random index
        swap(m_chrom[i], m_chrom[j]);
    }
}

// ============================================================
// ========================= Mutations ========================
// ============================================================


void Chromosome :: Swap () {
    int i = int(m_rand->Rannyu(1,m_N)); // posizione prima città
    int j = int(m_rand->Rannyu(1,m_N)); // posizione seconda città
    
    // if (i==0 or j==0) cout << "Problem: can't swap the first city" << endl;
    while (j==i) {
        j = int(m_rand->Rannyu(1,m_N));
    }
    swap(m_chrom[i],m_chrom[j]);
}

void Chromosome :: Inversion () {
    int m = int(m_rand->Rannyu(2,m_N)); // numero di città da invertire
    int c = int(m_rand->Rannyu(1,m_N-m)); // inzio inversione
    
    // if((m+c)>m_N) cout << "Problem: array limit exceeded" << endl;
    // if (c==0) cout << "Problem: can't swap the first city" << endl;
    
    for(int i=0; i<int(m/2); i++) {
        swap(m_chrom[c+i],m_chrom[m+c-i-1]);
    }
}

void Chromosome :: Shift () {
    int m = int(m_rand->Rannyu(1,m_N-1)); // numero di città da shiftare
    int c = int(m_rand->Rannyu(1,m_N-m-1)); // inizio shift
    int n = int(m_rand->Rannyu(2,m_N-m-c-1)); // numero di posizioni shiftate
    
    // if((m+c+n)>m_N) cout << "Problem: array limit exceeded" << endl;
    // if (c==0) cout << "Problem: can't swap the first city" << endl;
    
    for (int i=0; i<m; i++) {
        swap(m_chrom[m+c-1-i],m_chrom[m+c-i]);
        swap(m_chrom[m+c-i],m_chrom[m+c+n-1-i]);
    }
}

void Chromosome :: Cycle () {
    int m = int(m_rand->Rannyu(2,m_N)); // numero di città da permutare
    int c = int(m_rand->Rannyu(1,m_N-m)); // inizio permutazione
    
    // if((m+c)>m_N) cout << "Problem: array limit exceeded" << endl;
    // if (c==0) cout << "Problem: can't swap the first city" << endl;

    int temp = m_chrom[c]; // salvo il primo elemento

    for(int i=0; i<m; i++) {
        if(i == m-1) m_chrom[i+c] = temp; // l'ultimo elemento lo sostituisco con il primo
        else m_chrom[i+c] = m_chrom[i+c+1]; // per gli altri elementi shift a sinistra
    }
}

void Chromosome :: Swap_Sequence () {
    int m = int(m_rand->Rannyu(2,m_N/2.)); // grandezza sequenz2
    int c1 = int(m_rand->Rannyu(1,m_N-2*m)); // inizio sequenza 1
    int c2 = int(m_rand->Rannyu(m+c1,m_N-m-c1)); // inizio sequenza 2
    
    // if(m>=m_N/2.) cout << "Problem: too many cities to swap" << endl;
    // if(m+c1>=m_N) cout << "Problem: array limit exceeded" << endl;
    
    for (int i=0; i<m; i++) {
        swap(m_chrom[c1+i],m_chrom[c2+i]);
    }

}
