/* Name: Madhusudan Pranav Venugopal
netid: mxv130430
UTD Id : 2021163441
pcn programming assignment 1
*/

#include <iostream>
#include <math.h>

using namespace std;
struct event
{
  int type;
  double time;
}e1,e2,e3,r;
double a1=0,a2=0,b1=0,b2=0,Ndep=0,clock1=0,prev=0,EN=0;
int N=0,k,l,m,done=0;
double lamda1,lamda2,mu,rho;
double seed=1111;
double uni_rv()           
{
  double k = 16807.0;
  double m = 2.147483647e9;
  double rv;

  seed=fmod((k*seed),m);
  rv=seed/m;
  return(rv);
}

double exp_rv(double lambda)
{
  double exp;
  exp = ((-1) / lambda) * log(uni_rv());
  return(exp);
}

class eventlist
{
  event *e;
  int front1;
  int rear1;
public:
  eventlist()
  {
    front1=0;
    rear1=-1;
    e= new event[200000];
        
  }
  void push(event e1)
  {rear1++;
    e[rear1]=e1;
  }
  event pop()
  {
    event r1;
    r1=e[front1];
    front1++;
    return r1;
  }
}q1;

int main()
{
  cout<<"enter the value of k";
  cin>>k;
  cout<<"enter the value of m";
  cin>>m;
  cout<<"enter the value of rho";
  cin>>rho;
  cout<<"enter the value of lamda2";
  cin>>lamda2;
  cout<<"enter the value of mu";
  cin>>mu;
  cout<<"enter the value of l";
  cin>>l;
  lamda1=rho*mu*m;
    
  e1.type=0;
  e2.type=1;
  e3.type=2;
     
  e1.time=exp_rv(lamda1);
  // N++;
  e2.time=exp_rv(lamda2);
  //N++;
  q1.push(e1);
  a1++;
  q1.push(e2);
  a2++;
  while(done==0)
    {
      r=q1.pop();
      prev=clock1;
      clock1=r.time;
      switch(r.type)
        {
        case 0:
	  {
	    EN+=N*(clock1-prev);
	    if(N<k)
	      {
		N++;
		a1++;
		e1.time=clock1+exp_rv(lamda1);
		q1.push(e1);
                    
	      }
	     if(N<=m&&N>0)
	      {
		e3.time=clock1+exp_rv(mu);
		q1.push(e3);
                    
	      }
	     if(N>=k)
	       {
		b1++;
		e1.time=clock1+exp_rv(lamda1);
		q1.push(e1);
		a1++;
	      }
	    break;
	  }
        
        case 1:
	  {
	    EN+=N*(clock1-prev);
	    if(N<l)
	      {
		N++;
		e2.time=clock1+exp_rv(lamda2);
		q1.push(e2);
		a2++;
                    
	      }
	     if(N<=m&&N>0)
	      {
		e3.time=clock1+exp_rv(mu);
		q1.push(e3);
	      }
	     if(N>=l)
	      {
		b2++;
		e2.time=clock1+exp_rv(lamda2);
		q1.push(e2);
		a2++;
	      }
	    break;
	  }
        case 2:
	  {
	    EN+=N*(clock1-prev);
	    if(N>0)
	      {
		N--;
		Ndep++;
                    
	      }
	    if(N>=m)
	      {N--;
		e3.time=clock1+exp_rv(mu);
		q1.push(e3);
                    
	      }
	    if(N==0)
	      {
		N++;
		
		e1.time=clock1+exp_rv(lamda1);
		e2.time=clock1+exp_rv(lamda2);
		a1++;
		a2++;   
	      }
	    break;
	  }
	}
      if(Ndep>100000)
        done=1;
    
    }
  cout<<endl<<"expected num of customers:"<<EN/clock1;
  cout<<endl<<"expected wait time:"<<EN/(a1+a2);
  cout<<endl<<"probability of user job being blocked:"<<(double)(b2/(a2));
  cout<<endl<<"probability of admin jobs are being blocked :"<<(long double)(b1/(a1));
  return 0;
}
