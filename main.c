#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<dos.h>
#include<time.h>
#define MAX 100

int currnodes=0,count=0;
int i,s ,j,t,b,k,c,size;
int a[MAX];

struct ad
{
    char data[1000];
    struct add *next;
};

typedef struct ad AD;

struct news_variables
{
    int p;
    int v1;
    int v2;
};

typedef struct news_variables NV;

AD *append(AD * start,char data[],int position)
{
   AD * temp=start;
   int i=0;

   while(i<position - 1)
   {
       temp=temp->next;
       i++;
   }

   strcpy(temp->data,data);

   return start;
}

AD *displayNTimes(AD * start,int n,char content[])
{
    int l;
     for(l=0;l<n;l++)
    {
        t=rand()%MAX;

        while(1)
        {
            if(a[t]==0)
            {
                start=append(start,content,t+1);
                a[t]=1;
                break;
            }
            else
                t=rand()%MAX;
        }
    }
    return start;
}

 AD * InsertNth(AD * start,char data[],int position)
 {
    AD * newnode, *nextnode;
    k=0;

    if(position < 1 || position > currnodes+1)
        printf("Invalid Position!\n");
    else
    {
        newnode = (AD *) malloc(sizeof(AD));

        if(newnode == NULL)
            return start;

        strcpy(newnode->data,data);
        newnode->next=NULL;

        if(position == 1)
        {
            newnode->next= start;
            start= newnode;
        }
        else if(position == currnodes + 1)
            {
                nextnode=start;

                while(nextnode->next!=NULL)
                    nextnode = nextnode->next;

                nextnode->next = newnode;
            }
        else
            {
                nextnode = start;
                k = 1;

                while(k < position-1)
                {
                    nextnode =nextnode->next;
                    k++;
                }

                newnode->next =nextnode->next;
                nextnode->next =newnode;
            }
        currnodes++;
    }
    return start;
}

void centerstring(char *s)
{
    int i;
    int l=strlen(s);
    int pos=(int)((80-l)/2);
    for(i=0;i<pos;i++)
        printf(" ");
    printf("%s\n",s);
}

