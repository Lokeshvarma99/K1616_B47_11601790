#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
struct processes{

    int  tb;
    int  ta;
	int  id;
    int  process_class;
	int  tat;
	int  wt;
	int  ct;
};

int gt;

int main(){
	char buffer [100];
	int n;
	write(1,"Number of processes to be created               : ",40);
	scanf("%d",&n);
	struct processes processes[n];
	struct processes queue1[n];
	struct processes queue2[n];
	int count=0;
	
	while(count < n)
	{
		write(1,"Enter arrival time of the process        : ",40);
		scanf("%d",&processes[count].ta);

    	write(1,"Enter burst  time of the process        : ",40);
		scanf("%d",&processes[count].tb);
	
		write(1,"Enter process type (sys/user-0/1)       : ",40);
		scanf("%d",&processes[count].process_class);
	
		processes[count].id=count;
		count++;
	
	} 

	int q1_count=0;
	int q2_count=0;
	int i;
	for(i=0;i<n;i++){
		if(processes[i].process_class == 0){
				queue1[q1_count]=processes[i];
				q1_count++;
			}
		else if(processes[i].process_class == 1){
				queue2[q2_count]=processes[i];
				q2_count++;
			}
	}
	
	
	write(1,"\nEnter starting time  :  ",40);
	scanf("%d",&gt);
	fflush(stdin);
	
	int time_quant=2;
	int bz=0;
	int rt[n];
	int flag ;
	int k=0;
	int j;
	int z;
	struct processes temp;
	int comp= 0, t = 0, minm=queue1[0].tb;
	int shortest = 0, finish_time;
	int flag1 = 0;
	while(1){
		
		for (i = 0; i < q1_count;i++){
			rt[i] = queue1[i].tb;
		}
       				
       	while(comp != q1_count){
	       		for (j = 0; j < q1_count; j++) {
	            	if ((queue1[j].ta <= gt) && (rt[j] <= minm) && rt[j] > 0) {
	                	minm = rt[j];
	                	shortest = j;
	                	flag1=1;
					}
	       		}
	       		
	       			
	 		if(flag1==0) {
	            gt++;
	            continue;
	        }
			
			
	        rt[shortest]--;
	
	        minm = rt[shortest];
	        if(minm == 0)
	             minm = INT_MAX;
			 
			if (rt[shortest] == 0) {
	 			     comp++;
	            queue1[shortest].ct = gt;
	            finish_time = gt + 1;
	 			queue1[shortest].ct = gt+1;
			}
				
	           
	        gt ++ ;		
		}
		
		printf("\n\nQueue1 executed !!");
		int a;
		for(a=0; a< q1_count ; a++)
		{
			printf("\nCompletion time of proc. %d = %d ",queue1[a].id,queue1[a].ct);
		}
		        for(j=0;bz != q2_count;){
					if(queue2[j].tb <= time_quant && queue2[j].tb >0 ){
						gt+=queue2[j].tb;
      					queue2[j].tb=0;
     					flag=1; 
					}
					else if(queue2[j].tb>0)
    				{ 
     					queue2[j].tb-=time_quant;
      					gt+=time_quant; 
   					}
					   
					if(queue2[j].tb==0 && flag==1)
				    { 
				    	bz++; 
					  	queue2[j].ct = gt+1; 
				      	flag=0; 
				    }  
					if(j==q2_count -1) 
      					j=0; 
					else if(queue2[j+1].ta<=gt)
      					j++; 
					else 
      					j=0; 

			}
	        printf("\n\nQueue2 executed !!");
			for(a=0; a< q2_count ; a++)
				{
					printf("\nCompletion time of proc. %d = %d ",queue2[a].id,queue2[a].ct);
				}
 
			break;
	}
	
	int avg_tat1=0;
	int avg_tat2=0;
	int avg_wt1=0;
	int avg_wt2=0;


	for(i=0;i<q1_count;i++){
		queue1[i].tat=queue1[i].ct - queue1[i].ta;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].tat=queue2[i].ct - queue2[i].ta;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].wt=queue2[i].tat - queue2[i].tb;
	
	}
	
	for(i=0;i<q1_count;i++){
		queue1[i].wt=queue1[i].tat - queue1[i].tb;
	
	}
	
	printf("\n\nPROCESS NAME |\t TURN AROUND TIME |\t WAITING TIME \n");
	for(i=0;i<q1_count;i++){
	printf(" %d             |\t\t%d         |\t\t%d \n",queue1[i].id,queue1[i].tat,queue1[i].wt);
	}
	for(j=0;j<q2_count;j++){
	printf(" %d             |\t\t%d         |\t\t%d \n ",queue2[j].id,queue2[j].tat,queue2[j].wt);
	}

	
	for(i=0;i<q1_count;i++){
	
		avg_tat1=avg_tat1+queue1[i].tat;
	}
	avg_tat1= (avg_tat1 / q1_count);
	for(i=0;i<q2_count;i++){
	
		avg_tat2=avg_tat2+queue2[i].tat;
	}
	avg_tat2= (avg_tat2 / q2_count);
	for(i=0;i<q2_count;i++){
	
		avg_wt2=avg_wt2+queue2[i].wt;
	}
	avg_wt2= (avg_wt2 / q2_count);
	for(i=0;i<q1_count;i++){
	
		avg_wt1=avg_wt1+queue1[i].wt;
	}
	avg_wt1= (avg_wt1 / q1_count);
	
	printf("\n\nPROCESS ID |\t AVERAGE TURN AROUND TIME |\t AVERAGE WAITING TIME \n");
	printf(" %d            |\t\t%d         |\t\t%d \n",queue1[i].id,avg_tat1,avg_wt1);
	printf(" %d            |\t\t%d         |\t\t%d \n",queue1[i].id,avg_tat2,avg_wt2);
	
	
	
	
}
