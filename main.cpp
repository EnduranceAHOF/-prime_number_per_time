#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]);
int prime_number(int n, int id, int p, int t);

int main(int argc, char* argv[])
{
	int id;
	int ierr;
	int n;
	int p;
	int primes;
	int primes_part;
	int tiempo;
	double wtime;

	n = 2000000000;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	cout << "Ingrese Tiempo: " << endl;
	cin >> tiempo;

	if (id == 0)
	{
		wtime = MPI_Wtime();
	}
	ierr = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	primes_part = prime_number(n, id, p,tiempo);

	ierr = MPI_Reduce(&primes_part, &primes, 1, MPI_INT, MPI_SUM, 0,
		MPI_COMM_WORLD);

	if (id == 0)
	{
		wtime = MPI_Wtime() - wtime;
        cout << " Tiempo Transcurrido al final de la operacion " << wtime << "\n";
	}
	MPI_Finalize();

	return 0;
}

int prime_number(int n, int id, int p, int tiempo)
{
	int i;
	int j;
	int prime;
	int total;
	double t1 = MPI_Wtime();;
	double t2;

	total = 0;

	for (i = 2 + id; t2 - t1 < tiempo; i = i + p)
	{
	    t2 = MPI_Wtime();
		prime = 1;
		for (j = 2; j < i; j++)
		{
			if ((i % j) == 0)
			{
				prime = 0;
				break;
			}
		}
		cout << i << endl;
		total = total + prime;
		if(t2 - t1 > tiempo){
            break;
		}
	}

	return total;
}