void delay(int sec)
{
    int ms=1000*sec;
    clock_t start_time=clock();
    while(clock() < start_time+ ms)
        ;
}
int main()
{
    FILE *fp1,*fp2,*fp3;

    AD *temp=NULL;
    int i,c,w,n;
    char addata[1000];

    for(i=0;i<MAX;i++)
        a[i]=0;

    AD *start=NULL;
    AD *paper=NULL;
    AD *paper1=NULL;

    NV news1,news2;

for(i=1;i<=MAX;i++)
        start=InsertNth(start,"Currently No Ad",i);

for(i=1;i<=26;i++)
        paper=InsertNth(paper,"Currently No Ad",i);

for(i=1;i<=16;i++)
        paper1=InsertNth(paper1,"Currently No Ad",i);

    news1.p=2;
    news2.p=2;
    news1.v1=0;
    news2.v1=0;
    news1.v2=0;
    news2.v2=0;

    while(1)
    {
        printf("*******************************\n");
        printf("Enter the Choice :\n1.Add an Advertisement in TV\n2.Add an Advertisement in Times of India Newspaper\n3.Add an advertisement in Hindu Newspaper\n4.Display ads in Times of India\n5.Display ads in Hindu Newspaper\n6.Delete all the contents in the files\n");
        scanf("%d",&c);
        printf("*******************************\n");
        switch(c)
        {
        case 1:
                    {
                        if(count==MAX)
                        {
                                printf("No more adds can be displayed today....\n");
                                break;
                        }
                        printf("The Charges for displaying an add 10 minutes a day is 1 lakh. Assuming an add is of 1 minute .\n");

                        printf("Enter the advertisement : ");
                        getchar();
                        scanf("%[^\n]s",addata);

                        printf("How many minutes you want your add to display in a day:");
                        scanf("%d",&n);

                        printf("Therefore your charges will be %f Lakhs\n",n/10.0);
                        printf("Are you ready to pay the charges : \n 1.Yes\n0.No\n");
                        scanf("%d",&w);

                        if(w==1)
                        {
                            count=count+n;

                            if(count>MAX)
                            {
                                    printf("The no of minutes are greater than 100. So now you can only display an add for %d minutes",n-count+MAX);
                                    printf("The charges will be %f\n",(n-count+MAX)/10.0);
                                    printf("Is that ok.\n1.Yes\n0.No\n");
                                    scanf("%d",&w);

                                    if(w==1)
                                    {
                                        n=n-count+MAX;
                                        count=MAX;
                                    }
                            }

                            start=displayNTimes(start,n,addata);



                            printf("Your Add will be displayed for %d minutes today.\n",n);
                            break;
                        }
                    }
        case 2:
                     {
                         printf("Welcome to TIMES OF INDIA ad section\n");
                         printf("**********************************\n");

                         printf("We follow the following ad categories\n");
                         printf("1.Matrimony:- \t1.Inner Page=735/sq.cm\t2.Front Page=800/sq.cm\t3.Back Page=760/sq.cm\n2.Retail:- \t1.Inner Page=500/sq.cm\t2.Front Page=600/sq.cm\t3.Back Page=550/sq.cm\n3.Services:-\t1.Inner Page=132/sq.cm\t2.Front Page=149/sq.cm\t3.Back Page=140/sq.cm\n4.Education:-\t1.Inner Page=800/sq.cm\t2.Front Page: 850/sq.cm\t3.Back Page=820/sq.cm\n5.Others:-\t1.Inner Page=120/sq.cm\t2.Front Page=200/sq.cm\t3.Back Page=185/sq.cm\n");
                         printf("Please select your category\n");
                         scanf("%d",&c);
                         switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Matrimonial for Inner page is %d rupees\n",size*735);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Matrimonial for Front page is %d rupees\n",size*800);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Matrimonial for Back page is %d rupees\n",size*760);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }
                                                        }
                                                        else
                                                            printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                        case 2:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Retail for Inner page is %d rupees\n",size*500);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Retail for Front page is %d rupees\n",size*600);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Retail for Back page is %d rupees\n",size*550);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }
                                                        }

                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                     case 3:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Services for Inner page is %d rupees\n",size*132);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Services for Front page is %d rupees\n",size*149);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Services for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 4:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Education for Inner page is %d rupees\n",size*800);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Education for Front page is %d rupees\n",size*820);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Education for Back page is %d rupees\n",size*820);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 5:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Inner page is %d rupees\n",size*120);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");

                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad for Front page is %d rupees\n",size*200);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad for Back page is %d rupees\n",size*185);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    } break;
                                        }

                                    }
                                    break;
                    }
                    break;


                     }
        case 3:
                    {
                        printf("Welcome to THE HINDU NEWSPAPER\n");
                        printf("*******************************\n");

                        printf("There are different ad category below:\n");
                        printf("The Tariff rates in Rupees per Sq.cm for different category are : \n");
                        printf("1.Property    : - \t1.Inner Page = 70\t2.Front Page = 125\t3.Back Page = 95\n2.Empower     : - \t1.Inner Page = 75\t2.Front Page = 350\t3.Back Page = 175\n3.Tenders     : - \t1.Inner Page = 70\t2.Front Page = 125\t3.Back Page = 95\n4.Automobile  : - \t1.Inner Page = 125\t2.Front Page = 160\t3.Back Page = 150\n5.Others      : - \t1.Inner Page = 120\t2.Front Page = 200\t3.Back Page = 185\n");
                        printf("Please select your category : ");
                        scanf("%d",&c);
                        switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in property for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in property for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in property for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }
                                                        }
                                                        else
                                                            printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                        case 2:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Empower for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Empower for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                        printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Empower for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }
                                                        }

                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                     case 3:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Tender for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Tender for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Tender for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 4:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Automobile for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Automobile for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Automobile for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 5:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                               paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");

                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    }
                    break;
                }

          case 4:
                    {
                       fp1= fopen("Data_stored_TimesOfIndia.txt","a+");

                        i=1;
                        AD *tmp=paper;
                        while(tmp->next!=NULL)
                        {
                            printf("%s\n",tmp->data);

                            tmp=tmp->next;
                            i++;
                        }
                        printf("%s\n",tmp->data);

                        fclose(fp1);
                    }
                    break;
          case 5:
                    {
                        fp2=fopen("Data_stored_Hindu.txt","a+");

                                            {
                        i=1;
                        AD *tmp=paper1;
                        while(tmp->next!=NULL)
                        {
                            printf("%s\n",tmp->data);

                            tmp=tmp->next;
                            i++;
                        }
                        printf("%s\n",tmp->data);
                    }
                        fclose(fp2);
                        break;
                    }
        case 0:     exit(0);
        case 6:
                    {
                        printf("Deleted all the previous data in the files.\n");

                        fp1=fopen("Data_stored_Hindu.txt","w");
                        fp2=fopen("Data_stored_TV.txt","w");
                        fp3=fopen("Data_stored_TimesOfIndia.txt","w");

                        fclose(fp1);
                        fclose(fp2);
                        fclose(fp3);
                    }
                    break;
        case 10:
                    {
                        fp3=fopen("Data_stored_TV.txt","a+");

                        fprintf(fp3,"\n%s\n\n", "Today's ads in Television are : ");

                        i=1;
                        AD *tmp=start;
                        while(tmp->next!=NULL)
                        {
                            delay(1);
                            centerstring(tmp->data);
                            fprintf(fp3,"%s %d %s %s\n","Add in",i,"th minute is ",tmp->data);
                            tmp=tmp->next;
                            i++;
                        }
                        printf("%s\n",tmp->data);
                        fprintf(fp3,"%s %d %s %s\n","Add in",i,"th minute is ",tmp->data);
                        fclose(fp3);
                    }
        }
    }
    return 0;
}
