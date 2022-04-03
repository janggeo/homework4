#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*메뉴 출력후 메뉴중 한개를 입력받은후 리턴*/
char print_menu();
/* row x col사이즈의 이차원배열을 동적할당으로 생성하고 이차원포인터형을 반환 */
int** create_matrix(int row, int col);
/* 동적할당된  matrix를 free시켜준다. */
int free_matrix(int** matrix, int row, int col);
/* row x col사이즈의 matrix를 출력 */
void print_matrix(int** matrix, int row, int col);
/* rand()함수를 이용해 랜덤한값을 matrix에 할당*/
int fill_data(int** matrix, int row, int col);
/* matrix의 전치행렬을 생성*/
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int check; // 초기화 했는지 검사 변수

int main(void)
{
	printf("[----- [장정환]  [2021076029]-----]\n");
	int row,col=0;			//행과 열을 int형변수로 생성 후 초기화
	printf("Input row and col :");
	scanf("%d %d",&row,&col);
	//각 matrix동적할당으로 생성 
	int** A=create_matrix(row,col);
	int** B=create_matrix(row,col);
	int** T=create_matrix(col,row);

	printf("Matrix Created.\n");
	if (A==NULL || B==NULL || T==NULL) {return -1;}	//힙 영역에 동적할당된 주소의 반환이 제대로 안 되었을 경우 -1반환

	while(1){
		char choice=print_menu();		//메뉴출력후 선택받은 메뉴를 choice에 할당

		switch(choice){
			//동적할당된 matrixA,B에 값을 할당 
			case 'z': case'Z':
				printf("Matrix Initialized\n");
				check++; //초기화 완료
				fill_data(A,row,col);
				fill_data(B,row,col);
				break;
			//matrixA,B를 출력
			case 'p': case'P':
				printf("Print Matrix\n");
				printf("matrix_A\n");
				print_matrix(A,row,col);
				printf("matrix_B\n");
				print_matrix(B,row,col);
				break;
			//matrixA + matrixB 출력
			case 'a': case'A':
				printf("Add two matrices\n");
				addition_matrix(A,B,row,col);
				break;
		    //matrixA - matrixB 출력
			case 's': case'S':
				printf("Subtract two matrices\n");
				subtraction_matrix(A,B,row,col);
				break;
			//동적할당된 matrix T에 matrix A의 전치행렬값을 할당
			case 't': case'T':
				printf("Transpose matrix_A\n");
				transpose_matrix(A,T,col,row);
				break;
			//matrix T에 matrix A의 전치행렬 값을 할당후 matrix A * matrix T를 출력
			case 'm': case'M':
				printf("Multiply matrix_A with transposed matrix_A\n");
				transpose_matrix(A,T,col,row);
				multiply_matrix(A,T,row,col);
				break;
			//동적할당한 matrix들 free후  종료
			case 'q': case 'Q':
				printf("Free all matrices\n");
				free_matrix(A,row,col);
				free_matrix(B,row,col);
				free_matrix(T,col,row);
				return 0;
			//지정된 메뉴 이외의 값일 경우 오류 메시지 출력
			default:
				printf("\n		>>concentration<<		\n");
				break;
		}
	}
}

/*메뉴 출력후 메뉴중 한개를 입력받은후 리턴*/
char print_menu(){
	char command;
	printf("-----------------------------------------------------------------\n");
	printf("					Matrix Manipulation							 \n");
	printf("-----------------------------------------------------------------\n");
	printf(" Initialize Matrix	=z			Print Matrix		=p\n");
	printf(" Add Matrix		    =a			Subtract Matrix		=s\n");
	printf(" Transpose matrix_a	=t			Multiply Matrix		=m\n");
	printf(" Quit			    =q\n");
	printf("-----------------------------------------------------------------\n");
	printf(" Command =");
	getchar(); 				//개행문자제거를 위해 버퍼비우기
	scanf("%c",&command);	//메뉴중 하나를 입력받음
	return command;
}

/* row x col사이즈의 이차원배열을 동적할당으로 생성하고 이차원포인터형을 반환 */
int** create_matrix(int row, int col){
	if(row<=0 || col <=0){	//row와 col의 크기가 제대로 지정되지 않았을경우 NULL값 반환
		printf("check the sizes of row and col!\n");
		return NULL;	
	}

	int **matrix=(int**)malloc(sizeof(int*)*row);	//row만큼의 int*형을 동적할당
	for(int i=0;i<row;i++)
	{
		matrix[i]=(int*)malloc(col*sizeof(int));		//row크기만큼 int형을 col만큼동적할당
	}

	if(matrix==NULL){
		printf("Fail to alloc memory!\n");
		return NULL;
	}
	return matrix;	//matrix 반환
}

