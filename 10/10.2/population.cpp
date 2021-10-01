#include "population.h"

Population :: Population (Random * rand, unsigned int n_chrom, double p) {
    m_n_chrom = n_chrom;
    m_rand = rand;
    m_p = p;
}

void Population :: Sort () {
    int p;
    for (int i=0; i<m_n_chrom-1; i++) {
        p=i;
        for (int j=i+1; j<m_n_chrom; j++) 
            if (m_pop[j].Cost()<m_pop[p].Cost()) p=j;
        swap(m_pop[i],m_pop[p]);
    }
}

void Population :: First_Pop_Square (unsigned int N, double l) {
    m_c = false;
    
    Chromosome chrom(N, m_rand);
    chrom.Set_l(l);
    chrom.Square();
    chrom.Gen_Rand();

    m_pop.push_back(chrom);
    for (int i=1; i<m_n_chrom; i++) {
        Chromosome chrom_s = chrom;
        chrom_s.Gen_Rand();
        m_pop.push_back(chrom_s);
    }
    
    Sort();
}

void Population :: New_Pop () {
        
    vector<Chromosome> NextGen;
    
    for (int k=0; k<(int)m_pop.size()/2; k++) {
        
        // Selection
        int i = int(m_n_chrom*pow(m_rand->Rannyu(),m_p));
        int j = int(m_n_chrom*pow(m_rand->Rannyu(),m_p));
        
        while (j==i) {
            j = int(m_n_chrom*pow(m_rand->Rannyu(),m_p));
        }
        
        unsigned int N = m_pop[i].Get_N();

        vector<int> g1 = m_pop[i].Get_chrom();
        vector<int> g2 = m_pop[j].Get_chrom();
        
        Chromosome f1 = m_pop[i];
        f1.Set_chrom(g1);
        Chromosome f2 = m_pop[j];
        f2.Set_chrom(g2);
        
        // Crossover
        if (m_rand->Rannyu()<0.8) {
            vector<int> s1;
            vector<int> s2;
            int M = int(m_rand->Rannyu(1,N));
            
            if (M>N) cout << M << " " << N << endl << "Problem: cut is too large" << endl;
            
            for (int s=0; s<M; s++) {
                s1.push_back(g1[s]);
                s2.push_back(g2[s]);
            }
            
            for (int s=0; s<N; s++) {
                bool cross = true;
                for (int t=0; t<M; t++) {
                    if (g2[s]==s1[t]) cross = false;
                }
                if (cross!=false) s1.push_back(g2[s]);
            }
            
            for (int s=0; s<N; s++) {
                bool cross = true;
                for (int t=0; t<M; t++) {
                    if (g1[s]==s2[t]) cross = false;
                }
                if (cross!=false) s2.push_back(g1[s]);
            }
            
            f1.Set_chrom(s1);
            f2.Set_chrom(s2);
            
            // f1.Check();
            // f2.Check();
        }
        
        // Mutations
        if (m_rand->Rannyu()<0.08) f1.Swap();
        if (m_rand->Rannyu()<0.08) f2.Swap();
        
        if (m_rand->Rannyu()<0.08) f1.Shift();
        if (m_rand->Rannyu()<0.08) f2.Shift();
        
        if (m_rand->Rannyu()<0.08) f1.Inversion();
        if (m_rand->Rannyu()<0.08) f2.Inversion();
        
        if (m_rand->Rannyu()<0.08) f1.Cycle();
        if (m_rand->Rannyu()<0.08) f2.Cycle();
        
        if (m_rand->Rannyu()<0.08) f1.Swap_Sequence();
        if (m_rand->Rannyu()<0.08) f2.Swap_Sequence();
    
        NextGen.push_back(f1);
        NextGen.push_back(f2);
            
    }
    if(NextGen.size()==m_n_chrom) m_pop = NextGen;
    else cout << "PROBLEM" << endl;
        
    Sort();
}

void Population :: Change_Chrom (vector<int> chrom, int site) {
    if (site>m_n_chrom) cout << "Problem: site too high. Site max = " << m_n_chrom-1 << endl;
    else m_pop[site].Set_chrom(chrom);
}

double Population :: Best_Path_Length () {
    return m_pop[0].Cost();

}

double Population :: Half_Best_Ave () {
    double ave=0.;
    int M = int(m_n_chrom/2.);
    for (int i=0; i<M; i++) ave += m_pop[i].Cost();
    return ave/double(M);
}

void Population :: Print_Best_Path (string filename) {
        ofstream fout(filename);
        if (!fout) cerr << "Non posso creare il file " << filename << endl;
        vector<int> best = m_pop[0].Get_chrom();
        for (int i=0; i<best.size(); i++) {
            fout << best[i] << endl;
        }
        fout.close();
}

void Population :: Print_on_File (string filename) {
    ofstream fout(filename);
    if (!fout) cerr << "Non posso creare il file " << filename << endl;
    
    for (int i=0; i<m_n_chrom; i++) {
        int N = m_pop[i].Get_N();
        vector<int> chrom = m_pop[i].Get_chrom();
        for (int j=0; j<N; j++) {
            fout << chrom[j] << " ";
        }
        fout << endl;
    }
    fout.close();
}
