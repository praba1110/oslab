#include <bits/stdc++.h>
using namespace std;
struct process{
	int bt,tt,burst;
};
int main(){
	int n;
	int totalburst = 0;
	cout<<" Enter number of processes: ";
	cin>>n;
	cout<<"Enter burst timefor each process"<<endl;
	vector<process> ps(n);
	for(int i=0;i<ps.size();i++){
		cin>>ps[i].bt;
		ps[i].burst = ps[i].bt;
		totalburst += ps[i].bt;
	}
	int tslice;
	cout<<"Total burst time "<<totalburst<<endl;
	cout<<"Enter Time slice:";
	cin>>tslice;
	vector<int> ans;
	int size = 0;
	int j = -1;
	int i = 0;
	while(totalburst!=0){
		while(true){
			j = (j+1)%n;
			if(ps[j].bt!=0)
				break;		
		}
		for(int k = 0;k<tslice&&ps[j].bt!=0;k++){
			ans.push_back(j+1);
			i++;
			ps[j].bt -= 1;
			totalburst--;
		}
		if(ps[j].bt == 0)
			ps[j].tt = i;
	}
	cout<<"0 -> ";
	for(int i=1;i<ans.size();i++){
		while(ans[i]==ans[i-1])
			i++;
		cout<<"P"<<ans[i-1]<<" -> "<<i<<" -> ";
	}
	cout<<"ends"<<endl;
	int avgwait = 0, avgtt = 0;
	cout<<" id   waiting time   burst time  turnaround time"<<endl;;
	for(int i=0;i<ps.size();i++){
		cout<<i+1<<"        "<<ps[i].tt - ps[i].burst<<"              "<<ps[i].burst<<"               "<<ps[i].tt<<endl;
		avgtt += ps[i].tt;
		avgwait += ps[i].tt - ps[i].burst;
	}
	cout<<"avg waiting time "<<avgwait/n<<endl;
	cout<<"avg turnaround time "<<avgtt/n<<endl;
	return 0;
}
