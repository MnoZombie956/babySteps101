/**
 *
 * @author marco956
 */
public class Main {
    /**
     * @param args the command line arguments
     */
    public static double determinant(double[][] matrix){ 
        int sum=0; 
        int s;
        if(matrix.length==1){  
          return(matrix[0][0]);
        }
        for(int i=0;i<matrix.length;i++){ 
            double[][]smaller= new double[matrix.length-1][matrix.length-1]; 
            for(int a=1;a<matrix.length;a++){
                for(int b=0;b<matrix.length;b++){
                    if(b<i){
                        smaller[a-1][b]=matrix[a][b];
                    }
                    else if(b>i){
                        smaller[a-1][b-1]=matrix[a][b];
                    }
                }
            }
            if(i%2==0){ //sign changes based on i
                s=1;
            }
            else{
               s=-1;
            }
            sum+=s*matrix[0][i]*(determinant(smaller));// recursive step: determinant of larger determined by smaller.
        }
        return(sum); //returns determinant value. once stack is finished, returns final determinant.
    }
    public static void main(String[] args) {
        double mtz[][] = {{-7,4,2,1,8},{0,-5,4,1,8},{5,3,1,1,5},{1,1,5,1,5},{9,8,7,4,1}};
        
        System.out.println("Det: "+determinant(mtz));
    }
}