/* 동적할당된  matrix를 free시켜준다. */
int free_matrix(int** matrix, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix==NULL){
		printf("check the matrix!\n");
		return -1;
	}

	for(int i=0;i<row;i++){
		free(matrix[i]);	//각 row에 동적할당된 col만큼의 int 형을 free
		matrix[i]=NULL; 	//해당 메모리 해제 했음을 확실히 하기위해 포인터값을 지운다.
	}
	free(matrix);			//matrix에 동적할당된 row만큼의 int* 형을 free
	matrix=NULL;			//해당 메모리 해제 했음을 확실히 하기위해 포인터값을 지운다.
	printf("free is completed!\n");
	return 1;
}

/* row x col사이즈의 matrix를 출력 */
void print_matrix(int** matrix, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 오류메시지 출력
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");	
	}
	if(matrix==NULL){
		printf("check the matrix!\n");
	}
	//값이 초기화가 안된경우 메시지 출력
	if(check==0){
		printf("initialize first!\n");
	}
	else{
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			printf("%2d ",matrix[i][j]);	//이중for문으로 행열을 지정하여 출력
		}
		printf("\n");	//한 행을 출력후 개행
	}
	printf("\n");
	}

}

/* rand()함수를 이용해 랜덤한값을 matrix에 할당*/
int fill_data(int** matrix, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix==NULL){
		printf("check the matrix!\n");
		return -1;
	}

	srand((unsigned int)time(NULL));	//time 함수를 통해 시드값을 다르게 준다.
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix[i][j]=rand()%20;	//rnad 함수를 이용 0~19사이의 정수를 할당
		}
	}
	print_matrix(matrix,row,col);
	return 1;
}

/* matrix의 전치행렬을 생성*/
int transpose_matrix(int** matrix, int** matrix_t, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix==NULL || matrix_t==NULL){
		printf("check the matrix!\n");
		return -1;
	}
	//값이 초기화가 안된경우 메시지 출력
	if(check==0){
		printf("initialize first!\n");
		return -1;
	}

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix_t[i][j]=matrix[j][i];	//행과 열을 전치시켜 할당
		}
	}
	printf("matrix_t\n");
	print_matrix(matrix_t,row,col);
	return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix_a==NULL || matrix_b==NULL){
		printf("check the matrix!\n");
		return -1;
	}
	//값이 초기화가 안된경우 메시지 출력
	if(check==0){
		printf("initialize first!\n");
		return -1;
	}


	int** matrix_sum=create_matrix(row,col);	//두행렬의 합을 저장공간을 가리킬 이중포인터선언
	if(matrix_sum==NULL){	//동적할당 실패된 경우 -1반환
		printf("동적할당 실패!\n");
		return -1;
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix_sum[i][j]=matrix_a[i][j]+matrix_b[i][j];	//각 대치되는 행렬의 값을 더해 할당
		}
	}
	printf("matrix_a + matrix_b\n");
	print_matrix(matrix_sum,row,col);
	free_matrix(matrix_sum,row,col);	//사용이 다끝났으므로 matrix_sum을 free
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix_a==NULL || matrix_b==NULL){
		printf("check the matrix!\n");
		return -1;
	}
	//값이 초기화가 안된경우 메시지 출력
	if(check==0){
		printf("initialize first!\n");
		return -1;
	}

	int** matrix_sub=create_matrix(row,col);	//두행렬의 차를 저장공간을 가리킬 이중포인터선언
	if(matrix_sub==NULL){	//동적할당 실패한 경우 -1 반환
		printf("동적할당 실패\n");
		return -1;
	}
	for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];	//각 행렬의 대치되는 값을 빼서 할당
			}
		}
	printf("matrix_a - matrix_b\n");
	print_matrix(matrix_sub,row,col);		
	free_matrix(matrix_sub,row,col);	//사용이 다 끝났으므로 matrix_sub을 free
	
	return 1;
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col){
	//row와 col의 크기가 제대로 지정되지 않았을경우, matrix에 동적할당된 주소가 없을 경우 -1 반환
	if(row<=0 || col <=0){	
		printf("check the sizes of row and col!\n");
		return -1;	
	}
	if(matrix_a==NULL || matrix_t==NULL){
		printf("check the matrix!\n");
		return -1;
	}
	//값이 초기화가 안된경우 메시지 출력
	if(check==0){
		printf("initialize first!\n");
		return -1;
	}

	int** matrix_axt=create_matrix(row,col);	//전치행렬을 가리킬 이중포인터 생성
	if(matrix_axt==NULL){	//동적할당 실패한 경우 -1 반환
		printf("동적할당 실패\n");
		return -1;
	}
	for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				matrix_axt[i][j]=matrix_a[i][j]*matrix_t[i][j];	//각 대치되는 행렬의 값을 곱해 할당
			}
		}
	printf("matrix_a x matrix_t\n");
	print_matrix(matrix_axt,row,col);		
	free_matrix(matrix_axt,row,col);	//사용이 다 끝난 matrix_axt를 free
	return 1;
}
