#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10000
#include<time.h>
//����  78 99 43 100 170 143 80 120 55
typedef struct
{
    int track;//�ŵ���
    int flag;//��־λ��0��ʾδ��Ӧ��1��ʾ����Ӧ��
}diskreq;//һ����������

diskreq *reqSeq;//��������ָ��
int RN,START;//�����������г��Ⱥʹ�ͷ���λ��
float meanD;//ƽ��Ѱ������
//int main();
void init();//��ʼ���������������
void clear();//ÿ�˷���ǰflag����
int search();//���Ҿ��뵱ǰλ�����������㣬���شŵ���
void FCFS(diskreq*,int);//FCFS�㷨
void SSTF(diskreq*,int);//SSTF�㷨
void SCAN(diskreq*,int);//SCAN�㷨
void CSCAN(diskreq*,int);//CSCAN�㷨
void sort(diskreq*);//������ɨ���㷨����Ҫ




int main()
{
    int i,j,k,num;
    init();//��ʼ��

    printf("����˵����\n");
    printf("    num=0  ���������\n");
    printf("    num=1  FCFS�㷨\n");
    printf("    num=2  SSTF�㷨\n");
    printf("    num=3  SCAN�㷨\n");
    printf("    num=4  CSCAN�㷨\n");
    printf("==============================\n");
    printf("\n");
    printf("����������num��");
    scanf("%d",&num);
    while(1)
    {
        switch(num)
        {
            case 0:printf("\n=====���������=====\n");return 0;
            case 1:printf("\n��FCFS�㷨��\n");FCFS(reqSeq,START);break;
            case 2:printf("\n��SSTF�㷨��\n");SSTF(reqSeq,START);break;
            case 3:printf("\n��SCAN�㷨��\n");SCAN(reqSeq,START);break;
            case 4:printf("\n��CSCAN�㷨��\n");CSCAN(reqSeq,START);break;
            default:printf("\n=====��������=====\n");
        }
        printf("\n");
        printf("����������num��");
        scanf("%d",&num);
    }
}

void init()
{
    int i;
    printf("�������������г���RN��");
    scanf("%d",&RN);
    printf("\n");
    printf("�������ͷ���START��");
    scanf("%d",&START);
    printf("\n");
    reqSeq=(diskreq*)malloc(RN*sizeof(diskreq));   //����������������
    printf("��������������reqSeq��");
    srand((unsigned int)time(NULL));
    for(i=0;i<RN;i++)
	     // reqSeq[i].track = rand()% 201 + 0  ;
         scanf("%d",&reqSeq[i].track);
    printf("===================================================\n");
}

void clear()//��־λ����
{
    int i;
    for(i=0;i<RN;i++)
        reqSeq[i].flag=0;
    meanD=0;
}

int search(diskreq* rq,int pos)
{//���Ҿ��뵱ǰλ������������
    int i,d,mi,md=MAX;
    for(i=0;i<RN;i++)
        if(rq[i].flag==0)
        {//ֻ���Ǳ�־λΪ0�������
            d=abs(rq[i].track-pos);//ÿ������㵽��ǰλ�õľ���d
            if(d<md)
            {
                mi=i;//��С�����������±�mi
                md=d;
            }
        }
    rq[mi].flag=1;         //��־λ��1����ʾ����Ӧ��
    meanD=meanD+md;        //Ѱ�������ۼ�
    return rq[mi].track;   //��������ŵ���
}

void sort(diskreq* rq)
{
    int i,j,t,temp;
    for(i=0;i<RN-1;i++)//��������
    {
        t=i;
        for(j=i+1;j<RN;j++)
            if(rq[j].track<rq[t].track)t=j;
        if(t!=i)
        {
           temp=rq[i].track;
           rq[i].track=rq[t].track;
           rq[t].track=temp;
        }
    }
}

void FCFS(diskreq* rq,int s)
{//����˵���������̷������У���ͷ��㣩
    int i;
    clear();//flag����
    meanD=abs(s-rq[0].track);//��ͷ�ƶ����������
    printf("��Ӧ����%4d",rq[0].track);//�����һ�������
    for(i=1;i<RN;i++)
    {//�������ÿ�δ�ͷ�ƶ����룬������ŵ���
        meanD=meanD+abs(reqSeq[i].track-reqSeq[i-1].track);
        printf("%4d",reqSeq[i].track);
    }
    printf("\n\n");
    meanD=meanD/RN;//���ƽ��Ѱ������
    printf("ƽ��Ѱ�����ȣ�%6.1f\n",meanD);
    printf("==============================\n");
}

