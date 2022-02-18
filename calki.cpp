#include <iostream>
#include <math.h>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <ctime>

double give_value(){
    double x;
    while (true){
    std::cin>>x;
    if (std::cin.fail()){
        std::cout<<"wrong value, try again\n";
        std::cin.clear();
        std::cin.ignore();
    } else break;
    }  
    return x;
}

std::pair<double,double> values(std::tuple<double,double,double,double,double> t, double rmin, double rmax){
double vmin,vmax;
vmin=std::get<0>(t)*rmin*rmin*rmin*rmin+std::get<1>(t)*rmin*rmin*rmin+std::get<2>(t)*rmin*rmin+std::get<3>(t)*rmin+std::get<4>(t);
vmax=vmin;
for (double i=rmin;i<rmax+0.001;i+=0.001){
    if(vmin>std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t)) vmin=std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t);
    if(vmax<std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t)) vmax=std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t);
}
    return std::make_pair(vmin,vmax);
}

double rectangle(std::tuple<double,double,double,double,double> t, double rmin, double rmax){
double result=0;
for (double i=rmin+0.0005;i<rmax+0.001;i+=0.001){
result += (std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t))*0.001;
}
return result;
}

double trapezium(std::tuple<double,double,double,double,double> t, double rmin, double rmax){
double result=0;
for (double i=rmin;i<rmax;i+=0.001){
result += ((std::get<0>(t)*i*i*i*i+std::get<1>(t)*i*i*i+std::get<2>(t)*i*i+std::get<3>(t)*i+std::get<4>(t))+(std::get<0>(t)*(i+0.001)*(i+0.001)*(i+0.001)*(i+0.001)+std::get<1>(t)*(i+0.001)*(i+0.001)*(i+0.001)+std::get<2>(t)*(i+0.001)*(i+0.001)+std::get<3>(t)*(i+0.001)+std::get<4>(t)))*0.0005;
}
return result;
}

double analysis(std::tuple<double,double,double,double,double> t, double rmin, double rmax){
double ap, bp, cp, dp, ep;
ap=std::get<0>(t)/5;
bp=std::get<1>(t)/4;
cp=std::get<2>(t)/3;
dp=std::get<3>(t)/2;
ep=std::get<4>(t);
double result = (ap*rmax*rmax*rmax*rmax*rmax+bp*rmax*rmax*rmax*rmax+cp*rmax*rmax*rmax+dp*rmax*rmax+ep*rmax)-(ap*rmin*rmin*rmin*rmin*rmin+bp*rmin*rmin*rmin*rmin+cp*rmin*rmin*rmin+dp*rmin*rmin+ep*rmin);
return result;
}

double monte_carlo(std::tuple<double,double,double,double,double> t, double rmin, double rmax, std::pair<double,double> p){
double x,y,r,result;
for (int i=0;i<10000000;i++){
    x=((double)std::rand()/RAND_MAX)*(rmax-rmin)+rmin;
    y=((double)std::rand()/RAND_MAX)*(p.second-p.first)+p.first;
    if((y<(std::get<0>(t)*x*x*x*x+std::get<1>(t)*x*x*x+std::get<2>(t)*x*x+std::get<3>(t)*x+std::get<4>(t)))&&y>0) r++;
    if((y>(std::get<0>(t)*x*x*x*x+std::get<1>(t)*x*x*x+std::get<2>(t)*x*x+std::get<3>(t)*x+std::get<4>(t)))&&y<0) r--;
}
result = (r/10000000)*((p.second-p.first)*(rmax-rmin));
if (p.first>0) result += (rmax-rmin)*p.first;
if (p.second<0) result += (rmax-rmin)*p.second;
return result;
}

std::tuple<double,double,double,double,double> inputs(){
    double a,b,c,d,e;
    std::cout<<"Enter a:\n";
    a=give_value();
    std::cout<<"Enter b:\n";
    b=give_value();
    std::cout<<"Enter c:\n";
    c=give_value();
    std::cout<<"Enter d:\n";
    d=give_value();
    std::cout<<"Enter e:\n";
    e=give_value();
    return std::make_tuple(a,b,c,d,e);
}

int main(){

srand(time(NULL));

std::cout<<"The form of function is: y=a*x^4+b*x^3+c*x^2+d*x+e \n";
auto input = inputs();

bool cal=true;

double rmin,rmax;
std::cout<<"Enter the x range. Available is -10:10 \n";
std::cout<<"Enter x min \n";
while (true){
    rmin=give_value();
    if (rmin<-10||rmin>10){
        std::cout<<"wrong value, try again\n";
    }else break;
}
std::cout<<"Enter x max \n";
while (true){
    rmax=give_value();
    if (rmax<-10||rmax>10){
        std::cout<<"wrong value, try again\n";
    }else break;
}

if(rmin==rmax){
    cal=false;
    std::cout<<"x-min=x-max, result=0.";
}else if (rmin>rmax){
    double rch=rmin;
    rmin=rmax;
    rmax=rch;
    std::cout<<"x-min > x-max, values changed.\n";
}

if (cal){

    auto mima = values(input,rmin,rmax);
    std::cout<<"min. value: "<<mima.first<<std::endl;
    std::cout<<"max. value: "<<mima.second<<std::endl;
    double a=analysis(input,rmin,rmax);
    std::cout<<"Analysis - exact value: "<<a<<std::endl;
    double r=rectangle(input,rmin,rmax);
    std::cout<<"Rectangle - 1 step=0.001: "<<r<<"  difference: "<<100*(r-a)/a<<"%"<<std::endl;
    double t=trapezium(input,rmin,rmax);
    std::cout<<"Trapezium - 1 step=0.001: "<<t<<"  difference: "<<100*(t-a)/a<<"%"<<std::endl;
    double m=monte_carlo(input,rmin,rmax,mima);
    std::cout<<"Monte Carlo 1*10^7 points: "<<m<<"  difference: "<<100*(m-a)/a<<"%"<<std::endl;
   
}

    return 0;
}