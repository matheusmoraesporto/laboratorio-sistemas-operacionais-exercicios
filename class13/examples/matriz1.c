/* matriz.c */
#define TAM 3000
int main( ) {
 int i, j;
 unsigned char mat[TAM][TAM];
 for(i=0; i<TAM; i++)
 for(j=0; j<TAM; j++)
 mat[i][j] = '1';
 return 0;
}
