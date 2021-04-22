import java.io.*;
/*
Complexity Analysis

1 : Bubble Sort
	Worst O(n^2), Best O(n), Shuffled(avg)=Worst 
	Space O(1), just a temporary
2 : Selection Sort
	Theta(n^2)
	Space O(1)
	NOT stable
3 : Insertion Sort
	Worst O(n^2), Best O(n), Shuffled=Worst
4 : Quick Sort
	Worst O(n^2), Best O(n*log(n))
	Space O(log n)
	NOT stable
5 : Merge Sort
	Theta(n*log n)
	Space O(n)

Not mentioned, stability:
	It's just a question on whether same values different keys will stay or not in the same order after sorting
counting sort:
	really cool, linear, keeps count of elements
	ocurrences and map indexes
radix sort:
	I heard that it isn't well studied by undergrads,
	time complexity better than n*log n since there is no
	comparassions
	it's quite place inefficient because its intermediate steps
	good for large ranges numbers
bucket sort:
	for floating points mainly
	"buckets" containing certain range are sorted 
*more details in my personal notes
*/
class sortArray{
	int a[];
	int n;
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public sortArray (int nn){
		a = new int[nn];
		n = nn; 
	}
	public static void main (String args[]) throws IOException{
		System.out.print ("\nEnter the size of the array : ");//quite naive but ok
		int nn = Integer.parseInt (br.readLine ());
		sortArray call = new sortArray (nn);
		System.out.println ("\nEnter " + nn + " elements :");

		call.readArray ();

		System.out.println ("Choose Sorting Algorithm:\n");

		System.out.println ("1 : Bubble Sort");

		System.out.println ("2 : Selection Sort");

		System.out.println ("3 : Insertion Sort");

		System.out.println ("4 : Quick Sort");

		System.out.println ("5 : Merge Sort");

		System.out.print ("\nYour Choice : ");

		int choice = Integer.parseInt (br.readLine ());

		switch (choice){
			case 1:call.bubbleSort();
			break;
			case 2:call.selectionSort();
			break;
			case 3:call.insertionSort();
			break;
			case 4:call.quickSort();
			break;
			case 5:call.mergeSort(call.a,0,call.n);
			break;
			default:System.out.println ("\nInvalid Choice !");
			System.exit (1);
			break;
		}
		call.display ();		// Print the sorted array
	}

	public void readArray () throws IOException{
		for (int i = 0; i < n; i++)
			a[i] = Integer.parseInt (br.readLine ());
	}
	public void bubbleSort (){
		int t;
		for (int i = 0; i < n - 1; i++){
			for (int j = 0; j < n - 1 - i; j++){
				if (a[j] > a[j + 1]){
					t = a[j];
					a[j] = a[j + 1];
					a[j + 1] = t;
				}
			}
		}
	}
	public void selectionSort (){
		int t, min;
		for (int i = 0; i < n - 1; i++){
			min = i;
			for (int j = i + 1; j < n; j++){
				if (a[min] > a[j])
					min = j;
			}
			if (min != i){
				t = a[min];
				a[min] = a[i];
				a[i] = t;
			}
		}
	}
	public void insertionSort (){
		int t, j;
		for (int i = 1; i < n; i++){
			j = i - 1;
			t = a[i];
			while (t < a[j] && j >= 0){
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = t;
		}
	}
	public void quickSort () {
		int t;
		for (int i = 0; i < n - 1; i++){
			for (int j = i + 1; j < n; j++){
				if (a[i] > a[j]){
					t = a[i];
					a[i] = a[j];
					a[j] = t;
				}
			}
		}
	}
	public void mergeSort_merge(int arr[], int p, int q, int r) {//util
		// Create L <- A[p..q] and M <- A[q+1..r]
		int n1 = q - p + 1; int n2 = r - q;
		int L[] = new int[n1]; int M[] = new int[n2];
		for (int i = 0; i < n1; i++)
			L[i] = arr[p + i];
		for (int j = 0; j < n2; j++)
			M[j] = arr[q + 1 + j];
		// Maintain current index of sub-arrays and main array
		int i, j, k;
		i = 0;
		j = 0;
		k = p;
		// Until we reach either end of either L or M, pick larger among
		// elements L and M and place them in the correct position at A[p..r]
		while (i < n1 && j < n2) {
			if (L[i] <= M[j]) {
				arr[k] = L[i];
				i++;
			} else {
				arr[k] = M[j];
				j++;
			}
			k++;
		}
		// When we run out of elements in either L or M,
		// pick up the remaining elements and put in A[p..r]
		while (i < n1) {
			arr[k] = L[i];
			i++;
			k++;
		}
		while (j < n2) {
			arr[k] = M[j];
			j++;
			k++;
		}
	}
	public void mergeSort(int arr[], int l, int r) {
		// Divide the array into two subarrays, sort them and merge them
		if (l < r) {
			// m is the point where the array is divided into two subarrays
			int m = (l + r) / 2;
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);
			// Merge the sorted subarrays
			merge(arr, l, m, r);
		}
	}
	public void display (){
		System.out.println ("\nSorted Array :");
		for (int i = 0; i < n; i++)
			System.out.println (a[i]);
	}
}
