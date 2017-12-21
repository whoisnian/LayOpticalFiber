#include<queue>
#include<cstring>
#include<cstdio>
int teachernum,coursenum;//��ʦ���������γ̵����� 
int graph[105][105];//����ͼ���ڽӾ���洢 
int teacher_result[105],course_result[105];//�洢ƥ���� 
int visited[105];
int teacher_dis[105],course_dis[105];//�洢����·�ľ��� 
int mindis;
bool searchpath()//������ true,��ʾ�����������·���� 
{
	std::queue<int>q;//ʹ��stl�ڵĶ��� 
	while(!q.empty())q.pop();//��� 
	memset(teacher_dis,-1,sizeof(teacher_dis));//��ʼ�� 
	memset(course_dis,-1,sizeof(course_dis));
	mindis=99999;//�൱�������
	int i;
	for(i=0;i<teachernum;i++)//���л�û�п��ϵ���ʦ��� 
	if(teacher_result[i]==-1)
	{
		q.push(i);
		teacher_dis[i]=0;
	}
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		if(teacher_dis[now]>mindis)break;//·�����ȴ����Ѿ��ҵ����������·�����ȣ��˳� 
		for(i=0;i<coursenum;i++)
		{
			if(graph[now][i]&&course_dis[i]==-1)//������ڱ�
			{
				course_dis[i]=teacher_dis[now]+1;//���¸ÿγ�������·���ϵľ��� 
				if(course_result[i]==-1)
					mindis=course_dis[i];//��������·������¼�������·������ 
				else
				{
					teacher_dis[course_result[i]]=course_dis[i]+1;//���¾��룬����Ѱ�� 
					q.push(course_result[i]);
				}
			}
		}
	}
	if(mindis!=99999)return true;
	else return false;
}
int findpath(int now)
{
	int i;
	for(i=0;i<coursenum;i++)
	{
		if(!visited[i]&&graph[now][i]&&course_dis[i]==teacher_dis[now]+1)//���ÿγ�δ�����ҷ��Ͼ����ϵ��������� 
		{
			visited[i]=1;
			if(course_result[i]!=-1&&course_dis[i]==mindis)continue;//���ÿγ�������ʦ�����Ѵﵽ����������ĳ��ȣ������ÿγ� 
			if(course_result[i]==-1||findpath(course_result[i]))//���ÿγ�û����ʦ�ϻ����ҵ����������·������¼ƥ���� 
			{
				course_result[i]=now;
				teacher_result[now]=i;
				return true;
			}
		}
	}
	return false;
}
int maxmatch()//�����������㷨������ֵΪ���ƥ���� 
{
	int i,maxmatchnum=0;
	memset(teacher_result,-1,sizeof(teacher_result));//��ʼ�� 
	memset(course_result,-1,sizeof(course_result));
	while(searchpath())//����������· 
	{
		memset(visited,0,sizeof(visited));//��շ��ʱ�� 
		for(i=0;i<teachernum;i++)//����ÿ����ʦ�����û�пΣ�������һ�� 
		if(teacher_result[i]==-1)
			maxmatchnum+=findpath(i);//���ɹ�ƥ�䣬�𰸼�һ 
	}
	return maxmatchnum;
}
int main()
{
	int tt,i,j,s,t;
	scanf("%d",&tt);
	while(tt--)
	{
		scanf("%d %d",&teachernum,&coursenum);
		memset(graph,0,sizeof(graph));
		for(i=0;i<teachernum;i++)
		{
			scanf("%d",&s);
			for(j=0;j<s;j++)
			{
				scanf("%d",&t);
				graph[i][t-1]=1;
			}
		}
		printf("%d\n",maxmatch());
	}
	return 0;
}
