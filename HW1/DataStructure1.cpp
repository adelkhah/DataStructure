// data structure exercise sulotion 1


// 1_st question 
void get_lower_triangle(int i, int j)
{
	// from row 0 to n from column 0 to m collect none zero element 
	int before = (i*(i+1))/2;
	return a[before + j];
}

//2_nd question
void get_upper_triangle(int i, int j)
{
	// from column 0 to m from row 0 to n collect none zero element
	int before = (j*(j+1))/2;
	return a[before + i];
}


// 3_rd question
// main idea: the product of two arbitrary element like a[i][k] and b[k][j]
// will be added to the ans[i][j] where ans = a*b
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
// main idea : count the number of elements before the current element in transpose
// and store it in "cnt" then that element is in transpose[cnt]
void transpose(int a[][3], int ans[][3])
{
	ans[0][2] = a[0][2]; 
	ans[0][0] = a[0][1];
	ans[0][1] = a[0][0];
	
	for(int i = 1; i <= a[0][2]; i++){
		int cnt = 0;
		for(int j = 1; j <= a[0][2]; j++){
			if(a[j][1] < a[i][1]){
				cnt++;
			}
			else if(a[j][1] == a[i][1] && a[j][0] < a[i][0]){
				cnt++;
			}
			else{
				continue;
			}
		}
		ans[cnt+1][2] = a[i][2];
		ans[cnt+1][0] = a[i][1];
		ans[cnt+1][1] = a[i][0];
	}
	return ans;
}

// written by Ali Adelkhah