#include <stdio.h>
#include <string.h>

int main(){
    
    int prices[]   = {7,4,8,4,8,1,6,5,4,8,7,3,2,8754,546,84,8754,6,58,45,984954,6,4,3,1,98498452};
    int pricesSize = sizeof(prices)/4;//26;//strlen(prices);
    
    int biggestSell=0;
    int quickSell=0;
    int dayToBuy=0, dayToSell=0;
    
    for(int i=0;i<pricesSize;i++){
        for(int j=i;j<pricesSize;j++){
            quickSell=prices[j]-prices[i];
            if(quickSell>biggestSell){
                dayToBuy = i;
                dayToSell= j;
                biggestSell=quickSell;
            }
        }
    }
    =
    printf("buyIn:%d sellIn:%d profit:%d",dayToBuy+1,dayToSell+1,biggestSell);
}


