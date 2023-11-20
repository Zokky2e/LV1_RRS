#include <stdio.h>
#include <mpi.h>
#include <string>
int main(int argc, char* argv[]) {
	const char* filename = "test.txt";
	FILE* fp = fopen(filename, "a+");
	if (fp == NULL)
	{
		printf("Error opening the file %s", filename);
		return -1;
	}
	MPI_Init(&argc, &argv); //inicijaliziraj MPI
	char name;
	int reslen;
	MPI_Get_processor_name(&name, &reslen);
	int velicina;
	MPI_Comm_size(MPI_COMM_WORLD, &velicina);
	int rang;
	MPI_Comm_rank(MPI_COMM_WORLD, &rang);
	char subcommunicator;
	int colour;
	int key;
	if (rang % 2 == 0)
	{
		subcommunicator = 'A';
		colour = 0;
		key = rang;
	}
	else
	{
		subcommunicator = 'B';
		colour = 1;
		key = velicina - rang;
	}
	MPI_Comm komSplit;
	MPI_Comm_split(MPI_COMM_WORLD, colour, key, &komSplit);
	int kom1;
	MPI_Comm_rank(komSplit, &kom1);
	int velicina1;
	MPI_Comm_size(komSplit, &velicina1);
	fprintf(fp, "P%d od %d se izvršava na procesoru %d. Na komunikatoru %c: rang %d od %d\n", rang, velicina, name, subcommunicator, kom1, velicina1);
	MPI_Finalize();
	fclose(fp);
	return 0;
}
