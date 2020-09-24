


// 3_rd question
void multiple_sparse(int a[][3], int b[][3], int c[][3])
{
	if(a[0][1] != b[0][0]){ // cant multiple these matrix
		return;
	}

	int row = a[0][0];
	int col = b[0][1];
	c[0][0] = row;
	c[0][1] = col;
	c[0][2] = 0;

	for(int i = 1; i <= a[0][2]; i++){
		for(int j = 1; j <= b[0][2]; j++){

			bool finded = false;
			int k;
			for(k = 1; k <= c[0][2]; k++){
				int rowA = a[i][0];
				int colA = a[i][1];
				int rowB = b[i][0];
				int colB = b[i][1];
				int valA = a[i][2];
				int valB = b[i][2];
				int rowC = c[i][0];
				int colC = c[i][1];
				int valC = c[i][2];
				if(colA == rowB && rowC == rowA && colC == colB){
					c[k][2] += valA * valB;
					finded = true;
					break;
				}
			}

			if(colA == rowB && finded == false){
				c[k][0] = rowA;
				c[k][1] = colB;
				c[k][2] = valA * valB;
				c[0][2]++;
			}

		}
	}

}



// 4_th question
int* transfer_to_matrix(int a[][3])
{
	int row = a[0][0];
	int col = a[0][1];
	int ans[row][col];
	memset(ans, 0, sizeof(ans)); // initialize all elements to zero

	for(int i = 1; i <= a[0][2]; i++){
	    int row = a[i][0];
        int col = a[i][1];
   	    int val = a[i][2];
        ans[row][col] = val;
    }
	return ans;
}
