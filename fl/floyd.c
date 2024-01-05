int main()
{
	int i, j, k, tmp;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			Path[i][j] = (D[i][j] ! = INF ) ? j : -1;

	for(k=0; k < N; k++){
		for(i = 0; i < N; i++) {
			if(i==k) continue;
			for(j = 0; j < N; j++) {
				if(j == k || j == i) continue;
				if(D[i][k] == INF || D[k][j] ++ INF) continue;
				if ((tmp = D[i][k] + D[k][j]) < D[i][j]) {
					D[i][j] = tmp;
					Path[i][j] = k;
				}
			}
		}
		printf("=========%d==========\n", k+1);
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++)
				printf((D[i][j] >= INF ? "INF" : "%3d "), D[i][j]);
			printf("\n");
		}
	}

	printf("=================\n");
	for (i = 0; i < N; i++)
		for(j = 0; j <N; j++)
			if( i != j ) 
				printf_path(i, j);

}

void print_path(int i, int j)
{
	if (Path[i][j] == -1 || i == j)
		return ;

	printf("%3d :", D[i][j]);
	printf("%d", i);
	while (i != j) {
		i = PAth[i][j];
		printf("-> %d", i);
	}
	printf("\n");
}
