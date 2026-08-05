#include<stdio.h>

int main (){
	int t,n,m,k;
	scanf("%d", &t);
	while(t>0){
		scanf("%d%d%d", &n, &m, &k);
		int rb[n];
		int esp[m];
		
		for (int x=0;x<n;x++)
			scanf("%d", &rb[x]);
			
		for (int x=0;x<m;x++)
			scanf("%d", &esp[x]);
		int rb_vivo = n;
		for(int i=0; i<k;i++){
			char mov;
			scanf(" %c", &mov);
			if (rb_vivo>0){
				if (mov == 'L') //-1
				{
					for(int x=0;x<n;x++)
					{
						rb[x] = rb[x]--;
						for(int y=0; y<m;y++)
							if(rb[x] == esp[y])
								rb_vivo--;
					}
						
				
				}
				else //+1
				{
					for(int x=0;x<n;x++)
					{
						rb[x] = rb[x]++;
						for(int y=0; y<m;y++)
							if(rb[x] == esp[y])
								rb_vivo--;
					}
				}	
			}			
			printf("%d ", rb_vivo);
		}		
		t--;
	}
	
}
