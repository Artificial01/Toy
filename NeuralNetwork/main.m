clc;
clear all;

load traindata.txt;
load testdata.txt;

mindata=min(traindata);
maxdata=max(traindata);
for k=1:4
  traindata(:,k)=(traindata(:,k)-mindata(1,k))/(maxdata(1,k)-mindata(1,k));
  testdata(:,k)=(testdata(:,k)-mindata(1,k))/(maxdata(1,k)-mindata(1,k));
end

L1=zeros(4,1);
W1=2*rand(10,4)-1;
L2=zeros(10,1);
W2=2*rand(3,10)-1;
L3=zeros(3,1);

alpha=0.005;
D=zeros(3,1);
detal1=zeros(3,1);
detal2=zeros(10,1);
for k=1:20000
  m=ceil(75*rand());
  for l=1:4
    L1(l,1)=traindata(m,l);
  end
  L2=activation(W1*L1);
  L3=softmax(W2*L2);
  for l=1:3
    D(l,1)=(traindata(m,5)==(l-1));
  end
  detal1=L3-D;
  detal2=guideactivation(L2).*(transpose(W2)*detal1);
  W1=W1-alpha*detal2*transpose(L1);
  W2=W2-alpha*detal1*transpose(L2);
end

rightcount=0;
for k=1:75
  for l=1:4
    L1(l,1)=testdata(k,l);
  end
  L2=activation(W1*L1);
  L3=softmax(W2*L2);
  [maxvalue,result]=max(L3);
  rightcount=rightcount+(testdata(k,5)==(result-1));
end
rightrate=rightcount/75