void SSTF(diskreq* rq,int s)
{//����˵���������̷������У���ͷ��㣩
    int i=0;
    clear();//flag����
    printf("��Ӧ����");
    while(i<RN)
    {//�����������㣬ֱ������
        s=search(rq,s);
        printf("%4d",s);
        i++;
    }
    printf("\n\n");
    meanD=meanD/RN;
    printf("ƽ��Ѱ�����ȣ�%6.1f\n",meanD);
    printf("==============================\n");
}

void SCAN(diskreq* rq0,int s)
{
    int i,j,d,pos;
    diskreq* rq;
    rq=(diskreq*)malloc(RN*sizeof(diskreq));
    //��ΪҪ�Է������������������ٽ���һ������
    for(i=0;i<RN;i++)//���Ʒ�������
        rq[i]=rq0[i];
    sort(rq);//��������
    i=0;
    while(s>rq[i].track)i++;//�ҵ�s��λ��
    pos=i;
    printf(" 1 ��ʾ��ͷ��ŵ������ӷ����ƶ�\n");
    printf(" 2 ��ʾ��ͷ��ŵ��ż��ٷ����ƶ�\n\n");
    printf("�������ͷ�ƶ�����d: ");
    while(1)
    {
       scanf("%d",&d);
       if(!(d==1||d==2))
       {
          printf("����������������룺");
          continue;
       }
       break;
    }
    if(d==1)
    {
        if(s==rq[0].track||s==rq[RN-1].track)//�����պ��������˵�λ��ʱ
            meanD=rq[RN-1].track-rq[0].track;
        else
            meanD=2*rq[RN-1].track-s-rq[0].track;
        printf("\n");
        printf("��Ӧ����");//�����Ӧ����
        for(j=pos;j<RN;j++)
            printf("%4d",rq[j].track);
        for(j=pos-1;j>=0;j--)
            printf("%4d",rq[j].track);
    }
    else
    {
        if(s==rq[0].track||s==rq[RN-1].track)//�����պ��������˵�λ��ʱ��
            meanD=rq[RN-1].track-rq[0].track;
        else
            meanD=rq[RN-1].track+s-2*rq[0].track;
        printf("\n");
        printf("��Ӧ����");//�����Ӧ����
        for(j=pos-1;j>=0;j--)
            printf("%4d",rq[j].track);
        for(j=pos;j<RN;j++)
            printf("%4d",rq[j].track);
    }
    printf("\n\n");
    meanD=meanD/RN;
    printf("ƽ��Ѱ�����ȣ�%6.1f\n",meanD);
    printf("==============================\n");
}

void CSCAN(diskreq* rq0,int s)
{
    int i,j,d,pos;
    diskreq* rq;
    rq=(diskreq*)malloc(RN*sizeof(diskreq));
    //��ΪҪ�Է������������������ٽ���һ������
    for(i=0;i<RN;i++)//���Ʒ�������
        rq[i]=rq0[i];
    sort(rq);//��������
    i=0;
    while(s>rq[i].track)i++;//�ҵ�s��λ��
    pos=i;
    printf(" 1 ��ʾ��ͷ��ŵ������ӷ����ƶ�\n");
    printf(" 2 ��ʾ��ͷ��ŵ��ż��ٷ����ƶ�\n\n");
    printf("�������ͷ�ƶ�����d: ");
    while(1)
    {
       scanf("%d",&d);
       if(!(d==1||d==2))
       {
          printf("����������������룺");
          continue;
       }
       break;
    }
    if(d==1)
    {
        if(s==rq[0].track||s==rq[RN-1].track)//�����պ��������˵�λ��ʱ��
            meanD=rq[RN-1].track-rq[0].track;
        else
            meanD=2*(rq[RN-1].track-rq[0].track)-(s-rq[pos-1].track);
        printf("\n");
        printf("��Ӧ����");//�����Ӧ����
        for(j=pos;j<RN;j++)
            printf("%4d",rq[j].track);
        for(j=0;j<pos;j++)
            printf("%4d",rq[j].track);
    }
    else
    {
        if(s==rq[0].track||s==rq[RN-1].track)//�����պ��������˵�λ��ʱ��
            meanD=rq[RN-1].track-rq[0].track;
        else
            meanD=2*(rq[RN-1].track-rq[0].track)-(rq[pos].track-s);
        printf("\n");
        printf("��Ӧ����");//�����Ӧ����
        for(j=pos-1;j>=0;j--)
            printf("%4d",rq[j].track);
        for(j=RN-1;j>=pos;j--)
            printf("%4d",rq[j].track);
    }
    printf("\n\n");
    meanD=meanD/RN;
    printf("ƽ��Ѱ�����ȣ�%6.1f\n",meanD);
    printf("==============================\n");
}

