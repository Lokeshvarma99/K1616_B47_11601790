#include<iostream>
using namespace std;

int res,pro,avail[20],alloc[20][20],maximum[10][20],needed[20][20];

void rollback(int roll[],int a)
{
    for(int k=0;k<res;k++)
    {
        avail[k]=avail[k]+roll[k];
        alloc[pro][k]=alloc[pro][k]-roll[k];
        needed[pro][k]=alloc[pro][k]+roll[k];
    }
}

int safety()
{
	int w[10],f[10],flag=0,k,count=0,cn,flag1=0,ans;
	cout<<"The allocation table is : "<<endl;
	cout<<"PROCESS";
	for(int i=0;i<res;i++)
	{
       cout<<"     Resource"<<i+1;
	}
   	cout<<endl;
   	for(int i=0;i<pro;i++)
   	{
       cout<<"Process"<<i+1<<"        ";  
       for(int j=0;j<res;j++)
       {
           cout<<alloc[i][j]<<"             ";
       }
       cout<<endl;
   	}
    int j=0;
	for(int i=0;i<res;i++)
	{	
       w[j]=avail[i];
       j++;
	}
	for(int i=0;i<pro;i++)
	{
        f[i]=0;
	}
	while(count<=10)
	{
		for(int i=0;i<pro;i++)
    	{
        	if(f[i]==0)
        	{
        		for(int j=0;j<res;j++)
        		{
            		if(needed[i][j]<=w[j])
            		{
                		flag=1;
            		}
            		else
            		{
                		flag=0;
                		break;
            		}
            	}	
         		if(flag==1)
				{
             		cout<<"The process"<<i+1<<" ran successfully"<<endl;
             	    f[i]=1;
             		for(k=0;k<res;k++)
             		{
                 		w[k]=w[k]+alloc[i][k];
             		}
         		}
      		}
    	}
    	for(int i=0;i<pro;i++)
    	{
        	if(f[i]==1)
        	{
            	flag1=1;
        	}	
        	else
        	{
            	flag1=0;
            	break;
        	}
    	}	
    	count++;
    	if(flag1==1)
    	{
       		cout<<"System is safe"<<endl;;
       		ans=0;
       		break;
     	}
	}
    if(flag1==0)
    {
       cout<<"System is not safe"<<endl;
        ans=1;
    }
    return ans;
}

int requesting()
{
	int value1,k=0,roll[10],a;
	cout<<"Enter the processor requesting : ";
    cin>>a;
    for(int i=0;i<res;i++)
    {
        cout<<"Enter the value for the resource"<<i+1<<" : ";
        B : cin>>value1;
        if(value1>maximum[a][i])
        {  
        	cout<<"Please enter the value again : ";
           	goto B;
        }
   		else
        {
            alloc[a][i]=alloc[a][i]+value1;
            avail[i]=avail[i]-value1;
            needed[a][i]=needed[a][i]-value1;
            roll[k]=value1;
            k++;
        }
    }
    int ans=safety();
    if(ans==1)
    {
	    rollback(roll,a);
    } 
}

int main()
{
	cout<<"Enter the number of Resources : ";
	cin>>res;//m
	cout<<"Enter the number of processes : ";
	cin>>pro;//n
	int value;//val
	cout<<"Enter the max value for resources : "<<endl;
	for(int i=0;i<res;i++)
	{
		cout<<i+1<<".";
		cin>>value;
		avail[i]=value;//avail
	}
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			alloc[i][j]=0;//alloc
		}
	}
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			cout<<"Enter the maximum required value for process"<<i+1<<" resouce"<<j+1<<" : ";
			A : cin>>value;
			if(value>avail[j])
			{
				cout<<"The value is greater. Please enter again";
				goto A;
			}
			else
			maximum[i][j]=value;
		}
	}
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			needed[i][j]=maximum[i][j]-alloc[i][j];
		}
	}
	int choice;
	while(1)
	{
		cout<<"Enter '1' to request : ";
		cin>>choice;
		if(choice==1)
		requesting();
		else
		break;
	}
}
