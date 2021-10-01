#include <string>
#include "random.h"
#include "chromosome.h"
#include "population.h"
#include "mpi.h"

using namespace std;
 
int main (int argc, char *argv[]) {
    
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat1, stat2;
    
    // double tstart = MPI_Wtime();
    
    // stesso seme ma prendo diversi numeri in Primes per ogni processo
    Random * rnd = new Random();
    int seed[4];
    int p1, p2;
    ifstream Primes("Primes");
    if (Primes.is_open()) {
        for (int i=0; i<rank+1; i++) Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()) {
        while ( !input.eof() ) {
            input >> property;
            if( property == "RANDOMSEED" ) {
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd->SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
    
    unsigned int N = 32;
    double l = 1.;
    double p = 2;
    unsigned int n_chrom = 100;

    if (rank==0) {
        cout << endl << "TRAVELING SALESMAN PROBLEM - Parallel Genetic Algorithm"  << endl;
        cout << "32 Cities inside a square of side L = " << l << endl << endl;
    }
    
    int N_migr = 100;
    
    Population S(rnd, n_chrom, p);
    S.First_Pop_Square(N,l);
    
    cout << "Rank " << rank << ": popolazione iniziale creata" << endl;
    
    S.Print_on_File("first_generation" + to_string(rank+1) + ".out");
    
    ofstream Best_S("bp_length_square" + to_string(rank+1) + ".out");
    
    int ranks[4];
    int itag[4];
    for (int j=0; j<size; j++) {
        ranks[j]=j;
        itag[j]=j+1;
    }
    
    int M_s = 2000;
    for (int i=1; i<=M_s; i++) {
        S.New_Pop();
        
        if (i%N_migr==0) {
            
            // permutazione casuale nel vettore ranks
            if (rank==0) {
                for (int i=size-1; i>0; i--) {
                    // Pick a random index from 0 to i
                    int j = int(rnd->Rannyu(0,i+1));
                    // Swap ranks[i] with the element at random index
                    swap(ranks[i], ranks[j]);
                }
            }
            MPI_Bcast(&ranks, 4, MPI_INTEGER, 0, MPI_COMM_WORLD); // ora ranks cambia per tutto
            
            int imesg1[N];
            int imesg2[N];
            int imesg3[N];
            int imesg4[N];
            vector<int> best1;
            vector<int> best2;
            vector<int> best3;
            vector<int> best4;
            
            if (rank==ranks[0]) {
                best1 = S.Get_Best();
                for (int i=0; i<N; i++) imesg1[i] = best1[i];
            }
            if (rank==ranks[1]) {
                best2 = S.Get_Best();
                for (int i=0; i<N; i++) imesg2[i] = best2[i];
            }
            if (rank==ranks[2]) {
                best3 = S.Get_Best();
                for (int i=0; i<N; i++) imesg3[i] = best3[i];
            }
            if (rank==ranks[3]) {
                best4 = S.Get_Best();
                for (int i=0; i<N; i++) imesg4[i] = best4[i];
            }
            
            if (rank==ranks[0]) {
                MPI_Send(&imesg1[0], N, MPI_INTEGER, ranks[1], itag[ranks[0]], MPI_COMM_WORLD);
                MPI_Recv(&imesg2[0], N, MPI_INTEGER, ranks[1], itag[ranks[1]], MPI_COMM_WORLD, &stat1);
                for (int i=0; i<N; i++) best1[i]=imesg2[i];
                S.Change_Chrom(best1,0);
                S.Sort();
            }
            if (rank==ranks[1]) {
                MPI_Send(&imesg2[0], N, MPI_INTEGER, ranks[0], itag[ranks[1]], MPI_COMM_WORLD);
                MPI_Recv(&imesg1[0], N, MPI_INTEGER, ranks[0], itag[ranks[0]], MPI_COMM_WORLD, &stat2);
                for (int i=0; i<N; i++) best2[i]=imesg1[i];
                S.Change_Chrom(best2,0);
                S.Sort();
            }
            if (rank==ranks[2]) {
                MPI_Send(&imesg3[0], N, MPI_INTEGER, ranks[3], itag[ranks[2]], MPI_COMM_WORLD);
                MPI_Recv(&imesg4[0], N, MPI_INTEGER, ranks[3], itag[ranks[3]], MPI_COMM_WORLD, &stat1);
                for (int i=0; i<N; i++) best3[i]=imesg4[i];
                S.Change_Chrom(best3,0);
                S.Sort();
            }
            if (rank==ranks[3]) {
                MPI_Send(&imesg4[0], N, MPI_INTEGER, ranks[2], itag[ranks[3]], MPI_COMM_WORLD);
                MPI_Recv(&imesg3[0], N, MPI_INTEGER, ranks[2], itag[ranks[2]], MPI_COMM_WORLD, &stat2);
                for (int i=0; i<N; i++) best4[i]=imesg3[i];
                S.Change_Chrom(best4,0);
                S.Sort();
            }
        } 
        Best_S << i << " " << S.Best_Path_Length() << endl;
    }
    
    S.Print_Best_Path("final_path" + to_string(rank+1) + ".out");
    
    rnd->SaveSeed();
    delete rnd;
    
    // double tend = MPI_Wtime();
    // double dt = tend - tstart;
    
    // cout << "io sono " << rank << "; tempo = " << dt << endl;
    
    MPI_Finalize();
    
    cout << "Rank " << rank << " has finished!\n";
    return 0;
    
}
