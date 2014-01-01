//#define lgg
#include <cstdio>
#include <algorithm>
#define mod 100000000
using namespace std;
char a[5002], b[5002];
int sa, sb, f[5001][5001];
unsigned long g[5001][5001];

void read(); void dp();
#ifdef lgg
void show();
#endif
 
int main()
{
	freopen("lcs.in", "r", stdin); freopen("lcs.out", "w", stdout);
	read();
	dp();
	#ifdef lgg
	show();
	#endif
	printf("%d\n%lu\n", f[sa][sb], g[sa][sb]);
	return 0;
}
inline void read()
{
	char t;
	while(!((t=getchar())>='A' && t<='Z'));
	a[1]=t; sa=1;
	while((t=getchar())!='.')a[++sa]=t;
	while(!((t=getchar())>='A' && t<='Z'));
	b[1]=t; sb=1;
	while((t=getchar())!='.')b[++sb]=t;
	return;
}
inline void dp()
{
	for(int i(0); i<=sa; ++i)
		g[i][0]=1;
	for(int i(0); i<=sb; ++i)
		g[0][i]=1;
	for(int i(1); i<=sa; ++i)
		for(int j(1); j<=sb; ++j)
		{
			if(a[i]==b[j])
			{
				f[i][j]=f[i-1][j-1]+1;
				//if(i==1 || j==1)continue;
				if(f[i][j-1]==f[i][j])g[i][j]+=g[i][j-1];
				if(f[i-1][j]==f[i][j])g[i][j]+=g[i-1][j];
				g[i][j]+=g[i-1][j-1];
			}
			else
			{
				f[i][j]=max(f[i-1][j], f[i][j-1]);
				//if(i==1 || j==1)continue;
				g[i][j]=mod;
				if(f[i][j-1]==f[i][j])g[i][j]+=g[i][j-1];
				if(f[i-1][j]==f[i][j])g[i][j]+=g[i-1][j];
				if(f[i-1][j-1]==f[i][j])g[i][j]-=g[i-1][j-1];
			}
			g[i][j]%=mod;
		}
	return;
}
#ifdef lgg
inline void show()
{
	printf("    ");
	for(int i(1); i<=sb; ++i)
		printf(" %c  ", b[i]);
	putchar('\n');
	printf("    ");
	for(int i(1); i<=sb; ++i)
		printf(" %d  ", i);
	putchar('\n');
	for(int i(1); i<=sa; ++i)
	{
		printf("%c %d ", a[i], i);
		for(int j(1); j<=sb; ++j)
			printf("%d,%lu ", f[i][j], g[i][j]);
		putchar('\n');
	}
	putchar('\n');
	return;
}
#endif
/*
情况分析：
①a[i]==b[j]
	首先，一定有f[i-1][j-1]部分，即在原来所有的a[i-1]，b[j-1]部分上的每个lcs都可以加上a[i]与
	b[j]构成更长的一个lcs。
	其次，如果f[i-1][j]==f[i][j]，说明a[i]的加入并没有显著地给lcs长度带来了什么增加，
	所以关于g[i][j]一定含有g[i-1][j]的部分，即在a[i-1]与b[j]之间的lcs个数。并且，这些部分没有
	和上一步中提到的每个末尾加上共同字符的方案相重叠的部分。
	同理，如果f[i][j-1]==f[i][j]则一定含有不与上述两个情况相重合的部分，有g[i][j-1]个。
②a[i]!=b[j]
	可以发现，a[i]与b[j]没有什么共同的关系。
	首先，如果f[i-1][j]==f[i][j]说明g[i][j]一定含有g[i-1][j]的部分。
	其次，如果f[i][j-1]==f[i][j]说明g[i][j]一定含有g[i][j-1]的部分。
	但是如果f[i-1][j-1]==f[i][j]表明，上两次计算一定计算了共同的部分g[i-1][j-1]，所以要减去。
	另外注意由于%操作，如果是负数（即只是操作了f[i-1][j-1]==f[i][j]的情况）会出错，所以建议
	先加上mod的值。
③关于边界条件的讨论
	知道，如果a序列或者b序列只要有一个为空，则lcs只能为空集，并且数量为一个，所以
	g[i][0]，g[0][j]都为1。
*/
