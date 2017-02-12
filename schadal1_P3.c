#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>
FILE *input_file;
FILE *output_file;
double elapsed_time=0;
int n,m,sizeC,flag=0,mflag=1,nflag=0,and=1;
int promising(int depth,int x[])
{
        int i,j,k=0,temp1[sizeC],temp2[sizeC],or,t1,tk=1,tval,p,q,r,zflag=0;
        int tuple[m];
        for(i=0;i<m;i++)
        {
                tuple[i]=9;
        }
//      printf("depth = %d",depth);
        if(depth==0)
        {
//              printf("depth =%d\n",depth);
                return 1;
        }
        else if(depth <= n)
        {
//              printf("depth =%d\n",depth);
                rewind(input_file);
                fscanf(input_file,"%d",&n);
                fscanf(input_file,"%d",&m);
                fscanf(input_file,"%d",&sizeC);
                for(j=0;j<m;j++)
                {
                        or=0;
                        tk=1;
                         for(i=0;i<sizeC;i++)
                        {
                                fscanf(input_file,"%d",&temp1[i]);
//                              printf("temp1[%d]= %d ",i,temp1[i]);

                                if(temp1[i]>0)
                                {
                                        temp2[i]=1;
                                }
                                if(temp1[i]<0)
                                {
                                        temp1[i]=temp1[i]*-1;
                                        temp2[i]=0;
                                }
//                              printf(" temp2[%d]= %d",i,temp2[i]);
                                t1=temp1[i];
                                t1=t1-1;
                                        if(t1>=depth)
                                        {
                                                x[t1]=-101;
                                        }

//                              printf(" x[%d]=%d\t",t1,x[t1]);
                                if(temp2[i]==0)
                                {
                                        if(x[t1]==1)
                                        {
                                                p=0;
                                                if(tuple[k]==9)
                                                {
                                                        tuple[k]=0;
                                                }
                                                else
                                                {
                                                        tuple[k]=tuple[k]|p;
                                                }
                                        }
                                        else if(x[t1]==0)
                                        {
                                                p=1;
                                                if(tuple[k]==9)
                                                {
                                                        tuple[k]=1;
                                                }
                                                else
                                                {
                                                        tuple[k]=tuple[k]|p;
                                                }
                                        }
                                        else if(x[t1]==-101 && tuple[k]!=1)
                                        {
                                                tuple[k]=9;
                                        }
                                }
                                else if(temp2[i]==1)
                                {
                                        if(x[t1]==0)
                                        {
                                                p=x[t1];
                                                //or=or|p;
                                                if(tuple[k]==9 && tk==1)
                                                {
                                                        tuple[k]=tuple[k]|p;
                                                        tk=0;

                                                }
                                                else if(tuple[k]==1)
                                                {
                                                        tuple[k]=1;
                                                }
                                                else if(tuple[k]==9 && tk ==0)
                                                {
                                                        tuple[k]=0;
                                                }
                                        }
                                        else if(x[t1]==1)
                                        {
                                                p=1;
                                                if(tuple[k]==9)
                                                {
                                                        tuple[k]=1;
                                                }
                                                else
                                                {
                                                        tuple[k]=tuple[k]|p;
                                                }

                                        }
                                        else if(x[t1]==-101 && tuple[k]!=1)
                                        {
                                                tuple[k]=9;
                                        }

                                }
//                              printf(" p=%d    or=%d\t",p,or);
//                              printf("tuple[%d]= %d \n",k,tuple[k]);
                        }
//                      printf("\n");
                        if(tuple[k]==0)
                        {
                                return 0;
                        }
                        else if(tuple[k]!=9)
                        {
                                and = and & tuple[k];
                        }
                        else if(tuple[k]==9)
                        {
                        //      r=1;
                        }
                        k++;

                }
                if(and!=0)
                {
                        for(q=0;q<sizeC;q++)
                        {
                                if(tuple[q]==9)
                                {
//                                      printf("zflag=%d",zflag);
                                        zflag=1;
                                }
                        }
                        if(zflag!=1)// && r!=1)
                        {
                                flag=1;
                                return 0;
                        }
                        return 1;

                }
                else if(and==0)
                {
                        return 0;
                }
        }
        else if(depth>n)
        {
                return 0;
        }

}
void backTrackCompute(int depth,int x[],int y[])
{
        int i,j,temp[n],t1,t2,k=n;
        /*To check all clauses are satisfied with currentassignment of variables*/
        //Flow of logic
        if (promising(depth,x))
        {
                x[depth]=1;
                backTrackCompute(depth+1,x,y);
                x[depth]=0;
                backTrackCompute(depth +1,x,y);
        }
//      printf("flag = %d\n",flag);
        if(flag!=0)
        {
//              printf("answer\n");
		if(n<=5)
		{
                	for(i=0;i<depth;i++)
	                {
        	                fprintf(output_file,"x[%d]=%d\n",i+1,x[i]);
                	}
		}
		else if(n>5 && m<=30)
		{
			 for(i=0;i<depth;i++)
                        {
                                fprintf(output_file,"x[%d]=%d\n",i+1,x[i]);
                        }
			exit(1);
		}
		 else if(n>5 && m>30)
                        {
                                fprintf(output_file,"There is a satisfying assignment \n");
                                exit(1);

                     }	
               flag =0;
                fprintf(output_file,"\n");
                nflag=1;
                return;
        }


}
int main(int argc,char *argv[])
{
//Taking input file from command line argument
        int i;
        clock_t start,end;
        input_file = fopen(argv[1],"r");
        output_file = fopen(argv[2],"w");
        if(!input_file)
        {
                fprintf(output_file,"\n Error while proccesing input file\n Please give input file.txt\n");
                return 0;
        }
        fscanf(input_file,"%d",&n);
        int x[n];
        for(i=0;i<n;i++)
        {
                x[i]=-101;
        }
        int y[n];
        fscanf(input_file,"%d",&m);
        fscanf(input_file,"%d",&sizeC);
//calling Recursive dfs function
//      printf("n= %d\tm=%d sizeC=%d\n",n,m,sizeC);
        start=clock();
        backTrackCompute(0,x,y);
        end=clock();
        if(flag == 0 && nflag==0)
        {
                fprintf(output_file,"\nNo satisfying assignment\n");
        }
        elapsed_time=((double)((end-start))/CLOCKS_PER_SEC)*1000;
        fprintf(output_file,"The Run Time is %f milli seconds\n",elapsed_time);
//Printing the run time
        fclose(input_file);
        fclose(output_file);

        return 0;

}
