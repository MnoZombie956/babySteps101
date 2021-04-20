import java.io.*;

class sortArray{
  int a[];
  int n;
  static BufferedReader br = new BufferedReader(
    new InputStreamReader(System.in)
  );
  public sortArray (int nn){
    a = new int[nn];
    n = nn; 
  }
  public static void main (String args[]) throws IOException{
    System.out.print ("\nEnter the size of the array : ");
    int nn = Integer.parseInt (br.readLine ());
    sortArray call = new sortArray (nn);
    System.out.println ("\nEnter " + nn + " elements :");

    call.readArray ();

    System.out.println ("Choose Sorting Technique :\n");

    System.out.println ("1 : Bubble Sort");

    System.out.println ("2 : Selection Sort");

    System.out.println ("3 : Insertion Sort");

    System.out.println ("4 : Quick Sort");

    System.out.print ("\nYour Choice : ");

    int choice = Integer.parseInt (br.readLine ());

    switch (choice){
      case 1:call.bubbleSort ();
      break;
      case 2:call.selectionSort ();
      break;
      case 3:call.insertionSort ();
      break;
      case 4:call.quickSort ();
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
  public void display (){
    System.out.println ("\nSorted Array :");
    for (int i = 0; i < n; i++)
      System.out.println (a[i]);
 }
}
/**
* Algorithm for Selection Sort :
* ----------------------------
* 1. Start
* 2. Construct a single-dimensional array of appropriate size.
* 3. Fill the array with data entries.
* 4. Using selection sort technique bring the smallest number to the
first unsorted position of the array.
* 5. Repeat step 4 till the entire array is sorted.
* 6. Print the sorted array.
* 7. End
*
* Algorithm for Bubble Sort :
* ----------------------------
* 1. Start
* 2. Construct a single-dimensional array of appropriate size.
* 3. Fill the array with data entries.
* 4. Using bubble sort technique push the largest number to the last
unsorted position of the array.
* 5. Repeat step 4 till the entire array is sorted.
* 6. Print the sorted array.
* 7. End
*
* Algorithm for Insertion Sort :
* ----------------------------
* 1. Start
* 2. Construct a single-dimensional array of appropriate size.
* 3. Fill the array with data entries.
* 4. Using insertion sort technique push the largest number to the
last unsorted position of the array.
* 5. Repeat step 4 till the entire array is sorted.
* 6. Print the sorted array.
* 7. End
*
* Algorithm for Quick Sort :
* ----------------------------
* 1. Start
* 2. Construct a single-dimensional array of appropriate size.
* 3. Fill the array with data entries.
* 4. Using quick sort technique push the largest number to the last
unsorted position of the array.
* 5. Repeat step 4 till the entire array is sorted.
* 6. Print the sorted array.
* 7. End
*/
