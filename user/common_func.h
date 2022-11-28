#ifndef COMMON_FUNC

#define For(i,a,b) for(int i=a;i<b;i++)

#define COMMON_FUNC

int check_str_is_int(char* argv)
{
	char* node=argv;
	while(*node)
	{
		if(*node<='9'&&*node>='0')continue;
		if(*node=='-') continue;
		return 0;
	}
	return 1;
}

int check_has_substring(char *s,char *substring)
{
	// base on kmp
	// https://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
	int len1 = strlen(substring),len2 = strlen(s);
	int pre[len1+1];
	For(i,0,len1) pre[i]=0;
	pre[0]=-1;
	int node=pre[0];
	For(i,1,len1)
	{
		while(~node && substring[i] != substring[node+1])
			node=pre[node];
		// build pre array
		node+=(substring[i]==substring[node+1]);
		pre[i]=node;
	}

	node=-1;
	For(i,0,len2)
	{
		while(~node && substring[node+1]!=s[i])
			node=pre[node];
		if(substring[node+1]==s[i])
			node+=1;
		if(node == len1-1)
		{
			return 1;
		}
	}

	return 0;

}

#endif
