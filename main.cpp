#include<bits/stdc++.h>
int main()
{
    double n,t;
    std::cin>>n>>t;
    double base = 4000;
    double ans = 0;
    if(n>=6)
    {
        if(t>=3.5) ans = std::max(ans,(n-2)/2*200*20*1.4);
        else if(t>=3) ans = std::max(ans,(n-2)/2*200*20*1.2);
        else if(t>=2.5) ans = std::max(ans,(n-2)/2*200*20.0);
    }
    if(n>=4)
    {
        if(t>=3) ans = std::max(ans,1100.0);
        else if(t>=2.5) ans = std::max(ans,900.0);
        else if(t>=2) ans = std::max(ans,700.0);
    }
    if(n>=3)
    {
        if(t>=3) ans = std::max(ans,500.0);
        else if(t>=2.5) ans = std::max(ans,400.0);
        else if(t>=2) ans = std::max(ans,300.0);
    }
    if(n>=2&&t>=2.5) ans = std::max(ans,200.0);
    std::cout<<std::fixed<<std::setprecision(2)<<ans+base<<'\n';
    return 0;
}