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
	fprintf(fp, "P%d od %d se izvršava na procesoru %d.\n", rang, velicina, name);
	MPI_Finalize();
	fclose(fp);
	return 0;
}
